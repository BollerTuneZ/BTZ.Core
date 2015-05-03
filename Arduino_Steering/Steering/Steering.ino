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
MessageGenerator _messageGenerator;

/*Steering*/
SteeringState _state;
void setup() {
  Serial.begin(9600);
  pinMode(_steeringBoard.DirectionLeftPin,OUTPUT);
  pinMode(_steeringBoard.DirectionRightPin,OUTPUT);
  pinMode(_steeringBoard.PowerPin,OUTPUT);
  EthernetSetup();
  //SteeringSetup();
}

void loop() {
 _messageReceiverAction.check();
 //ProcessSteering();
  /*
  pinMode(_steeringBoard.EndStopLeft,INPUT);
  pinMode(_steeringBoard.EndStopRight,INPUT);*/
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
  Every Message got an attribute 'isLegal', check it befor using the Message!
  
  Jede Message enthaelt das Attribut 'isLegal' welches angibt ob die Message 
  den vorschriften entspricht oder nicht. Vorher pruefen sonst koennte es gewaltig knallen!
  */
  Serial.println("Warte auf startsignal...");
  int keepRunning = 1;
  while(keepRunning == 1)
  {
    incommingMessage = messageProcessor->ReceiveMessage();
    if(incommingMessage->isLegal == 0x01)
    {  
      Serial.println("Message Received");
      if(incommingMessage->Type == 0x02)
      {
          Serial.println("Starte SteeringProcess");
          keepRunning = 0;
      }
    }
  }
}


void ProcessSteering()
{
    _state.RealPosition = (int)encoderMotor.read();
    _state.SteeringEncoderPosition = (int)encoderSteering.read();
    if(_state.Enabled != 1)
    {
      SetSteeringSpeed(0);
      SetDirection('O');
      return;
    }
    
    int diff = 0;
    int tempdirectionState = 0;
    if(_state.InputType == 1)
    {
        int calculatedValue = 0;
        if(_state.SteeringEncoderPosition > _state.MaxRange)
        {
          calculatedValue = _state.MaxRange;
        }else if(_state.SteeringEncoderPosition < 0)
        {
          calculatedValue = 0;
        }
        
        int tempDiff = _state.RealPosition - _state.SteeringEncoderPosition;
        
        if(tempDiff < 0)
        {
          diff = tempDiff * (-1);
          tempdirectionState = 1;
        }else
        {
          diff = tempDiff;
        }
    }else if(_state.InputType == 2)
    {
      int remotePosition = _state.RemoteToReal();
      int tempDiff = _state.RealPosition - remotePosition;
      
      if(tempDiff < 0)
      {
        diff = tempDiff * (-1);
        tempdirectionState = 1;
      }else
      {
        diff = tempDiff;
      }
    }
    
    if(tempdirectionState == 0)
    {
      SetDirection('L');
    }else
    {
      SetDirection('R');
    }
    SetSteeringSpeed(_state.CalculateSpeed(diff));
}

void SetSteeringSpeed(int value)
{
  if(value > 0)
  {
    Serial.print("MotorSpeed:");
    Serial.println(value);
  }
  digitalWrite(_steeringBoard.PowerPin,value);
}

void SteeringSetup()
{
    Serial.println("SteeringSetup gestartet");
    /*Zum Rechten Endtaster fahren und Position auf null setzen*/
    while(ReadEndStops()[1] == _state.EndStopPullUp)
    {
        SetDirection('R');
        analogWrite(_steeringBoard.PowerPin,_state.SetupSpeed);
    }
    //Position auf Null setzen und messen
    encoderMotor.write(0);
    
    while(ReadEndStops()[0] == _state.EndStopPullUp)
    {
        SetDirection('L');
        analogWrite(_steeringBoard.PowerPin,_state.SetupSpeed);
        _state.RealPosition = encoderMotor.read();
    }
    Serial.print("MaxRange ist.");
    Serial.print(_state.MaxRange);
    Serial.print(" Center ist:");
    Serial.println(_state.Center);
    _state.MaxRange = _state.RealPosition;
    _state.Center = (_state.RealPosition / 2) + _state.centerOffset;
}

void ReceiveMessages()
{
  incommingMessage = messageProcessor->ReceiveMessage();
    if(incommingMessage->isLegal == 0x01)
    {  
        if(incommingMessage->Type == _common.SetInputTypeType)
        {
            _state.InputType = (int)(unsigned char)incommingMessage->Data[0];
        }else if(incommingMessage->Type == _common.SetPositionType)
        {
          _state.RemotePosition = (int)(unsigned char)incommingMessage->Data[0];
        }else if(incommingMessage->Type == _common.ReadPositionType)
        {
          Message *readResponse = _messageGenerator.CreateReadPositionMessage(_state.RealPosition);
            messageProcessor->SendMessage(client,readResponse);
            Serial.print("Position wurde auf: ");
            Serial.println(_state.RemotePosition);
        }
    }
}

int* ReadEndStops()
{
  int *endStops = new int[2];
  
  endStops[0] = digitalRead(_steeringBoard.EndStopLeft);
  endStops[1] = digitalRead(_steeringBoard.EndStopRight);
  
  return endStops;
}

void SetDirection(char dir)
{
  if(dir == 'L')
  {
    _state.Direction = 1;
      digitalWrite(_steeringBoard.DirectionLeftPin,_state.LeftOn);
      digitalWrite(_steeringBoard.DirectionRightPin,_state.RightOff);
      Serial.print("Direction is set to:");
      Serial.println(dir);
  }else if(dir == 'R')
  {
    _state.Direction = 2;
     digitalWrite(_steeringBoard.DirectionLeftPin,_state.LeftOff);
     digitalWrite(_steeringBoard.DirectionRightPin,_state.RightOn);
     Serial.print("Direction is set to:");
     Serial.println(dir);
  }else 
  {
    _state.Direction = 0;
     digitalWrite(_steeringBoard.DirectionLeftPin,_state.LeftOff);
     digitalWrite(_steeringBoard.DirectionRightPin,_state.RightOff);
  }
  
}
