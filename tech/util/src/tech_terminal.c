#include <tech/util/include/tech_terminal.h>
#include <tech/util/include/tech_thread.h>
#include <tech/util/include/tech_error.h>

// Flag list for all signals currently supported, internal
__attribute__((visibility("hidden"))) struct tech_terminal_signal_flag_list_struct_t{
    volatile sig_atomic_t tech_terminal_signal_resize_flag;
}tech_terminal_signal_flag_list = {0};


// internal declarations
__attribute__((visibility("hidden"))) tech_return_t tech_terminal_mode_internal(tech_terminal_mode_directive_t directive, ...);

__attribute__((visibility("hidden"))) tech_return_t tech_terminal_stdin_buffer_check_internal(bool *check);

__attribute__((visibility("hidden"))) tech_return_t tech_terminal_cursor_get_position_internal(tech_terminal_cursor_position_t *row, tech_terminal_cursor_position_t *col);

__attribute__((visibility("hidden"))) tech_return_t tech_terminal_stdout_print_internal(tech_terminal_cursor_position_t row, tech_terminal_cursor_position_t col, va_list *received_args, const char *format, ...);

__attribute__((visibility("hidden"))) tech_return_t tech_terminal_stdin_get_byte_internal(tech_byte_t *byte);

__attribute__((visibility("hidden"))) tech_return_t tech_terminal_stdin_get_char_internal(tech_terminal_char_t *terminal_char);

__attribute__((visibility("hidden"))) tech_return_t tech_terminal_cursor_set_position_internal(tech_terminal_cursor_position_t row, tech_terminal_cursor_position_t col);

__attribute__((visibility("hidden"))) tech_return_t tech_terminal_stdout_print_char_internal(tech_terminal_cursor_position_t row, tech_terminal_cursor_position_t col, tech_terminal_char_t terminal_char);

// internal definitions
__attribute__((visibility("hidden"))) tech_return_t tech_terminal_mode_internal(tech_terminal_mode_directive_t directive, ...)
{

    static struct termios tios_original = {0}; // Setting everything to zero, including padding bytes
    static struct termios tios_raw = {0};      // Setting everything to zero, including padding bytes
    static struct termios tios_saved = {0};    // Setting everything to zero, including padding bytes
    static tech_terminal_mode_t terminal_mode;
    static bool tios_configured = false;

    if (!tios_configured)
    {
        terminal_mode = TECH_TERMINAL_MODE_ORIGINAL;
        tcgetattr(STDIN_FILENO, &tios_original);
        tcgetattr(STDIN_FILENO, &tios_saved);
        tcgetattr(STDIN_FILENO, &tios_raw);
        cfmakeraw(&tios_raw);
        tios_configured = true;
    }

    switch (directive)
    {

    case TECH_TERMINAL_MODE_DIRECTIVE_GET:
    {

        va_list args;
        va_start(args, directive);

        tech_terminal_mode_t *mode = va_arg(args, tech_terminal_mode_t *);

        if (mode == NULL)
        {
            tech_error_number = TECH_ERROR_INVALID_ARGUMENT;
            return TECH_RETURN_FAILURE;
        }

        va_end(args);

        if (mode == NULL)
        {
            tech_error_number = TECH_ERROR_NULL_POINTER;
            return TECH_RETURN_FAILURE;
        }

        *mode = terminal_mode;
    }
    break;

    case TECH_TERMINAL_MODE_DIRECTIVE_SET:
    {

        va_list args;
        va_start(args, directive);

        if (args == NULL)
        {
            tech_error_number = TECH_ERROR_INVALID_ARGUMENT;
            return TECH_RETURN_FAILURE;
        }

        tech_terminal_mode_t mode = va_arg(args, tech_terminal_mode_t);
        va_end(args);

        switch (mode)
        {
        case TECH_TERMINAL_MODE_ORIGINAL:
            if (tcsetattr(STDIN_FILENO, TCSANOW, &tios_original) < 0)
            {
                tech_error_number = TECH_ERROR_TERMINAL_MODE_CANNOT_SET;
            }
            else
            {
                terminal_mode = TECH_TERMINAL_MODE_ORIGINAL;
                tech_error_number = TECH_SUCCESS;
            }
            break;
        case TECH_TERMINAL_MODE_RAW:
            if (tcsetattr(STDIN_FILENO, TCSANOW, &tios_raw) < 0)
            {
                tech_error_number = TECH_ERROR_TERMINAL_MODE_CANNOT_SET;
            }
            else
            {
                terminal_mode = TECH_TERMINAL_MODE_RAW;
                tech_error_number = TECH_SUCCESS;
            }
            break;

        case TECH_TERMINAL_MODE_SAVED:
        {
            if (tcsetattr(STDIN_FILENO, TCSANOW, &tios_saved) < 0)
            {
                tech_error_number = TECH_ERROR_TERMINAL_MODE_CANNOT_SET;
            }
            else
            {
                if (memcmp(&tios_saved, &tios_original, sizeof(struct termios)) == 0)
                {
                    terminal_mode = TECH_TERMINAL_MODE_ORIGINAL;
                }
                else if (memcmp(&tios_saved, &tios_raw, sizeof(struct termios)) == 0)
                {
                    terminal_mode = TECH_TERMINAL_MODE_RAW;
                }
                else
                {
                    terminal_mode = TECH_TERMINAL_MODE_SAVED;
                }
                tech_error_number = TECH_SUCCESS;
            }
        }
        break;

        default:
        {
            tech_error_number = TECH_ERROR_INVALID_ARGUMENT;
        }
        break;
        }
    }
    break;

    case TECH_TERMINAL_MODE_DIRECTIVE_SAVE:
    {
        if (tcgetattr(STDIN_FILENO, &tios_saved) < 0)
        {
            tech_error_number = TECH_ERROR_TERMINAL_MODE_CANNOT_GET;
        }
        else
        {
            tech_error_number = TECH_SUCCESS;
        }
    }
    break;

    default:
    {
        tech_error_number = TECH_ERROR_INVALID_ARGUMENT;
        return TECH_RETURN_SUCCESS;
    }
    }

    if (tech_error_number)
    {
        return TECH_RETURN_FAILURE;
    }
    else
    {
        return TECH_RETURN_SUCCESS;
    }
}

