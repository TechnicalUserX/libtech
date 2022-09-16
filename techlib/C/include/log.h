#ifndef _TECHLIB_LOG_H
#define _TECHLIB_LOG_H

#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <stdarg.h>
#include <stdbool.h>

enum techlib_log_style{
    TECHLIB_LOG_STYLE_NONE = 0b00000,
    TECHLIB_LOG_STYLE_CLOCK = 0b10000,
    TECHLIB_LOG_STYLE_YEAR = 0b01000,
    TECHLIB_LOG_STYLE_MONTH = 0b00100,
    TECHLIB_LOG_STYLE_DAY = 0b00010,
    TECHLIB_LOG_STYLE_DAY_NAME = 0b00001
};

void techlib_log(enum techlib_log_style style, const char* display_string, ...);


#endif