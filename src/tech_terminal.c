#include "../include/tech_terminal.h"
#include "../include/tech_thread.h"
#include "../include/tech_error.h"

// Reserved declarations
__attribute__((visibility("hidden"))) tech_return_t tech_terminal_mode_reserved(tech_terminal_mode_directive_t directive, ...);

__attribute__((visibility("hidden"))) tech_return_t tech_terminal_stdin_buffer_check_reserved(bool *check);

__attribute__((visibility("hidden"))) tech_return_t tech_terminal_cursor_get_position_reserved(tech_terminal_cursor_position_t *row, tech_terminal_cursor_position_t *col);

__attribute__((visibility("hidden"))) tech_return_t tech_terminal_stdout_print_reserved(tech_terminal_cursor_position_t row, tech_terminal_cursor_position_t col, va_list *received_args, const char *format, ...);

__attribute__((visibility("hidden"))) tech_return_t tech_terminal_stdin_get_byte_reserved(tech_byte_t *byte);

__attribute__((visibility("hidden"))) tech_return_t tech_terminal_stdin_get_char_reserved(tech_terminal_char_t *terminal_char);

__attribute__((visibility("hidden"))) tech_return_t tech_terminal_cursor_set_position_reserved(tech_terminal_cursor_position_t row, tech_terminal_cursor_position_t col);

__attribute__((visibility("hidden"))) tech_return_t tech_terminal_stdout_print_char_reserved(tech_terminal_cursor_position_t row, tech_terminal_cursor_position_t col, tech_terminal_char_t terminal_char);


