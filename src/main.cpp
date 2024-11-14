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

#include <Arduino.h>
#include <drive.h>
#include <globals.h>
#include <journal.h>
#include <ps2x.h>

// Globals
PS2X Controller;
MotorDriver MDriver;
ServoDriver SDriver;

void loop()
{
	MDriver.run()
}

void setup()
{
	const auto log = Log("setup");
	Serial.begin(9600);
	log.info("Initializing...");

	for (int i = 0; i < 10; i++) {
		delay(100);
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
	}

	MotorDriver::initialize();
	ServoDriver::initialize();
	log.ok("Setup complete.");
}