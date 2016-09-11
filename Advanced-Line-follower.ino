#include <EnableInterrupt.h>

#include "DCMotors.h" 
#include "Sensor.h"

#define START 's'
#define STOP 't'
#define isrPinRight 3
#define isrPinLeft 5

bool debug = false;
bool startDrive = false;
volatile bool isrInProcess  = false;


DCMotors<10,18,19,11,14,15> motors; //enL, L1, L2, enR, R1, R2
Sensor<2,3,4,5,6> sensors;

float Kp=7.5, Ki=5 ,Kd=0.08;

float P=0, D=0;
volatile float PID_value=0;
volatile float I=0;
float error=0;
float previous_error=0, previous_I=0;
char c;

void setup() {
  
  motors.configure();
  sensors.configure();
  Serial.begin(9600);

  debug = false;

  delay(300);
  
  invalidate();
  
}

void loop() {


     /** if(Serial.available()){
        c = Serial.read();
     
        if(c == START){ 
          invalidate();
          startDrive = true; }
        else {
          
          startDrive = false;}
        
        if(debug){ btDebug(); }
      }**/

      //if(startDrive){

      if(isrInProcess){
              //Serial.println("looping");
              return;
        }
     
      sensors.updateError();
      calculate_pid();

      if(sensors.isTurnRequired){

          // Serial.println(error);
           if(error < 0 ){ //turn right
                   //Serial.println("isr right begins");
                  enableInterrupt(isrPinLeft, isrRightTurnComplete, FALLING );
            
            } else if (error > 0){
                 // Serial.println("isr left begins");
                  enableInterrupt(isrPinRight, isrLeftTurnComplete, FALLING );
                
              }
          isrInProcess = true;
          motors.turn(error);
          
        } else {
            motors.drive((int)PID_value);
          }

     /** }
      else if(!startDrive){
      invalidate();
      motors.stopMoving();
    }**/
    delay(1);
}


void invalidate(){
  sensors.error = 0;
   PID_value = 0;
   I=0;
}

void calculate_pid()
{

    error = (sensors.error);
    Serial.print("\t");
    Serial.println(error);
    
    P = error;
    I = I + error*0.001;
    D = (error - previous_error)/.001;
    
    PID_value = (Kp*P) + (Ki*I) + (Kd*D);
        
    previous_error=error;
}

void isrRightTurnComplete(){
  
    motors.stopMoving();
    disableInterrupt(isrPinLeft);
    sensors.isTurnRequired = false;
    invalidate();
    isrInProcess = false;
  }

void isrLeftTurnComplete(){
  
    motors.stopMoving();
    disableInterrupt(isrPinRight);
    sensors.isTurnRequired = false;
    invalidate();
    isrInProcess = false;
  }

  void deactivateInterrupt(){
    
    motors.stopMoving();
    disableInterrupt(isrPinRight);
    disableInterrupt(isrPinLeft);
    invalidate();
    isrInProcess = false;
    
    }

void btDebug()
{
      if(c=='1'){
          Ki+=0.1;
          Serial.println(Ki);
      }
      else if(c=='0'){  
          Kd+=0.1;
          Serial.println(Kd);
      }
      else if(c=='2'){
          Kp+=1;
          Serial.println(Kp);
      }
      else if(c=='3'){
          Ki-=0.1;
          Serial.println(Ki);
      }
      else if(c=='4'){  
          Kd-=0.1;
          Serial.println(Kd);
      }
      else if(c=='5'){
          Kp-=1;
          Serial.println(Kp);
      } else if(c=='6'){
        motors.spConst += 1;
        Serial.println(motors.spConst);
          
      } else if(c=='7'){
        motors.spConst -= 1;  
      }
}

