#ifndef AIO_H_
#define AIO_H_
#include "drive.h"
#include <vector>

class Future {
	int angle;
	Servo servo;
	const ServoDriver *driver;
	unsigned long startTime = 0;
	unsigned long waitTime = 0;

    public:
	Future(const ServoDriver *driver, Servo servo, int angle,
	       unsigned long milis);
	int poll() const;
};

class EventLoop {
	std::vector<Future> activeFutures{};

    public:
	void poll();
	int addTask(const Future &task);
};

#endif // AIO_H_
