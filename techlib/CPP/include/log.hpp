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


#ifndef _TECHLIB_LOG_HPP
#define _TECHLIB_LOG_HPP

#include <cstdio>
#include <cwchar>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <ctime>
#include <cstdarg>

namespace techlib{
namespace log{


// Prints ASCII Character
void log_ascii(const char* display_string, ...);

// Prints Wide Character
void log_widechar(const wchar_t* display_string, ...);


};
};
#endif