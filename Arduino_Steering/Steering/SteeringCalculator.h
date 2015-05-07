#ifndef SteeringCalculator_h
#define SteeringCalculator_h

#include "Arduino.h"
#include "Config.h"
#include "SteeringState.h"


class SteeringCalculator
{
  public:
  SteeringCalculator();
  ~SteeringCalculator();
  
    //Initialisiert den Calculator
    void Initialize(Config *sConfig,SteeringState *sSteeringState);
    
    //Berechnet die Geschwindigkeit für den Motor
    void CalculateSpeed();
    
  private:
    int ConvertRemotePosToRealPos();
  
    char _isInitialized;//Gibt an ob die Klasse ordnungsgemäß Initialisiert worden ist
    char *_currentSpeed;
    Config *_config;
    SteeringState *_state;
    
};


#endif
