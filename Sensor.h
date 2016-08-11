#include <Arduino.h>

template<byte ps1, byte ps2, byte ps3, byte ps4, byte ps5, byte ps6, byte ps7, byte ps8 >

class Sensor{
  

public:


int error = 0;
void configure(){

  pinMode(ps1,INPUT);
  pinMode(ps2,INPUT);
  pinMode(ps3,INPUT);
  pinMode(ps4,INPUT);
  pinMode(ps5,INPUT);
  pinMode(ps6,INPUT);
  pinMode(ps7,INPUT);
  pinMode(ps8,INPUT);
}

void updateError(){

  //error = 0;
  if(!digitalRead(ps1)) {error-=4;}
  if(!digitalRead(ps2)) {error-=3;}
  if(!digitalRead(ps3)) {error-=2;}
  if(!digitalRead(ps4)) {error-=1;}
  if(!digitalRead(ps5)) {error+=1;}
  if(!digitalRead(ps6)) {error+=2;}
  if(!digitalRead(ps7)) {error+=3;}
  if(!digitalRead(ps8)) {error+=4;}
  
}

};
