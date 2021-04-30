#ifndef STEPPERMOTOR_H
#define STEPPERMOTOR_H


class StepperMotor {

private:
	int stepPin;
	int dirPin;
	int msPins[3] = {0,0,0};
	bool changePins = false;
	int stepsPerRot = 200;
	double speed = 1.0;
	int dir = 1;

public:
	
	//REQUIRES: sPin and dirPin be valid GPIO pins on Raspberry Pi
	//EFFECTS: Creates and Initializes a stepper motor with the desired
	//step pin and direction pin.
	StepperMotor(int sPin, int dirPin);
	
	//REQUIRES: sPin and dirPin be valid GPIO pins on Raspberry Pi, and d > 0
	//EFFECTS: Creates and Initializes a stepper motor with the desired
	//step pin and direction pin. Specifys the motor degree angle to be d.
	StepperMotor(int sPin, int dirPin, double d);
	
	//EFFECTS: Returns the set speed of the motor
	double getSpeed() const;
	
	
	//EFFECTS: Returns the direction of the motor, 1 for CW, 0 for CCW
	bool getDir() const;
	
	//EFFECTS: Sets turning speed of motor to s.
	void setSpeed(double s);
	
	//REQUIRES: d be either 1 or 0, throws -1 otherwise
	//EFFECTS: Sets direction of motor, 1 -> CW, 0 -> CCW
	void setDir(int d);
	
	//EFFECTS: Changes direction, CW -> CCW and CCW -> CW
	void changeDir();
	
	//EFFECTS: Turns the motor rot number of rotations
	void turn(double rot) const;
};

#endif
