#include "../include/tech_window.h"
#include "../include/tech_error.h"


tech_window_t *tech_window_new(tech_terminal_cursor_position_t origin_row, tech_terminal_cursor_position_t origin_col, tech_size_t row_size, tech_size_t col_size)
{

    if(row_size == 0 || col_size == 0){
        tech_error_number = TECH_ERROR_SIZE_ZERO;
        return NULL;
    }


    tech_window_t *new_window = (tech_window_t*)malloc(sizeof(tech_window_t));

    new_window->origin_col = origin_col;
    new_window->origin_row = origin_row;

    new_window->col_size = col_size;
    new_window->row_size = row_size;

    // These are 0-indexed
    new_window->viewpoint.top = 0;
    new_window->viewpoint.bottom = row_size - 1;

    new_window->line_buffer_size = row_size;
    new_window->line_buffer = (tech_window_line_buffer_t *)malloc(sizeof(tech_window_line_buffer_t) * row_size);

    for (tech_size_t i = 0; i < row_size; i++)
    {

        tech_window_line_buffer_t *current_line_buffer = (new_window->line_buffer + i);
        current_line_buffer->char_buffer_size = col_size;
        current_line_buffer->char_buffer = (tech_window_line_char_buffer_t *)malloc(sizeof(tech_window_line_char_buffer_t) * col_size);

        for (tech_size_t j = 0; j < col_size; j++)
        {

            memset(&(current_line_buffer->char_buffer[j].attribute), 0x0, sizeof(tech_terminal_attribute_t)); // Setting attributes to zero
            current_line_buffer->char_buffer[j].refresh = false;                                              // There is nothing to print
            current_line_buffer->char_buffer[j].terminal_char = TECH_TERMINAL_CHAR_NULL_TERMINATOR;
        }
    }

    return new_window;
}


void tech_window_refresh(tech_window_t *win)
{

    if (win == NULL)
    {
        return;
    }

    // Top has lower value than bottom
    for (tech_size_t i = win->viewpoint.top; i <= win->viewpoint.bottom; i++)
    {

        for (tech_size_t j = 0; j < win->col_size; j++)
        {

            if (win->line_buffer[i].char_buffer[j].refresh){

                tech_terminal_set_attribute(&(win->line_buffer[i].char_buffer[j].attribute));
                tech_terminal_stdout_print_char(win->origin_row + i, win->origin_col + j, win->line_buffer[i].char_buffer[j].terminal_char);
                win->line_buffer[i].char_buffer[j].refresh = false;
                tech_terminal_set_attribute(NULL); // Resetting attributes
            }
        }
    }
    
    tech_terminal_stdout_print(0,0,TECH_TERMINAL_ATTRIBUTE_CLEAR); // Reseting the attributes of the terminal

    tech_window_refresh(win->parent);
}


tech_return_t tech_window_print(tech_window_t *win, tech_window_position_t row, tech_window_position_t col, tech_terminal_attribute_t *attribute, const char *format, ...){

    tech_window_position_t print_row = win->viewpoint.top + row;

    // bottom is included
    if (win->viewpoint.top + print_row > win->viewpoint.bottom){
        return TECH_RETURN_FAILURE;
    }


    char internal_buffer[TECH_WINDOW_PRINT_INTERNAL_BUFFER_SIZE] = {0};
    va_list args;
    va_start(args, format);
    vsnprintf(internal_buffer, TECH_WINDOW_PRINT_INTERNAL_BUFFER_SIZE, format, args);
    va_end(args);


    const char *mb_char_iterator = (const char *)internal_buffer;
    tech_size_t mb_total_size = strnlen(internal_buffer,TECH_WINDOW_PRINT_INTERNAL_BUFFER_SIZE); // null terminator not included
    tech_size_t mb_gathered_size = 0;

    for (tech_size_t i = 0;; i++)
    {

        if (mb_gathered_size == mb_total_size){
            break;
        }

        tech_window_position_t print_col = col + i;

        if (print_col >= win->col_size){
            break;
        }


        tech_terminal_char_t terminal_char_temp = {0};


        tech_terminal_char_extract_from_char_stream(&terminal_char_temp,mb_char_iterator,mb_total_size-mb_gathered_size);

        tech_size_t mb_char_size = terminal_char_temp.byte_size;

        mb_gathered_size += mb_char_size;


        // Setting attribute
        if (attribute == NULL){
            memset(&(win->line_buffer[print_row].char_buffer[print_col].attribute), 0x0, sizeof(tech_terminal_attribute_t)); // Resetting everything inside attribute
        }else{
            win->line_buffer[print_row].char_buffer[print_col].attribute = (*attribute);
        }

        win->line_buffer[print_row].char_buffer[print_col].refresh = true;
        win->line_buffer[print_row].char_buffer[print_col].terminal_char = terminal_char_temp;



        mb_char_iterator += mb_char_size;
    }

    return TECH_RETURN_SUCCESS;
}


void tech_window_free(tech_window_t **win)
{

    if (win == NULL)
        return;

    for (tech_size_t i = 0; i < (*win)->row_size; i++)
    {
        free((**win).line_buffer[i].char_buffer);
    }

    free((**win).line_buffer);
    free(*win);
    *win = NULL;
    return;
}

