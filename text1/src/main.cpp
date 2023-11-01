/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       86152                                                     */
/*    Created:      2023/10/22 17:11:06                                       */
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
int main() {
    
    vex::vision vis(7);
    vex::vision::signature  Green1(2,-6371, -5205, -5788, -3855, -2855, -3354, 6, 0);
    vis.setSignature(Green1);
    vis.setBrightness(100);
    while(1){
        vis.takeSnapshot(Green1);
        double a = vis.largestObject.centerX;
        Brain.Screen.setCursor(1,1);
        Brain.Screen.print(a);
        if(vis.largestObject.exists){
            LeftMotorG.spin(fwd,(a-150)/7,rpm);
            RightMotorG.spin(fwd,(150-a)/7,rpm);
        }
        else{
            LeftMotorG.spin(fwd,0,rpm);
            RightMotorG.spin(fwd,0,rpm);
        }
        this_thread::sleep_for(100);
    }
    

}
