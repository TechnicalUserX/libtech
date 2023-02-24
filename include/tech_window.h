#ifndef TECH_WINDOW_H
#define TECH_WINDOW_H




#include "../config/tech_features.h"
#include "../shared/tech_include.h"
#include "../shared/tech_types.h"

#include "tech_terminal.h"

#define TECH_WINDOW_PRINT_INTERNAL_BUFFER_SIZE 10000


#ifdef __cplusplus
    extern "C" {
#endif

typedef uint16_t tech_window_position_t; // 0-indexed

typedef struct tech_window_line_char_buffer_struct_t
{
    bool refresh;
    tech_terminal_attribute_t attribute;
    tech_terminal_char_t terminal_char;

} tech_window_line_char_buffer_t;


typedef struct tech_window_line_buffer_struct_t
{
    tech_size_t char_buffer_size;
    struct tech_window_line_char_buffer_struct_t *char_buffer;

} tech_window_line_buffer_t;


typedef struct tech_window_struct_t
{

    tech_size_t row_size; // Maximum size for rows
    tech_size_t col_size; // Maximum size for columns

    tech_terminal_cursor_position_t origin_row; // Top-side origin
    tech_terminal_cursor_position_t origin_col; // Left-side origin

    tech_size_t line_buffer_size;
    tech_window_line_buffer_t *line_buffer;

    // 0-indexed
    // Hiding anything outside this viewpoint
    struct
    {
        tech_window_position_t top;
        tech_window_position_t bottom;
    } viewpoint;

    struct tech_window_struct_t *parent;
} tech_window_t;




tech_window_t *tech_window_new(tech_terminal_cursor_position_t origin_row, tech_terminal_cursor_position_t origin_col, tech_size_t row_size, tech_size_t col_size);


void tech_window_refresh(tech_window_t *win);


tech_return_t tech_window_print(tech_window_t *win, tech_window_position_t row, tech_window_position_t col, tech_terminal_attribute_t *attribute, const char *format, ...);


void tech_window_free(tech_window_t **win);


#ifdef __cplusplus
    }
#endif

#endif // TECH_WINDOW_H