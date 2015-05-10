#ifndef SteeringState_h
#define SteeringState_h

#include "Arduino.h"


class SteeringState
{
  public:
   char SetupState = 'N';
   char MotorSpeed = 0;
   char Running = 'N';
   char Enabled = 'N';
   
   char Direction = 'N';
   
   int RealPosition;
   int SteeringEncoderPosition;
   
   int RemotePosition;
   
   int centerOffset = 0;
};


#endif
