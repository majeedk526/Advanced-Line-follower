#include "DCMotors.h" 
#include "Sensor.h"


DCMotors<10,18,19,11,14,15> motors; //enL, L1, L2, enR, R1, R2
Sensor<2,3,4,5,6,7,8,9> sensors;

float Kp=0, Ki=0,Kd=0;
float error=0, P=0, I=0, D=0, PID_value=0;
float previous_error=0, previous_I=0;
int sensor[8]={0, 0, 0, 0, 0, 0, 0, 0};

void read_sensor_values(void);
void calculate_pid(void);
void motor_control(void);

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

    sensors.updateError;
    calculate_pid();
    motor_control();

}


void calculate_pid()
{
    error = sensors.error;
    P = error;
    I = I + error;
    D = error - previous_error;
    
    PID_value = (Kp*P) + (Ki*I) + (Kd*D);
    
    previous_error=error;
}

void motor_control()
{
    int left_motor_speed = initial_motor_speed-PID_value;
    int right_motor_speed = initial_motor_speed+PID_value;
    
    constrain(left_motor_speed,0,255);
    constrain(right_motor_speed,0,255);
    
    analogWrite(9,left_motor_speed);   //Left Motor Speed
    analogWrite(10,right_motor_speed);  //Right Motor Speed
    
    digitalWrite(4,HIGH);
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
    digitalWrite(7,HIGH);
}
