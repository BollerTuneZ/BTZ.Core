#ifndef UdpConnectionInfo_h
#define UdpConnectionInfo_h

#include "Arduino.h"

class UDPConnectionInfo
{
  public:
    UDPConnectionInfo();
    void Initialize(char ip1,char ip2,char ip3,char ip4,unsigned int port);
    
    void ChangeMacAddress(char *macaddr);
    
    char *ipAddress;
     
    unsigned int GetPort();
    
    char * GetMacAddress();
    
  private:
    unsigned int *port;
    char *macAddr;
    
};


#endif
