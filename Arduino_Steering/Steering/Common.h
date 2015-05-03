#ifndef Common_h
#define Common_h

#include "Arduino.h"

class Common
{
  public:
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
