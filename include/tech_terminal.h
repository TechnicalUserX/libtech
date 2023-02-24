// This library is built for UTF-8
// If UTF-8 is not set for encoding, library will assume ASCII

#ifndef TECH_TERMINAL_H
#define TECH_TERMINAL_H

#include "../config/tech_features.h"
#include "../shared/tech_include.h"
#include "../shared/tech_types.h"


#define TECH_TERMINAL_ATTRIBUTE_BOLD           "\033[1m"
#define TECH_TERMINAL_ATTRIBUTE_DIM            "\033[2m"
#define TECH_TERMINAL_ATTRIBUTE_ITALIC         "\033[3m"
#define TECH_TERMINAL_ATTRIBUTE_UNDERLINE      "\033[4m"
#define TECH_TERMINAL_ATTRIBUTE_BLINK          "\033[5m"
#define TECH_TERMINAL_ATTRIBUTE_FAST_BLINK     "\033[6m"
#define TECH_TERMINAL_ATTRIBUTE_INVERSE        "\033[7m"
#define TECH_TERMINAL_ATTRIBUTE_HIDDEN         "\033[8m"
#define TECH_TERMINAL_ATTRIBUTE_STRIKETHROUGH  "\033[9m"
#define TECH_TERMINAL_ATTRIBUTE_CLEAR          "\033[0m"

#define TECH_TERMINAL_ATTRIBUTE_BRIGHT TECH_TERMINAL_ATTRIBUTE_BOLD

#define TECH_TERMINAL_ATTRIBUTE_BLACK          "\033[30m"
#define TECH_TERMINAL_ATTRIBUTE_RED            "\033[31m"
#define TECH_TERMINAL_ATTRIBUTE_GREEN          "\033[32m"
#define TECH_TERMINAL_ATTRIBUTE_YELLOW         "\033[33m"
#define TECH_TERMINAL_ATTRIBUTE_BLUE           "\033[34m"
#define TECH_TERMINAL_ATTRIBUTE_MAGENTA        "\033[35m"
#define TECH_TERMINAL_ATTRIBUTE_CYAN           "\033[36m"
#define TECH_TERMINAL_ATTRIBUTE_WHITE          "\033[37m"


#define TECH_TERMINAL_ATTRIBUTE_256COLOR(c)    "\033[38;5;"#c"m"
#define TECH_TERMINAL_ATTRIBUTE_256COLOR_BG(c) "\033[48;5;"#c"m"


#define TECH_TERMINAL_ATTRIBUTE_RGB(r,g,b)     "\033[38;2;"#r";"#g";"#b"m"
#define TECH_TERMINAL_ATTRIBUTE_RGB_BG(r,g,b)  "\033[48;2;"#r";"#g";"#b"m"


#define TECH_TERMINAL_ATTRIBUTE_BLACK_BG       "\033[40m"
#define TECH_TERMINAL_ATTRIBUTE_RED_BG         "\033[41m"
#define TECH_TERMINAL_ATTRIBUTE_GREEN_BG       "\033[42m"
#define TECH_TERMINAL_ATTRIBUTE_YELLOW_BG      "\033[43m"
#define TECH_TERMINAL_ATTRIBUTE_BLUE_BG        "\033[44m"
#define TECH_TERMINAL_ATTRIBUTE_MAGENTA_BG     "\033[45m"
#define TECH_TERMINAL_ATTRIBUTE_CYAN_BG        "\033[46m"
#define TECH_TERMINAL_ATTRIBUTE_WHITE_BG       "\033[47m"
#define TECH_TERMINAL_ATTRIBUTE_GRAY_BG        "\033[100m"
#define TECH_TERMINAL_ATTRIBUTE_LRED_BG        "\033[101m"
#define TECH_TERMINAL_ATTRIBUTE_LGREEN_BG      "\033[102m"
#define TECH_TERMINAL_ATTRIBUTE_LYELLOW_BG     "\033[103m"
#define TECH_TERMINAL_ATTRIBUTE_LBLUE_BG       "\033[104m"
#define TECH_TERMINAL_ATTRIBUTE_LPURPLE_BG     "\033[105m"
#define TECH_TERMINAL_ATTRIBUTE_TEAL_BG        "\033[106m"


