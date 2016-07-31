#include <Arduino.h>


template <byte enL, byte inpL1, byte inpL2, byte enR, byte inpR1, byte inpR2 >

class DCMotors{

  public:

  byte pid_val = 0;
  byte spConst = 100; //speed const

  void configure(){
    pinMode(enL, OUTPUT);
    pinMode(inpL1,OUTPUT);
    pinMode(inpL2,OUTPUT);
    pinMode(enR, OUTPUT);
    pinMode(inpR1, OUTPUT);
    pinMode(inpR2, OUTPUT);
    stopMoving();
  }
  
  void correctDrive(int cor){
    analogWrite(enL, spConst+cor);
    analogWrite(enR, spConst-cor);;
  }

  void driveForward(int cor){
    analogWrite(enL,0);
    analogWrite(enR,0);
    digitalWrite(inpL1,LOW);
    digitalWrite(inpL2,HIGH);
    digitalWrite(inpR1,HIGH);
    digitalWrite(inpR2,LOW);

    correctDrive(cor);
  }

  void driveBack(int cor){
    analogWrite(enL,0);
    analogWrite(enR,0);
    digitalWrite(inpL1,HIGH);
    digitalWrite(inpL2,LOW);
    digitalWrite(inpR1,LOW);
    digitalWrite(inpR2,HIGH);

    correctDrive(cor);
  }


  void turnLeft(){
    analogWrite(enL,0);
    analogWrite(enR,0);
    digitalWrite(inpL1,LOW);
    digitalWrite(inpL2,HIGH);
    digitalWrite(inpR1,LOW);
    digitalWrite(inpR2,HIGH);  
    analogWrite(enL,spConst);
    analogWrite(enR,spConst);  
  }

  void turnRight(){
    analogWrite(enL,0);
    analogWrite(enR,0);
    digitalWrite(inpL1,HIGH);
    digitalWrite(inpL2,LOW);
    digitalWrite(inpR1,HIGH);
    digitalWrite(inpR2,LOW);
    analogWrite(enL,spConst);
    analogWrite(enR,spConst);
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

