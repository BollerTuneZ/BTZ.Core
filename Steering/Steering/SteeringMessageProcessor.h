// SteeringMessageProcessor.h

#ifndef _STEERINGMESSAGEPROCESSOR_h
#define _STEERINGMESSAGEPROCESSOR_h

#include "UDPService.h"
#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class SteeringMessageProcessorClass
{
 protected:


 public:
	void init();
};

extern SteeringMessageProcessorClass SteeringMessageProcessor;

#endif

