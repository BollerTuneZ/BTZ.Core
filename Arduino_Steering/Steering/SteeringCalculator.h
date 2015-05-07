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
    char * CalculateSpeed(int steeringPosition,int currentPosition,char remotePosition,char inputType,char dirLeft,char dirRight,char invert,int maxPos,char minSpeed,char maxSpeed);
    
  private:
    int ConvertRemotePosToRealPos(int remotePosition,int maximum);
  
    char _isInitialized;//Gibt an ob die Klasse ordnungsgemäß Initialisiert worden ist
    char *_currentSpeed;
    Config *_config;
    SteeringState *_state;
    
};


#endif
