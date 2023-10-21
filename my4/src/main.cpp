/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       86152                                                     */
/*    Created:      2023/10/5 17:00:00                                        */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

// define your global instances of motors and other devices here
vex::motor LeftMotor1(16,true);
vex::motor LeftMotor2(17,true);
vex::motor RightMotor1(18);
vex::motor RightMotor2(19);
vex::motor tranMotor1(0);
vex::motor tranMotor2(9,true);
vex::motor shotmotor(1,true);
vex::motor_group LeftMotorG(LeftMotor1,LeftMotor2);
vex::motor_group RightMotorG(RightMotor1,RightMotor2);
vex::motor_group tranMotorG(tranMotor1,tranMotor2);
void tranballin();
void tranballout();
void down_toshot();
void up_shot();
int vmax =180;
int vmax2 = 50;
int main() {
    void (*trin)();
    void (*trout)();
    void (*down_st)();
    void (*up_st)();
    trin = tranballin;
    trout = tranballout;
    down_st = down_toshot;
    up_st = up_shot;
    while(1){
        vex::controller con1;
        int nf = con1.Axis3.position(pct);
        int nr = con1.Axis4.position(pct);
        double vf = vmax*nf/100;
        double vr = vmax2*nr/100;
        double v1 = vf + vr;
        double v2 = vf - vr;
        LeftMotorG.spin(fwd,v1,rpm);
        RightMotorG.spin(fwd,v2,rpm);
        con1.ButtonR1.pressed(trout);        
        con1.ButtonL1.pressed(trin);
        con1.ButtonDown.pressed(down_st);
        con1.ButtonUp.pressed(up_st);
        wait(10,msec);
    }
}

void tranballin(){
    if(tranMotorG.velocity(rpm)<180){
        tranMotorG.spin(fwd,360,rpm);
    }
    else{
        tranMotorG.stop();
    }
}
void tranballout(){
    if(tranMotorG.velocity(rpm)>-180){
        tranMotorG.spin(fwd,-360,rpm);
    }
    else{
        tranMotorG.stop();
    }
}
void down_toshot(){
    shotmotor.resetPosition();
    shotmotor.spinTo(90,deg,10,rpm,true);
}
void up_shot(){
    shotmotor.resetPosition();
    shotmotor.spinTo(270,deg,10,rpm,true);
}