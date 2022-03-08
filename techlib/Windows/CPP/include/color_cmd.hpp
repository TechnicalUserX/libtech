 //===================================================================================================//
/**
 *  WRITER: TechnicaluserX
 *  
 *  DESCRIPTION: C Library for color text printing.
 *  
 *  LICENSE: This library is not currently under any license and it is free to modify/distribute. 
 * 
 */
 //===================================================================================================//


#ifndef _TECHLIB_COLOR_CMD_H
#define _TECHLIB_COLOR_CMD_H

#define TECHLIB_WINDLL_API __declspec(dllexport)


#include <windows.h>

namespace techlib{
namespace color{
	
	WORD WHITE_B = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
	WORD WHITE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
	WORD BLACK_B = 0;


	WORD LGRAY_B = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
	WORD GRAY_B = BACKGROUND_INTENSITY;
	WORD GRAY = FOREGROUND_INTENSITY;
	WORD LGRAY = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

	WORD BLUE_B = BACKGROUND_BLUE;
	WORD BLUE = FOREGROUND_BLUE;
	WORD LBLUE_B = BACKGROUND_BLUE | BACKGROUND_INTENSITY;
	WORD LBLUE = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
	
	WORD GREEN_B = BACKGROUND_GREEN;
	WORD GREEN = FOREGROUND_GREEN;
	WORD LGREEN_B = BACKGROUND_GREEN | BACKGROUND_INTENSITY;
	WORD LGREEN = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	
	WORD RED_B = BACKGROUND_RED;
	WORD RED = FOREGROUND_RED;
	WORD LRED_B = BACKGROUND_RED | BACKGROUND_INTENSITY;
	WORD LRED = FOREGROUND_RED | FOREGROUND_INTENSITY;
	
	WORD AQUA_B = BACKGROUND_BLUE | BACKGROUND_GREEN;
	WORD AQUA = FOREGROUND_BLUE | FOREGROUND_GREEN;
	WORD LAQUA_B = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
	WORD LAQUA = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;	
	
	WORD YELLOW_B = BACKGROUND_RED | BACKGROUND_GREEN;
	WORD YELLOW = FOREGROUND_RED | FOREGROUND_GREEN;
	WORD LYELLOW_B = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
	WORD LYELLOW = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;	
	
	WORD PURPLE_B = BACKGROUND_RED | BACKGROUND_BLUE;
	WORD PURPLE = FOREGROUND_RED | FOREGROUND_BLUE;
	WORD LPURPLE_B = BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
	WORD LPURPLE = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;

    TECHLIB_WINDLL_API void color(WORD color);
	
};
};
	
#endif
