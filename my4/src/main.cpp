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
vex::motor shotmotor1(1,true);
vex::motor shotmotor2(8);
vex::motor hangmotor1(10,true);
vex::motor hangmotor2(11);
vex::motor_group LeftMotorG(LeftMotor1,LeftMotor2);
vex::motor_group RightMotorG(RightMotor1,RightMotor2);
vex::motor_group tranMotorG(tranMotor1,tranMotor2);
vex::motor_group shotmotorG(shotmotor1,shotmotor2);
vex::motor_group hangmotorG(hangmotor1,hangmotor2);
vex::vision vis(7);
void tranballin();
void tranballout();
void shotball();
void hangit();
void upit();
int hangcount = 0;
int vmax =180;
int vmax2 = 50;
int main() {
    void (*trin)();
    void (*trout)();
    void (*stbl)();
    void (*hag)();
    void (*uit)();
    trin = tranballin;
    trout = tranballout;
    stbl = shotball;
    hag = hangit;
    uit = upit;
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
        con1.ButtonDown.pressed(stbl);
        con1.ButtonRight.pressed(hag);
        con1.ButtonLeft.pressed(uit);
        this_thread::sleep_for(10);
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
void shotball(){
    shotmotorG.spin(fwd,10,rpm);
    this_thread::sleep_for(4000);
    while(1){
        double m1 = shotmotor1.torque();
        double m2 = shotmotor2.torque();
        double m = m1 + m2;
        if(m>0.78){
            shotmotorG.stop(hold);
            break;
        }
        else{
            this_thread::sleep_for(10);
            continue;
        }
    }
}
void hangit()
{hangmotorG.spin(fwd,30,rpm);
this_thread::sleep_for(7500);
hangmotorG.spin(fwd,0,rpm);
hangmotorG.stop(hold);}
void upit()
{hangmotorG.spin(fwd,-30,rpm);
this_thread::sleep_for(7500);
hangmotorG.spin(fwd,0,rpm);
hangmotorG.stop(hold);}
