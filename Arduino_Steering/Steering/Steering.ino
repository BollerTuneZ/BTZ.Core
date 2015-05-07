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
/*Config*/
Config *_config;
Config test;
/*Steering*/
SteeringState *_state;
SteeringCalculator _steeringCalculator;
void setup() {
  Serial.begin(9600);
  pinMode(_steeringBoard.DirectionLeftPin,OUTPUT);
  pinMode(_steeringBoard.DirectionRightPin,OUTPUT);
  pinMode(_steeringBoard.PowerPin,OUTPUT);
  _config = new Config();
  _config->SetInputType('X');
  _state = new SteeringState();
  EthernetSetup();
  
}

void loop() {
 _messageReceiverAction.check();
 if(_state->_enterSetup != 'N')
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
    client = new UDPClient(192,168,2,101,9050); //Server Endpoint  
  /*  
  Jede Message enthaelt das Attribut 'isLegal' welches angibt ob die Message 
  den vorschriften entspricht oder nicht. Vorher pruefen sonst koennte es gewaltig knallen!
  */
  Serial.println("Waiting for Commands...");
  _steeringMessageProcessor.Initialize(_config,_state,messageProcessor,client);
  
}

void SteeringSetup()
{
    if(_state->_enterSetup == 'L')
    {
      if(_config->InvertDirection == 'X')
      {
         _state->Direction = _config->ConstDirRight;
      }else
      {
        _state->Direction = _config->ConstDirLeft;
      }
       _state->MotorSpeed = _config->SetupSpeed;
       SetDirection();
       SetSteeringSpeed();
    }else
    if(_state->_enterSetup == 'C')
    {
      encoderMotor.write(0);  
      _state->_enterSetup = 'E';
    }else
    if(_state->_enterSetup == 'E')
    {
      _state->RealPosition = (int)encoderMotor.read();  
    }if(_state->_enterSetup == 'F')
    {
      _config->MaximalPosition = _state->RealPosition;
      _config->Center = (int)(_config->MaximalPosition / 2);
      _state->_enterSetup = 'N';
    }
}

void ProcessSteering()
{
  if(_state->Enabled == 0)
  {
    return;
  }
    //Position von beiden Encodern abfragen
    _state->RealPosition = (int)encoderMotor.read();
    _state->SteeringEncoderPosition = (int)encoderSteering.read();
    
    if(*_config->InputType == 'N')
    {
      _state->Direction = 'N';
      _state->MotorSpeed = 0;
      SetDirection();
      SetSteeringSpeed();
      return;
    } 
    _steeringCalculator.CalculateSpeed();
    SetDirection();
    SetSteeringSpeed();
}

void SetSteeringSpeed()
{
  digitalWrite(_steeringBoard.PowerPin,_state->MotorSpeed);
}

void SetDirection()
{
  if(_state->Direction == 'L')
  {
      digitalWrite(_steeringBoard.DirectionLeftPin,_config->LeftOn);
      digitalWrite(_steeringBoard.DirectionRightPin,_config->RightOff);
  }else if(_state->Direction == 'R')
  {
     digitalWrite(_steeringBoard.DirectionLeftPin,_config->LeftOff);
     digitalWrite(_steeringBoard.DirectionRightPin,_config->RightOn);
  }else 
  {
     digitalWrite(_steeringBoard.DirectionLeftPin,_config->LeftOff);
     digitalWrite(_steeringBoard.DirectionRightPin,_config->RightOff);
  }
}

void ReceiveMessages()
{
  //Kommunikation mit dem Core Server
  _steeringMessageProcessor.ProcessMessages();
}
