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
void SteeringCalculator::CalculateSpeed()
{
  int positionSteering = _state->SteeringEncoderPosition;
  _currentSpeed = new char[2];
  _currentSpeed[0] = 'N';
  
  if(*_config->InputType == 'R')
  {
    positionSteering = ConvertRemotePosToRealPos();
  }
  int diff = _state->RealPosition -positionSteering;
  
  if(diff < 0)
  {
    if(_config->InvertDirection == 'X')
    {
      _state->Direction = _config->ConstDirLeft;
    }else
    {
       _state->Direction = _config->ConstDirRight;
    }
  }else
  {
    if(_config->InvertDirection == 'X')
    {
      _state->Direction = _config->ConstDirRight;
    }else
    {
       _state->Direction = _config->ConstDirLeft;
    }
  }
  _state->MotorSpeed =  map(diff,0,_config->MaximalPosition,_config->MinimalSpeed,_config->MaximalSpeed);
}

int SteeringCalculator::ConvertRemotePosToRealPos()
{
    return map(_state->RemotePosition,0,255,0,_config->MaximalPosition);
}
