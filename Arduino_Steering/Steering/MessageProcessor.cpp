#include "Arduino.h"
#include "MessageProcessor.h"


MessageProcessor::MessageProcessor(UdpService *udpService)
{
  //Service to get Messages from Remote
    char *emptyDataArray = new char[1];
    emptyDataArray[0] = 0;
    
   this->udpService = udpService; 
   erMessage = new Message();
   erMessage->isLegal = 0;
   rMessage = new Message();
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

Message * MessageProcessor::ReceiveMessage()
{
  //Message
  //0 = startByte
  //1 = Type
  //2 = Length
  //3 = Data[]
  //4 = endbyte
   
   this->udpService->GetBytes();
    
   if(udpService->packetBuffer[0] != startByte)
   {
      //Startbyte is not what we expected
     return erMessage; 
   }
   //as we now know how long the dataArray should be
   //we can easily find out if the Endbyte is right
   
   if(udpService->packetBuffer[udpService->packetBuffer[2] + 3] != endByte)
   {
     //Endbyte is not what we expected,
     //that means the Message must be broken
     
     return erMessage;
   }
   _length = (int)((unsigned char)udpService->packetBuffer[2]);
   
   char *dataBytes; 
   char testBuffer[_length];
   
  //Store the DataBytes, which always begin at index 3
  for(int i=0;i < _length;i++)
  {
    testBuffer[i] = udpService->packetBuffer[(i +3)];
  }  
  
  dataBytes = testBuffer;
  
  rMessage->isLegal = 1;
  rMessage->Length = udpService->packetBuffer[2];
  rMessage->Type = udpService->packetBuffer[1];
  rMessage->Data = dataBytes;
  return rMessage;
}


