#ifndef TECH_LOG_H
#define TECH_LOG_H

#include "../config/tech_features.h"
#include "../shared/tech_include.h"

#ifdef __cplusplus
    extern "C" {
#endif

enum tech_log_style_t{
    TECH_LOG_STYLE_NONE = 0b00000,
    TECH_LOG_STYLE_CLOCK = 0b10000,
    TECH_LOG_STYLE_YEAR = 0b01000,
    TECH_LOG_STYLE_MONTH = 0b00100,
    TECH_LOG_STYLE_DAY = 0b00010,
    TECH_LOG_STYLE_DAY_NAME = 0b00001
};

void tech_log(FILE* output_file,enum tech_log_style_t style, const char* display_string, ...);


#ifdef __cplusplus
    }
#endif

#endif // TECH_LOG_H