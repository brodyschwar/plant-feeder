#ifdef STEPPERMOTOR_H
#define STEPPERMOTOR_H


class StepperMotor {
public:

	StepperMotor::StepperMotor(int sPin, int dirPin);
	
	StepperMotor::StepperMotor(int sPin, int dirPin, int d);
	
	double StepperMotor::getSpeed() const;
	
	bool StepperMotor::getDir() const;
	
	void StepperMotor::setSpeed(double s);
	
	void StepperMotor::setDir(int d);
	
	void StepperMotor::changeDir();
	
	void StepperMotor::turn(double rot) const;
};

#endif
