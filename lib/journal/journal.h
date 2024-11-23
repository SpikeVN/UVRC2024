/**
 * Journaling and logging utility functions
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

#ifndef JOURNAL_H
#define JOURNAL_H

#include <string>

class Log {
	const char *lname;

    public:
	explicit Log(const char *name);

	/**
         *  Logs to the serial output.
         */
	void logf(const char *format, ...) const
		// C++ has implicit this argument
		__attribute__((format(printf, 2, 3)));


	void debug(const char *format, ...) const
		__attribute__((format(printf, 2, 3)));

	void info(const char *format, ...) const
		__attribute__((format(printf, 2, 3)));

	void ok(const char *format, ...) const
		__attribute__((format(printf, 2, 3)));

	void warning(const char *format, ...) const
		__attribute__((format(printf, 2, 3)));

	void error(const char *format, ...) const
		__attribute__((format(printf, 2, 3)));
};

#endif //JOURNAL_H
