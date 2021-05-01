#include <stdio.h>
#include <pigpio.h>
#include <chrono>
#include <thread>
#include <iostream>

#include "stepperMotor.h"

using std::cout;
using std::endl;

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds

int main(int argc, char ** argv){
	cout << "start" << endl;
	int pins[6] = {21, 20, 26, 0, 0, 0};
	int speed = 2;
	int dir = 1;
	gpioInitialise();
	
	StepperMotor motor(pins);
	motor.setSpeed(speed);
	cout << "Starting first Turn!" << endl;
	motor.setDir(dir);
	motor.holdOn();
	motor.turn(4);
	sleep_for(seconds(2));
	motor.changeDir();
	motor.setSpeed(8);
	cout << "Starting Second Turn!" << endl;
	motor.turn(10.0);
	motor.holdOff();
	gpioTerminate();
	cout << "end" << endl;
}