// Reserved definitions
__attribute__((visibility("hidden"))) tech_return_t tech_terminal_mode_reserved(tech_terminal_mode_directive_t directive, ...)
{

    static struct termios tios_original = {0};
    static struct termios tios_raw = {0};
    static struct termios tios_saved = {0};
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
                terminal_mode = TECH_TERMINAL_MODE_RAW;
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

__attribute__((visibility("hidden"))) tech_return_t tech_terminal_stdin_buffer_check_reserved(bool *check)
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

__attribute__((visibility("hidden"))) tech_return_t tech_terminal_cursor_get_position_reserved(tech_terminal_cursor_position_t *row, tech_terminal_cursor_position_t *col)
{

    char buffer[32];

    tech_terminal_mode_reserved(TECH_TERMINAL_MODE_DIRECTIVE_SAVE);
    tech_terminal_mode_reserved(TECH_TERMINAL_MODE_DIRECTIVE_SET, TECH_TERMINAL_MODE_RAW);

    // Send ANSI escape sequence to retrieve cursor position
    fprintf(stdout,"\033[6n");
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
    tech_terminal_mode_reserved(TECH_TERMINAL_MODE_DIRECTIVE_SET, TECH_TERMINAL_MODE_SAVED);

    if (tech_error_number)
    {
        return TECH_RETURN_FAILURE;
    }
    else
    {
        return TECH_RETURN_SUCCESS;
    }
}

__attribute__((visibility("hidden"))) tech_return_t tech_terminal_stdout_print_reserved(tech_terminal_cursor_position_t row, tech_terminal_cursor_position_t col, va_list *received_args, const char *format, ...){


    char internal_buffer[TECH_TERMINAL_STDOUT_PRINT_INTERNAL_BUFFER_SIZE] = {0};

    if (received_args == NULL)
    {
        va_list args;
        va_start(args, format);
        vsnprintf(internal_buffer, TECH_TERMINAL_STDOUT_PRINT_INTERNAL_BUFFER_SIZE, format, args);
        va_end(args);
    }
    else
    {
        vsnprintf(internal_buffer, TECH_TERMINAL_STDOUT_PRINT_INTERNAL_BUFFER_SIZE, format, *received_args);
    }

    tech_terminal_cursor_position_t cursor_row, cursor_col;
    tech_terminal_cursor_get_position_reserved(&cursor_row,&cursor_col);


    if(row == 0) row = cursor_row;
    if(col == 0) col = cursor_col;


    const char *mb_char_iterator = (const char *)internal_buffer;
    tech_size_t mb_total_size = strnlen(internal_buffer,TECH_TERMINAL_STDOUT_PRINT_INTERNAL_BUFFER_SIZE); // null terminator not included
    tech_size_t mb_gathered_size = 0;

    for (tech_size_t i = 0;; i++)
    {

        if (mb_gathered_size == mb_total_size){
            break;
        }


        tech_terminal_char_t terminal_char_temp = {0};


        tech_terminal_char_extract_from_char_stream(&terminal_char_temp,mb_char_iterator,mb_total_size-mb_gathered_size);

        tech_size_t mb_char_size = terminal_char_temp.byte_size;

        mb_gathered_size += mb_char_size;

        
        tech_terminal_stdout_print_char_reserved(row,col+i,terminal_char_temp);

        mb_char_iterator += mb_char_size;
    }


}

__attribute__((visibility("hidden"))) tech_return_t tech_terminal_stdin_get_byte_reserved(tech_byte_t *byte)
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

__attribute__((visibility("hidden"))) tech_return_t tech_terminal_stdin_get_char_reserved(tech_terminal_char_t *terminal_char)
{

    if (terminal_char == NULL)
    {
        tech_error_number = TECH_ERROR_NULL_POINTER;
        return TECH_RETURN_FAILURE;
    }

    tech_terminal_char_t terminal_char_temp;
    memset(&terminal_char_temp, 0x0, sizeof(terminal_char_temp));

    tech_byte_t initial_byte = 0x0;

    if (tech_terminal_stdin_get_byte_reserved(&initial_byte) == TECH_RETURN_SUCCESS)
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

        // Control character check
        bool control_char_check_complete = true;

        if (terminal_char_temp.byte_size == 1 && ((initial_byte >= 0 && initial_byte <= 31) || initial_byte == 127))
        {
            // This is a control character
            terminal_char_temp.is_control = true;
            terminal_char_temp.is_printable = false;

            // Escape sequence check
            if (initial_byte == TECH_TERMINAL_CONTROL_CHAR_ESC)
            {

                bool stdin_buffer_check = false;
                if (tech_terminal_stdin_buffer_check_reserved(&stdin_buffer_check) == TECH_RETURN_SUCCESS)
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
                                // Last byte is reserved for null terminator '\0'
                                // Maximum capacity has been reached for  terminal char type
                                // This is not a bug, this is a feature :)
                                break;
                            }

                            if (tech_terminal_stdin_get_byte_reserved(&byte) == TECH_RETURN_SUCCESS)
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

                            if (tech_terminal_stdin_buffer_check_reserved(&stdin_buffer_check) == TECH_RETURN_FAILURE)
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

            for (size_t i = 0, index = 1; i < terminal_char_temp.byte_size - 1; i++, index++)
            {

                tech_byte_t b = 0x0;
                if (tech_terminal_stdin_get_byte_reserved(&b) == TECH_RETURN_SUCCESS)
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
            memset(terminal_char, 0x0, sizeof(terminal_char));
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

__attribute__((visibility("hidden"))) tech_return_t tech_terminal_cursor_set_position_reserved(tech_terminal_cursor_position_t row, tech_terminal_cursor_position_t col)
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

__attribute__((visibility("hidden"))) tech_return_t tech_terminal_attribute_set_reserved(tech_terminal_attribute_t *attribute){

    tech_terminal_type_t type = tech_terminal_get_type();

    if (type == TECH_TERMINAL_TYPE_UNKNOWN)
    {
        tech_error_number = TECH_ERROR_TERMINAL_ATTRIBUTE_CANNOT_SET;
        return TECH_RETURN_FAILURE;
    }

    if (attribute == NULL)
    {
        tech_error_number = TECH_SUCCESS;
        return TECH_RETURN_SUCCESS;
    }

    tech_terminal_stdout_print_reserved(0,0,NULL,TECH_TERMINAL_ATTRIBUTE_CLEAR);

    // Needs to check color compatibility
    if (attribute->set_fg)
    {

        switch (type)
        {

        case TECH_TERMINAL_TYPE_TRUECOLOR: // Also 24BIT
        {
            tech_terminal_stdout_print_reserved(0, 0, NULL, "\033[38;2;%u;%u;%um", attribute->fg.red, attribute->fg.green, attribute->fg.blue);
            tech_error_number = TECH_SUCCESS;
        }
        break;

        case TECH_TERMINAL_TYPE_XTERM256:
        {
            tech_byte_t downgraded_color_256 = tech_tool_convert_truecolor_to_xterm256(attribute->fg.red, attribute->fg.green, attribute->fg.blue);
            tech_terminal_stdout_print_reserved(0, 0, NULL, "\033[38;5;%um", downgraded_color_256);
            tech_error_number = TECH_SUCCESS;
        }
        break;

        case TECH_TERMINAL_TYPE_XTERM:
        {
            tech_byte_t downgraded_color_256 = tech_tool_convert_truecolor_to_xterm256(attribute->fg.red, attribute->fg.green, attribute->fg.blue);
            tech_byte_t downgraded_color_16 = tech_tool_convert_xterm256_to_xterm16(downgraded_color_256);

            tech_terminal_stdout_print_reserved(0, 0, NULL, "\033[%um", 30 + (downgraded_color_16 % 8));

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

        case TECH_TERMINAL_TYPE_TRUECOLOR: // Also 24BIT
        {
            tech_terminal_stdout_print_reserved(0, 0, NULL, "\033[48;2;%u;%u;%um", attribute->fg.red, attribute->fg.green, attribute->fg.blue);
            tech_error_number = TECH_SUCCESS;
        }
        break;

        case TECH_TERMINAL_TYPE_XTERM256:
        {
            tech_byte_t downgraded_color_256 = tech_tool_convert_truecolor_to_xterm256(attribute->fg.red, attribute->fg.green, attribute->fg.blue);
            tech_terminal_stdout_print_reserved(0, 0, NULL, "\033[48;5;%um", downgraded_color_256);
            tech_error_number = TECH_SUCCESS;
        }
        break;

        case TECH_TERMINAL_TYPE_XTERM:
        {
            tech_byte_t downgraded_color_256 = tech_tool_convert_truecolor_to_xterm256(attribute->fg.red, attribute->fg.green, attribute->fg.blue);
            tech_byte_t downgraded_color_16 = tech_tool_convert_xterm256_to_xterm16(downgraded_color_256);

            tech_terminal_stdout_print_reserved(0, 0, NULL, "\033[%um", 40 + (downgraded_color_16 % 8));

            tech_error_number = TECH_SUCCESS;
        }
        break;
        }
    }

    if (attribute->set_underline)
    {
        tech_terminal_stdout_print_reserved(0, 0, NULL, TECH_TERMINAL_ATTRIBUTE_UNDERLINE);
    }

    if (attribute->set_bold)
    {
        tech_terminal_stdout_print_reserved(0, 0, NULL, TECH_TERMINAL_ATTRIBUTE_BOLD);
    }

    if (attribute->set_italic)
    {
        tech_terminal_stdout_print_reserved(0, 0, NULL, TECH_TERMINAL_ATTRIBUTE_ITALIC);
    }

    if (attribute->set_inverse)
    {
        tech_terminal_stdout_print_reserved(0, 0, NULL, TECH_TERMINAL_ATTRIBUTE_INVERSE);
    }

    if (attribute->set_strikethrough)
    {
        tech_terminal_stdout_print_reserved(0, 0, NULL, TECH_TERMINAL_ATTRIBUTE_STRIKETHROUGH);
    }

}

__attribute__((visibility("hidden"))) tech_return_t tech_terminal_stdout_print_char_reserved(tech_terminal_cursor_position_t row, tech_terminal_cursor_position_t col, tech_terminal_char_t terminal_char){
      
    if(tech_terminal_cursor_set_position_reserved(row, col)){
    return TECH_RETURN_FAILURE;
    }
    
    tech_terminal_encoding_t encoding = tech_terminal_get_encoding();

    if(encoding == TECH_TERMINAL_ENCODING_UNKNOWN){
        return TECH_RETURN_FAILURE;
    }

    if(terminal_char.is_utf_8){
        if(encoding == TECH_TERMINAL_ENCODING_UTF_8){
            fprintf(stdout, "%s", (char *)terminal_char.bytes);
        }else if(encoding == TECH_TERMINAL_ENCODING_ASCII){
            fprintf(stdout, " ");
        }
    }else{
        if(encoding == TECH_TERMINAL_ENCODING_ASCII){
            fprintf(stdout, "%s", (char *)terminal_char.bytes);
        }
    }
        fflush(stdout);
        tech_error_number = TECH_SUCCESS;
    return TECH_RETURN_SUCCESS;
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
        return TECH_TERMINAL_TYPE_UNKNOWN;
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

tech_return_t tech_terminal_attribute_set(tech_terminal_attribute_t *attribute)
{

    tech_return_t ret;
    TECH_THREAD_SAFE_BLOCK_GLOBAL_START(TECH_TERMINAL_STDOUT_LOCK)
        ret = tech_terminal_attribute_set_reserved(attribute);
    TECH_THREAD_SAFE_BLOCK_GLOBAL_END(TECH_TERMINAL_STDOUT_LOCK)
    return ret;
}

tech_terminal_key_t tech_terminal_key_translate(tech_terminal_char_t terminal_char)
{

    if (terminal_char.byte_size == 0)
    {
        return TECH_TERMINAL_KEY_NOT_DETECTED;
    }

    if (terminal_char.is_escape_sequence)
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
                if (terminal_char.bytes[3] = '~')
                    return TECH_TERMINAL_KEY_DELETE;
            }
            break;

            default:
                return TECH_TERMINAL_KEY_NOT_DETECTED;
            }
        }

        return 0;
    }
    else
    {
        // Some characters are also considered a KEY, for example ENTER or BACKSPACE

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
}

// Uses reserved function
tech_return_t tech_terminal_cursor_get_position(tech_terminal_cursor_position_t *row, tech_terminal_cursor_position_t *col)
{

    tech_return_t ret;
    TECH_THREAD_SAFE_BLOCK_GLOBAL_START(TECH_TERMINAL_STDIN_LOCK);
    ret = tech_terminal_cursor_get_position_reserved(row, col);
    TECH_THREAD_SAFE_BLOCK_GLOBAL_END(TECH_TERMINAL_STDIN_LOCK);

    TECH_THREAD_SAFE_BLOCK_FAIL_START
    tech_error_number = TECH_ERROR_THREAD_SAFE_BLOCK_UNEXPECTED_EXIT;
    return TECH_RETURN_FAILURE;
    TECH_THREAD_SAFE_BLOCK_FAIL_END

    return ret;
}

// Uses reserved function
tech_return_t tech_terminal_cursor_set_position(tech_terminal_cursor_position_t row, tech_terminal_cursor_position_t col)
{

    tech_return_t ret;
    TECH_THREAD_SAFE_BLOCK_GLOBAL_START(TECH_TERMINAL_STDOUT_LOCK)
    ret = tech_terminal_cursor_set_position_reserved(row, col);
    TECH_THREAD_SAFE_BLOCK_GLOBAL_END(TECH_TERMINAL_STDOUT_LOCK)

    TECH_THREAD_SAFE_BLOCK_FAIL_START
    tech_error_number = TECH_ERROR_THREAD_SAFE_BLOCK_UNEXPECTED_EXIT;
    return TECH_RETURN_FAILURE;
    TECH_THREAD_SAFE_BLOCK_FAIL_END

    return ret;
}

// Uses reserved function
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
        ret = tech_terminal_mode_reserved(directive, mode);
    }
    break;

    case TECH_TERMINAL_MODE_DIRECTIVE_GET:
    {
        tech_terminal_mode_t *mode = va_arg(args, tech_terminal_mode_t *);
        ret = tech_terminal_mode_reserved(directive, mode);
    }
    break;

    case TECH_TERMINAL_MODE_DIRECTIVE_SAVE:
    {
        ret = tech_terminal_mode_reserved(directive);
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

// Uses reserved function
tech_return_t tech_terminal_stdin_get_byte(tech_byte_t *byte)
{

    tech_return_t ret;

    TECH_THREAD_SAFE_BLOCK_GLOBAL_START(TECH_TERMINAL_STDIN_LOCK)
    ret = tech_terminal_stdin_get_byte_reserved(byte);
    TECH_THREAD_SAFE_BLOCK_GLOBAL_END(TECH_TERMINAL_STDIN_LOCK)

    TECH_THREAD_SAFE_BLOCK_FAIL_START
    tech_error_number = TECH_ERROR_THREAD_SAFE_BLOCK_UNEXPECTED_EXIT;
    return TECH_RETURN_FAILURE;
    TECH_THREAD_SAFE_BLOCK_FAIL_END

    return ret;
}

// Uses reserved function
tech_return_t tech_terminal_stdin_get_char(tech_terminal_char_t *terminal_char)
{

    tech_return_t ret;

    TECH_THREAD_SAFE_BLOCK_GLOBAL_START(TECH_TERMINAL_STDIN_LOCK)
    ret = tech_terminal_stdin_get_char_reserved(terminal_char);
    TECH_THREAD_SAFE_BLOCK_GLOBAL_END(TECH_TERMINAL_STDIN_LOCK)

    TECH_THREAD_SAFE_BLOCK_FAIL_START
    tech_error_number = TECH_ERROR_THREAD_SAFE_BLOCK_UNEXPECTED_EXIT;
    return TECH_RETURN_FAILURE;
    TECH_THREAD_SAFE_BLOCK_FAIL_END

    return ret;
}

// Uses reserved function
tech_return_t tech_terminal_stdin_buffer_check(bool *check)
{

    tech_return_t ret;
    TECH_THREAD_SAFE_BLOCK_GLOBAL_START(TECH_TERMINAL_STDIN_LOCK)
    ret = tech_terminal_stdin_buffer_check_reserved(check);
    TECH_THREAD_SAFE_BLOCK_GLOBAL_END(TECH_TERMINAL_STDIN_LOCK)

    TECH_THREAD_SAFE_BLOCK_FAIL_START
    tech_error_number = TECH_ERROR_THREAD_SAFE_BLOCK_UNEXPECTED_EXIT;
    return TECH_RETURN_FAILURE;
    TECH_THREAD_SAFE_BLOCK_FAIL_END

    return ret;
}

// Uses reserved function
tech_return_t tech_terminal_stdin_buffer_consume(void)
{

    TECH_THREAD_SAFE_BLOCK_GLOBAL_START(TECH_TERMINAL_STDIN_LOCK);

    tech_byte_t b;

    while (1)
    {
        bool check = false;
        if (tech_terminal_stdin_buffer_check_reserved(&check))
        {
            tech_error_number = TECH_ERROR_TERMINAL_STDIN_BUFFER_CHECK_FAIL;
            break;
        }
        if (check)
        {
            if (tech_terminal_stdin_get_byte_reserved(&b))
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
    tech_terminal_cursor_set_position_reserved(row, col);

    // Do not lock stdin, print escape sequence to retrieve cursor position
    // This is the position after set, this is the beginning
    tech_terminal_cursor_get_position_reserved(&init_row, &init_col);

    // Create a temporary buffer
    tech_terminal_char_t terminal_string_temp[size];
    memset(terminal_string_temp, 0x0, size * sizeof(tech_terminal_char_t));

    tech_size_t string_cursor = 0;

    bool char_read_complete = false;
    tech_size_t acquired_string_size = 0;

    while (!char_read_complete)
    {
        tech_terminal_char_t terminal_char = {0};

        if (tech_terminal_stdin_get_char_reserved(&terminal_char) == TECH_RETURN_SUCCESS)
        {

            switch (tech_terminal_key_translate(terminal_char))
            {

            case TECH_TERMINAL_KEY_LEFT:
            {
                if (string_cursor > 0)
                {
                    string_cursor--;
                    tech_terminal_cursor_set_position_reserved(init_row, init_col + string_cursor);
                }
            }
            break;

            case TECH_TERMINAL_KEY_RIGHT:
            {
                if (string_cursor < acquired_string_size)
                {
                    string_cursor++;
                    tech_terminal_cursor_set_position_reserved(init_row, init_col + string_cursor);
                }
            }
            break;

            case TECH_TERMINAL_KEY_DELETE:
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
                        tech_terminal_stdout_print_reserved(0, 0, NULL, "%s", (char *)terminal_string_temp[i].bytes);
                    }
                    tech_terminal_stdout_print_reserved(init_row, init_col + acquired_string_size, NULL, " ");
                    tech_terminal_cursor_set_position_reserved(init_row, init_col + string_cursor);
                }
            }
            break;

            case TECH_TERMINAL_KEY_BACKSPACE:
            {
                if (string_cursor > 0)
                {
                    if (string_cursor == acquired_string_size)
                    {
                        string_cursor--;
                        acquired_string_size--;
                        tech_terminal_stdout_print_reserved(init_row, init_col + string_cursor, NULL, " ");
                        tech_terminal_cursor_set_position_reserved(init_row, init_col + string_cursor);
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

                        tech_terminal_cursor_set_position_reserved(init_row, init_col + string_cursor);

                        // Print the rest of the string if exists
                        for (tech_size_t i = string_cursor; i < acquired_string_size; i++)
                        {
                            tech_terminal_stdout_print_reserved(0, 0, NULL, "%s", (char *)terminal_string_temp[i].bytes);
                        }
                        tech_terminal_stdout_print_reserved(init_row, init_col + acquired_string_size, NULL, " ");
                        tech_terminal_cursor_set_position_reserved(init_row, init_col + string_cursor);
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
                        tech_terminal_stdout_print_reserved(0, 0, NULL, "%s", (char *)terminal_char.bytes);
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
                            tech_terminal_stdout_print_reserved(0, 0, NULL, "%s", (char *)terminal_string_temp[i].bytes);
                        }

                        string_cursor++;
                        tech_terminal_cursor_set_position_reserved(init_row, init_col + string_cursor);
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

// Uses reserved function
tech_return_t tech_terminal_stdout_print_char(tech_terminal_cursor_position_t row, tech_terminal_cursor_position_t col, tech_terminal_char_t terminal_char)
{

    tech_return_t ret;
    TECH_THREAD_SAFE_BLOCK_GLOBAL_START(TECH_TERMINAL_STDOUT_LOCK)
        ret = tech_terminal_stdout_print_char_reserved(row,col,terminal_char);
    TECH_THREAD_SAFE_BLOCK_GLOBAL_END(TECH_TERMINAL_STDOUT_LOCK)


    TECH_THREAD_SAFE_BLOCK_FAIL_START
        tech_error_number = TECH_ERROR_THREAD_SAFE_BLOCK_UNEXPECTED_EXIT;
        return TECH_RETURN_FAILURE;
    TECH_THREAD_SAFE_BLOCK_FAIL_END


    return ret;
}

// Uses reserved function
tech_return_t tech_terminal_stdout_print(tech_terminal_cursor_position_t row, tech_terminal_cursor_position_t col, const char *format, ...)
{

    TECH_THREAD_SAFE_BLOCK_GLOBAL_START(TECH_TERMINAL_STDOUT_LOCK)
        va_list args;
        va_start(args, format);
        tech_terminal_stdout_print_reserved(row, col, &args, format);
        va_end(args);
    TECH_THREAD_SAFE_BLOCK_GLOBAL_END(TECH_TERMINAL_STDOUT_LOCK)
}

tech_return_t tech_terminal_convert_to_char_stream(char *destination, tech_size_t destination_size, tech_terminal_char_t *source, tech_size_t source_size)
{

    if (destination == NULL || source == NULL)
    {
        tech_error_number = TECH_ERROR_NULL_POINTER;
        return TECH_RETURN_FAILURE;
    }

    if (destination_size == 0)
    {
        tech_error_number = TECH_ERROR_SIZE_ZERO;
        return TECH_RETURN_FAILURE;
    }

    tech_size_t destination_write_offset = 0; // This can also be thaught as the written bytes

    memset(destination, 0x0, destination_size);
    for (tech_size_t i = 0; i < source_size; i++)
    {

        if ((destination_write_offset + source[i].byte_size < destination_size) && (source[i].bytes[0] != 0))
        { // Last char is reserved for a null terminator
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

tech_return_t tech_terminal_char_extract_from_char_stream(tech_terminal_char_t* terminal_char, const char* stream, tech_size_t stream_size){


        if(terminal_char == NULL || stream == NULL){
            return TECH_RETURN_FAILURE;
        }
        if(stream_size == 0){
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

        if(terminal_char_temp.byte_size > stream_size){
            // Size provided is invalid
            return TECH_RETURN_FAILURE;
        }

        memcpy(terminal_char_temp.bytes,stream,terminal_char_temp.byte_size);
        terminal_char_temp.is_control = false;
        terminal_char_temp.is_escape_sequence = false;
        terminal_char_temp.is_printable = true;

        *terminal_char = terminal_char_temp;

    return TECH_RETURN_SUCCESS;
}
