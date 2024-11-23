//
// Created by triph on 23/11/2024.
//

#ifndef MCCOLOR_H
#define MCCOLOR_H

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

#define COLOR_BLACK "\e[30m"
#define COLOR_RED "\e[31m"
#define COLOR_GREEN "\e[32m"
#define COLOR_YELLOW "\e[33m"
#define COLOR_BLUE "\e[34m"
#define COLOR_MAGENTA "\e[35m"
#define COLOR_CYAN "\e[36m"
#define COLOR_WHITE "\e[37m"

#define COLOR_BRIGHT_BLACK "\e[30;1m"
#define COLOR_GRAY "\e[30;1m"
#define COLOR_GREY "\e[30;1m"
#define COLOR_BRIGHT_RED "\e[31;1m"
#define COLOR_BRIGHT_GREEN "\e[32;1m"
#define COLOR_BRIGHT_YELLOW "\e[33;1m"
#define COLOR_BRIGHT_BLUE "\e[34;1m"
#define COLOR_BRIGHT_MAGENTA "\e[35;1m"
#define COLOR_BRIGHT_CYAN "\e[36;1m"
#define COLOR_BRIGHT_WHITE "\e[37;1m"

#define FM_RESET "\e[0m"
#define FM_BOLD "\e[1m"
#define FM_UNDERLINE "\e[4m"
#define FM_REVERSED "\e[7m"

/**
 * Translates Minecraft color codes into ASCII color codes.
 */
char *colorize(char *input);

/**
 * Translates Minecraft color codes into ASCII color codes.
 */
char *colorizeesc(char *input, char escChar);

#endif // MCCOLOR_H
