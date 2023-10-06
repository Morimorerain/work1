/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       86152                                                     */
/*    Created:      2023/10/3 21:15:16                                        */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

// define your global instances of motors and other devices here


int main() {
    vex::motor motor1(0);
    vex::motor motor2(9);
    motor1.spin(fwd,180,rpm);
    motor2.spin(fwd,-60,rpm);
    this_thread::sleep_for(5000);
    motor1.spin(fwd,60,rpm);
    motor2.spin(fwd,-180,rpm);
    this_thread::sleep_for(4500);
    motor1.stop();
    motor2.stop();
    return 0;
}
