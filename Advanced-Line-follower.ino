#include "DCMotors.h" 
#include "Sensor.h"

#define START 's'
#define STOP 't'

bool debug = false;
bool startDrive = false;
bool is90 = false;

DCMotors<10,18,19,11,14,15> motors; //enL, L1, L2, enR, R1, R2
Sensor<2,3,4,5,6,7,8,9> sensors;

float Kp=3.21, Ki=0,Kd=6.3;
float P=0, I=0, D=0, PID_value=0;
float error=0;
float previous_error=0, previous_I=0;
char c;
float speedmlp = 0.0;

void read_sensor_values(void);
void calculate_pid(void);
void btDebug();
void motor_control(void);

void setup() {
  
  motors.configure();
  sensors.configure();
  Serial.begin(9600);

  debug = true;
  
}

void loop() {
    
    if(Serial.available()){
        c = Serial.read();
     
        if(c == START){ 
          sensors.error = 0;
          PID_value = 0;
          speedmlp=0;
          I=0;
          startDrive = true; }
        else {
          
          startDrive = false;}
        
        if(debug){ btDebug(); }
      }
      
    if(startDrive){ 
      sensors.updateError();
      calculate_pid();
      if(!is90){
        motors.drive((int)PID_value);  
        }
        else {
            motors.turn90((int)PID_value);
            is90 = false;
            sensors.error = 0;
            PID_value = 0;
          }
       
    }
    else if(!startDrive){
      motors.stopMoving();
    }
    delay(5);

}


void calculate_pid()
{

    /**if(speedmlp<1.5){
      speedmlp+=0.001;
      }**/
    error = (sensors.error);

    if(error>16 || error<-16){//error*=1.5;
    is90 = true;
    } //detect 90 degree
    
/**
    if(error<0){error += -speedmlp;}
    else if(error>0) {error += speedmlp;}
   **/ 
    P = error;
    I = I + error*5;
    D = (error - previous_error)/5;
    
    PID_value = (Kp*P) + (Ki*I) + (Kd*D);
    
    //Serial.println(PID_value);
    
    
    previous_error=error;
}

void btDebug()
{
      if(c=='1'){
          Ki+=0.001;
          Serial.println(Ki);
      }
      else if(c=='0'){  
          Kd+=0.1;
          Serial.println(Kd);
      }
      else if(c=='2'){
          Kp+=0.01;
          Serial.println(Kp);
      }
      else if(c=='3'){
          Ki-=0.001;
          Serial.println(Ki);
      }
      else if(c=='4'){  
          Kd-=0.1;
          Serial.println(Kd);
      }
      else if(c=='5'){
          Kp-=0.01;
          Serial.println(Kp);
      }
}

