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

StepperMotor::StepperMotor(int p[]) {
	for (int i = 0; i < numPins; i++) {
		pins[i] = p[i];
	}
	stepsPerRot = 200;
	setPinModes();
}
	
StepperMotor::StepperMotor(int* p, double d) {
	for (int i = 0; i < numPins; i++) {
		pins[i] = p[i];
	}
	stepsPerRot = 360/d;
	setPinModes();
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
	int delay = (1.0/(stepsPerRot*speed))*1000000000;
	cout << "Steps: " << steps << endl;
	cout << "Delay: " << delay << endl;
	if(!hold) awaken();
	gpioWrite(pins[1], dir);
	for (int i = 0; i < steps; ++i) {
		gpioWrite(pins[0], 1);
		sleep_for(nanoseconds(delay));
		gpioWrite(pins[0],0);
		sleep_for(nanoseconds(delay));
	}
	if(!hold) bed();
}

bool StepperMotor::awaken() const {
	if (pins[2] == 0) return false;
	else {
		gpioWrite(pins[2], 1);
		return true;
	}
}

bool StepperMotor::bed() const {
	if (pins[2] == 0) return false;
	else {
		gpioWrite(pins[2], 0);
		return true;
	}
}

void StepperMotor::holdOn() {
	if(!awaken()) throw -1;
	hold = true;
}

void StepperMotor::holdOff() {
	if(!bed()) throw -1;
	hold = false;
}

void StepperMotor::setPinModes() const {
	for(int i = 0; i < numPins; i++) {
		if(pins[i] != 0) gpioSetMode(pins[i], PI_OUTPUT);
	}
}