#define TECH_TERMINAL_CONTROL_CHAR_NULL    0
#define TECH_TERMINAL_CONTROL_CHAR_SOH     1
#define TECH_TERMINAL_CONTROL_CHAR_STX     2
#define TECH_TERMINAL_CONTROL_CHAR_ETX     3
#define TECH_TERMINAL_CONTROL_CHAR_EOT     4
#define TECH_TERMINAL_CONTROL_CHAR_ENQ     5
#define TECH_TERMINAL_CONTROL_CHAR_ACK     6
#define TECH_TERMINAL_CONTROL_CHAR_BEL     7
#define TECH_TERMINAL_CONTROL_CHAR_BS      8
#define TECH_TERMINAL_CONTROL_CHAR_TAB     9
#define TECH_TERMINAL_CONTROL_CHAR_LF      10
#define TECH_TERMINAL_CONTROL_CHAR_VT      11
#define TECH_TERMINAL_CONTROL_CHAR_FF      12
#define TECH_TERMINAL_CONTROL_CHAR_CR      13
#define TECH_TERMINAL_CONTROL_CHAR_SO      14
#define TECH_TERMINAL_CONTROL_CHAR_SI      15
#define TECH_TERMINAL_CONTROL_CHAR_DLE     16
#define TECH_TERMINAL_CONTROL_CHAR_DC1     17
#define TECH_TERMINAL_CONTROL_CHAR_DC2     18
#define TECH_TERMINAL_CONTROL_CHAR_DC3     19
#define TECH_TERMINAL_CONTROL_CHAR_DC4     20
#define TECH_TERMINAL_CONTROL_CHAR_NAK     21
#define TECH_TERMINAL_CONTROL_CHAR_SYN     22
#define TECH_TERMINAL_CONTROL_CHAR_ETB     23
#define TECH_TERMINAL_CONTROL_CHAR_CAN     24
#define TECH_TERMINAL_CONTROL_CHAR_EM      25
#define TECH_TERMINAL_CONTROL_CHAR_SUB     26
#define TECH_TERMINAL_CONTROL_CHAR_ESC     27
#define TECH_TERMINAL_CONTROL_CHAR_FS      28
#define TECH_TERMINAL_CONTROL_CHAR_GS      29
#define TECH_TERMINAL_CONTROL_CHAR_RS      30
#define TECH_TERMINAL_CONTROL_CHAR_US      31
#define TECH_TERMINAL_CONTROL_CHAR_DEL     127

#define TECH_TERMINAL_KEY_NOT_DETECTED  0
#define TECH_TERMINAL_KEY_UP            1
#define TECH_TERMINAL_KEY_DOWN          2
#define TECH_TERMINAL_KEY_RIGHT         3
#define TECH_TERMINAL_KEY_LEFT          4
#define TECH_TERMINAL_KEY_BACKSPACE     5
#define TECH_TERMINAL_KEY_ENTER         6
#define TECH_TERMINAL_KEY_DELETE        7

// General design idea for this lock is to make this lock 'non-blocking'
// Functions which use this should be pseudo-non-blocking
// Printing must be pseudo-atomic
#define TECH_TERMINAL_STDOUT_LOCK tech_thread_safe_block_global_terminal_stdout_lock

#define TECH_TERMINAL_STDOUT_PRINT_INTERNAL_BUFFER_SIZE 10000


// General design idea for this lock is to make this lock 'blocking'
// Functions using this lock shall prevent others from getting input
// Try to avoid using functions which use this lock at the same time from different threads
#define TECH_TERMINAL_STDIN_LOCK tech_thread_safe_block_global_terminal_stdin_lock


#define TECH_TERMINAL_CHAR_BYTES_MAX_SIZE 8


#define TECH_TERMINAL_CHAR_NULL_TERMINATOR (tech_terminal_char_t){.byte_size = 1,.bytes[0 ... (TECH_TERMINAL_CHAR_BYTES_MAX_SIZE-1)] = 0,.is_control = true,.is_escape_sequence = false,.is_printable = false,.is_utf_8 = false}

