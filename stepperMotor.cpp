#include <stdio.h>
#include <pigpio.h>
#include <chrono>
#include <thread>

#include "stepperMotor.h"

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds

class StepperMotor {
private:
	const int stepPin;
	const int dirPin;	
	int msPins[3] = {0,0,0};
	bool changePins;	
	double deg;
	
	double speed = 1;
	int dir = 1;
	
public:
	StepperMotor(int sPin, int dirPin) : stepPin(sPin), dirPin(dirPin), msPins(), changePins(false), deg(), speed(), dir() {
		gpioSetMode(sPin, PI_OUTPUT);
		gpioSetMode(dirPin, PI_OUTPUT);
	}
	
	StepperMotor(int sPin, int dirPin, int d) : stepPin(sPin), dirPin(dirPin), msPins(), changePins(false), deg(d),  speed(), dir(){
		gpioSetMode(sPin, PI_OUTPUT);
		gpioSetMode(dirPin, PI_OUTPUT);
	}
	
	
	double getSpeed() {
		return speed;
	}
	
	bool getDir() {
		return dir;
	}
	
	void setSpeed(double s) {
		speed = s;
	}

	void setDir(int d) {
		if (d == 1 || d == 0) dir = d;
		else throw -1;
	}
	
	void changeDir() {
		dir = (dir * -1) + 1;
	}
	
	void turn(double rot) {
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
};
