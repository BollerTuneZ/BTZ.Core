#include "Arduino.h"
#include "UDPConnectionInfo.h"


UDPConnectionInfo::UDPConnectionInfo()
{
    this->macAddr = new char[6];
  
  //Default MacAddress
  this->macAddr[0] = 0x00;
  this->macAddr[1] = 0xAD;
  this->macAddr[2] = 0xBE;
  this->macAddr[3] = 0xEF;
  this->macAddr[4] = 0xFE;
  this->macAddr[5] = 0xED;
  
}


void UDPConnectionInfo::Initialize(char ip1,char ip2,char ip3,char ip4,unsigned int port)
{
   this->ipAddress = new char[4];
  
    this->ipAddress[0] = ip1;
    this->ipAddress[1] = ip2;
    this->ipAddress[2] = ip3;
    this->ipAddress[3] = ip4;
    
    
    this->port = new unsigned int(port);
  
}

void UDPConnectionInfo::ChangeMacAddress(char *macaddr)
{
  this->macAddr = macaddr;
  
}

char * UDPConnectionInfo::GetMacAddress()
{
   return this->macAddr;
}


unsigned int UDPConnectionInfo::GetPort()
{
   return *this->port; 
  
}
