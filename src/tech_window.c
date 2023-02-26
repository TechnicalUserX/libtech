#include "../include/tech_window.h"
#include "../include/tech_error.h"


tech_window_t *tech_window_new(tech_window_position_t origin_row, tech_window_position_t origin_col, tech_size_t row_size, tech_size_t col_size)
{

    if(row_size == 0 || col_size == 0){
        tech_error_number = TECH_ERROR_SIZE_ZERO;
        return TECH_RETURN_NULL;
    }


    tech_window_t *new_window = (tech_window_t*)malloc(sizeof(tech_window_t));

	if(new_window == NULL){
		tech_error_number = TECH_ERROR_CANNOT_ALLOC_MEMORY;
		return TECH_RETURN_NULL;
	}

    new_window->origin_col = origin_col;
    new_window->origin_row = origin_row;

	// Origin position are also relative positions to the top of the terminal screen
	// tech_window_new() function creates windows relative to top-left of terminal screen
	new_window->relative_row = origin_row; 
	new_window->relative_col = origin_col;

    new_window->col_size = col_size;
    new_window->row_size = row_size;

    // These are 0-indexed
    new_window->viewpoint.top = 0;
    new_window->viewpoint.bottom = row_size - 1;

    new_window->line_buffer_size = row_size;
    new_window->line_buffer = (tech_window_line_buffer_t *)malloc(sizeof(tech_window_line_buffer_t) * row_size);

	if(new_window->line_buffer == NULL){
		tech_error_number = TECH_ERROR_CANNOT_ALLOC_MEMORY;
		return TECH_RETURN_NULL;
	}

    for (tech_size_t i = 0; i < row_size; i++)
    {

        tech_window_line_buffer_t *current_line_buffer = (new_window->line_buffer + i);
        current_line_buffer->char_buffer_size = col_size;
        current_line_buffer->char_buffer = (tech_window_line_char_buffer_t *)malloc(sizeof(tech_window_line_char_buffer_t) * col_size);

		if(current_line_buffer->char_buffer == NULL){
			tech_error_number = TECH_ERROR_CANNOT_ALLOC_MEMORY;
			return TECH_RETURN_NULL;			
		}

        for (tech_size_t j = 0; j < col_size; j++)
        {

            memset(&(current_line_buffer->char_buffer[j].attribute), 0x0, sizeof(tech_terminal_attribute_t)); // Setting attributes to zero
            current_line_buffer->char_buffer[j].refresh = false;                                              // There is nothing to print
            memset(&(current_line_buffer->char_buffer[j].terminal_char), 0x0, sizeof(tech_terminal_char_t));
        }
    }

    return new_window;
}


tech_return_t tech_window_refresh(tech_window_t *win)
{

    if (win == NULL)
    {
		tech_error_number = TECH_ERROR_NULL_POINTER;
		return TECH_RETURN_FAILURE;
    }


	tech_window_position_t max_row_possible;
	tech_window_position_t max_col_possible;
	tech_window_position_t row_restriction;
	tech_window_position_t col_restriction;

	if(win->parent != NULL){
		tech_window_refresh(win->parent);

		win->origin_row = win->parent->origin_row + win->relative_row;
		win->origin_col = win->parent->origin_col + win->relative_col;

		max_row_possible = win->parent->row_size - win->origin_row;
		max_col_possible = win->parent->col_size - win->origin_col;

		if(max_row_possible > win->row_size){

			row_restriction = win->viewpoint.top + (win->row_size-1);

		}else{
			
			row_restriction = win->viewpoint.top + (max_row_possible-1);
		}

		if(max_col_possible > win->col_size){

			col_restriction =  win->col_size-1;
		}else{
			col_restriction = (max_col_possible-1);
		}

	}else{
		row_restriction = win->viewpoint.bottom;
		col_restriction = win->col_size-1;
	}




    // Top has lower value than bottom
    for (tech_size_t i = win->viewpoint.top; i <= row_restriction; i++)
    {
        for (tech_size_t j = 0; j <= col_restriction; j++)
        {

            if (win->line_buffer[i].char_buffer[j].refresh){

                tech_terminal_set_attribute(&(win->line_buffer[i].char_buffer[j].attribute));
                tech_terminal_stdout_print_char(win->origin_row + 1 + i, win->origin_col + 1 + j, win->line_buffer[i].char_buffer[j].terminal_char);
                win->line_buffer[i].char_buffer[j].refresh = false;
                tech_terminal_set_attribute(NULL); // Resetting attributes
            }
        }
    }
    
    tech_terminal_stdout_print(0,0,TECH_TERMINAL_ATTRIBUTE_CLEAR); // Reseting the attributes of the terminal
	tech_error_number = TECH_SUCCESS;
	return TECH_RETURN_SUCCESS;
}


