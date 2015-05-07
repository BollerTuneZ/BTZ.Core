#ifndef Config_h
#define Config_h

#include "Arduino.h"

class Config
{
public:
	char InputType = 0x1; //1=aus;2=encoder;3=Remote

	/*Gibt die Maximale Geschwindigkeit an
	* default = 125
	*/
	char MaximumSpeed = 125; 
	/*Gibt die Minimale Geschwindigkeit an
	* default = 1
	*/
	char MinimumSpeed = 1;

	int MaximumLeft;
					//Gibt an wie weit nach links und nach rechts gefahren werden darf
	int MaximumRight;

	//gibt an vo sich die Mitte befindet
	int Center;
};


#endif