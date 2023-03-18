#ifndef TECH_LOG_H
#define TECH_LOG_H

#include <tech/config/features.h>
#include <tech/shared/include.h>

#ifdef __cplusplus
extern "C"
{
#endif

    typedef enum tech_log_style_enum_t
    {
        TECH_LOG_STYLE_NONE = 0b00000,
        TECH_LOG_STYLE_CLOCK = 0b10000,
        TECH_LOG_STYLE_YEAR = 0b01000,
        TECH_LOG_STYLE_MONTH = 0b00100,
        TECH_LOG_STYLE_DAY = 0b00010,
        TECH_LOG_STYLE_DAY_NAME = 0b00001
    }tech_log_style_t;

    void tech_log(FILE *output_file, tech_log_style_t style, const char *display_string, ...);

#ifdef __cplusplus
}
#endif

#endif // TECH_LOG_H