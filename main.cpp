#include <stdio.h>
#include <pigpio.h>
#include <chrono>
#include <thread>
#include <iostream>

#include "stepperMotor.h"

using std::cout;
using std::endl;

using std::thread;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds

void turningTest(StepperMotor* motor) {
	motor->holdOn();
	cout << "Starting first Turn!" << endl;
	motor->turn(4);
	sleep_for(seconds(2));
	motor->changeDir();
	cout << "Starting Second Turn!" << endl;
	motor->turn(3);
	motor->holdOff();
}

void runningTest(StepperMotor* motor) {
	bool go = true;
	thread t1(&StepperMotor::runUntil, *motor, std::ref(go));
	cout << go << endl;
	sleep_for(seconds(20));
	go = false;
	cout << go << endl;
	t1.join();
}
int main(int argc, char ** argv){
	cout << "start" << endl;
	int pins[6] = {21, 20, 26, 0, 0, 0};
	int speed = 5;
	int dir = 1;
	gpioInitialise();
	
	StepperMotor * motor = new StepperMotor(pins);
	motor->setSpeed(speed);
	motor->setDir(dir);
	
	runningTest(motor);
	
	motor->setSpeed(10);
	runningTest(motor);
	
	gpioTerminate();
	cout << "end" << endl;
	delete motor;
}