__attribute__((visibility("hidden"))) tech_return_t tech_terminal_stdin_buffer_check_internal(bool *check)
{

    if (check == NULL)
    {
        tech_error_number = TECH_ERROR_NULL_POINTER;
        return TECH_RETURN_SUCCESS;
    }

    bool buffer_available = false;

    struct timeval tv = {0L, 0L};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    buffer_available = (select(1, &fds, NULL, NULL, &tv));

    if (buffer_available > 0)
    {
        *check = true;
        tech_error_number = TECH_SUCCESS;
    }
    else if (buffer_available == 0)
    {
        *check = false;
        tech_error_number = TECH_SUCCESS;
    }
    else
    {
        tech_error_number = TECH_ERROR_TERMINAL_STDIN_BUFFER_CHECK_FAIL;
    }

    if (tech_error_number)
    {
        return TECH_RETURN_FAILURE;
    }
    else
    {
        return TECH_RETURN_SUCCESS;
    }
}

__attribute__((visibility("hidden"))) tech_return_t tech_terminal_cursor_get_position_internal(tech_terminal_cursor_position_t *row, tech_terminal_cursor_position_t *col)
{

    char buffer[32];

    tech_terminal_mode_internal(TECH_TERMINAL_MODE_DIRECTIVE_SAVE);
    tech_terminal_mode_internal(TECH_TERMINAL_MODE_DIRECTIVE_SET, TECH_TERMINAL_MODE_RAW);

    // Send ANSI escape sequence to retrieve cursor position
    fprintf(stdout, "\033[6n");
    fflush(stdout);
    // Read the response from the terminal
    int n_read = read(STDIN_FILENO, buffer, sizeof(buffer));

    if (n_read > 0)
    {
        sscanf(buffer, "\033[%hu;%huR", row, col);
    }
    else
    {
        tech_error_number = TECH_ERROR_TERMINAL_CURSOR_POSITION_CANNOT_GET;
    }

    // Revert terminal to its original state
    tech_terminal_mode_internal(TECH_TERMINAL_MODE_DIRECTIVE_SET, TECH_TERMINAL_MODE_SAVED);

    if (tech_error_number)
    {
        return TECH_RETURN_FAILURE;
    }
    else
    {
        return TECH_RETURN_SUCCESS;
    }
}

__attribute__((visibility("hidden"))) tech_return_t tech_terminal_stdout_print_internal(tech_terminal_cursor_position_t row, tech_terminal_cursor_position_t col, va_list *received_args, const char *format, ...)
{

    tech_terminal_cursor_set_position_internal(row, col);

    if (received_args == NULL)
    {
        va_list args;
        va_start(args, format);
        vfprintf(stdout, format, args);
        va_end(args);
    }
    else
    {
        vfprintf(stdout, format, *received_args);
    }
    fflush(stdout);

    return TECH_RETURN_SUCCESS;
}

__attribute__((visibility("hidden"))) tech_return_t tech_terminal_stdin_get_byte_internal(tech_byte_t *byte)
{

    if (byte == NULL)
    {
        tech_error_number = TECH_ERROR_NULL_POINTER;
        return TECH_RETURN_FAILURE;
    }

    ssize_t r;
    tech_byte_t c;
    if ((r = read(STDIN_FILENO, &c, sizeof(c))) < 0)
    {
        tech_error_number = TECH_ERROR_TERMINAL_STDIN_GET_BYTE_FAILED;
    }
    else
    {
        *byte = c;
        tech_error_number = TECH_SUCCESS;
    }

    if (tech_error_number)
    {
        return TECH_RETURN_FAILURE;
    }
    else
    {
        return TECH_RETURN_SUCCESS;
    }
}

__attribute__((visibility("hidden"))) tech_return_t tech_terminal_stdin_get_char_internal(tech_terminal_char_t *terminal_char)
{

    if (terminal_char == NULL)
    {
        tech_error_number = TECH_ERROR_NULL_POINTER;
        return TECH_RETURN_FAILURE;
    }

    tech_terminal_char_t terminal_char_temp;
    memset(&terminal_char_temp, 0x0, sizeof(terminal_char_temp));

    tech_byte_t initial_byte = 0x0;

    if (tech_terminal_stdin_get_byte_internal(&initial_byte) == TECH_RETURN_SUCCESS)
    {

        if ((initial_byte & 0b11111000) == 0b11110000)
        { // 1111 0000
            // 4 Byte UTF-8 Character
            terminal_char_temp.is_utf_8 = true;
            terminal_char_temp.byte_size = 4;
        }
        else if ((initial_byte & 0b11110000) == 0b11100000)
        { // 1110 0000
            // 3 Byte UTF-8 Character
            terminal_char_temp.is_utf_8 = true;
            terminal_char_temp.byte_size = 3;
        }
        else if ((initial_byte & 0b11100000) == 0b11000000)
        { // 1100 0000
            // 2 Byte UTF-8 Character
            terminal_char_temp.is_utf_8 = true;
            terminal_char_temp.byte_size = 2;
        }
        else if ((initial_byte & 0b11000000) == 0b10000000)
        { // 1000 0000
            // 1 Byte UTF-8 Character
            terminal_char_temp.is_utf_8 = true;
            terminal_char_temp.byte_size = 1;
        }
        else
        {
            // 1 Byte ASCII Character
            terminal_char_temp.is_utf_8 = false;
            terminal_char_temp.byte_size = 1;
        }

        terminal_char_temp.bytes[0] = initial_byte;

        bool byte_read_complete = true;



        if (terminal_char_temp.byte_size == 1 && (initial_byte <= 31 || initial_byte == 127))
        {
            // This is a control character
            terminal_char_temp.is_control = true;
            terminal_char_temp.is_printable = false;

            // Escape sequence check
            if (initial_byte == TECH_TERMINAL_CONTROL_CHAR_ESC)
            {

                bool stdin_buffer_check = false;
                if (tech_terminal_stdin_buffer_check_internal(&stdin_buffer_check) == TECH_RETURN_SUCCESS)
                {

                    if (stdin_buffer_check)
                    {
                        terminal_char_temp.is_escape_sequence = true;
                        // This is an escape sequence
                        uint8_t index = 1;

                        while (stdin_buffer_check)
                        {

                            // Read further escape sequence bytes

                            tech_byte_t byte = 0x0;

                            if (index >= TECH_TERMINAL_CHAR_BYTES_MAX_SIZE - 1)
                            {
                                // Last byte is internal for null terminator '\0'
                                // Maximum capacity has been reached for  terminal char type
                                // This is not a bug, this is a feature :)
                                break;
                            }

                            if (tech_terminal_stdin_get_byte_internal(&byte) == TECH_RETURN_SUCCESS)
                            {

                                // Byte read was successful
                                terminal_char_temp.bytes[index] = byte;
                                terminal_char_temp.byte_size++; // Increase byte size for every successfull read
                                index++;
                            }
                            else
                            {
                                // Byte read was unsuccessful
                                byte_read_complete = false;
                                break;
                            }

                            if (tech_terminal_stdin_buffer_check_internal(&stdin_buffer_check) == TECH_RETURN_FAILURE)
                            {
                                // Error getting stdin buffer info
                                byte_read_complete = false;
                                stdin_buffer_check = false;
                                break;
                            }
                        }
                    }
                    else
                    {
                        terminal_char_temp.is_escape_sequence = false;
                    }
                    terminal_char_temp.is_signal = false;
                }
                else
                {
                    tech_error_number = TECH_ERROR_TERMINAL_STDIN_BUFFER_CHECK_FAIL;
                }
            }
        }
        else
        {

            terminal_char_temp.is_printable = true;
            terminal_char_temp.is_control = false;
            terminal_char_temp.is_escape_sequence = false;

            // This for loop will work only for UTF-8 chars which are larger than 1 byte,
            // so this will be skipped for ASCII chars and 1 byte UTF-8 characters

            for (tech_size_t i = 0, index = 1; i < terminal_char_temp.byte_size - 1; i++, index++)
            {

                tech_byte_t b = 0x0;
                if (tech_terminal_stdin_get_byte_internal(&b) == TECH_RETURN_SUCCESS)
                {
                    terminal_char_temp.bytes[index] = b;
                }
                else
                {
                    byte_read_complete = false;
                    break;
                }
            }
        }

        if (byte_read_complete)
        {
            // Copy the bytes to the argument
            memset(terminal_char, 0x0, sizeof(tech_terminal_char_t));
            terminal_char->byte_size = terminal_char_temp.byte_size;
            for (size_t i = 0; i < TECH_TERMINAL_CHAR_BYTES_MAX_SIZE; i++)
            {
                terminal_char->bytes[i] = terminal_char_temp.bytes[i];
            }
            terminal_char->is_utf_8 = terminal_char_temp.is_utf_8;
            terminal_char->is_control = terminal_char_temp.is_control;
            terminal_char->is_printable = terminal_char_temp.is_printable;
            terminal_char->is_escape_sequence = terminal_char_temp.is_escape_sequence;
            terminal_char->bytes[TECH_TERMINAL_CHAR_BYTES_MAX_SIZE - 1] = 0x0; // Explicit null termination
            tech_error_number = TECH_SUCCESS;
        }
        else
        {
            tech_error_number = TECH_ERROR_TERMINAL_STDIN_GET_CHAR_FAILED;
        }
    }
    else
    {
        tech_error_number = TECH_ERROR_TERMINAL_STDIN_GET_CHAR_FAILED;
    }

    if (tech_error_number)
    {
        return TECH_RETURN_FAILURE;
    }
    else
    {
        return TECH_RETURN_SUCCESS;
    }
}

