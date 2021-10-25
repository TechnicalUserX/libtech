#ifndef _TECHLIB_LOG_H
#define _TECHLIB_LOG_H

#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <stdarg.h>



// Logging functions

void techlib_log_ascii(const char* display_string, ...);

void techlib_log_widechar(const wchar_t* display_string, ...);

#endif