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
	FruitServoDriver.setOscillatorFrequency(Clock_PCA9685);
	FruitServoDriver.setPWMFreq(Motor_FREQ);
	FruitServoDriver.setPWM(1, 0, 0);
	FruitServoDriver.setPWM(2, 0, 0);
	FruitServoDriver.setPWM(3, 0, 0);
	FruitServoDriver.setPWM(4, 0, 0);
	isMotorInitialized = true;
}

void MotorDriver::run(const Motor motor, int16_t pwm_input, bool dir)
{
	if (dir == 1) {
		IN1 = 0;
		IN2 = pwm_input;
		IN3 = 0;
		IN4 = 0;
	} else {
		IN1 = 0;
		IN2 = 0;
		IN3 = 0;
		IN4 = pwm_input;
	}
	FruitServoDriver.setPWM(Motor_A[motor - 1], IN1, IN2);
	FruitServoDriver.setPWM(Motor_B[motor - 1], IN3, IN4);
}

void MotorDriver::stop(const Motor motor)
{
	IN1 = 0;
	IN2 = 4096;
	IN3 = 0;
	IN4 = 4096;
	FruitServoDriver.setPWM(Motor_A[motor - 1], IN1, IN2);
	FruitServoDriver.setPWM(Motor_B[motor - 1], IN3, IN4);
}

void MotorDriver::lift(const Motor motor, const MotorOperation status,
		       const int16_t pwm_input)
{
	switch (status) {
	case UP:
		FruitServoDriver.setPWM(Motor_A[motor - 1], 0, pwm_input);
		FruitServoDriver.setPWM(Motor_B[motor - 1], 0, 0);
		lift_stt = 1;
		break;

	case DOWN:
		FruitServoDriver.setPWM(Motor_A[motor - 1], 0, 0);
		FruitServoDriver.setPWM(Motor_B[motor - 1], 0, pwm_input);
		lift_stt = -1;
		break;

	case STOP:
		FruitServoDriver.setPWM(Motor_A[motor - 1], 4096, 4096);
		FruitServoDriver.setPWM(Motor_B[motor - 1], 4096, 4096);
		lift_stt = 0;
		break;
	}
} //up, down or stop
void ServoDriver::initialize()
{
	if (!isMotorInitialized) {
		FruitServoDriver.begin();
		FruitServoDriver.setOscillatorFrequency(Clock_PCA9685);
		FruitServoDriver.setPWMFreq(Motor_FREQ);
	}
}

void ServoDriver::setAngle(const int angle, const int servo_num) const
{
	const long tmp = map(angle, 0, 180, 400, 2600); // T_on in ms
	// T_on = tmp / 1000.0;
	Serial.println(tmp);
	// Serial.println(T_on*1000);
	FruitServoDriver.writeMicroseconds(servoList[servo_num - 1], tmp);
	// pwm_val = (int) (T_on/(Ts/4096));
	// pwm.setPWM(My_servo[servo_num-1],0,pwm_val);
}

void ServoDriver::stop(const int servo_num) const
{
	FruitServoDriver.setPWM(servoList[servo_num - 1], 4096, 4096);
}
