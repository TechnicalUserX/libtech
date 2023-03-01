#ifndef TECH_ERROR_H
#define TECH_ERROR_H

#include <tech/config/tech_features.h>
#include <tech/shared/tech_include.h>
#include <tech/shared/tech_types.h>


#ifdef __cplusplus
extern "C"
{
#endif


    enum tech_error_t
    {
        TECH_SUCCESS = 0,
        TECH_ERROR_NULL_POINTER,
        TECH_ERROR_SIZE_ZERO,
        TECH_ERROR_CANNOT_FFLUSH,
        TECH_ERROR_INVALID_ARGUMENT,
        TECH_ERROR_CANNOT_ALLOC_MEMORY,
        TECH_ERROR_TERMINAL_PRINT_FAILED,
        TECH_ERROR_TERMINAL_STDIN_BUFFER_CHECK_FAIL,
        TECH_ERROR_TERMINAL_STDIN_GET_CHAR_FAILED,
        TECH_ERROR_TERMINAL_STDIN_GET_BYTE_FAILED,
        TECH_ERROR_TERMINAL_MODE_CANNOT_SET,
        TECH_ERROR_TERMINAL_MODE_CANNOT_GET,
        TECH_ERROR_TERMINAL_CURSOR_POSITION_CANNOT_GET,
        TECH_ERROR_TERMINAL_ATTRIBUTE_CANNOT_SET,
        TECH_ERROR_THREAD_SAFE_BLOCK_UNEXPECTED_EXIT,
        TECH_ERROR_THREAD_SAFE_BLOCK_GLOBAL_CANNOT_LOCK,
        TECH_ERROR_THREAD_SAFE_BLOCK_GLOBAL_CANNOT_UNLOCK,
        TECH_ERROR_TERMINAL_SIGNAL_NOT_FOUND
    };

    extern tech_thread_local_t enum tech_error_t tech_error_number;

    const char *tech_error_what(enum tech_error_t error);

#ifdef __cplusplus
}
#endif

#endif // TECH_ERROR_H