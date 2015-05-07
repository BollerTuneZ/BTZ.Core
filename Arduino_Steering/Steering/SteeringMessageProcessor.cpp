#include "Arduino.h"
#include "SteeringMessageProcessor.h"

SteeringMessageProcessor::SteeringMessageProcessor()
{
}
SteeringMessageProcessor::~SteeringMessageProcessor()
{
}

void SteeringMessageProcessor::ProcessMessages()
{
   incommingMessage = _messageProcessor->ReceiveMessage();  
    if(incommingMessage.isLegal == 0x01)
    {               
      Serial.println("GotMail");
      if(incommingMessage.Type == _tCBase)
      {
        Serial.println("Controlling Message");
        ProcessControllMessage();  
      }else
      if(incommingMessage.Type == _tCFBase)
      {
         Serial.println("Config Message");
        ProcessConfigMessage();  
      }else
      if(incommingMessage.Type == _tCSBase)
      {
        Serial.println("State Message");
        ProcessStateMessage();  
      }
    }
}
//Initialisiert den Calculator
void SteeringMessageProcessor::Initialize(Config *sConfig,SteeringState *sSteeringState,MessageProcessor *sMessageProcessor,UDPClient *sClient)
{
  _config = sConfig;
  _state = sSteeringState;
  _messageProcessor = sMessageProcessor;
  _client = sClient;
}

