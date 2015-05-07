#include "Arduino.h"
#include "Config.h"
Config::Config()
{
}
Config::~Config()
{
}
void Config::SetInputType(char t){
  Serial.println(t);
  delay(1000);
  InputType = new char('X');
}
void Config::SetMaximalSpeed(char s){
  MaximalSpeed =s;
}
void Config::SetMinimalSpeed(char s){
  MinimalSpeed =s;
}
void Config::SetMaximalPosition(int p){
  MaximalPosition =p;
}
void Config::SetMaximalCenter(int p){
  Center =p;
}
void Config::SetInvert(char i){
  InvertDirection =i;
}

