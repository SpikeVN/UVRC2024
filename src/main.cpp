/**
 * Source code for CBN Open Science's entry in UVRC 2024
 * Copyright (C) 2024 CBN Open Science
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "aio.h"
#include "globals.h"
#include "peripherals.h"
#include <Arduino.h>
#include <drive.h>
#include <journal.h>
#include <movement.h>
#include <ps2x.h>

// Globals
PS2X Controller;
MotorDriver MDriver;
ServoDriver SDriver;

Peripherals peripherals;
Movement movement;
EventLoop eventLoop;

void loop()
{
	Controller.read_gamepad(false, false);
	Peripherals::processInput(eventLoop, Controller, MDriver, SDriver);
	Movement::processInput(eventLoop, Controller, MDriver, SDriver);
	eventLoop.poll();
}

void setup()
{
	Serial.begin(9600);
	Serial.println("");
	const auto log = Log("setup");
	log.info("Initializing...");

	for (int i = 0; i < 10; i++) {
		const int ecode = Controller.config_gamepad(PS2_CLK, PS2_CMD,
							    PS2_SEL, PS2_DAT,
							    PS2_pressures,
							    PS2_rumble);
		if (!ecode) {
			log.ok("Controller connected");
			break;
		}
		log.warning(
			"Cannot connect to controller. Trying again in 100ms.");
		delay(100);
	}

	MotorDriver::initialize();
	ServoDriver::initialize();

	peripherals = Peripherals();
	movement = Movement();
	eventLoop = EventLoop();

	log.ok("Setup complete.");
}