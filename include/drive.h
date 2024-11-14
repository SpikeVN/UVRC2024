#ifndef EEB_h
#define EEB_h

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
#define M1_A 8
#define M1_B 9
#define M2_A 10
#define M2_B 11
#define M3_A 12
#define M3_B 13
#define M4_A 14
#define M4_B 15

#define Motor_FREQ 50
#define Clock_PCA9685 27000000

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
	int16_t IN1 = 0, IN2 = 0, IN3 = 0, IN4 = 0;
	// 4 value to control dc motor using setPWM function of PCA9685 library
	int Motor_A[4] = { M1_A, M2_A, M3_A, M4_A },
	    Motor_B[4] = { M1_B, M2_B, M3_B, M4_B };

    public:
	int lift_stt = 0;
	static void initialize();
	/*!
    	 *  @brief  Note: motor 4 using lift mechanism and motor 3 using rotate mechanism
    	 *  @param  motor the motor to move
    	 *  @param  pwm_input pwm to control motor, 0-4096
    	 *  @param  dir direction of motor, 0: clockwise 1:counterclockwise
    	 */
	void run(Motor motor, int16_t pwm_input, bool dir);

	/*!
         *  @brief  Stop lift
         */
	void stop(Motor motor);

	/*!
    	 *  @brief  Note: motor 4 using lift mechanism and motor 3 using rotate mechanism
    	 *  @param  motor the motor
    	 *  @param  status: LIFT_UP, LIFT_DOWN or LIFT_STOP
    	 *  @param  pwm_input pwm to control motor, 0-4096
    	 */
	void lift(Motor motor, MotorOperation status,
		  int16_t pwm_input); //up, down or stop
};

class ServoDriver {
	int servoList[6] = { Servo1, Servo2, Servo3, Servo4, Servo5, Servo6 };
	int pwm_val;
	float T_on;
	float T_ON_90 = 1.5, T_ON_0 = 1.0, T_ON_180 = 2.0;
	float pwmServoCycleMilis =
		20; // Cycle of PWM control servo. Set to 20ms or 50Hz.
	// T_ON_90 is time in ms to control servo in 90 degree.Ts is cycle of PWM control servo: 20ms ~ freq: 50Hz

    public:
	static void initialize();

	/*!
	 *  @brief  Control angle of servo function
	 *  @param  angle	angle of motor, 0-180. If servo 360, 0 is CW, 180 is CCW, 90 is stop
	 *  @param  servo_num	servo ID
	 */
	void setAngle(int angle, int servo_num) const;
	void stop(int servo_num) const;
};

void scani2c();
#endif