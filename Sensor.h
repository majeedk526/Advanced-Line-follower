#include <Arduino.h>

template<byte ps1, byte ps2, byte ps3, byte ps4, byte ps5, byte ps6, byte ps7, byte ps8 >

class Sensor{
  

public:

byte vps[8] = {0,0,0,0,0,0,0,0};
volatile float error = 0;
volatile bool is90 = false;
volatile bool is135 = false;

volatile bool isTurnRequired = false;

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
  

  printArrayStatus();

  if(!vps[0]) {
      isTurnRequired = true;
      error = -1; // left turn
      Serial.println("left turn required");
      return;
    } 
  else if (!vps[7]){
      isTurnRequired = true;
      error = 1; // right turn
      Serial.println("right turn required");
      return;
    }
  /**
  if(!vps[0] && !vps[1] && !vps[2] && !vps[3] && vps[7] && vps[6]){
    error = -0.8; //turn left
    is90 = true;
    Serial.println("turn left");
    return;
    }

  if(!vps[4] && !vps[5] && !vps[6] && !vps[7] && vps[0] && vps[1]){
    error = 0.8; //turn right
    is90 = true;
    Serial.println("turn right");
    return;
    }

   if((!vps[0] || !vps[1]) && vps[2] && !vps[3] && vps[7]){
      error = -0.8; //turn left
      is135 = true;
      Serial.println("turn 135 left");
      return;
   }

   if((!vps[4]) && vps[5] && (!vps[6] || !vps[7]) && vps[0]){
     //if(!vps[6] && vps[7])
      error = 0.8; //turn right
      is135 = true;
      Serial.println("turn 135 right");
      return;
   }

   if( (!vps[0] || !vps[1]) && !vps[2] && !vps[3] && !vps[4] && !vps[5] && (!vps[6] || !vps[7])){
    
      isCross = true;
      Serial.println("cross");
      return;
    
    }**/

  if(!vps[0]) {error=-3.5;}
  if(!vps[1]) {error=-2;}
  if(!vps[2]) {error=-1;}
  if(!vps[3]) {error=-0.3;}
  if(!vps[4]) {error=0.3;}
  if(!vps[5]) {error=1;}
  if(!vps[6]) {error=2;}
  if(!vps[7]) {error=3.5;}
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
  Serial.print("\t");
  Serial.print(vps[5]);
  Serial.print("\t");
  Serial.print(vps[6]);
  Serial.print("\t");
  Serial.println(vps[7]);
  
  }

};
