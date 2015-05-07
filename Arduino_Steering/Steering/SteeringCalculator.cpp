#include "Arduino.h"
#include "SteeringCalculator.h"

SteeringCalculator::SteeringCalculator()
{
}
SteeringCalculator::~SteeringCalculator()
{
}
  
//Initialisiert den Calculator
void SteeringCalculator::Initialize(Config *sConfig,SteeringState *sSteeringState)
{
  _config = sConfig;
  _state = sSteeringState;
}
    
//Berechnet die Geschwindigkeit für den Motor InvertDirection
char* SteeringCalculator::CalculateSpeed(
int steeringPosition,
int currentPosition,
char remotePosition,
char inputType,
char dirLeft,
char dirRight,
char invert,
int maxPos,
char minSpeed,
char maxSpeed)
{
  int positionSteering = steeringPosition;
  _currentSpeed = new char[2];
  _currentSpeed[0] = 'N';
  
  if(inputType == 'R')
  {
    positionSteering = ConvertRemotePosToRealPos(remotePosition,maxPos);
  }
  int diff = currentPosition -positionSteering;
  
  if(diff < 0)
  {
    if(invert == 'X')
    {
      _currentSpeed[0] = dirLeft;
    }else
    {
       _currentSpeed[0] = dirRight;
    }
  }else
  {
     if(invert == 'X')
    {
      _currentSpeed[0] = dirRight;
    }else
    {
       _currentSpeed[0] = dirLeft;
    }
  }
  _currentSpeed[1] = map(diff,0,maxPos,minSpeed,maxSpeed);
  return _currentSpeed;
}

int SteeringCalculator::ConvertRemotePosToRealPos(int remotePosition,int maximum)
{
    return map(remotePosition,0,255,0,maximum);
}