__attribute__((visibility("hidden"))) tech_return_t tech_terminal_cursor_set_position_internal(tech_terminal_cursor_position_t row, tech_terminal_cursor_position_t col)
{

    // If row or col is zero, then each one of them is kept constant

    if (row != 0 && col != 0)
    {
        if (fprintf(stdout, "\033[%d;%dH", row, col) < 0)
        {
            tech_error_number = TECH_ERROR_TERMINAL_PRINT_FAILED;
            return TECH_RETURN_FAILURE;
        }
    }
    else if (row == 0 && col != 0)
    {
        if (fprintf(stdout, "\033[%dG", col) < 0)
        {
            tech_error_number = TECH_ERROR_TERMINAL_PRINT_FAILED;
            return TECH_RETURN_FAILURE;
        }
    }
    else if (col == 0 && row != 0)
    {
        if (fprintf(stdout, "\033[%dd", row) < 0)
        {
            tech_error_number = TECH_ERROR_TERMINAL_PRINT_FAILED;
            return TECH_RETURN_FAILURE;
        }
    }

    if (fflush(stdout) < 0)
    {
        tech_error_number = TECH_ERROR_CANNOT_FFLUSH;
        return TECH_RETURN_FAILURE;
    }
    tech_error_number = TECH_SUCCESS;

    if (tech_error_number)
    {
        return TECH_RETURN_FAILURE;
    }
    else
    {
        return TECH_RETURN_SUCCESS;
    }
}

