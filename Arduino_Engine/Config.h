#ifndef Config_h
#define Config_h

#include "Arduino.h"

class Config
{
   public:
     Config();
     ~Config();
     
   char ConstDirFor = 'F';
   char ConstDirBack = 'B';
   /*
   *Gibt an ob die richtung gedreht werden soll
   *N = NoInvert; X = Invert
   */
   char InvertDirection = 'N';         
};
#endif
