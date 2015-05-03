#ifndef SteeringState_h
#define SteeringState_h

#include "Arduino.h"


class SteeringState
{
  public:
    SteeringState();
   
   int Enabled; 
   
   int Direction;
   int RealPosition;
   int SteeringEncoderPosition;
   
   int LeftEnd;
   int RightEnd;
   
   int MaxRange;
   int Center;

   int InputType;
   
   
   int RemotePosition;
   
   int EndStopPullUp = HIGH;
    
   int SetupSpeed = 5;
   
   /*Steering invert*/
   int LeftOn = HIGH;
   int LeftOff = LOW;
   
   int RightOn = HIGH;
   int RightOff = LOW;
   
   int centerOffset = 0;
   
   int RemoteToReal();
   
   int CalculateSpeed(int diff);
   
};


#endif
