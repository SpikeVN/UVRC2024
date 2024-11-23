#include "peripherals.h"
#include "aio.h"
#include "globals.h"
#include <drive.h>
#include <journal.h>
#include <ps2x.h>

#define MOTOR_GATHER Motor1

enum MotorDirection { GET_BALL = 1, RELEASE_BALL = 0 };

const auto logger = Log("perp");

Future spinAngleAsync(const ServoDriver *driver, const Servo servo,
		      const int angle)
{
	int pwmAngle = 0;
	if (angle < 0) {
		pwmAngle = 180;
	} else if (angle > 0) {
		pwmAngle = 0;
	} else {
		pwmAngle = 90;
	}
	const auto a = Future(driver, servo, pwmAngle, 1000 * angle / 180);
	return a;
}

void Peripherals::processInput(EventLoop eventLoop, PS2X controller,
			       MotorDriver mDriver, ServoDriver sDriver)
{
	if (controller.Button(PSB_L1) || controller.Button(PSB_R1)) {
		logger.debug("L1 or R1 pressed.");
		mDriver.run(MOTOR_GATHER, SPEED_MAX, GET_BALL);
	} else if (controller.Button(PSB_L2) || controller.Button(PSB_R2)) {
		logger.debug("L2 or R2 pressed.");
		mDriver.run(MOTOR_GATHER, SPEED_MAX, RELEASE_BALL);
	} else {
		mDriver.stop(MOTOR_GATHER);
	}

	if (controller.Button(PSB_CIRCLE)) {
		logger.debug("circle");
		// eventLoop.addTask(spinAngleAsync(&sDriver, Servo1, 90));
		sDriver.execute(Servo1, 50);
		delay(20);
		sDriver.stop(Servo1);

	} else if (controller.Button(PSB_SQUARE)) {
		logger.debug("square");
		sDriver.execute(Servo1, 150);
		delay(20);
		// delay(1000 * 90 / 180);
		sDriver.stop(Servo1);
	}
}
