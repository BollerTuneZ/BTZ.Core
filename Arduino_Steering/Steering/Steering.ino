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
Encoder encoderMotor = Encoder(3,7);
Encoder encoderSteering = Encoder(2,4);
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
 //_debugLogAction.check();
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
        _state.Direction = _config.ConstDirLeft;
        SetDirection(_state.Direction);
        _state.MotorSpeed = 100;
        SetSteeringSpeed(_state.MotorSpeed);
         encoderMotor.write(0);
    }else if(_state.SetupState == 'X')
    {
     
      _state.Direction = 'N';
      _state.MotorSpeed = 0;
      SetDirection(_state.Direction);
      SetSteeringSpeed(_state.MotorSpeed);
    }else if(_state.SetupState == 'C')
    {
      _state.Direction = _config.ConstDirRight;
      _state.MotorSpeed = 100;
      SetDirection(_state.Direction);
      SetSteeringSpeed(_state.MotorSpeed);
      _state.RealPosition = encoderMotor.read();
    }else if(_state.SetupState == 'S')
    {
      _state.Direction = 'N';
      _state.MotorSpeed = 0;
      SetDirection(_state.Direction);
      SetSteeringSpeed(_state.MotorSpeed);
      _config.MaximalPosition = encoderMotor.read();
      _config.Center = (int)(_config.MaximalPosition /2 );
      _state.SetupState = 'R';
      Serial.println(_config.MaximalPosition);
      delay(2000);
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

void SetSteeringSpeed(char motorSpeed)
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
   Serial.println("Message received");
   if(updService->packetBuffer[1] == _config.T_SetupStep)
   {
       _state.SetupState = updService->packetBuffer[2];
   }else if(updService->packetBuffer[1] == _config.T_InputType)
   {
     _config.InputType = updService->packetBuffer[2];
   }else if(updService->packetBuffer[1] == _config.T_Steer)
   {
     _state.RemotePosition = (unsigned char)updService->packetBuffer[2];
     Serial.print("RemotePosition:");
     Serial.println(_state.RemotePosition);  
 }
}

unsigned char CalculateSpeed()
{
  int steeringPosition = encoderSteering.read();
  _state.RealPosition = encoderMotor.read();

  if(_config.InputType == 'R')
  {
    
     steeringPosition = map(_state.RemotePosition,0,255,0,_config.MaximalPosition); 
/*     Serial.print("CalculatedDiff:");
     
     Serial.println(steeringPosition);
       Serial.print("motorPosition");
  Serial.println(_state.RealPosition);
     */
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
  
  unsigned char cSpeed = (unsigned char)map(diff,0,_config.MaximalPosition,40,255);
  
  if(diff < 300)
  {
    _state.Direction = 'N';
    return 0x00;  
  }else
  {
    return cSpeed;
  }
}

void DebugLog()
{
  if(_state.SetupState == 'N')
  {return;}
    Serial.print("MotorSpeed = ");
    Serial.print(_state.MotorSpeed);  
    Serial.print("  Direction = ");
    Serial.println(_state.Direction);
   Serial.print("SetupState = ");
    Serial.println(_state.SetupState);
    Serial.print("MotorEncoder = ");
    Serial.println(_state.RealPosition);
}
