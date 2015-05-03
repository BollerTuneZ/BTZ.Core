#ifndef MessageGenerator_h
#define MessageGenerator_h

#include "Arduino.h"
#include "Message.h"

class MessageGenerator
{
  public:
    MessageGenerator();
    ~MessageGenerator();
    
    Message* CreateReadPositionMessage(int Position);
    Message* CreateEngineSpeedMessage(int engineSpeed);
    Message* CreateEngineDirectionMessage(int engineDirection);
    
    
  private:
    Message *ReadPosition;
    Message *EngineSpeed;
    Message *EnigneDirection;
    
    char Startbyte = 0x01;
    char Endbyte = 0xDE;
    
    /*PositionSteering*/
    char *steeringPosition;
    char *m_engineSpeed;
    char *m_engineDirection;
    
    char SetPositionType = 0x14;
    char ReadPositionType = 0x15;
    char SetInputTypeType = 0x16;
    char SetMaxPowerType = 0x17;
    
    char Engine_ReadDirection = 0x1E;
    char Engine_ReadSpeed = 0x1F;
    char Engine_SetDirection = 0x20;
    char Engine_SetSpeed = 0x21;
    
};


#endif
