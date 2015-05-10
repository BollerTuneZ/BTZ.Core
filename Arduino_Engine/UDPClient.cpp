
#include "Arduino.h"
#include "UDPClient.h"

UDPClient::UDPClient(int ip1,int ip2,int ip3,int ip4 ,unsigned int port)
{
   ipAddress = IPAddress(ip1,ip2,ip3,ip4);
   this->port = new unsigned int(port);
}


unsigned int UDPClient::GetPort()
{
   return *this->port; 
}
IPAddress UDPClient::GetIpAddress()
{
    
    return ipAddress;
}