#ifdef __cplusplus
    extern "C" {
#endif


typedef enum tech_terminal_type_enum_t{
    TECH_TERMINAL_TYPE_UNKNOWN, 
    TECH_TERMINAL_TYPE_XTERM,
    TECH_TERMINAL_TYPE_XTERM256,
    TECH_TERMINAL_TYPE_TRUECOLOR,
    TECH_TERMINAL_TYPE_24BIT = TECH_TERMINAL_TYPE_TRUECOLOR
}tech_terminal_type_t;


typedef enum tech_terminal_encoding_enum_t{
    TECH_TERMINAL_ENCODING_UNKNOWN,
    TECH_TERMINAL_ENCODING_ASCII,
    TECH_TERMINAL_ENCODING_UTF_8
}tech_terminal_encoding_t;


typedef enum tech_terminal_mode_directive_enum_t{
    TECH_TERMINAL_MODE_DIRECTIVE_GET = 0,
    TECH_TERMINAL_MODE_DIRECTIVE_SET,
    TECH_TERMINAL_MODE_DIRECTIVE_SAVE
}tech_terminal_mode_directive_t;


typedef enum tech_terminal_mode_enum_t{
    TECH_TERMINAL_MODE_ORIGINAL = 0, // This is the terminal's initial state, before the program started
    TECH_TERMINAL_MODE_RAW,
    TECH_TERMINAL_MODE_SAVED
}tech_terminal_mode_t;


/**
 * Types of terminal chars
 * 
 * -> Printable char
 * -> Control char
 * -> Escape sequence (is also a control char)
 * 
 */
typedef struct tech_terminal_char_struct_t{
    tech_byte_t bytes[TECH_TERMINAL_CHAR_BYTES_MAX_SIZE];    
    uint8_t byte_size;
    bool is_printable;
    bool is_control;
    bool is_escape_sequence;
    bool is_utf_8; // If 0, assumed ASCII
}tech_terminal_char_t;


typedef struct tech_terminal_attribute_struct_t{
    bool set_fg;
    struct fg_struct{
        tech_byte_t red;
        tech_byte_t green;
        tech_byte_t blue;
    }fg;
    bool set_bg;
    struct bg_struct{
        tech_byte_t red;
        tech_byte_t green;
        tech_byte_t blue;
    }bg;

    bool set_underline;
    bool set_bold;
    bool set_italic;
    bool set_inverse;
    bool set_strikethrough;

}tech_terminal_attribute_t;


typedef uint16_t tech_terminal_key_t;

typedef uint16_t tech_terminal_cursor_position_t; // 1-indexed


// Returning unkown type is equivalent to returning TECH_RETURN_FAILURE
tech_terminal_type_t tech_terminal_get_type(void);


// Returning unkown type is equivalent to returning TECH_RETURN_FAILURE
tech_terminal_encoding_t tech_terminal_get_encoding(void);


// Thread-safe(STDOUT)
// Changes terminal attributes
tech_return_t tech_terminal_attribute_set(tech_terminal_attribute_t* attribute);


// Not thread-safe
tech_terminal_key_t tech_terminal_key_translate(tech_terminal_char_t terminal_char);


// Thread-safe(STDOUT)
// Sets cursor position
// Origin at (1,1)
// Value 0 is being rounded to 1
tech_return_t tech_terminal_cursor_set_position(tech_terminal_cursor_position_t row, tech_terminal_cursor_position_t col);


// Thread-safe(STDIN)
// Gets cursor position
// Origin at (1,1)
tech_return_t tech_terminal_cursor_get_position(tech_terminal_cursor_position_t *row, tech_terminal_cursor_position_t *col);


// Thread-safe(STDIN)
// Set terminal mode
// Variadic function, use with caution
tech_return_t tech_terminal_mode(tech_terminal_mode_directive_t directive, ...);


// Thread-safe(STDIN)
// Read a byte from stdin
// Call multiple times for UTF character reading
// This function reads the newline when not used int raw mode, needs further processing
tech_return_t tech_terminal_stdin_get_byte(tech_byte_t* byte);


// Thread-safe(STDIN)
// Returns a terminal char type by parameter
// Supports ASCII & UTF-8 printable chars, control characters, escape sequences
tech_return_t tech_terminal_stdin_get_char(tech_terminal_char_t* terminal_char);


// Thread-safe(STDIN)
// Checks whether there are ready to read bytes inside stdint buffer
tech_return_t tech_terminal_stdin_buffer_check(bool* check);


// Thread-safe(STDIN)
// Empties all waiting bytes in the stdin buffer
tech_return_t tech_terminal_stdin_buffer_consume(void);

// Thread-safe(STDIN)
// This function does not initially set the cursor position
tech_return_t tech_terminal_stdin_get_string(tech_terminal_cursor_position_t row, tech_terminal_cursor_position_t col, tech_terminal_char_t* terminal_string,tech_size_t size);


// Thread-safe(STDOUT)
// Prints a terminal char at the given location
tech_return_t tech_terminal_stdout_print_char(tech_terminal_cursor_position_t row, tech_terminal_cursor_position_t col, tech_terminal_char_t terminal_char);


// Thread-safe(STDOUT)
// Printf but tech library compliant
tech_return_t tech_terminal_stdout_print(tech_terminal_cursor_position_t row, tech_terminal_cursor_position_t col, const char* format, ...);


// 'destination' might not have the sufficient size when the 'source' is converted to multi-byte char string
// For %100 guaranteed conversion, destination size could be set to 4 times the source size, (wide char = 4 x char)
tech_return_t tech_terminal_convert_to_char_stream(char* destination, tech_size_t destination_size, tech_terminal_char_t* source, tech_size_t source_size);

tech_return_t tech_terminal_char_extract_from_char_stream(tech_terminal_char_t* terminal_char, const char* stream, tech_size_t stream_size);


#ifdef __cplusplus
    }
#endif

#endif // TECH_TERMINAL_H