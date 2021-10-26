#include "../include/color_cmd.h"

TECHLIB_WINDLL_API void color(WORD color){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
    return;
}