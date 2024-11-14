#include "journal.h"
#include <Arduino.h>
#include <string>

Log::Log(const char *name)
{
	this->lname = name;
}

void Log::logf(const char *format, ...) const
{
	char *output = nullptr;
	va_list args;
	asprintf(&output, "[%s] ", this->lname);

	va_start(args, format);
	if (0 > vasprintf(&output, format, args))
		// this is for logging, so failed allocation is not fatal
		output = nullptr;
	va_end(args);

	if (output) {
		Serial.println(output);
		free(output);
	}
}

void Log::debug(const char *format, ...) const
{
	char *output = nullptr;
	va_list args;
	asprintf(&output, "[%s DEBUG] ", this->lname);
	va_start(args, format);
	if (0 > vasprintf(&output, format, args))
		// this is for logging, so failed allocation is not fatal
		output = nullptr;
	va_end(args);

	if (output) {
		Serial.println(output);
		free(output);
	}
}

void Log::info(const char *format, ...) const
{
	char *output = nullptr;
	va_list args;
	asprintf(&output, "[%s INFO] ", this->lname);
	va_start(args, format);
	if (0 > vasprintf(&output, format, args))
		// this is for logging, so failed allocation is not fatal
		output = nullptr;
	va_end(args);

	if (output) {
		Serial.println(output);
		free(output);
	}
}

void Log::ok(const char *format, ...) const
{
	char *output = nullptr;
	va_list args;

	asprintf(&output, "[%s OK] ", this->lname);
	va_start(args, format);
	if (0 > vasprintf(&output, format, args))
		// this is for logging, so failed allocation is not fatal
		output = nullptr;
	va_end(args);

	if (output) {
		Serial.println(output);
		free(output);
	}
}

void Log::warning(const char *format, ...) const
{
	char *output = nullptr;
	va_list args;

	asprintf(&output, "[%s WARN] ", this->lname);
	va_start(args, format);
	if (0 > vasprintf(&output, format, args))
		// this is for logging, so failed allocation is not fatal
		output = nullptr;
	va_end(args);

	if (output) {
		Serial.println(output);
		free(output);
	}
}

void Log::error(const char *format, ...) const
{
	char *output = nullptr;
	va_list args;

	asprintf(&output, "[%s ERROR] ", this->lname);
	va_start(args, format);
	if (0 > vasprintf(&output, format, args))
		// this is for logging, so failed allocation is not fatal
		output = nullptr;
	va_end(args);

	if (output) {
		Serial.println(output);
		free(output);
	}
}