tech_return_t tech_window_print(tech_window_t *win, tech_window_position_t row, tech_window_position_t col, tech_terminal_attribute_t *attribute, const char *format, ...){

    if (win == NULL)
    {
		tech_error_number = TECH_ERROR_NULL_POINTER;
		return TECH_RETURN_FAILURE;
    }

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

	tech_error_number = TECH_SUCCESS;
	return TECH_RETURN_SUCCESS;
}


tech_return_t tech_window_free(tech_window_t **win)
{

	if(win == NULL){
		tech_error_number = TECH_ERROR_NULL_POINTER;
		return TECH_RETURN_FAILURE;
	}
	if(*win == NULL){
		tech_error_number = TECH_ERROR_NULL_POINTER;
		return TECH_RETURN_FAILURE;		
	}

    for (tech_size_t i = 0; i < (*win)->row_size; i++)
    {
        free((**win).line_buffer[i].char_buffer);
    }

    free((**win).line_buffer);
    free(*win);
    *win = NULL;
    return TECH_RETURN_SUCCESS;
}


tech_return_t tech_window_border(tech_window_t* win,tech_terminal_attribute_t* attribute){


	if(win == NULL){
		tech_error_number = TECH_ERROR_NULL_POINTER;
		return TECH_RETURN_FAILURE;;
	}

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

	tech_error_number = TECH_SUCCESS;
	return TECH_RETURN_SUCCESS;
}


tech_return_t tech_window_clear(tech_window_t *win)
{

	if(win == NULL){
		tech_error_number = TECH_ERROR_NULL_POINTER;
		return TECH_RETURN_FAILURE;
	}

	tech_terminal_char_t explicit_empty_char = {
		.byte_size = 1,
		.bytes[0] = ' ',
		.is_control = false,
		.is_escape_sequence = false,
		.is_printable = true,
		.is_signal = false,
		.is_utf_8 = false};

	for (tech_size_t i = 0; i < win->row_size; i++)
	{

		for (tech_size_t j = 0; j < win->col_size; j++)
		{

			win->line_buffer[i].char_buffer[j].refresh = true;
			memset(&(win->line_buffer[i].char_buffer[j].attribute), 0x0, sizeof(tech_terminal_attribute_t));
			win->line_buffer[i].char_buffer[j].terminal_char = explicit_empty_char;
		}
	}
}


tech_return_t tech_window_resize(tech_window_t *win, tech_size_t new_row_size, tech_size_t new_col_size)
{

	if (win == NULL)
	{
		tech_error_number = TECH_ERROR_NULL_POINTER;
		return TECH_RETURN_FAILURE;
	}

	if (new_col_size == 0 || new_row_size == 0)
	{
		tech_error_number = TECH_ERROR_SIZE_ZERO;
		return TECH_RETURN_FAILURE;
	}

	// Deleting all char buffers
	for (tech_size_t i = 0; i < (*win).row_size; i++)
	{
		free((*win).line_buffer[i].char_buffer);
	}

	// Deleting line buffer
	free((*win).line_buffer);

	win->col_size = new_col_size;
	win->row_size = new_row_size;

	// These are 0-indexed
	win->viewpoint.top = 0;
	win->viewpoint.bottom = new_row_size - 1;

	win->line_buffer_size = new_row_size;
	win->line_buffer = (tech_window_line_buffer_t *)malloc(sizeof(tech_window_line_buffer_t) * new_row_size);

	if(win->line_buffer == NULL){
		tech_error_number = TECH_ERROR_CANNOT_ALLOC_MEMORY;
		return TECH_RETURN_FAILURE;
	}

	for (tech_size_t i = 0; i < new_row_size; i++)
	{

		tech_window_line_buffer_t *current_line_buffer = (win->line_buffer + i);
		current_line_buffer->char_buffer_size = new_col_size;
		current_line_buffer->char_buffer = (tech_window_line_char_buffer_t *)malloc(sizeof(tech_window_line_char_buffer_t) * new_col_size);

		if(current_line_buffer->char_buffer == NULL){
			tech_error_number = TECH_ERROR_CANNOT_ALLOC_MEMORY;
			return TECH_RETURN_FAILURE;
		}

		for (tech_size_t j = 0; j < new_col_size; j++)
		{

			memset(&(current_line_buffer->char_buffer[j].attribute), 0x0, sizeof(tech_terminal_attribute_t)); // Setting attributes to zero
			current_line_buffer->char_buffer[j].refresh = false;											  // There is nothing to print
			current_line_buffer->char_buffer[j].terminal_char = TECH_TERMINAL_CHAR_NULL_TERMINATOR;
		}
	}

	return TECH_RETURN_SUCCESS;
}


