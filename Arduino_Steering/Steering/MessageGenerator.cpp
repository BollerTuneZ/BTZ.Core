#include "Arduino.h"
#include "MessageGenerator.h"


MessageGenerator::MessageGenerator()
{
  
}
MessageGenerator::~MessageGenerator()
{
  
}
    
Message* MessageGenerator::CreateReadPositionMessage(int Position)
{
    ReadPosition = new Message();
    ReadPosition->StartByte = Startbyte;
    ReadPosition->EndByte = Endbyte;
    ReadPosition->Type = ReadPositionType;
    steeringPosition = new char[5];
    String str;
    str=String(Position);
    str.toCharArray(steeringPosition,5);
    ReadPosition->Data = steeringPosition;
    ReadPosition->Length = 5;
    return ReadPosition;
}



Message* MessageGenerator::CreateEngineSpeedMessage(int engineSpeed)
{
    EngineSpeed = new Message();
    EngineSpeed->StartByte = Startbyte;
    EngineSpeed->EndByte = Endbyte;
    EngineSpeed->Type = Engine_ReadSpeed;
    m_engineSpeed = new char[5];
    String str;
    str=String(engineSpeed);
    str.toCharArray(m_engineSpeed,5);
    ReadPosition->Data = m_engineSpeed;
    ReadPosition->Length = 5;
    return ReadPosition;
}
Message* MessageGenerator::CreateEngineDirectionMessage(int engineDirection)
{
    EnigneDirection = new Message();
    EnigneDirection->StartByte = Startbyte;
    EnigneDirection->EndByte = Endbyte;
    EnigneDirection->Type = Engine_ReadDirection;
    m_engineDirection = new char(0x01);
    
    if(engineDirection == 1)
    {
       m_engineDirection = new char(0x02);
    }
    EnigneDirection->Data = m_engineDirection;
    EnigneDirection->Length = 1;
    return ReadPosition;
}
