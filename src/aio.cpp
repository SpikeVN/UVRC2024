#include "aio.h"

#include <esp32-hal.h>
#include <vector>

Future::Future(const ServoDriver *driver, Servo servo, int angle,
	       const unsigned long milis)
{
	this->angle = angle;
	this->servo = servo;
	this->driver = driver;
	this->startTime = millis();
	this->waitTime = milis;
}

int Future::poll() const
{
	if (millis() - this->startTime >= this->waitTime) {
		driver->execute(this->servo, angle);
		return true;
	}
	return false;
}

void EventLoop::poll()
{
	std::vector<int> removeList{};
	for (int i = 0; i < this->activeFutures.size(); i++) {
		if (this->activeFutures[i].poll()) {
			removeList.push_back(i);
		}
	}
	for (const int i : removeList) {
		this->activeFutures.erase(this->activeFutures.begin() + i);
	}
}

int EventLoop::addTask(const Future &task)
{
	this->activeFutures.push_back(task);
	return static_cast<int>(this->activeFutures.size()) - 1;
}
