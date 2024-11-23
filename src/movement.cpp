#include "movement.h"
#include "globals.h"
#include <aio.h>
#include <journal.h>

int DEFAULT_SPEED = 1400;

auto LEFT_WHEEL = Motor3;
auto RIGHT_WHEEL = Motor2;
int16_t pwm_left = 0, pwm_right = 0;
bool dir_left = 0, dir_right = 0;

Log logger = Log("movement");

void CanCau(EventLoop eventLoop, PS2X controller, MotorDriver mDriver,
	    ServoDriver sDriver)
{
	int16_t ry = controller.Analog(PSS_RY);
	int16_t ly = controller.Analog(PSS_LY);

	// Denoise

	if (ry >= NOISE_JOYSTICK_UPPER || ry <= NOISE_JOYSTICK_LOWER) {
		ry = map(ry, 0, 255, DEFAULT_SPEED, -DEFAULT_SPEED);
	} else
		ry = 0;
	if (ly >= NOISE_JOYSTICK_UPPER || ly <= NOISE_JOYSTICK_LOWER) {
		ly = map(ly, 0, 255, DEFAULT_SPEED, -DEFAULT_SPEED);
	} else
		ly = 0;

	mDriver.run(LEFT_WHEEL, abs(ly), ly < 0);
	mDriver.run(RIGHT_WHEEL, abs(ry), ry < 0);

	Serial.printf("lm %d rm %d\n", ly, ry);
}

void MotCan(EventLoop eventLoop, PS2X controller, MotorDriver mDriver,
	    ServoDriver sDriver)
{
	int16_t val_RY, val_RX;
	val_RY = controller.Analog(PSS_RY);
	val_RX = controller.Analog(PSS_RX);

	// loc nhieu
	if (val_RY >= NOISE_JOYSTICK_UPPER || val_RY <= NOISE_JOYSTICK_LOWER) {
		val_RY = map(val_RY, 0, 255, DEFAULT_SPEED, -DEFAULT_SPEED);
	} else
		val_RY = 0;
	if (val_RX >= NOISE_JOYSTICK_UPPER || val_RX <= NOISE_JOYSTICK_LOWER) {
		val_RX = map(val_RX, 0, 255, DEFAULT_SPEED, -DEFAULT_SPEED) *
			 ROTATE_SPEED_SCALE;
	} else
		val_RX = 0;

	// Serial.printf("%d %d\n", val_RY, val_RX);

	// tinh toan

	if (val_RY >= 0) {
		pwm_left = val_RY - val_RX;
		pwm_right = val_RY + val_RX;
	}

	else {
		pwm_left = val_RY + val_RX;
		pwm_right = val_RY - val_RX;
	}

	if (abs(pwm_left) <= MIN_PWM)
		pwm_left = 0;
	if (abs(pwm_right) <= MIN_PWM)
		pwm_right = 0;

	if (pwm_right > DEFAULT_SPEED)
		pwm_right = DEFAULT_SPEED;
	if (pwm_right < -DEFAULT_SPEED)
		pwm_right = -DEFAULT_SPEED;

	if (pwm_left > DEFAULT_SPEED)
		pwm_left = DEFAULT_SPEED;
	if (pwm_left < -DEFAULT_SPEED)
		pwm_left = -DEFAULT_SPEED;

	if (pwm_left >= 0)
		dir_left = 0;
	else {
		dir_left = 1;
		pwm_left = -pwm_left;
	}
	if (pwm_right >= 0)
		dir_right = 0;
	else {
		dir_right = 1;
		pwm_right = -pwm_right;
	}

	// Serial.printf("%d %d\n", pwm_left, pwm_right);

	mDriver.run(LEFT_WHEEL, pwm_left, dir_left);
	mDriver.run(RIGHT_WHEEL, pwm_right, dir_right);

	// mDriver.run(LEFT_WHEEL, 500, 1);
	// mDriver.run(RIGHT_WHEEL, 500, 1);
}

void Movement::processInput(EventLoop eventLoop, PS2X controller,
			    MotorDriver mDriver, ServoDriver sDriver)
{
	MotCan(eventLoop, controller, mDriver, sDriver);
}
