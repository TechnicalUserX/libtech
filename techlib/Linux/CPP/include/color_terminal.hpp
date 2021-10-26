 //===================================================================================================//
/**
 *  WRITER: TechnicaluserX
 * 
 *  VERSION: 1.0.0
 *  
 *  DESCRIPTION: Prints colorful output to the UNIX/Linux terminal.
 *  
 *  LICENSE: This library is not currently under any license and it is free to modify/distribute. 
 * 
 */
 //===================================================================================================//


#ifndef _TECHLIB_COLOR_TERMINAL_HPP
#define _TECHLIB_COLOR_TERMINAL_HPP

#include <cstdio>
#include <cstring>


namespace techlib{
namespace color{

	#define COLOR "\033["
	#define RESET "0;"
	#define BOLD "1;"
	#define UNDERLINE "4;"
	#define INVERSE "7;"
	#define BOLDOFF "21;"
	#define UNDERLINEOFF "24;"
	#define INVERSEOFF "27;"
	#define CLEAR "\033[0m"
	
	#define BLACK "30m"
	#define RED "31m"
	#define GREEN "32m"
	#define YELLOW "33m"
	#define BLUE "34m"
	#define MAGENTA "35m"
	#define CYAN "36m"
	#define WHITE "37m"
	
	#define COLOR256 "38;5;"

	#define BLACK_B "40;"
	#define RED_B "41;"
	#define GREEN_B "42;"
	#define YELLOW_B "43;"
	#define BLUE_B "44;"
	#define MAGENTA_B "45;"
	#define CYAN_B "46;"
	#define WHITE_B "47;"
	#define GRAY_B "100;"
	#define LRED_B "101;"
	#define LGREEN_B "102;"
	#define LYELLOW_B "103;"
	#define LBLUE_B "104;"
	#define LPURPLE "105;"
	#define TEAL_B "106;"
	
	void test_256_colors(void);

};
};

#endif