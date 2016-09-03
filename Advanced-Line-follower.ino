#include "DCMotors.h" 
#include "Sensor.h"

#define START 's'
#define STOP 't'

bool debug = true;
bool startDrive = false;


DCMotors<10,18,19,11,14,15> motors; //enL, L1, L2, enR, R1, R2
Sensor<2,3,4,5,6,7,8,9> sensors;

float Kp=8, Ki=5 ,Kd=0.03;

float P=0, I=0, D=0, PID_value=0;
float error=0;
float previous_error=0, previous_I=0;
char c;
//float speedmlp = 0.0;

void setup() {
  
  motors.configure();
  sensors.configure();
  Serial.begin(9600);

  debug = false;
  
}

void loop() {
    
    if(Serial.available()){
        c = Serial.read();
     
        if(c == START){ 
          invalidate();
          startDrive = true; }
        else {
          
          startDrive = false;}
        
        if(debug){ btDebug(); }
      }
      
    if(startDrive){ 
      sensors.updateError();
      calculate_pid();
      if(!sensors.is90 && !sensors.is135 && !sensors.isCross){
        motors.drive((int)PID_value);  
        }
       else if(sensors.is90 && !sensors.is135 && !sensors.isCross){
           motors.turn90((int)PID_value);
           //motors.stopMoving();
           sensors.is90 = false;
           invalidate();
        }
        else if (sensors.is135 && !sensors.is90 && !sensors.isCross){
            motors.turn135((int) PID_value);
            //motors.stopMoving();
            sensors.is135 = false;
            invalidate();          
        }
        else if ( sensors.isCross && !sensors.is135 && !sensors.is90){
            motors.driveCross();
            sensors.isCross = false;
            invalidate();
          }   
    }
    else if(!startDrive){
      invalidate();
      motors.stopMoving();
    }
    delay(1);

}


void invalidate(){
  sensors.error = 0;
   PID_value = 0;
   I=0;
}

void calculate_pid()
{

    //if(speedmlp<1.4){
      //speedmlp+=0.001;
      //}
    error = (sensors.error);
    Serial.print(error);

   // if(error == 3 || error == -3 || error == 5 || error == -5){motors.spConst = 60;}
    //if(error == 1 || error == -1 || error == 2 || error == -2){motors.spConst = 85;}
    
    //if(error>=13 || error<=-13){//error*=1.5;
      //is90 = true;
    //} //detect 90/270 degree
    

    //if(error<0){error += -speedmlp;}
    //else if(error>0) {error += speedmlp;}
    
    P = error;
    I = I + error*0.001;
    D = (error - previous_error)/.001;
    
    PID_value = (Kp*P) + (Ki*I) + (Kd*D);

    //if(PID_value>= 35){ PID_value = 35;}
    //if(PID_value <= -35){PID_value = -35;}
    
    //Serial.print(",");
    //Serial.println(PID_value);
        
    previous_error=error;
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

