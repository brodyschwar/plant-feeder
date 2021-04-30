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

StepperMotor::StepperMotor(int sPin, int dirPin) : stepPin(sPin), dirPin(dirPin), msPins(), changePins(false), stepsPerRot(), speed(), dir() {
	stepsPerRot = 200;
	gpioSetMode(sPin, PI_OUTPUT);
	gpioSetMode(dirPin, PI_OUTPUT);
}
	
StepperMotor::StepperMotor(int sPin, int dirPin, double d) : stepPin(sPin), dirPin(dirPin), msPins(), changePins(false), stepsPerRot(),  speed(), dir(){
	stepsPerRot = 360/d;
	gpioSetMode(sPin, PI_OUTPUT);
	gpioSetMode(dirPin, PI_OUTPUT);
}
	
	
double StepperMotor::getSpeed() const {
	return speed;
}
	
bool StepperMotor::getDir() const {
	return dir;
}

void StepperMotor::setSpeed(double s) {
	speed = s;
}

void StepperMotor::setDir(int d) {
	if (d == 1 || d == 0) dir = d;
	else throw -1;
}
	
void StepperMotor::changeDir() {
	dir = (dir * -1) + 1;
}
	
void StepperMotor::turn(double rot) const {
	int steps = rot*stepsPerRot;
	int delay = (speed/stepsPerRot)*1000000000;
	cout << "Steps: " << steps << endl;
	cout << "Delay: " << delay << endl;
	gpioWrite(dirPin, dir);
	for (int i = 0; i < steps; ++i) {
		gpioWrite(stepPin, 1);
		sleep_for(nanoseconds(delay));
		gpioWrite(stepPin,1);
		sleep_for(nanoseconds(delay));
	}
}
