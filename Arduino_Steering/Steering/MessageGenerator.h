#ifndef MessageGenerator_h
#define MessageGenerator_h

#include "Arduino.h"
#include "Message.h"
#include "Common.h"
class MessageGenerator
{
  public:
    MessageGenerator();
    ~MessageGenerator();
    
    Message* CreateReadPositionMessage(int Position);
    Message* CreateEngineSpeedMessage(int engineSpeed);
    Message* CreateEngineDirectionMessage(int engineDirection);
    Message* CreateSteeringStartMessage();
    
    
  private:
    Message *ReadPosition;
    Message *EngineSpeed;
    Message *EnigneDirection;
    Message *StartSteering;
    
    char Startbyte = 0x01;
    char Endbyte = 0xDE;
    
    /*PositionSteering*/
    char *steeringPosition;
    char *m_engineSpeed;
    char *m_engineDirection;
    char *fillByte;
    Common _common;

};


#endif