void tech_window_border(tech_window_t* win,tech_terminal_attribute_t* attribute){


	tech_terminal_attribute_t attribute_candidate;
	if(attribute == NULL){
		memset(&attribute_candidate,0x0,sizeof(tech_terminal_attribute_t));
	}else{
		attribute_candidate = (*attribute);
	}

	// Depending on the terminal encoding, the borders of the window will change

	tech_terminal_encoding_t encoding = tech_terminal_get_encoding();

	tech_terminal_char_t corner[4] = {0}; // Zeroing everything
	tech_terminal_char_t horizontal = {0}; // Zeroing everything
	tech_terminal_char_t vertical = {0}; // Zeroing everything

	if(encoding == TECH_TERMINAL_ENCODING_UTF_8){
		char c1[] = "╭";
		char c2[] = "╮";
		char c3[] = "╰";
		char c4[] = "╯";
		char h[] = "─";
		char v[] = "│";

		tech_terminal_char_t temp;

		memset(&temp,0x0,sizeof(tech_terminal_char_t));
		tech_terminal_char_extract_from_char_stream(&temp,c1,sizeof(c1));
		corner[0] = temp;

		memset(&temp,0x0,sizeof(tech_terminal_char_t));
		tech_terminal_char_extract_from_char_stream(&temp,c2,sizeof(c2));
		corner[1] = temp;

		memset(&temp,0x0,sizeof(tech_terminal_char_t));
		tech_terminal_char_extract_from_char_stream(&temp,c3,sizeof(c3));
		corner[2] = temp;

		memset(&temp,0x0,sizeof(tech_terminal_char_t));
		tech_terminal_char_extract_from_char_stream(&temp,c4,sizeof(c4));
		corner[3] = temp;

		memset(&temp,0x0,sizeof(tech_terminal_char_t));
		tech_terminal_char_extract_from_char_stream(&temp,h,sizeof(h));
		horizontal = temp;

		memset(&temp,0x0,sizeof(tech_terminal_char_t));
		tech_terminal_char_extract_from_char_stream(&temp,v,sizeof(v));
		vertical = temp;



	}else if(encoding == TECH_TERMINAL_ENCODING_ASCII){
		for(tech_size_t i = 0; i < 4; i++){
			corner[i].byte_size = 1;
			memset(corner[i].bytes,0x0,TECH_TERMINAL_CHAR_BYTES_MAX_SIZE);
			corner[i].bytes[0] = '+';
			corner[i].is_control = false;
			corner[i].is_escape_sequence = false;
			corner[i].is_printable = true;
			corner[i].is_utf_8 = false;
		}
		vertical.byte_size = 1;
		memset(vertical.bytes,0x0,TECH_TERMINAL_CHAR_BYTES_MAX_SIZE);
		vertical.bytes[0] = '|';
		vertical.is_control = false;
		vertical.is_escape_sequence = false;
		vertical.is_printable = true;
		vertical.is_utf_8 = false;

		horizontal.byte_size = 1;
		memset(horizontal.bytes,0x0,TECH_TERMINAL_CHAR_BYTES_MAX_SIZE);
		horizontal.bytes[0] = '-';
		horizontal.is_control = false;
		horizontal.is_escape_sequence = false;
		horizontal.is_printable = true;
		horizontal.is_utf_8 = false;



	}



	// Setting corners
	win->line_buffer[0].char_buffer[0].refresh = true;
	win->line_buffer[0].char_buffer[0].terminal_char = corner[0];
	win->line_buffer[0].char_buffer[0].attribute = attribute_candidate;
	win->line_buffer[0].char_buffer[win->col_size-1].refresh = true;
	win->line_buffer[0].char_buffer[win->col_size-1].terminal_char = corner[1];
	win->line_buffer[0].char_buffer[win->col_size-1].attribute = attribute_candidate;

	win->line_buffer[win->row_size-1].char_buffer[0].refresh = true;
	win->line_buffer[win->row_size-1].char_buffer[0].terminal_char = corner[2];
	win->line_buffer[win->row_size-1].char_buffer[0].attribute = attribute_candidate;
	win->line_buffer[win->row_size-1].char_buffer[win->col_size-1].refresh = true;
	win->line_buffer[win->row_size-1].char_buffer[win->col_size-1].terminal_char = corner[3];
	win->line_buffer[win->row_size-1].char_buffer[win->col_size-1].attribute = attribute_candidate;


	// Setting edges
	for(tech_size_t i = 1; i < win->col_size-1; i++){
		win->line_buffer[0].char_buffer[i].refresh = true;
		win->line_buffer[0].char_buffer[i].terminal_char = horizontal;
		win->line_buffer[0].char_buffer[i].attribute = attribute_candidate;

		win->line_buffer[win->row_size-1].char_buffer[i].refresh = true;
		win->line_buffer[win->row_size-1].char_buffer[i].terminal_char = horizontal;
		win->line_buffer[win->row_size-1].char_buffer[i].attribute = attribute_candidate;
	}

	for(tech_size_t i = 1; i < win->row_size-1; i++){
		win->line_buffer[i].char_buffer[0].refresh = true;
		win->line_buffer[i].char_buffer[0].terminal_char = vertical;
		win->line_buffer[i].char_buffer[0].attribute = attribute_candidate;

		win->line_buffer[i].char_buffer[win->col_size-1].refresh = true;
		win->line_buffer[i].char_buffer[win->col_size-1].terminal_char = vertical;
		win->line_buffer[i].char_buffer[win->col_size-1].attribute = attribute_candidate;
	}

}

