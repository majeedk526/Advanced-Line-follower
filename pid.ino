#include "DCMotors.h" 
#include "Sensor.h"

DCMotors<10,18,19,11,14,15> motors; //enL, L1, L2, enR, R1, R2
Sensor<2,3,4,5,6,7,8,9> sensors;

float Kp=0.6, Ki=0.1,Kd=0.4;
float P=0, I=0, D=0, PID_value=0;
int error=0;
float previous_error=0, previous_I=0;
//int sensor[8]={0, 0, 0, 0, 0, 0, 0, 0};

void read_sensor_values(void);
void calculate_pid(void);
void motor_control(void);

void setup() {
  // put your setup code here, to run once:

  motors.configure();
  sensors.configure();
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

    sensors.updateError();
    calculate_pid();
    motors.drive(PID_value);
    delay(500);

}


void calculate_pid()
{
    error = sensors.error;
    P = error;
    I = I + error;
    D = error - previous_error;
    
    PID_value = (Kp*P) + (Ki*I) + (Kd*D);
    
    previous_error=error;
    
    Serial.print("pidval : ");
      Serial.print(PID_value);
    Serial.println("\t");
/**
    Serial.print("P : ");
    Serial.print(P);
    Serial.print("\t");

    Serial.print("I : ");
    Serial.print(I);
    Serial.print("\t");

    Serial.print("D : ");
    Serial.print(D);
    Serial.print("\t");

    Serial.print("PIDVal : ");
    Serial.print(PID_value);
    Serial.print("\t");

    Serial.print("Prvs_error : ");
    Serial.print(previous_error);
    Serial.println();
   **/ 
}

