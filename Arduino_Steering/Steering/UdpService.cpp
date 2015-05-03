#include "Arduino.h"
#include "UdpService.h"

UdpService::UdpService()
{
  
}


void UdpService::Init(UDPConnectionInfo *connectionInfo)
{
   byte ipTest[] = {connectionInfo->ipAddress[0],connectionInfo->ipAddress[1],connectionInfo->ipAddress[2],connectionInfo->ipAddress[3]};
   unsigned int port = connectionInfo->GetPort();

  
  this->macAdress = new byte[6];
   char * mAddress = connectionInfo->GetMacAddress();
   
   this->macAdress[0] = mAddress[0];
   this->macAdress[1] = mAddress[1];
   this->macAdress[2] = mAddress[2];
   this->macAdress[3] = mAddress[3];
   this->macAdress[4] = mAddress[4];
   this->macAdress[5] = mAddress[5];
  
  Ethernet.begin(this->macAdress,ipTest);

  if(Udp.begin(port) == 0)
  {
   Serial.println("Failed to initialize UDP"); 
  }else
  {
     // print your local IP address:
  Serial.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print(".");
  }
    Serial.println("initialized UDP"); 
  }
}



void UdpService::GetBytes()
{
    int packetSize = Udp.parsePacket();
    for(int i=0;i<UDP_TX_PACKET_MAX_SIZE;i++) packetBuffer[i] = 0;
    
    if (packetSize)
    {
    
    // read the packet into packetBufffer
    Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    
    // send a reply, to the IP address and port that sent us the packet we received
    //Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    //Udp.write(ReplyBuffer);
    //Udp.endPacket();
  }
  
}

    
int UdpService::SendBytes(char *bytes,UDPClient *client)
{
  
   int result =  Udp.beginPacket(client->GetIpAddress(), client->GetPort());
    Udp.write(bytes);
    Udp.endPacket();
    return result;
}



