#include "Arduino.h"
#include "SteeringState.h"


SteeringState::SteeringState()
{
  
}

int SteeringState::RemoteToReal()
{
  
  int calculated = map(RemotePosition,0,255,0,MaxRange);
  return calculated;
}

 int SteeringState::CalculateSpeed(int diff)
 {
   return map(diff,0,MaxRange,0,255);
 }