__attribute__((visibility("hidden"))) tech_return_t tech_terminal_set_attribute_internal(tech_terminal_attribute_t *attribute)
{

    tech_terminal_type_t type = tech_terminal_get_type();


    if (attribute == NULL)
    {
        tech_error_number = TECH_SUCCESS;
        return TECH_RETURN_SUCCESS;
    }

    tech_terminal_stdout_print_internal(0, 0, NULL, TECH_TERMINAL_ATTRIBUTE_CLEAR);

    // Needs to check color compatibility
    if (attribute->set_fg)
    {

        switch (type)
        {

            case TECH_TERMINAL_TYPE_UNKNOWN:
            {
                tech_error_number = TECH_ERROR_TERMINAL_ATTRIBUTE_CANNOT_SET;
                return TECH_RETURN_FAILURE;
            }
            break;

        case TECH_TERMINAL_TYPE_TRUECOLOR: // Also 24BIT
        {
            tech_terminal_stdout_print_internal(0, 0, NULL, "\033[38;2;%u;%u;%um", attribute->fg.red, attribute->fg.green, attribute->fg.blue);
            tech_error_number = TECH_SUCCESS;
        }
        break;

        case TECH_TERMINAL_TYPE_XTERM256:
        {
            tech_byte_t downgraded_color_256 = tech_tool_convert_truecolor_to_xterm256(attribute->fg.red, attribute->fg.green, attribute->fg.blue);
            tech_terminal_stdout_print_internal(0, 0, NULL, "\033[38;5;%um", downgraded_color_256);
            tech_error_number = TECH_SUCCESS;
        }
        break;

        case TECH_TERMINAL_TYPE_XTERM:
        {
            tech_byte_t downgraded_color_256 = tech_tool_convert_truecolor_to_xterm256(attribute->fg.red, attribute->fg.green, attribute->fg.blue);
            tech_byte_t downgraded_color_16 = tech_tool_convert_xterm256_to_xterm16(downgraded_color_256);

            tech_terminal_stdout_print_internal(0, 0, NULL, "\033[%um", 30 + (downgraded_color_16 % 8));

            tech_error_number = TECH_SUCCESS;
        }
        break;
        }
    }

    // Needs to check color compatibility
    if (attribute->set_bg)
    {

        switch (type)
        {


        case TECH_TERMINAL_TYPE_UNKNOWN:
        {
            tech_error_number = TECH_ERROR_TERMINAL_ATTRIBUTE_CANNOT_SET;
            return TECH_RETURN_FAILURE;
        }
        break;

        case TECH_TERMINAL_TYPE_TRUECOLOR: // Also 24BIT
        {
            tech_terminal_stdout_print_internal(0, 0, NULL, "\033[48;2;%u;%u;%um", attribute->bg.red, attribute->bg.green, attribute->bg.blue);
            tech_error_number = TECH_SUCCESS;
        }
        break;

        case TECH_TERMINAL_TYPE_XTERM256:
        {
            tech_byte_t downgraded_color_256 = tech_tool_convert_truecolor_to_xterm256(attribute->bg.red, attribute->bg.green, attribute->bg.blue);
            tech_terminal_stdout_print_internal(0, 0, NULL, "\033[48;5;%um", downgraded_color_256);
            tech_error_number = TECH_SUCCESS;
        }
        break;

        case TECH_TERMINAL_TYPE_XTERM:
        {
            tech_byte_t downgraded_color_256 = tech_tool_convert_truecolor_to_xterm256(attribute->bg.red, attribute->bg.green, attribute->bg.blue);
            tech_byte_t downgraded_color_16 = tech_tool_convert_xterm256_to_xterm16(downgraded_color_256);

            tech_terminal_stdout_print_internal(0, 0, NULL, "\033[%um", 40 + (downgraded_color_16 % 8));

            tech_error_number = TECH_SUCCESS;
        }
        break;
        }
    }

    if (attribute->set_underline)
    {
        tech_terminal_stdout_print_internal(0, 0, NULL, TECH_TERMINAL_ATTRIBUTE_UNDERLINE);
    }

    if (attribute->set_bold)
    {
        tech_terminal_stdout_print_internal(0, 0, NULL, TECH_TERMINAL_ATTRIBUTE_BOLD);
    }

    if (attribute->set_italic)
    {
        tech_terminal_stdout_print_internal(0, 0, NULL, TECH_TERMINAL_ATTRIBUTE_ITALIC);
    }

    if (attribute->set_inverse)
    {
        tech_terminal_stdout_print_internal(0, 0, NULL, TECH_TERMINAL_ATTRIBUTE_INVERSE);
    }

    if (attribute->set_strikethrough)
    {
        tech_terminal_stdout_print_internal(0, 0, NULL, TECH_TERMINAL_ATTRIBUTE_STRIKETHROUGH);
    }

    return TECH_RETURN_SUCCESS;
}

__attribute__((visibility("hidden"))) tech_return_t tech_terminal_stdout_print_char_internal(tech_terminal_cursor_position_t row, tech_terminal_cursor_position_t col, tech_terminal_char_t terminal_char)
{

    if (tech_terminal_cursor_set_position_internal(row, col))
    {
        return TECH_RETURN_FAILURE;
    }

    tech_terminal_encoding_t encoding = tech_terminal_get_encoding();

    if (encoding == TECH_TERMINAL_ENCODING_UNKNOWN)
    {
        return TECH_RETURN_FAILURE;
    }

    if (encoding == TECH_TERMINAL_ENCODING_UTF_8)
    {
        fprintf(stdout, "%s", (char *)terminal_char.bytes);
    }
    else if(encoding == TECH_TERMINAL_ENCODING_ASCII)
    {
        if (terminal_char.is_utf_8)
        {
            fprintf(stdout, " ");
        }else{
            fprintf(stdout, "%s", (char *)terminal_char.bytes);

        }
    }
    fflush(stdout);
    tech_error_number = TECH_SUCCESS;
    return TECH_RETURN_SUCCESS;
}



// Signal to char converter
// If the signal flag is set, function returns a terminal char and returns TECH_RETURN_SUCCESS; else, return TECH_RETURN_FAILURE
__attribute__((visibility("hidden"))) tech_return_t tech_terminal_signal_translate(tech_terminal_char_t* terminal_char, tech_terminal_signal_t signal){


    if(terminal_char == NULL){
        tech_error_number = TECH_ERROR_NULL_POINTER;
        return TECH_RETURN_FAILURE;
    }

    tech_terminal_char_t terminal_char_temp = {0};
    terminal_char_temp.byte_size = 1;
    terminal_char_temp.is_control = false;
    terminal_char_temp.is_escape_sequence = false;
    terminal_char_temp.is_printable = false;
    terminal_char_temp.is_signal = false;
    terminal_char_temp.is_utf_8 = false;


    switch(signal){

        case TECH_TERMINAL_SIGNAL_RESIZE:{
            if (tech_terminal_signal_flag_list.tech_terminal_signal_resize_flag){
                terminal_char_temp.is_signal = true;    
                terminal_char_temp.bytes[0] = TECH_TERMINAL_SIGNAL_RESIZE;
                *terminal_char = terminal_char_temp;
                tech_terminal_signal_flag_list.tech_terminal_signal_resize_flag = false;
                return TECH_RETURN_SUCCESS;
            }else{
                tech_error_number = TECH_ERROR_TERMINAL_SIGNAL_NOT_FOUND;
                return TECH_RETURN_FAILURE;
            }
        }break;



        default:{
            tech_error_number = TECH_ERROR_TERMINAL_SIGNAL_NOT_FOUND;
            return TECH_RETURN_FAILURE;
        }break;
    }

}


// TECH_TERMINAL_SIGNAL_RESIZE(SIGWINCH) Handler
__attribute__((visibility("hidden"))) void tech_terminal_signal_resize_handler_internal()
{
	tech_terminal_signal_flag_list.tech_terminal_signal_resize_flag = true;
}


tech_terminal_type_t tech_terminal_get_type(void)
{

    const char *colorterm = getenv("COLORTERM");

    if (colorterm)
    {
        if ((strcmp(colorterm, "truecolor") == 0 || strcmp(colorterm, "24bit") == 0))
        {
            return TECH_TERMINAL_TYPE_TRUECOLOR;
        }
    }

    const char *term = getenv("TERM");

    if (term == NULL)
    {
        return TECH_TERMINAL_TYPE_UNKNOWN;
    }
    else
    {
        if (strcmp(term, "xterm-256color") == 0)
        {
            return TECH_TERMINAL_TYPE_XTERM256;
        }
        else if (strcmp(term, "xterm") == 0)
        {
            return TECH_TERMINAL_TYPE_XTERM;
        }
        else
        {
            return TECH_TERMINAL_TYPE_UNKNOWN;
        }
    }
}

