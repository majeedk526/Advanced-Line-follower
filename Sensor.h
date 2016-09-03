#include <Arduino.h>

template<byte ps1, byte ps2, byte ps3, byte ps4, byte ps5, byte ps6, byte ps7, byte ps8 >

class Sensor{
  

public:

byte vps[8] = {0,0,0,0,0,0,0,0};
float error = 0;
bool is90 = false;
bool is135 = false;
bool isCross = false;

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

  vps[0] = digitalRead(ps1);
  vps[1] = digitalRead(ps2);
  vps[2] = digitalRead(ps3);
  vps[3] = digitalRead(ps4);
  vps[4] = digitalRead(ps5);
  vps[5] = digitalRead(ps6);
  vps[6] = digitalRead(ps7);
  vps[7] = digitalRead(ps8);
  

  if(!vps[0] && !vps[1] && !vps[2] && !vps[3] && vps[7] && vps[6] && vps[5]){
    error = -1; //turn left
    is90 = true;
    return;
    }

  if(!vps[4] && !vps[5] && !vps[6] && !vps[7] && vps[0] && vps[1] && vps[2]){
    error = 1; //turn right
    is90 = true;
    return;
    }

   if(!vps[0] && (vps[1] || vps[2]) && !vps[3]){
      error = -5; //turn left
      is135 = true;
      return;
   }

   if(!vps[4] && (vps[5] || vps[6]) && !vps[7]){
      error = 5; //turn right
      is135 = true;
      return;
   }

   if( (!vps[0] || !vps[1]) && !vps[2] && !vps[3] && !vps[4] && !vps[5] && (!vps[6] || !vps[7])){
    
      isCross = true;
      return;
    
    }

  if(!vps[0]) {error=-3.5;}
  if(!vps[1]) {error=-3;}
  if(!vps[2]) {error=-1;}
  if(!vps[3]) {error=-0.5;}
  if(!vps[4]) {error=0.5;}
  if(!vps[5]) {error=2;}
  if(!vps[6]) {error=3;}
  if(!vps[7]) {error=3.5;}
}



};
