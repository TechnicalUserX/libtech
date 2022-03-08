 //===================================================================================================//
/**
 *  WRITER: TechnicaluserX
 *  
 *  DESCRIPTION: Prints text onto the screen with time stamps.
 *  
 *  LICENSE: This library is not currently under any license and it is free to modify/distribute. 
 * 
 */
 //===================================================================================================//


#ifndef _TECHLIB_LOG_HPP
#define _TECHLIB_LOG_HPP

#define TECHLIB_WINDLL_API __declspec(dllexport)


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
TECHLIB_WINDLL_API void log_ascii(const char* display_string, ...);

// Prints Wide Character
TECHLIB_WINDLL_API void log_widechar(const wchar_t* display_string, ...);


};
};
#endif