tech_terminal_encoding_t tech_terminal_get_encoding(void)
{

    const char *encoding_check_1 = nl_langinfo(CODESET);
    if (!encoding_check_1)
    {
        return TECH_TERMINAL_ENCODING_UNKNOWN;
    }
    if (strcmp(encoding_check_1, "UTF-8") == 0)
    {
        return TECH_TERMINAL_ENCODING_UTF_8;
    }

    const char *encoding_check_2 = setlocale(LC_ALL, NULL);

    if (!encoding_check_2)
    {
        return TECH_TERMINAL_ENCODING_UNKNOWN;
    }

    if (strcmp(encoding_check_2, "C") == 0 || strcmp(encoding_check_2, "POSIX") == 0)
    {
        return TECH_TERMINAL_ENCODING_ASCII;
    }

    return TECH_TERMINAL_ENCODING_UNKNOWN;
}

tech_return_t tech_terminal_set_attribute(tech_terminal_attribute_t *attribute)
{

    tech_return_t ret;
    TECH_THREAD_SAFE_BLOCK_GLOBAL_START(TECH_TERMINAL_STDOUT_LOCK)
    ret = tech_terminal_set_attribute_internal(attribute);
    TECH_THREAD_SAFE_BLOCK_GLOBAL_END(TECH_TERMINAL_STDOUT_LOCK)
    return ret;
}

tech_terminal_key_t tech_terminal_key_translate(tech_terminal_char_t terminal_char)
{

    if (terminal_char.byte_size == 0)
    {
        tech_error_number = TECH_ERROR_SIZE_ZERO;
        return TECH_TERMINAL_KEY_NOT_DETECTED;
    }

    if (terminal_char.is_escape_sequence && terminal_char.is_control)
    {
        // For now, only arrow keys are recognised

        if (terminal_char.bytes[1] == '[')
        {

            switch (terminal_char.bytes[2])
            {
            case 'A':
                return TECH_TERMINAL_KEY_UP;
            case 'B':
                return TECH_TERMINAL_KEY_DOWN;
            case 'C':
                return TECH_TERMINAL_KEY_RIGHT;
            case 'D':
                return TECH_TERMINAL_KEY_LEFT;
            case '3':
            {
                if (terminal_char.bytes[3] == '~')
                    return TECH_TERMINAL_KEY_DELETE;
            }
            break;

            default:
                return TECH_TERMINAL_KEY_NOT_DETECTED;
            }
        }

        return 0;
    }
    else if (terminal_char.is_printable)
    {
        return TECH_TERMINAL_KEY_PRINTABLE;
    }
    else if (terminal_char.is_signal){

        if (terminal_char.bytes[0] == TECH_TERMINAL_SIGNAL_RESIZE)
        {
            return TECH_TERMINAL_KEY_RESIZE;
        }
        else
        {
            return TECH_TERMINAL_KEY_NOT_DETECTED;
        }
    }
    else if (terminal_char.is_control){

        switch (terminal_char.bytes[0])
        {
        case TECH_TERMINAL_CONTROL_CHAR_DEL:
            return TECH_TERMINAL_KEY_BACKSPACE;

        case TECH_TERMINAL_CONTROL_CHAR_LF:

        case TECH_TERMINAL_CONTROL_CHAR_CR:
            return TECH_TERMINAL_KEY_ENTER;
        default:
            return TECH_TERMINAL_KEY_NOT_DETECTED;
        }
    }
    else
    {
        return TECH_TERMINAL_KEY_NOT_DETECTED;
    }
}

// Uses internal function
tech_return_t tech_terminal_cursor_get_position(tech_terminal_cursor_position_t *row, tech_terminal_cursor_position_t *col)
{

    tech_return_t ret;
    TECH_THREAD_SAFE_BLOCK_GLOBAL_START(TECH_TERMINAL_STDIN_LOCK);
    ret = tech_terminal_cursor_get_position_internal(row, col);
    TECH_THREAD_SAFE_BLOCK_GLOBAL_END(TECH_TERMINAL_STDIN_LOCK);

    TECH_THREAD_SAFE_BLOCK_FAIL_START
    tech_error_number = TECH_ERROR_THREAD_SAFE_BLOCK_UNEXPECTED_EXIT;
    return TECH_RETURN_FAILURE;
    TECH_THREAD_SAFE_BLOCK_FAIL_END

    return ret;
}

// Uses internal function
tech_return_t tech_terminal_cursor_set_position(tech_terminal_cursor_position_t row, tech_terminal_cursor_position_t col)
{

    tech_return_t ret;
    TECH_THREAD_SAFE_BLOCK_GLOBAL_START(TECH_TERMINAL_STDOUT_LOCK)
    ret = tech_terminal_cursor_set_position_internal(row, col);
    TECH_THREAD_SAFE_BLOCK_GLOBAL_END(TECH_TERMINAL_STDOUT_LOCK)

    TECH_THREAD_SAFE_BLOCK_FAIL_START
    tech_error_number = TECH_ERROR_THREAD_SAFE_BLOCK_UNEXPECTED_EXIT;
    return TECH_RETURN_FAILURE;
    TECH_THREAD_SAFE_BLOCK_FAIL_END

    return ret;
}

// Uses internal function
tech_return_t tech_terminal_mode(tech_terminal_mode_directive_t directive, ...)
{

    tech_return_t ret;

    TECH_THREAD_SAFE_BLOCK_GLOBAL_START(TECH_TERMINAL_STDIN_LOCK);
    va_list args;
    va_start(args, directive);
    switch (directive)
    {
    case TECH_TERMINAL_MODE_DIRECTIVE_SET:
    {
        tech_terminal_mode_t mode = va_arg(args, tech_terminal_mode_t);
        ret = tech_terminal_mode_internal(directive, mode);
    }
    break;

    case TECH_TERMINAL_MODE_DIRECTIVE_GET:
    {
        tech_terminal_mode_t *mode = va_arg(args, tech_terminal_mode_t *);
        ret = tech_terminal_mode_internal(directive, mode);
    }
    break;

    case TECH_TERMINAL_MODE_DIRECTIVE_SAVE:
    {
        ret = tech_terminal_mode_internal(directive);
    }
    break;
    }

    va_end(args);

    TECH_THREAD_SAFE_BLOCK_GLOBAL_END(TECH_TERMINAL_STDIN_LOCK);

    TECH_THREAD_SAFE_BLOCK_FAIL_START
        tech_error_number = TECH_ERROR_THREAD_SAFE_BLOCK_UNEXPECTED_EXIT;
        return TECH_RETURN_FAILURE;
    TECH_THREAD_SAFE_BLOCK_FAIL_END

    return ret;
}

