#ifndef DRIVE_H_
#define DRIVE_H_

#if ARDUINO > 22
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define M1_IO1 15
#define M1_IO2 2
#define M2_IO1 4
#define M2_IO2 16
#define M3_IO1 17
#define M3_IO2 5
#define M4_IO1 18
#define M4_IO2 19

// Via MotorShield motor channels
#define MOTOR1_PIN_A 8
#define MOTOR1_PIN_B 9
#define MOTOR2_PIN_A 10
#define MOTOR2_PIN_B 11
#define MOTOR3_PIN_A 12
#define MOTOR3_PIN_B 13
#define MOTOR4_PIN_A 14
#define MOTOR4_PIN_B 15

#define MOTOR_FREQUENCY 50
#define PCA9685_CLOCK_SPEED 27000000

enum Motor { Motor1 = 1, Motor2 = 2, Motor3 = 3, Motor4 = 4 };

enum Servo {
	Servo1 = 2,
	Servo2 = 3,
	Servo3 = 4,
	Servo4 = 5,
	Servo5 = 6,
	Servo6 = 7,
};

enum MotorOperation {
	UP = 1,
	DOWN = -1,
	STOP = 0,
};

class MotorDriver {
	/* data */
	// int16_t IN1 = 0, IN2 = 0, IN3 = 0, IN4 = 0;
	// 4 value to control dc motor using setPWM function of PCA9685 library
	int pinsA[4] = { MOTOR1_PIN_A, MOTOR2_PIN_A, MOTOR3_PIN_A,
			 MOTOR4_PIN_A },
	    pinsB[4] = { MOTOR1_PIN_B, MOTOR2_PIN_B, MOTOR3_PIN_B,
			 MOTOR4_PIN_B };

    public:
	MotorOperation currentAction = STOP;
	static void initialize();
	/*!
     *  @brief  Note: motor 4 using lift mechanism and motor 3 using rotate mechanism
     *  @param  motor the motor to move
     *  @param  pwmSpeed pwm to control motor, 0-4096
     *  @param  dir direction of motor, 0: clockwise 1:counterclockwise
     */
	void run(Motor motor, int16_t pwmSpeed, bool dir) const;

	/*!
     *  @brief  Stop lift
     */
	void stop(Motor motor) const;

	/*!
     *  @brief  Note: motor 4 using lift mechanism and motor 3 using rotate mechanism
     *  @param  motor the motor
     *  @param  status: LIFT_UP, LIFT_DOWN or LIFT_STOP
     *  @param  pwmSpeed pwm to control motor, 0-4096
     */
	void lift(Motor motor, MotorOperation status,
		  int16_t pwmSpeed); //up, down or stop
};

class ServoDriver {
	int servoList[6] = { Servo1, Servo2, Servo3, Servo4, Servo5, Servo6 };
	// int pwm_val;
	// float T_on;
	float T_ON_90 = 1.5, T_ON_0 = 1.0, T_ON_180 = 2.0;
	float pwmServoCycleMilis =
		20; // Cycle of PWM control servo. Set to 20ms or 50Hz.
	// T_ON_90 is time in ms to control servo in 90 degree.Ts is cycle of PWM control servo: 20ms ~ freq: 50Hz

    public:
	static void initialize();

	/*!
	 *  @brief  Control angle of servo function
	 *  @param  servo	the servo
	 *  @param  angle	angle of motor, 0-180. If servo 360, 0 is CW, 180 is CCW, 90 is stop
	 */
	void execute(Servo servo, int angle) const;
	void stop(Servo servo);

	void test() const;
};

void scani2c();
#endif