void SteeringMessageProcessor::ProcessControllMessage()
{
  char controllingType = incommingMessage.Data[0];
  
  if(controllingType == _tCTurn)
  {
      _state->RemotePosition = incommingMessage.Data[1];
  }else 
  if(controllingType == _tCStartSetup)
  {
      _state->_enterSetup = incommingMessage.Data[1];
  }else 
  if(controllingType == _tCSetZero)
  {
      _state->_enterSetup = incommingMessage.Data[1];
  }else 
  if(controllingType == _tCContinueSetup)
  {
      _state->_enterSetup = incommingMessage.Data[1];
  }else 
  if(controllingType == _tCSetMaximumAndExit)
  {
      _state->_enterSetup = incommingMessage.Data[1];
  }
}
void SteeringMessageProcessor::ProcessConfigMessage()
{
  char configType = incommingMessage.Data[0];
  if(configType == _tCFInputType)
  {
    Serial.print("Type");
    Serial.println(incommingMessage.Data[1]);
      if(incommingMessage.Data[1] == Read)
      {
        Serial.print("Read:");
         //Antwort erstellen
         Serial.println(_config->InputType);
        char *payload = CreatePayloadWithCharParamert(*_config->InputType,configType);
        _messageProcessor->SendMessage(_client,_messageGenerator.CreateMessage(_tCFBase,payload));
      }else if(incommingMessage.Data[1] == Write)
      {
        Serial.println("Write");
        //Serial.println(incommingMessage.Data[2]);
        
        _config->InputType = new char('H');  
        Serial.println(_config->InputType);
      }
  }else if(configType == _tCFMaximalSpeed)
  {
       if(incommingMessage.Data[1] == Read)
      {
         //Antwort erstellen
        char *payload = CreatePayloadWithCharParamert(_config->MaximalSpeed,configType);
        _messageProcessor->SendMessage(_client,_messageGenerator.CreateMessage(_tCFBase,payload));
      }else if(incommingMessage.Data[1] == Write)
      {
        _config->MaximalSpeed = (unsigned char)incommingMessage.Data[2];  
      }
  }else if(configType == _tCFMinimalSpeed)
  {
       if(incommingMessage.Data[1] == Read)
      {
         //Antwort erstellen
        char *payload = CreatePayloadWithCharParamert(_config->MinimalSpeed,configType);
        _messageProcessor->SendMessage(_client,_messageGenerator.CreateMessage(_tCFBase,payload));
      }else if(incommingMessage.Data[1] == Write)
      {
        _config->MaximalSpeed = (unsigned char)incommingMessage.Data[2];  
      }
  }else if(configType == _tCFMaximalPosition)
  {
       if(incommingMessage.Data[1] == Read)
      {
         //Antwort erstellen
        char *payload = CreatePayloadWithIntParamert(_config->MaximalPosition,configType);
        _messageProcessor->SendMessage(_client,_messageGenerator.CreateMessage(_tCFBase,payload));
      }else if(incommingMessage.Data[1] == Write)
      {
        //Nicht implementiert 
      }
  }else if(configType == _tCFCenter)
  {
       if(incommingMessage.Data[1] == Read)
      {
         //Antwort erstellen
        char *payload = CreatePayloadWithIntParamert(_config->Center,configType);
        _messageProcessor->SendMessage(_client,_messageGenerator.CreateMessage(_tCFBase,payload));
      }else if(incommingMessage.Data[1] == Write)
      {
        if(incommingMessage.Data[2] == 'U')
        {
          _config->Center = _config->Center + 1;
        }else if(incommingMessage.Data[2] == 'D')
        {
          _config->Center = _config->Center - 1;
        }
      }
  }else if(configType == _tCFSetupSpeed)
  {
       if(incommingMessage.Data[1] == Read)
      {
         //Antwort erstellen
        char *payload = CreatePayloadWithCharParamert(_config->SetupSpeed,configType);
        _messageProcessor->SendMessage(_client,_messageGenerator.CreateMessage(_tCFBase,payload));
      }else if(incommingMessage.Data[1] == Write)
      {
        _config->SetupSpeed = (unsigned char)incommingMessage.Data[2];  
      }
  }
  else if(configType == _tCFInvertDirection)
  {
       if(incommingMessage.Data[1] == Read)
      {
         //Antwort erstellen
        char *payload = CreatePayloadWithCharParamert(_config->InvertDirection,configType);
        _messageProcessor->SendMessage(_client,_messageGenerator.CreateMessage(_tCFBase,payload));
      }else if(incommingMessage.Data[1] == Write)
      {
        _config->InvertDirection = (unsigned char)incommingMessage.Data[2];  
      }
  }
}
void SteeringMessageProcessor::ProcessStateMessage()
{
  char stateType = incommingMessage.Data[0];
  
  if(stateType == _tSEncoderMotor)
  {
      if(incommingMessage.Data[1] == Read)
      {
         //Antwort erstellen
        char *payload = CreatePayloadWithIntParamert(_state->RealPosition,stateType);
        _messageProcessor->SendMessage(_client,_messageGenerator.CreateMessage(_tCSBase,payload));
      }else if(incommingMessage.Data[1] == Write)
      {
        //Keine Setter
      }    
  }else
  if(stateType == _tSEncoderSteering)
  {
      if(incommingMessage.Data[1] == Read)
      {
         //Antwort erstellen
        char *payload = CreatePayloadWithIntParamert(_state->SteeringEncoderPosition,stateType);
        _messageProcessor->SendMessage(_client,_messageGenerator.CreateMessage(_tCSBase,payload));
      }else if(incommingMessage.Data[1] == Write)
      {
        //Keine Setter
      }    
  }else
  if(stateType == _tSRemotePosition)
  {
      if(incommingMessage.Data[1] == Read)
      {
         //Antwort erstellen
        char *payload = CreatePayloadWithCharParamert(_state->RemotePosition,stateType);
        _messageProcessor->SendMessage(_client,_messageGenerator.CreateMessage(_tCSBase,payload));
      }else if(incommingMessage.Data[1] == Write)
      {
         //Keine Setter
      }    
  }else
  if(stateType == _tSEnabled)
  {
      if(incommingMessage.Data[1] == Read)
      {
         //Antwort erstellen
        char *payload = CreatePayloadWithCharParamert(_state->Enabled,stateType);
        _messageProcessor->SendMessage(_client,_messageGenerator.CreateMessage(_tCSBase,payload));
      }else if(incommingMessage.Data[1] == Write)
      {
        _state->Enabled = (unsigned char)incommingMessage.Data[2];  
      }    
  }else
  if(stateType == _tSRunning)
  {
      if(incommingMessage.Data[1] == Read)
      {
         //Antwort erstellen
        char *payload = CreatePayloadWithCharParamert(_state->Running,stateType);
        _messageProcessor->SendMessage(_client,_messageGenerator.CreateMessage(_tCSBase,payload));
      }else if(incommingMessage.Data[1] == Write)
      {
        //Kein Setter  
      }    
  }else
  if(stateType == _tSDirection)
  {
      if(incommingMessage.Data[1] == Read)
      {
         //Antwort erstellen
        char *payload = CreatePayloadWithCharParamert(_state->Direction,stateType);
        _messageProcessor->SendMessage(_client,_messageGenerator.CreateMessage(_tCSBase,payload));
      }else if(incommingMessage.Data[1] == Write)
      {
        //Kein Setter  
      }    
  }
}

/*Member*/
char *SteeringMessageProcessor::CreatePayloadWithCharParamert(char value,char type)
{
    char *payload = new char[3];
    payload[0] = *_config->Identity;
    payload[1] = type;
    payload[2] = value;
    return payload;
}

/*  String str;
    str=String(Position);
    str.toCharArray(steeringPosition,5);*/
char *SteeringMessageProcessor::CreatePayloadWithIntParamert(int value,char type)
{
  char *payload = new char[6];
  payload[0] = *_config->Identity;
  payload[1] = type;
  
  char b[4];
  String str;
  str=String(value);
  str.toCharArray(b,2);
  
  for(int i = 0;i < 4;i++)
  {
    payload[i + 2] = b[i];
  }
  return payload;
}