// Uses internal function
tech_return_t tech_terminal_stdin_get_byte(tech_byte_t *byte)
{

    tech_return_t ret;

    TECH_THREAD_SAFE_BLOCK_GLOBAL_START(TECH_TERMINAL_STDIN_LOCK)
    ret = tech_terminal_stdin_get_byte_internal(byte);
    TECH_THREAD_SAFE_BLOCK_GLOBAL_END(TECH_TERMINAL_STDIN_LOCK)

    TECH_THREAD_SAFE_BLOCK_FAIL_START
    tech_error_number = TECH_ERROR_THREAD_SAFE_BLOCK_UNEXPECTED_EXIT;
    return TECH_RETURN_FAILURE;
    TECH_THREAD_SAFE_BLOCK_FAIL_END

    return ret;
}

// Uses internal function
tech_return_t tech_terminal_stdin_get_char(tech_terminal_char_t *terminal_char)
{
    if (terminal_char == NULL)
    {
        tech_error_number = TECH_ERROR_NULL_POINTER;
        return TECH_RETURN_FAILURE;
    }

    tech_return_t ret;

    TECH_THREAD_SAFE_BLOCK_GLOBAL_START(TECH_TERMINAL_STDIN_LOCK)
        ret = tech_terminal_stdin_get_char_internal(terminal_char);
    TECH_THREAD_SAFE_BLOCK_GLOBAL_END(TECH_TERMINAL_STDIN_LOCK)

    TECH_THREAD_SAFE_BLOCK_FAIL_START
        tech_error_number = TECH_ERROR_THREAD_SAFE_BLOCK_UNEXPECTED_EXIT;
        return TECH_RETURN_FAILURE;
    TECH_THREAD_SAFE_BLOCK_FAIL_END


    if (ret == TECH_RETURN_FAILURE)
    {
        // Will check signals here
        tech_terminal_char_t temp;
        if(tech_terminal_signal_translate(&temp,TECH_TERMINAL_SIGNAL_RESIZE) == TECH_RETURN_SUCCESS){
            *terminal_char = temp;
            return TECH_RETURN_SUCCESS;
        }

    }
    return TECH_RETURN_FAILURE;
}

// Uses internal function
tech_return_t tech_terminal_stdin_buffer_check(bool *check)
{

    tech_return_t ret;
    TECH_THREAD_SAFE_BLOCK_GLOBAL_START(TECH_TERMINAL_STDIN_LOCK)
    ret = tech_terminal_stdin_buffer_check_internal(check);
    TECH_THREAD_SAFE_BLOCK_GLOBAL_END(TECH_TERMINAL_STDIN_LOCK)

    TECH_THREAD_SAFE_BLOCK_FAIL_START
    tech_error_number = TECH_ERROR_THREAD_SAFE_BLOCK_UNEXPECTED_EXIT;
    return TECH_RETURN_FAILURE;
    TECH_THREAD_SAFE_BLOCK_FAIL_END

    return ret;
}

// Uses internal function
tech_return_t tech_terminal_stdin_buffer_consume(void)
{

    TECH_THREAD_SAFE_BLOCK_GLOBAL_START(TECH_TERMINAL_STDIN_LOCK);

    tech_byte_t b;

    while (1)
    {
        bool check = false;
        if (tech_terminal_stdin_buffer_check_internal(&check))
        {
            tech_error_number = TECH_ERROR_TERMINAL_STDIN_BUFFER_CHECK_FAIL;
            break;
        }
        if (check)
        {
            if (tech_terminal_stdin_get_byte_internal(&b))
            {
                tech_error_number = TECH_ERROR_TERMINAL_STDIN_GET_BYTE_FAILED;
            }
        }
        else
        {
            break;
        }
    }

    TECH_THREAD_SAFE_BLOCK_GLOBAL_END(TECH_TERMINAL_STDIN_LOCK);

    TECH_THREAD_SAFE_BLOCK_FAIL_START
    tech_error_number = TECH_ERROR_THREAD_SAFE_BLOCK_UNEXPECTED_EXIT;
    TECH_THREAD_SAFE_BLOCK_FAIL_END

    if (tech_error_number)
    {
        return TECH_RETURN_FAILURE;
    }
    else
    {
        return TECH_RETURN_SUCCESS;
    }
}

