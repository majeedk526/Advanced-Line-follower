#include <Arduino.h>


template <byte enL, byte inpL1, byte inpL2, byte enR, byte inpR1, byte inpR2 >

class DCMotors{

  public:

  byte pid_val = 0;
  byte spConst = 100; //speed const

  int LMSpeed, RMSpeed; // left and right motro speeds

  void configure(){
    pinMode(enL, OUTPUT);
    pinMode(inpL1,OUTPUT);
    pinMode(inpL2,OUTPUT);
    pinMode(enR, OUTPUT);
    pinMode(inpR1, OUTPUT);
    pinMode(inpR2, OUTPUT);
    stopMoving();
  }

  void drive(int cor){

    LMSpeed = spConst + cor;
    RMSpeed = spConst - cor;
    
    analogWrite(enL,LMSpeed);
    analogWrite(enR,RMSpeed);
    digitalWrite(inpL1,LOW);
    digitalWrite(inpL2,HIGH);
    digitalWrite(inpR1,HIGH);
    digitalWrite(inpR2,LOW);
  }

  void stopMoving(){
    analogWrite(enL,0);
    analogWrite(enR,0);
    digitalWrite(inpL1,LOW);
    digitalWrite(inpL2,LOW);
    digitalWrite(inpR1,LOW);
    digitalWrite(inpR2,LOW);
  }
  
};

