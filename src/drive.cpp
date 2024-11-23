#include "drive.h"
#include <Adafruit_PWMServoDriver.h>

auto FruitServoDriver = Adafruit_PWMServoDriver();
bool isMotorInitialized = false;

void MotorDriver::initialize()
{
	pinMode(M1_IO1, OUTPUT);
	pinMode(M1_IO2, OUTPUT);
	pinMode(M2_IO1, OUTPUT);
	pinMode(M2_IO2, OUTPUT);
	pinMode(M3_IO1, OUTPUT);
	pinMode(M3_IO2, OUTPUT);
	pinMode(M4_IO1, OUTPUT);
	pinMode(M4_IO2, OUTPUT);
	FruitServoDriver.begin();
	FruitServoDriver.setOscillatorFrequency(PCA9685_CLOCK_SPEED);
	FruitServoDriver.setPWMFreq(MOTOR_FREQUENCY);
	FruitServoDriver.setPWM(1, 0, 0);
	FruitServoDriver.setPWM(2, 0, 0);
	FruitServoDriver.setPWM(3, 0, 0);
	FruitServoDriver.setPWM(4, 0, 0);
	isMotorInitialized = true;
}

void MotorDriver::run(const Motor motor, const int16_t pwmSpeed,
		      const bool dir) const
{
	int16_t A_ON, A_OFF, B_ON, B_OFF;
	if (dir == 1) {
		A_ON = 0;
		A_OFF = pwmSpeed;
		B_ON = 0;
		B_OFF = 0;
	} else {
		A_ON = 0;
		A_OFF = 0;
		B_ON = 0;
		B_OFF = pwmSpeed;
	}
	FruitServoDriver.setPWM(pinsA[motor], A_ON, A_OFF);
	FruitServoDriver.setPWM(pinsB[motor], B_ON, B_OFF);
}

void MotorDriver::stop(const Motor motor) const
{
	FruitServoDriver.setPWM(pinsA[motor], 0, 4096);
	FruitServoDriver.setPWM(pinsB[motor], 0, 4096);
}

void MotorDriver::lift(const Motor motor, const MotorOperation status,
		       const int16_t pwmSpeed)
{
	switch (status) {
	case UP:
		FruitServoDriver.setPWM(pinsA[motor], 0, pwmSpeed);
		FruitServoDriver.setPWM(pinsB[motor], 0, 0);
		currentAction = UP;
		break;

	case DOWN:
		FruitServoDriver.setPWM(pinsA[motor], 0, 0);
		FruitServoDriver.setPWM(pinsB[motor], 0, pwmSpeed);
		currentAction = DOWN;
		break;

	case STOP:
		FruitServoDriver.setPWM(pinsA[motor], 4096, 4096);
		FruitServoDriver.setPWM(pinsB[motor], 4096, 4096);
		currentAction = STOP;
		break;
	}
} //up, down or stop
void ServoDriver::initialize()
{
	if (!isMotorInitialized) {
		FruitServoDriver.begin();
		FruitServoDriver.setOscillatorFrequency(PCA9685_CLOCK_SPEED);
		FruitServoDriver.setPWMFreq(MOTOR_FREQUENCY);
	}
}

void ServoDriver::execute(const Servo servo, const int angle) const
{
	const long tmp = map(angle, 0, 180, 400, 2400); // T_on in ms
	Serial.println(tmp);
	Serial.println(servo);
	FruitServoDriver.writeMicroseconds(servo, tmp);
}

void ServoDriver::stop(const Servo servo)
{
	FruitServoDriver.setPWM(servo, 4096, 4096);
}
