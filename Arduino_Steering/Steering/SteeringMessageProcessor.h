#ifndef SteeringMessageProcessor_h
#define SteeringMessageProcessor_h

#include "Arduino.h"
#include "Config.h"
#include "SteeringState.h"
#include "MessageProcessor.h"
#include "Message.h"
#include "MessageGenerator.h"
#include "Common.h"
#include "UDPClient.h"

class SteeringMessageProcessor
{
  public:
  SteeringMessageProcessor();
  ~SteeringMessageProcessor();
  
  void Initialize(MessageProcessor *sMessageProcessor,UDPClient *sClient);
    
  void ProcessMessages();
    
 char IsEnabled();
 char GetSetupState();
 char GetInvertState();
 char GetDirRight();
 char GetDirLeft();
 char GetMotorSpeed();
 char GetSetupSpeed();
 int GetMaxPosition();
 int GetSteeringPosition();
 int GetCurrentPosition();
 char GetInputType();
 char GetDirection();
 char GetRemotePosition();
 char GetMaxSpeed();
 char GetMinSpeed();
 
 void SetDirection(char dir);
 void SetMotorSpeed(char speed);
 void SetSetupState(char state);
 void SetMaxPosition(int position);
 void SetCenterPosition(int position);
 void SetCurrentPosition(int position);
 void SetCurrentSteeringPosition(int position);
    
    
  private:

    Config *_config;
    SteeringState *_state;
    MessageProcessor *_messageProcessor;
    Message incommingMessage;
    MessageGenerator _messageGenerator;
    Common _common;
    UDPClient *_client;
    
    /*Processing*/
    void ProcessControllMessage();
    void ProcessConfigMessage();
    void ProcessStateMessage();
    
    /*Member*/
    char *CreatePayloadWithCharParamert(char value,char type);
    
    char *CreatePayloadWithIntParamert(int value,char type);
    /*Constante*/
      //General
    const char Read = 'R';
    const char Write = 'W';
    
    const char _tCBase = 'C';
      //Controlling
    const char _tCTurn = 'T';
    const char _tCEngineSpeed = 'S';
    const char _tCStartSetup = 's';
    const char _tCSetZero = 'O';
    const char _tCContinueSetup = 'c';
    const char _tCSetMaximumAndExit = 'e';
    
      
    const char _tCFBase = 'F';
      //Config
    const char _tCFInputType = 'I';
    const char _tCFMaximalSpeed = 'W';
    const char _tCFMinimalSpeed = 'S';
    const char _tCFMaximalPosition = 'M';
    const char _tCFCenter = 'C';
    const char _tCFSetupSpeed = 'U';
    const char _tCFLeftOn = 'q';
    const char _tCFLeftOff = 'w';
    const char _tCFRightOn = 'e';
    const char _tCFRightOff = 'r';
    const char _tCFConstDirLeft = 'L';
    const char _tCFConstDirRight = 'R';
    const char _tCFInvertDirection = 'D';
    
    const char _tCSBase = 'S';
      //State
    const char _tSCurrentPosition = 'P';
    const char _tSEnabled = 'E';
    const char _tSRunning = 'R';
    const char _tSDirection = 'D';
    const char _tSEncoderMotor = 'M';
    const char _tSEncoderSteering = 'N';
    const char _tSRemotePosition = 'r';
    
    
   
    
};


#endif
