#include <stdio.h>
#include <pigpio.h>
#include <chrono>
#include <thread>

#include "stepperMotor.h"

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds

int stepPin;
int dirPin;
int msPins[3];
bool changePins;
double deg;
double speed;
int dir;

StepperMotor::StepperMotor() {}

StepperMotor::StepperMotor(int sPin, int dirPin) : stepPin(sPin), dirPin(dirPin), msPins(), changePins(false), deg(), speed(), dir() {
	gpioSetMode(sPin, PI_OUTPUT);
	gpioSetMode(dirPin, PI_OUTPUT);
}
	
StepperMotor::StepperMotor(int sPin, int dirPin, double d) : stepPin(sPin), dirPin(dirPin), msPins(), changePins(false), deg(d),  speed(), dir(){
	gpioSetMode(sPin, PI_OUTPUT);
	gpioSetMode(dirPin, PI_OUTPUT);
}
	
	
double StepperMotor::getSpeed() {
	return speed;
}
	
bool StepperMotor::getDir() {
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
	
void StepperMotor::turn(double rot) {
	int delay = ((360/(speed*deg))*1000000000);
	int steps = rot*deg/360;
	for (int i = 0; i < steps; ++i) {
		gpioWrite(dirPin, dir);
		gpioWrite(stepPin, 1);
		sleep_for(nanoseconds(delay));
		gpioWrite(stepPin,0);
		sleep_for(nanoseconds(delay));
	}
}
