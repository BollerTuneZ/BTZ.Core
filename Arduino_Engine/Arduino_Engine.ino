#include <TimedAction.h>
#include <SPI.h>       
#include <Ethernet.h>
#include <EthernetUdp.h>
#include "EngineBoard.h"
#include "UDPConnectionInfo.h"
#include "UdpService.h"
#include "UDPClient.h"
#include "MessageProcessor.h"
#include "Message.h"
#include "Config.h"

Config _config;
EngineBoard _board;
/*Ethernet*/
Message incommingMessage;
MessageProcessor *messageProcessor;
UdpService * updService;
UDPConnectionInfo *udpConnectionInfo;
TimedAction messageReceiveAction = TimedAction(100,ProcessMessages);
TimedAction debugLogAction = TimedAction(100,DebugLog);
/*State*/
char _currentDirection = 'N';
char _currentSpeed = 0x00;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(_board.DirectionForPin,OUTPUT);
  pinMode(_board.DirectionBackPin,OUTPUT);
  pinMode(_board.PowerPin,OUTPUT);
  EthernetSetup();
}
void loop() {
  // put your main code here, to run repeatedly:
  messageReceiveAction.check();
  debugLogAction.check();
  SetDirection();
  SetMotorSpeed();
}
void EthernetSetup()
{
    Serial.println("Initialisiere Ethernet Componenten");
    udpConnectionInfo = new UDPConnectionInfo();
    udpConnectionInfo->Initialize(192,168,2,179,8887); //IP und Port änderung muss beim BTZ Core bekannt sein
    updService = new UdpService();    
    updService->Init(udpConnectionInfo);    
    messageProcessor = new MessageProcessor(updService);    
}

void ProcessMessages()
{
    incommingMessage = messageProcessor->ReceiveMessage();  
    if(incommingMessage.isLegal == 0x01)
    {   
      if(incommingMessage.Type == 'D')
      {
        Serial.println("OK");
         _currentDirection = incommingMessage.Data[0];
         _currentSpeed = (unsigned char)incommingMessage.Data[1];
      }
    }
}
void SetMotorSpeed()
{
  analogWrite(_board.PowerPin,_currentSpeed);
}
void SetDirection()
{
    if(_config.InvertDirection == 'X')
    {
        if(_currentDirection == 'F')
        {
          digitalWrite(_board.DirectionBackPin,HIGH);
         digitalWrite(_board.DirectionForPin,LOW);
        }else if(_currentDirection == 'B')
        {
           digitalWrite(_board.DirectionForPin,HIGH);
          digitalWrite(_board.DirectionBackPin,LOW);
        }
    }else
    {
      if(_currentDirection == 'F')
        {
         digitalWrite(_board.DirectionBackPin,LOW);
         digitalWrite(_board.DirectionForPin,HIGH);
        }else if(_currentDirection == 'B')
        {
          digitalWrite(_board.DirectionBackPin,HIGH);
          digitalWrite(_board.DirectionForPin,LOW);
        }
    }
}

void DebugLog()
{
  if(_currentDirection == 'N')
  {
    return;
  }
  Serial.print("Direction =");
  Serial.print(_currentDirection);
  Serial.print(" MotorSpeed =");
  Serial.println(_currentSpeed);
}
