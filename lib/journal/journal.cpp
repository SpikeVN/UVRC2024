#include "journal.h"
#include <Arduino.h>
#include <string>

Log::Log(const char *name)
{
	this->lname = name;
}

void Log::logf(const char *format, ...) const
{
	char *prefix = nullptr;
	char *output = nullptr;
	va_list args;
	asprintf(&prefix, "[%s] ", this->lname);

	va_start(args, format);
	if (0 > asprintf(&output, format, args))
		// this is for logging, so failed allocation is not fatal
		output = nullptr;
	va_end(args);

	if (output) {
		Serial.print(prefix);
		Serial.println(output);
		free(output);
	}
}

void Log::debug(const char *format, ...) const
{
	char *prefix = nullptr;
	char *output = nullptr;
	va_list args;
	asprintf(&prefix, "[%s DEBUG] ", this->lname);
	va_start(args, format);
	if (0 > asprintf(&output, format, args))
		// this is for logging, so failed allocation is not fatal
		output = nullptr;
	va_end(args);

	if (output) {
		Serial.print(prefix);
		Serial.println(output);
		free(output);
	}
}

void Log::info(const char *format, ...) const
{
	char *prefix = nullptr;
	char *output = nullptr;
	va_list args;
	asprintf(&prefix, "[%s INFO] ", this->lname);
	va_start(args, format);
	if (0 > asprintf(&output, format, args))
		// this is for logging, so failed allocation is not fatal
		output = nullptr;
	va_end(args);

	if (output) {
		Serial.print(prefix);
		Serial.println(output);
		free(output);
	}
}

void Log::ok(const char *format, ...) const
{
	char *prefix = nullptr;
	char *output = nullptr;
	va_list args;

	asprintf(&prefix, "[%s OK] ", this->lname);
	va_start(args, format);
	if (0 > asprintf(&output, format, args))
		// this is for logging, so failed allocation is not fatal
		output = nullptr;
	va_end(args);

	if (output) {
		Serial.print(prefix);
		Serial.println(output);
		free(output);
	}
}

void Log::warning(const char *format, ...) const
{
	char *prefix = nullptr;
	char *output = nullptr;
	va_list args;

	asprintf(&prefix, "[%s WARN] ", this->lname);
	va_start(args, format);
	if (0 > asprintf(&output, format, args))
		// this is for logging, so failed allocation is not fatal
		output = nullptr;
	va_end(args);

	if (output) {
		Serial.print(prefix);
		Serial.println(output);
		free(output);
	}
}

void Log::error(const char *format, ...) const
{
	char *prefix = nullptr;
	char *output = nullptr;
	va_list args;

	asprintf(&prefix, "[%s ERROR] ", this->lname);
	va_start(args, format);
	if (0 > asprintf(&output, format, args))
		// this is for logging, so failed allocation is not fatal
		output = nullptr;
	va_end(args);

	if (output) {
		Serial.print(prefix);
		Serial.println(output);
		free(output);
	}
}