tech_return_t tech_terminal_stdin_get_string(tech_terminal_cursor_position_t row, tech_terminal_cursor_position_t col, tech_terminal_char_t *terminal_string, tech_size_t size)
{

    if (size == 0)
    {
        tech_error_number = TECH_ERROR_SIZE_ZERO;
        return TECH_RETURN_FAILURE;
    }
    if (terminal_string == NULL)
    {
        tech_error_number = TECH_ERROR_NULL_POINTER;
        return TECH_RETURN_FAILURE;
    }

    TECH_THREAD_SAFE_BLOCK_GLOBAL_START(TECH_TERMINAL_STDIN_LOCK)

    uint16_t init_row, init_col;

    // Set the cursor position, if one is zero, that position is kept same
    tech_terminal_cursor_set_position_internal(row, col);

    // Do not lock stdin, print escape sequence to retrieve cursor position
    // This is the position after set, this is the beginning
    tech_terminal_cursor_get_position_internal(&init_row, &init_col);

    // Create a temporary buffer
    tech_terminal_char_t terminal_string_temp[size];
    memset(terminal_string_temp, 0x0, size * sizeof(tech_terminal_char_t));

    tech_size_t string_cursor = 0;

    bool char_read_complete = false;
    tech_size_t acquired_string_size = 0;

    tech_terminal_mode_t mode;
    
    tech_terminal_mode_internal(TECH_TERMINAL_MODE_DIRECTIVE_GET, &mode);

    while (!char_read_complete)
    {
        tech_terminal_char_t terminal_char = {0};

        if (tech_terminal_stdin_get_char_internal(&terminal_char) == TECH_RETURN_SUCCESS)
        {

            switch (tech_terminal_key_translate(terminal_char))
            {

            case TECH_TERMINAL_KEY_LEFT:
            {
                if (mode == TECH_TERMINAL_MODE_RAW)
                {
                    if (string_cursor > 0)
                    {
                        string_cursor--;
                        tech_terminal_cursor_set_position_internal(init_row, init_col + string_cursor);
                    }
                }
            }
            break;

            case TECH_TERMINAL_KEY_RIGHT:
            {
                if (mode == TECH_TERMINAL_MODE_RAW)
                {

                    if (string_cursor < acquired_string_size)
                    {
                        string_cursor++;
                        tech_terminal_cursor_set_position_internal(init_row, init_col + string_cursor);
                    }
                }
            }
            break;

            case TECH_TERMINAL_KEY_DELETE:
            {
                if (mode == TECH_TERMINAL_MODE_RAW)
                {

                    if (string_cursor < acquired_string_size)
                    {
                        for (tech_size_t i = string_cursor; i < acquired_string_size - 1; i++)
                        {
                            terminal_string_temp[i] = terminal_string_temp[i + 1];
                        }
                        acquired_string_size--;

                        for (tech_size_t i = string_cursor; i < acquired_string_size; i++)
                        {
                            tech_terminal_stdout_print_internal(0, 0, NULL, "%s", (char *)terminal_string_temp[i].bytes);
                        }
                        tech_terminal_stdout_print_internal(init_row, init_col + acquired_string_size, NULL, " ");
                        tech_terminal_cursor_set_position_internal(init_row, init_col + string_cursor);
                    }
                }
            }
            break;

            case TECH_TERMINAL_KEY_BACKSPACE:
            {
                if (mode == TECH_TERMINAL_MODE_RAW)
                {
                    if (string_cursor > 0)
                    {
                        if (string_cursor == acquired_string_size)
                        {
                            string_cursor--;
                            acquired_string_size--;
                            tech_terminal_stdout_print_internal(init_row, init_col + string_cursor, NULL, " ");
                            tech_terminal_cursor_set_position_internal(init_row, init_col + string_cursor);
                        }
                        else
                        {

                            // Delete
                            for (tech_size_t i = string_cursor - 1; i < acquired_string_size - 1; i++)
                            {
                                terminal_string_temp[i] = terminal_string_temp[i + 1];
                            }

                            // Go left and print rest of the characters

                            acquired_string_size--;
                            string_cursor--;

                            tech_terminal_cursor_set_position_internal(init_row, init_col + string_cursor);

                            // Print the rest of the string if exists
                            for (tech_size_t i = string_cursor; i < acquired_string_size; i++)
                            {
                                tech_terminal_stdout_print_internal(0, 0, NULL, "%s", (char *)terminal_string_temp[i].bytes);
                            }
                            tech_terminal_stdout_print_internal(init_row, init_col + acquired_string_size, NULL, " ");
                            tech_terminal_cursor_set_position_internal(init_row, init_col + string_cursor);
                        }
                    }
                }
            }
            break;

            case TECH_TERMINAL_KEY_ENTER:
            {

                for (tech_size_t i = 0; i < acquired_string_size; i++)
                {
                    terminal_string[i] = terminal_string_temp[i];
                }
                // NULL terminator insertion
                terminal_string[acquired_string_size].byte_size = 1;
                memset(terminal_string[acquired_string_size].bytes, 0x0, TECH_TERMINAL_CHAR_BYTES_MAX_SIZE);
                terminal_string[acquired_string_size].is_control = true;
                terminal_string[acquired_string_size].is_escape_sequence = false;
                terminal_string[acquired_string_size].is_printable = false;
                terminal_string[acquired_string_size].is_utf_8 = false;

                tech_error_number = TECH_SUCCESS;
                char_read_complete = true;
            }
            break;

            case TECH_TERMINAL_KEY_NOT_DETECTED:
            { // Must chech whether it is printable

                if (terminal_char.is_printable && acquired_string_size < size - 1)
                {

                    if (string_cursor == acquired_string_size)
                    {
                        acquired_string_size++;
                        terminal_string_temp[string_cursor] = terminal_char;
                        string_cursor++;
                        if (mode == TECH_TERMINAL_MODE_RAW)
                        {
                            tech_terminal_stdout_print_internal(0, 0, NULL, "%s", (char *)terminal_char.bytes);
                        }
                    }
                    else
                    {

                        for (tech_size_t i = acquired_string_size; i > string_cursor; i--)
                        {
                            terminal_string_temp[i] = terminal_string_temp[i - 1];
                        }
                        terminal_string_temp[string_cursor] = terminal_char;
                        acquired_string_size++;
                        for (tech_size_t i = string_cursor; i < acquired_string_size; i++)
                        {
                            if (mode == TECH_TERMINAL_MODE_RAW)
                            {
                                tech_terminal_stdout_print_internal(0, 0, NULL, "%s", (char *)terminal_string_temp[i].bytes);
                            }
                        }

                        string_cursor++;
                        tech_terminal_cursor_set_position_internal(init_row, init_col + string_cursor);
                    }
                }
            }
            break;
            }
        }
        else
        {
            tech_error_number = TECH_ERROR_TERMINAL_STDIN_GET_CHAR_FAILED;
            break;
        }

    } // String reading while loop

    TECH_THREAD_SAFE_BLOCK_GLOBAL_END(TECH_TERMINAL_STDIN_LOCK)

    if (tech_error_number)
    {
        return TECH_RETURN_FAILURE;
    }
    else
    {
        return TECH_RETURN_SUCCESS;
    }
}

// Uses internal function
tech_return_t tech_terminal_stdout_print_char(tech_terminal_cursor_position_t row, tech_terminal_cursor_position_t col, tech_terminal_char_t terminal_char)
{

    tech_return_t ret;
    TECH_THREAD_SAFE_BLOCK_GLOBAL_START(TECH_TERMINAL_STDOUT_LOCK)
    ret = tech_terminal_stdout_print_char_internal(row, col, terminal_char);
    TECH_THREAD_SAFE_BLOCK_GLOBAL_END(TECH_TERMINAL_STDOUT_LOCK)

    TECH_THREAD_SAFE_BLOCK_FAIL_START
    tech_error_number = TECH_ERROR_THREAD_SAFE_BLOCK_UNEXPECTED_EXIT;
    return TECH_RETURN_FAILURE;
    TECH_THREAD_SAFE_BLOCK_FAIL_END

    return ret;
}

