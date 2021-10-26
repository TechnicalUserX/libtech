#include "../include/color_cmd.hpp"

namespace techlib{
namespace color{

TECHLIB_WINDLL_API void color(WORD color){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
    return;
}

};
};