tech_window_t* tech_window_sub(tech_window_t* parent, tech_window_position_t relative_row, tech_window_position_t relative_col, tech_size_t row_size, tech_size_t col_size){

	if(parent == NULL){
		tech_error_number = TECH_ERROR_NULL_POINTER;
		return TECH_RETURN_NULL;
	}

	tech_window_position_t origin_row_candidate = parent->origin_row+relative_row;
	tech_window_position_t origin_col_candidate = parent->origin_col+relative_col;

	if((origin_row_candidate) >= (parent->origin_row + parent->row_size) ){
		tech_error_number = TECH_ERROR_INVALID_ARGUMENT;
		return TECH_RETURN_NULL;
	}


	if((origin_col_candidate) >= (parent->origin_col + parent->col_size) ){
		tech_error_number = TECH_ERROR_INVALID_ARGUMENT;
		return TECH_RETURN_NULL;
	}



	// Row size and col size are not restricted in size, but if the sub window has a parent, it will be restricted by its
	// parent's borders


	tech_window_t* new_sub_window = (tech_window_t*)malloc(sizeof(tech_window_t));

	new_sub_window->origin_row = origin_row_candidate;
	new_sub_window->origin_col = origin_col_candidate;

    new_sub_window->col_size = col_size;
    new_sub_window->row_size = row_size;

	new_sub_window->relative_row = relative_row;
	new_sub_window->relative_col = relative_col;

	new_sub_window->parent = parent;

    // These are 0-indexed
    new_sub_window->viewpoint.top = 0;
    new_sub_window->viewpoint.bottom = row_size - 1;

    new_sub_window->line_buffer_size = row_size;
    new_sub_window->line_buffer = (tech_window_line_buffer_t *)malloc(sizeof(tech_window_line_buffer_t) * row_size);

    for (tech_size_t i = 0; i < row_size; i++)
    {

        tech_window_line_buffer_t *current_line_buffer = (new_sub_window->line_buffer + i);
        current_line_buffer->char_buffer_size = col_size;
        current_line_buffer->char_buffer = (tech_window_line_char_buffer_t *)malloc(sizeof(tech_window_line_char_buffer_t) * col_size);

        for (tech_size_t j = 0; j < col_size; j++)
        {

            memset(&(current_line_buffer->char_buffer[j].attribute), 0x0, sizeof(tech_terminal_attribute_t)); // Setting attributes to zero
            current_line_buffer->char_buffer[j].refresh = false;                                              // There is nothing to print
            memset(&(current_line_buffer->char_buffer[j].terminal_char), 0x0, sizeof(tech_terminal_char_t));
        }
    }


    return new_sub_window;
}


tech_return_t tech_window_move(tech_window_t* win,tech_window_position_t new_row, tech_window_position_t new_col){

	if(win == NULL){
		tech_error_number = TECH_ERROR_NULL_POINTER;
		return TECH_RETURN_FAILURE;
	}

	if(win->parent == NULL){
		// Base window
		win->origin_row = new_row;
		win->origin_col = new_col;
		win->relative_row = new_row;
		win->relative_col = new_col;
	}else{
		// Sub window
		tech_window_position_t origin_row_candidate = win->parent->origin_row+new_row;
		tech_window_position_t origin_col_candidate = win->parent->origin_col+new_col;
		
		// You cannot move the window outside the parent
		if((origin_row_candidate) >= (win->parent->origin_row + win->parent->row_size) ){
			tech_error_number = TECH_ERROR_INVALID_ARGUMENT;
			return TECH_RETURN_FAILURE;
		}


		if((origin_col_candidate) >= (win->parent->origin_col + win->parent->col_size) ){
			tech_error_number = TECH_ERROR_INVALID_ARGUMENT;
			return TECH_RETURN_FAILURE;
		}

		win->origin_row = origin_row_candidate;
		win->origin_col = origin_col_candidate;

		win->relative_row = new_row;
		win->relative_col = new_col;


	}

	return TECH_RETURN_SUCCESS;
}	


