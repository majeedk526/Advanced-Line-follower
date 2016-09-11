#include <Arduino.h>

template<byte ps0, byte ps1, byte ps2, byte ps3, byte ps4 >

class Sensor{
  

public:

byte vps[5] = {0,0,0,0,0};
volatile float error = 0;
volatile bool isTurnRequired = false;

void configure(){

  pinMode(ps0,INPUT);
  pinMode(ps1,INPUT);
  pinMode(ps2,INPUT);
  pinMode(ps3,INPUT);
  pinMode(ps4,INPUT);
  
}

void updateError(){

  vps[0] = digitalRead(ps0);
  vps[1] = digitalRead(ps1);
  vps[2] = digitalRead(ps2);
  vps[3] = digitalRead(ps3);
  vps[4] = digitalRead(ps4);
  

  printArrayStatus();

  if(!vps[0] && vps[4]) {
      isTurnRequired = true;
      error = -1; // left turn
      //Serial.println("left turn required");
      return;
    } 
  else if (!vps[4] && vps[0]){
      isTurnRequired = true;
      error = 1; // right turn
      //Serial.println("right turn required");
      return;
    }

  if(!vps[0]) {error=-1;}
  if(!vps[1]) {error=-0.6;}
  if(!vps[2]) {error=-0.25;}
  if(!vps[3]) {error=0.6;}
  if(!vps[4]) {error=1;}
  
}

void printArrayStatus(){

  Serial.print(vps[0]);
  Serial.print("\t");
  Serial.print(vps[1]);
  Serial.print("\t");
  Serial.print(vps[2]);
  Serial.print("\t");
  Serial.print(vps[3]);
  Serial.print("\t");
  Serial.print(vps[4]);
  
  }

};
