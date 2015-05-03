#ifndef UDPClient_h
#define UDPClient_h

#include "Arduino.h"
#include <Ethernet.h>
class UDPClient
{
  public:
    UDPClient(int ip1,int ip2,int ip3,int ip4 ,unsigned int port);
    unsigned int GetPort();
    IPAddress GetIpAddress();
  private:
    unsigned int *port;
     IPAddress ipAddress;
    
};


#endif
