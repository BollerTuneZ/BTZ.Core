#include "Arduino.h"
#include "MessageProcessor.h"


MessageProcessor::MessageProcessor(UdpService *udpService)
{
  //Service to get Messages from Remote
    char *emptyDataArray = new char[1];
    emptyDataArray[0] = 0;
    
   this->udpService = udpService; 
   
   erMessage.isLegal = 0;

}



int MessageProcessor::SendMessage(UDPClient *client,Message *message)
{
  
  int totalLength = 4 + message->Length;
  
   char *data = new char[totalLength]; 
   data[0] = startByte;
   data[1] = message->Type;
   data[2] = message->Length;
   
   for(int i = 0;i < message->Length;i++)
   {
      data[i +3] = message->Data[i]; 
   }
   
   data[message->Length + 3] = endByte;
   
   udpService->SendBytes(data,client);
}

Message MessageProcessor::ReceiveMessage()
{
  //Message
  //0 = startByte
  //1 = Type
  //2 = Length
  //3 = Data[]
  //4 = endbyte
   rMessage->isLegal = 0;
   this->udpService->GetBytes();
    //Serial.println("StartParsing");
   if(udpService->packetBuffer[0] != startByte)
   {
      //Startbyte is not what we expected
     return erMessage; 
   }
   //Serial.println("Parsing");
   //as we now know how long the dataArray should be
   //we can easily find out if the Endbyte is right
   
   if(udpService->packetBuffer[udpService->packetBuffer[2] + 3] != endByte)
   {
     //Endbyte is not what we expected,
     //that means the Message must be broken    
     return erMessage;
   }
   Message tempMessage;
   _length = ((unsigned char)udpService->packetBuffer[2]);
   
   for(int i=0;i < 10;i++)
   {
      tempMessage.Data[i] == 0; 
   }
   
  //Store the DataBytes, which always begin at index 3
  for(int i=0;i < _length;i++)
  {
    tempMessage.Data[i] = udpService->packetBuffer[(i +3)];
    /*
      Serial.print("Buffer:");
      Serial.print("  Raw:");
      Serial.print(tempMessage.Data[i]);  
      Serial.print("//unsigned char:");
      Serial.println((unsigned char)tempMessage.Data[i]);
      */
  }  
    
  tempMessage.isLegal = 1;
  tempMessage.Length = udpService->packetBuffer[2];
  tempMessage.Type = udpService->packetBuffer[1];  
  return tempMessage;
}


