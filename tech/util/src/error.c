#include <tech/util/include/thread.h>
#include <tech/util/include/error.h>

tech_thread_local_t enum tech_error_t tech_error_number;

const char *tech_error_what(enum tech_error_t error)
{

    switch (error)
    {
    case TECH_SUCCESS:
        return "Success";

    case TECH_ERROR_GENERIC_FAIL_ASSERTION:
        return "Generic failure assertion detected";

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

    case TECH_ERROR_BAD_SYSTEM_CALL:
        return "Bad system call";

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

    case TECH_ERROR_NETWORK_CANNOT_CREATE_SOCKET:
        return "Cannot create socket";

    case TECH_ERROR_NETWORK_ADAPTER_WIFI_MODE_UNKNOWN:
        return "Unknown wifi adapter mode";

    case TECH_ERROR_NETWORK_ADAPTER_WIFI_FREQUENCY_FLAG_UNKNOWN:    
        return "Unknown wifi adapter frequency flag";

    case TECH_ERROR_NETWORK_ADAPTER_WIFI_NO_CHANNEL_FOR_FREQUENCY:
        return "No channel matching for the given frequency";

    case TECH_ERROR_NETWORK_ADAPTER_NOT_FOUND:
        return "Network adapter not found";

    case TECH_ERROR_NETWORK_ADAPTER_CANNOT_SET_MODE:
        return "Cannot set network wifi adapter mode";

    case TECH_ERROR_NETWORK_ADAPTER_CANNOT_SET_OPERSTATE:
        return "Cannot set network wifi adapter operation state";

    case TECH_ERROR_NETWORK_ADAPTER_CANNOT_SET_CHANNEL:
        return "Cannot set network wifi adapter channel";


    case TECH_ERROR_TOOL_FD_CHECK_AVAILABLE_DATA_FAILED:
        return "Cannot check available data for the given file descriptor";

    default:
        return "Unkown error";
    }
}
