#include <stdio.h>
#include <pigpio.h>

using std::string;

class StepperMotor {
private:
	const int stepPin;
	const int dirPin;	
	const int msPins[3];
	const bool changePins;	
	const double deg;
	
	double speed;
	bool dir;
	
public:

	StepperMotor(int sPin, int dirPin) : stepPin(sPin), 
										 dirPin(dirPin),
										 deg(1.8),
										 msPins(),
										 changePins(false)
										 speed(1)
										 dir(true) {}
	
	StepperMotor(int sPin, int dirPin, int d) : stepPin(sPin), 
												dirPin(dirPin),
												deg(d),
												msPins(),
												changePins(false) {}
	
	
	double getSpeed() {
		return speed;
	}
	
	string getDir() {
		if(dir) return "CW";
		else return "CCW";
	}
	
	void setSpeed(double s) {
		speed = s;
	}
	
	void setDir(string d) {
		if (d == "CW") dir = true;
		else if (d == "CCW") dir = false;
		else throw 1;
	}
	
	void changeDir() {
		dir = !dir;
	}
	
	void run() {
	}
	
	void halt() {
	}
	
	void turn(double rot) {
		double delay = (360/(speed*deg));
		int steps = rot*deg/360;
		for (int i = 0; i < steps; ++i) {
		//
		}
	}
};
