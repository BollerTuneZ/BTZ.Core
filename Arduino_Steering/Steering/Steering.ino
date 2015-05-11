#include <TimedAction.h>
#include <SPI.h>       
#include <Ethernet.h>
#include <EthernetUdp.h>
#include "SteeringBoard.h"
#include "UDPConnectionInfo.h"
#include "UdpService.h"
#include "UDPClient.h"
#include "MessageProcessor.h"
#include "Message.h"
#include "SteeringState.h"
#include "Config.h"


#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>
Encoder encoderMotor = Encoder(2,4);
Encoder encoderSteering = Encoder(3,7);
//TimedActions
TimedAction _messageReceiverAction = TimedAction(50,ReceiveMessages);
TimedAction _debugLogAction = TimedAction(100,DebugLog);
/*Ethernet Controller*/
UDPClient *client;
MessageProcessor *messageProcessor;
UdpService * updService;
UDPConnectionInfo *udpConnectionInfo;
/*Calculating Time*/
long lastTime = millis();
/*Steering*/
SteeringState _state;
Config _config;
SteeringBoard _steeringBoard;
int motorSpeed;
void setup() {
  Serial.begin(9600);
  pinMode(_steeringBoard.DirectionLeftPin,OUTPUT);
  pinMode(_steeringBoard.DirectionRightPin,OUTPUT);
  pinMode(_steeringBoard.PowerPin,OUTPUT);
  EthernetSetup();
}

void loop() {
 _messageReceiverAction.check();
 _debugLogAction.check();
 SteeringSetup();
 ProcessSteering();
}

void EthernetSetup()
{
    Serial.println("Initialisiere Ethernet Componenten");
    udpConnectionInfo = new UDPConnectionInfo();
    udpConnectionInfo->Initialize(192,168,2,177,8888); //IP und Port änderung muss beim BTZ Core bekannt sein
    updService = new UdpService();    
    updService->Init(udpConnectionInfo);       
    client = new UDPClient(192,168,2,100,9050); //Server Endpoint  
  Serial.println("Waiting for Commands...");
  
}

void SteeringSetup()
{
    if(_state.SetupState == 'Y')
    {
        SetDirection(_config.ConstDirLeft);
        SetSteeringSpeed(_config.SetupSpeed);
    }else if(_state.SetupState == 'X')
    {
      encoderMotor.write(0);
      SetDirection('N');
      SetSteeringSpeed(0);
    }else if(_state.SetupState == 'C')
    {
      SetDirection(_config.ConstDirRight);
      SetSteeringSpeed(_config.SetupSpeed);
      _state.RealPosition = encoderMotor.read();
    }else if(_state.SetupState == 'S')
    {
      SetDirection('N');
      SetSteeringSpeed(0);
      _config.MaximalPosition = encoderMotor.read();
      _config.Center = (int)(_config.MaximalPosition /2 );
      _state.SetupState = 'R';
    }
}

void ProcessSteering()
{
  if(_state.SetupState != 'R')
  {
    return;
  }
  _state.RealPosition = encoderMotor.read();
  
  motorSpeed = CalculateSpeed();
  
  SetDirection(_state.Direction);
  SetSteeringSpeed(motorSpeed);
}

void SetSteeringSpeed(int motorSpeed)
{
  analogWrite(_steeringBoard.PowerPin,motorSpeed);
}

void SetDirection(char sDirection)
{
  int h = HIGH;
  int l = LOW;   
  if(sDirection == 'L')
  {
      digitalWrite(_steeringBoard.DirectionLeftPin,h);
      digitalWrite(_steeringBoard.DirectionRightPin,l);
  }else if(sDirection == 'R')
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
  updService->GetBytes();
    //Serial.println("StartParsing");
   if(updService->packetBuffer[0] != _config.CommandChar)
   {
     return;
   }
   
   if(updService->packetBuffer[1] == _config.T_SetupStep)
   {
       _state.SetupState = updService->packetBuffer[2];
   }else if(updService->packetBuffer[1] == _config.T_InputType)
   {
     _config.InputType = updService->packetBuffer[2];
   }else if(updService->packetBuffer[1] == _config.T_Steer)
   {
     _state.RemotePosition = (int)(unsigned char)updService->packetBuffer[2];
   }
}

int CalculateSpeed()
{
  int steeringPosition = encoderSteering.read();
  
  if(_config.InputType == 'R')
  {
     steeringPosition = map(_state.RemotePosition,0,255,0,_config.MaximalPosition); 
  }
  
  int diff = _state.RealPosition - steeringPosition;
  
  if(diff < 0)
  {
    _state.Direction = _config.ConstDirRight;
  diff = diff *(-1);  
  }else if( diff == 0)
  {
    _state.Direction = 'N';
  }else 
  {
    _state.Direction = _config.ConstDirLeft;  
  }
  
  if(diff < 50)
  {
    return 0;  
  }
  
  return map(diff,0,_config.MaximalPosition,0,255);
}

void DebugLog()
{
    Serial.print("MotorSpeed = ");
    Serial.print(motorSpeed);  
    Serial.print("  Direction = ");
    Serial.println(_state.Direction);
   Serial.print("SetupState = ");
    Serial.println(_state.SetupState);
    Serial.print("MotorEncoder = ");
    Serial.println(_state.RealPosition);
}
