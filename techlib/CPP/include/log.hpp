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
enum style{
    TECHLIB_LOG_STYLE_NONE = 0b00000,
    TECHLIB_LOG_STYLE_CLOCK = 0b10000,
    TECHLIB_LOG_STYLE_YEAR = 0b01000,
    TECHLIB_LOG_STYLE_MONTH = 0b00100,
    TECHLIB_LOG_STYLE_DAY = 0b00010,
    TECHLIB_LOG_STYLE_DAY_NAME = 0b00001
};

void log(enum techlib::log::style style, const char* display_string, ...);


};
};
#endif