 //===================================================================================================//
/**
 *  WRITER: TechnicaluserX
 * 
 *  VERSION: 1.0.0
 *  
 *  DESCRIPTION: Prints text onto the screen with time stamps.
 *  
 *  LICENSE: This library is not currently under any license and it is free to modify/distribute. 
 * 
 */
 //===================================================================================================//


#ifndef _TECHLIB_LOG_H
#define _TECHLIB_LOG_H

#define TECHLIB_WINDLL_API __declspec(dllexport)

#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <stdarg.h>



// Logging functions

TECHLIB_WINDLL_API void techlib_log_ascii(const char* display_string, ...);

TECHLIB_WINDLL_API void techlib_log_widechar(const wchar_t* display_string, ...);

#endif