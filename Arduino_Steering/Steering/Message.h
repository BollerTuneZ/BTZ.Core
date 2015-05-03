#ifndef Message_h
#define Message_h

#include "Arduino.h"

class Message
{
  public:
    Message();
    ~Message();
    //Message(char startbyte,unsigned char mLength,unsigned char type, char *data,char endbyte,char legal);
    char StartByte;
    char Length;
    unsigned char Type;
    char *Data;
    char EndByte;
    
    char isLegal;
};


#endif
