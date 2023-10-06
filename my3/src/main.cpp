/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       86152                                                     */
/*    Created:      2023/10/4 16:07:52                                        */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

// define your global instances of motors and other devices here


float Wheel = 10.56; 
float WB =48.5; 
float EncPerCm = 360.0 / (Wheel* M_PI); 
float EncPerDeg =  WB / Wheel;
vex::motor LeftMotor(0);
vex::motor RightMotor(9,true);

void reportMotionValues(motor m, int line){

  Brain.Screen.printAt(5,line, "%8.2lf%8.2lf%8.2f", 
    m.position(rev), 
    m.position(deg)); 
}
void goStraight( float distance);
void turnRight( float degrees);
void turnLeft( float degrees);
int main() {  
    turnRight(60);
    int i = 0;
    while(true){
        goStraight(50);
        wait(100,msec);
        if(i == 5){
            break;
        }
        turnRight(100);
        i++;
    }
    for(int k = 0;k<=5;k++){
        goStraight(50);
        wait(100,msec);
        turnLeft(100);
    }
}




void goStraight( float distance ){	
	LeftMotor.resetPosition();
	RightMotor.resetPosition();
	float totalEnc = distance * EncPerCm;
    LeftMotor.setVelocity(50.0, percent);
    LeftMotor.spinToPosition(totalEnc, deg, false);
    RightMotor.setVelocity(50.0, percent);
    RightMotor.spinToPosition(totalEnc, deg, false);
    while (LeftMotor.isSpinning() || RightMotor.isSpinning() ) 
        wait(50, msec);
	return;
}
void turnRight( float degrees){
	
	LeftMotor.resetPosition();
	RightMotor.resetPosition();
  	
	float totalEnc = degrees * EncPerDeg;
    LeftMotor.setVelocity(100.0, percent);
    LeftMotor.spinToPosition(totalEnc, deg, false);
 
    RightMotor.setVelocity(-100.0, percent);
    RightMotor.spinToPosition(-totalEnc, deg, false);

    while(LeftMotor.isSpinning() || RightMotor.isSpinning() ) 
        wait(50, msec);
	return;
}
void turnLeft( float degrees){
	
	LeftMotor.resetPosition();
	RightMotor.resetPosition();
  	
	float totalEnc = degrees * EncPerDeg;
    LeftMotor.setVelocity(-100.0, percent);
    LeftMotor.spinToPosition(-totalEnc, deg, false);
 
    RightMotor.setVelocity(100.0, percent);
    RightMotor.spinToPosition(totalEnc, deg, false);

    while(LeftMotor.isSpinning() || RightMotor.isSpinning() ) 
        wait(50, msec);
	return;
}