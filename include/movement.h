#ifndef MOVEMENT_H
#define MOVEMENT_H
#include <aio.h>
#include <drive.h>
#include <ps2x.h>

class Movement {
    public:
	static void processInput(EventLoop eventLoop, PS2X controller,
				 MotorDriver mDriver, ServoDriver sDriver);
};

#endif
