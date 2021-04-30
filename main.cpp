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
	/*int sPin = 21;
	int dPin = 20;
	int speed = 1;
	int dir = 1;
	gpioInitialise();
	
	StepperMotor motor(sPin, dPin);
	motor.setSpeed(speed);
	cout << "Starting first Turn!" << endl;
	motor.setDir(dir);
	motor.turn(1.0);
	sleep_for(seconds(2));
	motor.changeDir();
	cout << "Starting Second Turn!" << endl;
	motor.turn(1.0);
	gpioTerminate();*/
	
	gpioInitialise();
	gpioSetMode(21, PI_OUTPUT);
	gpioSetMode(20, PI_OUTPUT);
	gpioWrite(20, 1);
	gpioWrite(21, 1);
	sleep_for(seconds(2));
	gpioWrite(21, 0);
	gpioTerminate();
	cout << "end" << endl;
}
