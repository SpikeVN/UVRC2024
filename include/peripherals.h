#ifndef PERIPHERALS_H
#define PERIPHERALS_H

#include "aio.h"
#include <drive.h>
#include <ps2x.h>

class Peripherals {
    public:
	static void processInput(EventLoop eventLoop, PS2X controller,
				 MotorDriver mDriver, ServoDriver sDriver);
};

#endif