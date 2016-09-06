#include <Arduino.h>


template <byte enL, byte inpL1, byte inpL2, byte enR, byte inpR1, byte inpR2 >

class DCMotors{

  public:
  
  byte spConst = 62; //speed const
  byte tunrSpeed = 45;

  int LMSpeed, RMSpeed; // left and right motor speeds

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
   
    if(LMSpeed < 0) {LMSpeed = 0;}
    if(LMSpeed > 255) {LMSpeed = 255;}

    if(RMSpeed < 0) {RMSpeed = 0;}
    if(RMSpeed > 255) {RMSpeed = 255;}
    
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

  void turn(int cor){

    stopMoving();
    delay(2);

     if(cor>0){

      analogWrite(enL,60);
      analogWrite(enR,0);
      digitalWrite(inpL1,LOW);
      digitalWrite(inpL2,HIGH);
      digitalWrite(inpR1,HIGH);
      digitalWrite(inpR2,LOW);
      
      
      //drive(22);
      
      }
     else if(cor<0){
      analogWrite(enL,0);
      analogWrite(enR,60);
      digitalWrite(inpL1,LOW);
      digitalWrite(inpL2,HIGH);
      digitalWrite(inpR1,HIGH);
      digitalWrite(inpR2,LOW);
      //drive(-22);
     }
    }
};

