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
	int sPin = 21;
	int dPin = 20;
	int speed = 1;
	int dir = 1;
	gpioInitialise();
	StepperMotor motor = StepperMotor(sPin, dPin);
	motor.setSpeed(speed);
	motor.setDir(dir);
	motor.turn(2);
	sleep_for(seconds(2));
	motor.changeDir();
	motor.turn(2);
	gpioTerminate();
	cout << "end" << endl;
}
