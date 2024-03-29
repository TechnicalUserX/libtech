#ifndef TECH_TOOL_H
#define TECH_TOOL_H

#include <tech/config/features.h>
#include <tech/shared/include.h>
#include <tech/shared/types.h>

#include <tech/util/include/error.h>


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

tech_return_t tech_tool_fd_check_available_data(int fd, bool* check, struct timeval to);

tech_return_t tech_tool_file_basename(const char* path, tech_size_t path_size, char* basename, tech_size_t basename_size);

tech_return_t tech_tool_file_dirname(const char* path, tech_size_t path_size, char* dirname, tech_size_t dirname_size);

tech_return_t tech_tool_endian_reverse_byte_order(tech_byte_t* bytes, tech_size_t byte_size);


#ifdef __cplusplus
    }
#endif

#endif