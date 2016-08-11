#include "DCMotors.h" 
#include "Sensor.h"

#define START 's'
#define STOP 't'

bool debug = false;
bool startDrive = false;

DCMotors<10,18,19,11,14,15> motors; //enL, L1, L2, enR, R1, R2
Sensor<2,3,4,5,6,7,8,9> sensors;

float Kp=0.5, Ki=1,Kd=1;
float P=0, I=0, D=0, PID_value=0;
int error=0;
float previous_error=0, previous_I=0;
char c;

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
    
    sensors.updateError();
    calculate_pid();


    if(Serial.available()){
        c = Serial.read();
        Serial.println(c);
        
        if(c == START){ startDrive = true; }
        else {startDrive = false;}
        
        if(debug){ btDebug(); }
      }

    

    if(startDrive){ motors.drive(PID_value); 
    }
    else if(!startDrive){motors.stopMoving();
    }
    delay(10);

}


void calculate_pid()
{
    error = (sensors.error);
    P = error;
    I = I + error*10;
    D = (error - previous_error)/10;
    
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
      if(c=='1'){
          Ki+=0.1;
          Serial.print("Ki : ");
          Serial.println(Ki);
      }
      else if(c=='0'){  
          Kd+=1;
          Serial.print("Kd : ");
          Serial.println(Kd);
      }
      else if(c=='2'){
          Kp+=1;
          Serial.print("Kp : ");
          Serial.println(Kp);
      }
      else if(c=='3'){
          Ki-=0.1;
          Serial.print("Ki : ");
          Serial.println(Ki);
      }
      else if(c=='4'){  
          Kd-=1;
          Serial.print("Kd : ");
          Serial.println(Kd);
      }
      else if(c=='5'){
          Kp-=1;
          Serial.print("Kp : ");
          Serial.println(Kp);
      }
}

