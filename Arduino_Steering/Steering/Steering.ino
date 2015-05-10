#include <TimedAction.h>
#include <SPI.h>       
#include <Ethernet.h>
#include <EthernetUdp.h>
#include "Common.h"
#include "SteeringBoard.h"
#include "UDPConnectionInfo.h"
#include "UdpService.h"
#include "UDPClient.h"
#include "MessageProcessor.h"
#include "Message.h"
#include "SteeringState.h"
#include "MessageGenerator.h"
#include "Config.h"
#include "SteeringCalculator.h"
#include "SteeringMessageProcessor.h"

SteeringBoard _steeringBoard;
Common _common;
#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>
Encoder encoderMotor = Encoder(2,4);
Encoder encoderSteering = Encoder(3,7);
//TimedActions
TimedAction _messageReceiverAction = TimedAction(100,ReceiveMessages);
/*Ethernet Controller*/
UDPClient *client;
MessageProcessor *messageProcessor;
UdpService * updService;
UDPConnectionInfo *udpConnectionInfo;
Message *incommingMessage;
/*Message Processing*/
SteeringMessageProcessor _steeringMessageProcessor;
/*Steering*/
SteeringCalculator _steeringCalculator;
void setup() {
  Serial.begin(9600);
  pinMode(_steeringBoard.DirectionLeftPin,OUTPUT);
  pinMode(_steeringBoard.DirectionRightPin,OUTPUT);
  pinMode(_steeringBoard.PowerPin,OUTPUT);
  EthernetSetup();
}

void loop() {
 _messageReceiverAction.check();
 if(_steeringMessageProcessor.GetSetupState() != 'N')
 {
     SteeringSetup();
 }
 ProcessSteering();
}

void EthernetSetup()
{
    Serial.println("Initialisiere Ethernet Componenten");
    udpConnectionInfo = new UDPConnectionInfo();
    udpConnectionInfo->Initialize(192,168,2,177,8888); //IP und Port änderung muss beim BTZ Core bekannt sein
    updService = new UdpService();    
    updService->Init(udpConnectionInfo);    
    messageProcessor = new MessageProcessor(updService);    
    client = new UDPClient(192,168,2,100,9050); //Server Endpoint  
  /*  
  Jede Message enthaelt das Attribut 'isLegal' welches angibt ob die Message 
  den vorschriften entspricht oder nicht. Vorher pruefen sonst koennte es gewaltig knallen!
  */
  Serial.println("Waiting for Commands...");
  _steeringMessageProcessor.Initialize(messageProcessor,client);
  
}

void SteeringSetup()
{
  Serial.print("SetUpState:");
  Serial.println(_steeringMessageProcessor.GetSetupState());
  
    if(_steeringMessageProcessor.GetSetupState() == 'L')
    {
      
      if(_steeringMessageProcessor.GetInvertState() == 'X')
      {
        _steeringMessageProcessor.SetDirection(_steeringMessageProcessor.GetDirRight());        
      }else
      {
        _steeringMessageProcessor.SetDirection(_steeringMessageProcessor.GetDirLeft());
      }
      _steeringMessageProcessor.SetMotorSpeed(_steeringMessageProcessor.GetSetupSpeed());
       SetDirection();
       SetSteeringSpeed();
    }else
    if(_steeringMessageProcessor.GetSetupState() == 'C')
    {
      encoderMotor.write(0);  
      _steeringMessageProcessor.SetSetupState('E');
    }else
    if(_steeringMessageProcessor.GetSetupState() == 'E')
    {
      _steeringMessageProcessor.SetCurrentPosition((int)encoderMotor.read()); 
     
      if(_steeringMessageProcessor.GetInvertState() == 'X')
      {
        _steeringMessageProcessor.SetDirection(_steeringMessageProcessor.GetDirLeft());        
      }else
      {
        _steeringMessageProcessor.SetDirection(_steeringMessageProcessor.GetDirRight());
      }
      _steeringMessageProcessor.SetMotorSpeed(_steeringMessageProcessor.GetSetupSpeed());
       SetDirection();
       SetSteeringSpeed();
      
    }if(_steeringMessageProcessor.GetSetupState() == 'F')
    {
      int maxi = _steeringMessageProcessor.GetCurrentPosition();
      _steeringMessageProcessor.SetMaxPosition(maxi);
      _steeringMessageProcessor.SetCenterPosition((int)(maxi / 2));
      _steeringMessageProcessor.SetSetupState('N');
    }
}

void ProcessSteering()
{
  if(_steeringMessageProcessor.IsEnabled() != 'Y')
  {
    return;
  }
    //Position von beiden Encodern abfragen
     _steeringMessageProcessor.SetCurrentPosition((int)encoderMotor.read());  
     _steeringMessageProcessor.SetCurrentSteeringPosition((int)encoderSteering.read());
    
    if(_steeringMessageProcessor.GetInputType() == 'N')
    {
      _steeringMessageProcessor.SetDirection('N');
      _steeringMessageProcessor.SetMotorSpeed(0);
      SetDirection();
      SetSteeringSpeed();
      return;
    } 
    //TODO Wert ob Remote oder nicht
    char *values = _steeringCalculator.CalculateSpeed(_steeringMessageProcessor.GetSteeringPosition(),
    _steeringMessageProcessor.GetCurrentPosition(),
    _steeringMessageProcessor.GetRemotePosition(),
    _steeringMessageProcessor.GetInputType(),
    _steeringMessageProcessor.GetDirLeft(),
    _steeringMessageProcessor.GetDirRight(),
    _steeringMessageProcessor.GetInvertState(),
    _steeringMessageProcessor.GetMaxPosition(),
    _steeringMessageProcessor.GetMinSpeed(),
    _steeringMessageProcessor.GetMaxSpeed());
    
    _steeringMessageProcessor.SetDirection(values[0]);
    _steeringMessageProcessor.SetMotorSpeed(values[1]);
    
    SetDirection();
    SetSteeringSpeed();
}

void SetSteeringSpeed()
{
  
  
  digitalWrite(_steeringBoard.PowerPin,_steeringMessageProcessor.GetMotorSpeed());
}

void SetDirection()
{
  int h = HIGH;
  int l = LOW;
  
  
  if(_steeringMessageProcessor.GetDirection() == 'L')
  {
      digitalWrite(_steeringBoard.DirectionLeftPin,h);
      digitalWrite(_steeringBoard.DirectionRightPin,l);
  }else if(_steeringMessageProcessor.GetDirection() == 'R')
  {
     digitalWrite(_steeringBoard.DirectionLeftPin,l);
     digitalWrite(_steeringBoard.DirectionRightPin,h);
  }else 
  {
     digitalWrite(_steeringBoard.DirectionLeftPin,l);
     digitalWrite(_steeringBoard.DirectionRightPin,l);
  }
}

void ReceiveMessages()
{
  //Kommunikation mit dem Core Server
  _steeringMessageProcessor.ProcessMessages();
}
