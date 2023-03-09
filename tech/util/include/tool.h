#ifndef TECH_TOOL_H
#define TECH_TOOL_H

#include <tech/config/features.h>
#include <tech/shared/include.h>
#include <tech/shared/types.h>

#ifdef __cplusplus
    extern "C" {
#endif

#ifdef __cplusplus
    #define TECH_TOOL_CHECK_TYPE(var, type) (typeid(var) == typeid(type))
#else
    #define TECH_TOOL_CHECK_TYPE(var, type) (__builtin_types_compatible_p(__typeof(var), type))
#endif


#define TECH_TOOL_STRINGIZE(x) #x

tech_byte_t tech_tool_convert_truecolor_to_xterm256(int r, int g, int b);

tech_byte_t tech_tool_convert_xterm256_to_xterm16(tech_byte_t color);

tech_size_t tech_tool_multibyte_length(const char* stream);

void tech_tool_hexdump(void* address, int size, int line);

#ifdef __cplusplus
    }
#endif

#endif