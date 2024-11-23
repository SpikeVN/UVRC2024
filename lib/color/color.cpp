/*
 *  mccolor: a bug-driven terminal graphic lirary.
 *  Copyright (c) 2023 SpikeBonjour.
 *
 *  This program is free software. It comes without any warranty, to
 *  the extent permitted by applicable law. You can redistribute it
 *  and/or modify it under the terms of the Do What the Fuck You Want
 *  to Public License, Version 2, as published by Sam Hocevar. See
 *  http://www.wtfpl.net/ for more details.
 */

#include "color.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define true 1
#define false 0

const char *getColor(const char color)
{
	switch (color) {
	case '0':
		return COLOR_BLACK;
	case '1':
		return COLOR_BLUE;
	case '2':
		return COLOR_GREEN;
	case '3':
		return COLOR_CYAN;
	case '4':
		return COLOR_RED;
	case '5':
		return COLOR_MAGENTA;
	case '6':
		return COLOR_YELLOW;
	case '7':
		return COLOR_GRAY;
	case '8':
		return COLOR_GRAY;
	case '9':
		return COLOR_BLUE;
	case 'a':
		return COLOR_BRIGHT_GREEN;
	case 'b':
		return COLOR_BRIGHT_CYAN;
	case 'c':
		return COLOR_BRIGHT_RED;
	case 'd':
		return COLOR_BRIGHT_MAGENTA;
	case 'e':
		return COLOR_BRIGHT_YELLOW;
	case 'f':
		return COLOR_WHITE;
	case 'r':
		return FM_RESET;
	case 'l':
		return FM_BOLD;
	case 'n':
		return FM_UNDERLINE;

	default:
		return "";
	}
}

char *colorizeesc(const char *input, const char escChar)
{
	size_t inputLength = strlen(input);
	int length = 0;
	int currentAlloc = inputLength + 50;
	char *output = malloc(currentAlloc);
	int encSpecialChar = false;
	for (int i = 0; i < inputLength; i++) {
		char currentChar = input[i];
		if (currentChar == escChar) {
			encSpecialChar = true;
			continue;
		}

		if (encSpecialChar) {
			length += 7;
		} else {
			length += 1;
		}

		if (length >= currentAlloc) {
			char *newoutput = malloc(length + 20);
			strcpy(newoutput, output);
			free(output);
			output = newoutput;
		}

		if (encSpecialChar) {
			char *color = getColor(currentChar);
			strcat(output, color);
			encSpecialChar = false;
		} else {
			strncat(output, &currentChar, 1);
		}
	}
	return output;
}

char *colorize(char *input)
{
	return colorizeesc(input, '&');
}