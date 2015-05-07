#include "Arduino.h"
#include "MessageGenerator.h"


MessageGenerator::MessageGenerator()
{
  
}
MessageGenerator::~MessageGenerator()
{
  
}

Message* MessageGenerator::CreateMessage(char type,char *payload)
{
  _message = new Message();
  int payloadSize = sizeof(payload);
  
  for(int i=0;i< payloadSize;i++)
  {
    _message->Data[i] = payload[i];
  }
  _message->StartByte = Startbyte;
  _message->EndByte = Endbyte;
  _message->Type = type;
  _message->Length = sizeof(payload);
  
  return _message;
}
/*  String str;
    str=String(Position);
    str.toCharArray(steeringPosition,5);*/

