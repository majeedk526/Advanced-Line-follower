#include "DCMotors.h" 
#include "Sensor.h"

#define START 's'
#define STOP 't'

bool debug = false;
bool startDrive = false;

DCMotors<10,18,19,11,14,15> motors; //enL, L1, L2, enR, R1, R2
Sensor<2,3,4,5,6,7,8,9> sensors;

float Kp=1, Ki=0,Kd=0;
float P=0, I=0, D=0, PID_value=0;
int error=0;
float previous_error=0, previous_I=0;

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

    if(debug){
      btDebug();  
    }
    
    sensors.updateError();
    calculate_pid();

    if(Serial.read() == START) {
      startDrive = true;    
    } 

    if(Serial.read() == STOP){
      startDrive = false;
    }

    if(startDrive){
      motors.drive(PID_value);  
    }
    
    delay(100);

}


void calculate_pid()
{
    error = (sensors.error)*10;
    P = error;
    I = I + error;
    D = error - previous_error;
    
    PID_value = (Kp*P) + (Ki*I) + (Kd*D);
    
    previous_error=error;
    
   // Serial.print("pidval : ");
     // Serial.print(PID_value);
    //Serial.println("\t");
    /**Serial.print("\n");
    Serial.print("PIDVal : ");
    Serial.print(PID_value);
    Serial.print("\t");

    Serial.print("P : ");
    Serial.print(P);
    Serial.print("\t");

    Serial.print("I : ");
    Serial.print(I);
    Serial.print("\t");

    Serial.print("D : ");
    Serial.print(D);
    Serial.print("\t");

    

    Serial.print("Prvs_error : ");
    Serial.print(previous_error);
    Serial.println();
   **/ 
}

void btDebug()
{
  
  if(Serial.available())
    {
      if(Serial.read()=='1'){
          Ki+=0.1;
          Serial.write("Ki value is incremented");
      }
      else if(Serial.read()=='0'){  
          Kd+=1;
          Serial.write("Kd value is incremented");
      }
      else if(Serial.read()=='2'){
          Kp+=1;
          Serial.write("Kp value is incremented");
      }
      else if(Serial.read()=='3'){
          Ki-=0.1;
          Serial.write("Ki value is decremented");
      }
      else if(Serial.read()=='4'){  
          Kd-=1;
          Serial.write("Kd value is decremented");
      }
      else if(Serial.read()=='5'){
          Kp-=1;
          Serial.write("Kp value is decremented");
      }
  }
}