// Uses internal function
tech_return_t tech_terminal_stdout_print(tech_terminal_cursor_position_t row, tech_terminal_cursor_position_t col, const char *format, ...)
{

    TECH_THREAD_SAFE_BLOCK_GLOBAL_START(TECH_TERMINAL_STDOUT_LOCK)
    va_list args;
    va_start(args, format);
    tech_terminal_stdout_print_internal(row, col, &args, format);
    va_end(args);
    TECH_THREAD_SAFE_BLOCK_GLOBAL_END(TECH_TERMINAL_STDOUT_LOCK)

    TECH_THREAD_SAFE_BLOCK_FAIL_START
        tech_error_number = TECH_ERROR_THREAD_SAFE_BLOCK_UNEXPECTED_EXIT;
        return TECH_RETURN_FAILURE;
    TECH_THREAD_SAFE_BLOCK_FAIL_END

    return TECH_RETURN_SUCCESS;
}

tech_return_t tech_terminal_string_convert_to_char_stream(char *destination, tech_size_t destination_size, tech_terminal_char_t *source, tech_size_t source_size)
{

    if (destination == NULL || source == NULL)
    {
        tech_error_number = TECH_ERROR_NULL_POINTER;
        return TECH_RETURN_FAILURE;
    }

    if (destination_size == 0 || source_size == 0)
    {
        tech_error_number = TECH_ERROR_SIZE_ZERO;
        return TECH_RETURN_FAILURE;
    }    

    tech_size_t destination_write_offset = 0; // This can also be thaught as the written bytes

    memset(destination, 0x0, destination_size);
    for (tech_size_t i = 0; i < source_size; i++)
    {

        if ((destination_write_offset + source[i].byte_size < destination_size) && (source[i].bytes[0] != 0))
        { // Last char is internal for a null terminator
            memcpy(destination + destination_write_offset, source[i].bytes, source[i].byte_size);
            destination_write_offset += source[i].byte_size;
        }
        else
        {
            destination[destination_write_offset] = '\0';
            break;
        }
    }
    return TECH_RETURN_SUCCESS;
}

tech_return_t tech_terminal_string_convert_from_char_stream(tech_terminal_char_t* destination, tech_size_t destination_size, const char* source, tech_size_t source_size){

    if (destination == NULL || source == NULL)
    {
        tech_error_number = TECH_ERROR_NULL_POINTER;
        return TECH_RETURN_FAILURE;
    }

    if (destination_size == 0 || source_size == 0)
    {
        tech_error_number = TECH_ERROR_SIZE_ZERO;
        return TECH_RETURN_FAILURE;
    }    

    tech_size_t mb_total_size = source_size;

    tech_size_t mb_gathered_size = 0;
    tech_size_t read_chars = 0;
    tech_terminal_char_t terminal_string_temp[destination_size];
    memset(terminal_string_temp,0x0,sizeof(terminal_string_temp));


    while(mb_gathered_size < mb_total_size && read_chars < destination_size ){


        tech_terminal_char_t terminal_char_temp = {0};
        
        if(tech_terminal_char_extract_from_char_stream(&terminal_char_temp,source+mb_gathered_size,source_size-mb_gathered_size) == TECH_RETURN_SUCCESS){
            tech_size_t mb_current_size = terminal_char_temp.byte_size;

            mb_gathered_size += mb_current_size;

            terminal_string_temp[read_chars] = terminal_char_temp;

            read_chars++;

        }else{
            // Failure reading, needs further checking...
            return TECH_RETURN_FAILURE;
        }

    }

    for(tech_size_t i = 0; i < destination_size; i++){
        destination[i] = terminal_string_temp[i];
    }


    return TECH_RETURN_SUCCESS;
}

tech_return_t tech_terminal_char_extract_from_char_stream(tech_terminal_char_t *terminal_char, const char *stream, tech_size_t stream_size)
{

    if (terminal_char == NULL || stream == NULL)
    {
        return TECH_RETURN_FAILURE;
    }
    if (stream_size == 0)
    {
        return TECH_RETURN_FAILURE;
    }

    tech_terminal_char_t terminal_char_temp = {0};

    tech_byte_t initial_byte = stream[0];

    if ((initial_byte & 0b11111000) == 0b11110000)
    { // 1111 0000
        // 4 Byte UTF-8 Character
        terminal_char_temp.is_utf_8 = true;
        terminal_char_temp.byte_size = 4;
    }
    else if ((initial_byte & 0b11110000) == 0b11100000)
    { // 1110 0000
        // 3 Byte UTF-8 Character
        terminal_char_temp.is_utf_8 = true;
        terminal_char_temp.byte_size = 3;
    }
    else if ((initial_byte & 0b11100000) == 0b11000000)
    { // 1100 0000
        // 2 Byte UTF-8 Character
        terminal_char_temp.is_utf_8 = true;
        terminal_char_temp.byte_size = 2;
    }
    else if ((initial_byte & 0b11000000) == 0b10000000)
    { // 1000 0000
        // 1 Byte UTF-8 Character
        terminal_char_temp.is_utf_8 = true;
        terminal_char_temp.byte_size = 1;
    }
    else
    {
        // 1 Byte ASCII Character
        terminal_char_temp.is_utf_8 = false;
        terminal_char_temp.byte_size = 1;
    }

    if (terminal_char_temp.byte_size > stream_size)
    {
        // Size provided is invalid
        return TECH_RETURN_FAILURE;
    }



    if (initial_byte <= 31 || initial_byte == 127)
    {
        terminal_char_temp.is_control = true;
        terminal_char_temp.is_printable = false;
    }else if(initial_byte == 0){
        terminal_char_temp = TECH_TERMINAL_CHAR_NULL_TERMINATOR;
    }
    else
    {
        memcpy(terminal_char_temp.bytes, stream, terminal_char_temp.byte_size);
        terminal_char_temp.is_control = false;
        terminal_char_temp.is_escape_sequence = false;
        terminal_char_temp.is_printable = true;
    }

    *terminal_char = terminal_char_temp;

    return TECH_RETURN_SUCCESS;
}

tech_terminal_echo_state_t tech_terminal_get_echo(void)
{
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    if (term.c_lflag & ECHO)
    {
        return TECH_TERMINAL_ECHO_STATE_ON;
    }
    else
    {
        return TECH_TERMINAL_ECHO_STATE_OFF;
    }
    return 0;
}

void tech_terminal_signal_init(void)
{
    // Initializes all signal handlers with signals supported

	// SA_RESTART is not set to detect window resize signal
	struct sigaction sa;
    memset(&sa,0x0,sizeof(struct sigaction));
	sa.sa_handler = tech_terminal_signal_resize_handler_internal;
	sigaction(SIGWINCH, &sa, NULL);
}