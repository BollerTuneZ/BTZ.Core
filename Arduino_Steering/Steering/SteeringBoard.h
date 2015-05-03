#ifndef SteeringBoard_h
#define SteeringBoard_h

#include "Arduino.h"

class SteeringBoard
{
  public:
    
    int DirectionLeftPin = 9;
    int DirectionRightPin = 8;
    int PowerPin = 5;
    
    int EndStopLeft = A0;
    int EndStopRight = A1;
    
   
    
    
};


#endif
