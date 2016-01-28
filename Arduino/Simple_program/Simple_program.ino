#include <Arduino.h>
#include <Wire.h>
#include <Servo.h>
#include <SoftwareSerial.h>

#include <MeOrion.h>

double angle_rad = PI/180.0;
double angle_deg = 180.0/PI;
double Speed;
double OffsetRight;
double OffsetLeft;
double direction;
double last_dir;
double count;
double distance;
MeUltrasonicSensor ultrasonic_3(3);
MeDCMotor motor_9(9);
MeDCMotor motor_10(10);



void setup(){
    Speed = 100;
    OffsetRight = 1;
    OffsetLeft = 0.93;
    direction = 0;
    last_dir = 0;
    count = 0;
    delay(1000*5);
    
}

void loop(){
    
    distance = ultrasonic_3.distanceCm();
    if((distance) < (20)){
        if((distance) < (10)){
            motor_9.run(((Speed) * (OffsetLeft)) * (1));
            motor_10.run(((Speed) * (OffsetRight)) * (1));
            delay(1000*0.5);
        }
        if((direction) < (1)){
            motor_9.run(((Speed) * (OffsetLeft)) * (1));
            motor_10.run(((Speed) * (OffsetRight)) * (-1));
            if(((last_dir)==(0))){
                direction = 1;
            }
            last_dir = 0;
            delay(1000*1);
        }else{
            motor_9.run(((Speed) * (OffsetLeft)) * (-1));
            motor_10.run(((Speed) * (OffsetRight)) * (1));
            if(((last_dir)==(1))){
                direction = 0;
            }
            last_dir = 1;
            delay(1000*1);
        }
    }else{
        motor_9.run(((Speed) * (OffsetLeft)) * (-1));
        motor_10.run(((Speed) * (OffsetRight)) * (-1));
        delay(1000*0.5);
        last_dir = -1;
    }
    
}

