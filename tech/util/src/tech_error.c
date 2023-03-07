#include <tech/util/include/tech_thread.h>
#include <tech/util/include/tech_error.h>

tech_thread_local_t enum tech_error_t tech_error_number;

const char *tech_error_what(enum tech_error_t error)
{

    switch (error)
    {
    case TECH_SUCCESS:
        return "Success";
    case TECH_ERROR_NULL_POINTER:
        return "NULL pointer detected";
    case TECH_ERROR_SIZE_ZERO:
        return "Provided size must not be zero";
    case TECH_ERROR_SIZE_EXCEED:
        return "Inteded size exceeded the limit";
    case TECH_ERROR_CANNOT_FFLUSH:
        return "fflush() failed";
    case TECH_ERROR_INVALID_ARGUMENT:
        return "Invalid argumenut was given";
    case TECH_ERROR_TERMINAL_PRINT_FAILED:
        return "Terminal print failed";
    case TECH_ERROR_TERMINAL_STDIN_BUFFER_CHECK_FAIL:
        return "Terminal stdin buffer check failed";
    case TECH_ERROR_TERMINAL_STDIN_GET_CHAR_FAILED:
        return "Terminal stdin get char failed";
    case TECH_ERROR_TERMINAL_STDIN_GET_BYTE_FAILED:
        return "Terminal stdin get byte failed";
    case TECH_ERROR_TERMINAL_MODE_CANNOT_SET:
        return "Terminal mode cannot be set";
    case TECH_ERROR_TERMINAL_MODE_CANNOT_GET:
        return "Terminal mode cannot be retrieved";
    case TECH_ERROR_TERMINAL_CURSOR_POSITION_CANNOT_GET:
        return "Terminal cannot get cursor position";
    case TECH_ERROR_TERMINAL_ATTRIBUTE_CANNOT_SET:
        return "Terminal attribute cannot be set";
    case TECH_ERROR_THREAD_SAFE_BLOCK_UNEXPECTED_EXIT:
        return "Thread exited unexpectedly";
    case TECH_ERROR_THREAD_SAFE_BLOCK_GLOBAL_CANNOT_LOCK:
        return "Thread global lock cannot be locked";
    case TECH_ERROR_THREAD_SAFE_BLOCK_GLOBAL_CANNOT_UNLOCK:
        return "Thread global lock cannot be unlocked";
    case TECH_ERROR_CANNOT_ALLOC_MEMORY:
        return "Cannot allocate memory";
    case TECH_ERROR_TERMINAL_SIGNAL_NOT_FOUND:
        return "Signal not found";
    default:
        return "Unkown error";
    }
}
