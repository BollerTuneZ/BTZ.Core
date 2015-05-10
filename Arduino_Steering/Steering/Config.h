#ifndef Config_h
#define Config_h

#include "Arduino.h"

class Config
{
   public:
     Config();
     ~Config();
     
     char CommandChar = 'c';
         
     /*Identität des Arduinos (Wichtig für das MessageSystem*/
     char Identity = 'L';
     /*Gibt an welcher Input genuutzt werden soll
       1 = Aus;2 = Encoder; 3 = Remote
     */
     char InputType = 'N'; 
     /*SpeedLimits*/
     char MaximalSpeed = 125; //default 125
     char MinimalSpeed = 1; //default 1
     /*Encoder limits*/
     int MaximalPosition;     
     int Center; //Gibt an wo sich die mitte befindet     
     /*
     * Gibt an in welcher Geschwindigkeit sich der Motor beim 
     * Calibrieren bewegen soll
     */
   int SetupSpeed = 5;   
   /*Steering invert*/
   int LeftOn = HIGH;
   int LeftOff = LOW;   
   int RightOn = HIGH;
   int RightOff = LOW;  
   /*Direction const 
   * Gibt die richtung für die jeweilige richtung an
   */
   char ConstDirLeft = 'L';
   char ConstDirRight = 'R';
   /*
   *Gibt an ob die richtung gedreht werden soll
   *N = NoInvert; X = Invert
   */
   char InvertDirection = 'N';      

  //Typen
      //General
   char T_SetupStep = 'S';
  char T_InputType = 'I';
 char T_Steer = 'T'; 
};
#endif
