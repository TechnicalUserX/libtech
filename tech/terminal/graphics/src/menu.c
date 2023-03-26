#include <tech/terminal/graphics/include/menu.h>



tech_menu_t* tech_menu_new(tech_size_t origin_row, tech_size_t origin_col, tech_size_t menu_row_size, tech_size_t menu_col_size, tech_size_t menu_item_row_size, tech_size_t menu_item_col_size, tech_size_t menu_item_size, tech_menu_item_t **menu_items, tech_terminal_attribute_t* menu_cursor_identifier,tech_terminal_attribute_t* menu_cursor_details)
{



	if (menu_row_size == 0 || menu_col_size == 0)
	{
		tech_error_number = TECH_ERROR_SIZE_ZERO;
		return TECH_RETURN_NULL;
	}

	if (menu_item_row_size == 0 || menu_item_col_size == 0)
	{
		tech_error_number = TECH_ERROR_SIZE_ZERO;
		return TECH_RETURN_NULL;
	}

	tech_size_t window_row_size = menu_row_size * menu_item_row_size;
	tech_size_t window_col_size = menu_col_size * menu_item_col_size;

	tech_menu_t* new_menu = (tech_menu_t *)malloc(sizeof(tech_menu_t));



	if (new_menu == NULL)
	{
		tech_error_number = TECH_ERROR_CANNOT_ALLOC_MEMORY;
		return TECH_RETURN_NULL;
	}

	// Zeroing memory
	memset(new_menu,0x0,sizeof(tech_menu_t));



	new_menu->window = tech_window_new(origin_row, origin_col, window_row_size, window_col_size);

	if (new_menu->window == NULL)
	{
		tech_error_number = TECH_ERROR_CANNOT_ALLOC_MEMORY;
		return TECH_RETURN_NULL;
	}

	// Setting menu cursor
	memset(&new_menu->menu_cursor_identifier,0x0, sizeof(tech_terminal_attribute_t));
	memset(&new_menu->menu_cursor_details,0x0, sizeof(tech_terminal_attribute_t));


	if(menu_cursor_identifier != NULL){
		new_menu->menu_cursor_identifier = *menu_cursor_identifier;
	}else{
		tech_terminal_attribute_t default_menu_cursor = {.set_fg = true,.set_bold = true, .fg = {255,255,255}};
		new_menu->menu_cursor_identifier = default_menu_cursor;
	}
	if(menu_cursor_details != NULL){
		new_menu->menu_cursor_details = *menu_cursor_details;
	}else{
		new_menu->menu_cursor_details = new_menu->menu_cursor_identifier;
	}	

	new_menu->menu_row_size = menu_row_size;
	new_menu->menu_col_size = menu_col_size;

	new_menu->menu_item_row_size = menu_item_row_size;
	new_menu->menu_item_col_size = menu_item_col_size;

	new_menu->menu_page_size = menu_row_size * menu_col_size;

	new_menu->menu_item_current_index = 0;

	new_menu->menu_item_size = menu_item_size;

	new_menu->menu_item_sub_window_size = menu_row_size * menu_col_size;

	new_menu->viewpoint.first_item = 0;
	new_menu->viewpoint.last_item = (menu_item_size > new_menu->menu_item_sub_window_size) ? new_menu->menu_item_sub_window_size-1 : (menu_item_size == 0 ? 0 : menu_item_size - 1 ) ;


	new_menu->menu_item_sub_windows = (tech_window_t **)malloc(sizeof(tech_window_t *) * new_menu->menu_item_sub_window_size);

	if (new_menu->menu_item_sub_windows == NULL)
	{
		tech_error_number = TECH_ERROR_CANNOT_ALLOC_MEMORY;
		return TECH_RETURN_NULL;
	}

	new_menu->menu_item_sub_window_size_reserved = new_menu->menu_item_sub_window_size;

	// There will be (menu_row_size * menu_col_size) sub windows in this window and each will have the area of (menu_item_row_size * menu_item_col_size)

	tech_size_t window_counter = 0;

	for (tech_size_t i = 0; i < menu_row_size; i++)
	{

		for (tech_size_t j = 0; j < menu_col_size; j++)
		{

			// menu[i][j]
			new_menu->menu_item_sub_windows[window_counter] = tech_window_sub(new_menu->window, i * menu_item_row_size, j * menu_item_col_size, menu_item_row_size, menu_item_col_size);
			if (new_menu->menu_item_sub_windows[window_counter] == NULL){
				tech_error_number = TECH_ERROR_CANNOT_ALLOC_MEMORY;
				return TECH_RETURN_NULL;
			}
			window_counter++;

		}
	}



	// Item creation
	new_menu->menu_item_size = menu_item_size;
	new_menu->menu_item_size_reserved = menu_item_size;

	if(menu_item_size){
		
		new_menu->menu_items = (tech_menu_item_t **)malloc(sizeof(tech_menu_item_t*)*menu_item_size);

		if(new_menu->menu_items == NULL){
			tech_error_number = TECH_ERROR_NULL_POINTER;
			return TECH_RETURN_NULL;
		}


		for (tech_size_t i = 0; i < menu_item_size; i++)
		{
			new_menu->menu_items[i] = (tech_menu_item_t*)malloc(sizeof(tech_menu_item_t));
			new_menu->menu_items[i]->line_count = menu_items[i]->line_count;

			for (tech_size_t j = 0; j < menu_items[i]->line_count; j++)
			{
				new_menu->menu_items[i]->lines[j].attribute = menu_items[i]->lines[j].attribute;
				new_menu->menu_items[i]->lines[j].line_buffer_size = menu_items[i]->lines[j].line_buffer_size;
				strncpy(new_menu->menu_items[i]->lines[j].line_buffer, menu_items[i]->lines[j].line_buffer, TECH_MENU_ITEM_LINE_BUFFER_MAX_SIZE);
			}
		}

	}else{
		new_menu->menu_items = NULL;
	}




	return new_menu;
}

tech_menu_item_t* tech_menu_item_new(tech_size_t line_buffer_size, tech_size_t line_count, const tech_menu_item_line_t *lines)
{

	if (line_count == 0 || line_buffer_size == 0)
	{
		tech_error_number = TECH_ERROR_SIZE_ZERO;
		return TECH_RETURN_NULL;
	}

	if (line_buffer_size > TECH_MENU_ITEM_LINE_BUFFER_MAX_SIZE)
	{
		tech_error_number = TECH_ERROR_SIZE_EXCEED;
		return TECH_RETURN_NULL;
	}

	tech_menu_item_t *new_item = (tech_menu_item_t *)malloc(sizeof(tech_menu_item_t));

	new_item->line_count = line_count;

	for (tech_size_t i = 0; i < line_count; i++)
	{
		new_item->lines[i].attribute = lines[i].attribute;
		new_item->lines[i].line_buffer_size = lines[i].line_buffer_size;
		strncpy(new_item->lines[i].line_buffer, lines[i].line_buffer, lines[i].line_buffer_size);
	}

	return new_item;
}

tech_return_t tech_menu_post(tech_menu_t *menu)
{

	if (menu == NULL)
	{
		tech_error_number = TECH_ERROR_NULL_POINTER;
		return TECH_RETURN_FAILURE;
	}

	for (tech_size_t subwin_index = 0, item_index = menu->viewpoint.first_item; subwin_index < menu->menu_item_sub_window_size && item_index <= menu->viewpoint.last_item && menu->menu_item_size > 0; subwin_index++, item_index++)
	{
		// For each sub window
		// Printing to sub window

		tech_window_t *current_window = menu->menu_item_sub_windows[subwin_index];
		tech_menu_item_t* current_item = menu->menu_items[item_index];

		tech_size_t limited_line_count = (current_item->line_count > menu->menu_item_row_size) ? menu->menu_item_row_size : current_item->line_count;


		if(item_index == menu->menu_item_current_index){

			for (tech_size_t line_index = 0; line_index < limited_line_count; line_index++)
			{

				tech_menu_item_line_t current_line = current_item->lines[line_index];
				if(line_index == 0){
					tech_window_print(current_window, line_index, 0, &(menu->menu_cursor_identifier), "%*s",-menu->menu_item_col_size*4,  current_line.line_buffer);
				}else{
					tech_window_print(current_window, line_index, 0, &(menu->menu_cursor_details), "%*s", -menu->menu_item_col_size*4, current_line.line_buffer);
				}

			}

		}else{

			for (tech_size_t line_index = 0; line_index < limited_line_count; line_index++)
			{
				tech_menu_item_line_t current_line = current_item->lines[line_index];
				tech_window_print(current_window, line_index, 0, &(current_line.attribute), "%*s", -menu->menu_item_col_size*4, current_line.line_buffer);
			}

		}

	}
	tech_error_number = TECH_SUCCESS;
	return TECH_RETURN_SUCCESS;
}

tech_return_t tech_menu_clear(tech_menu_t* menu){

	if (menu == NULL)
	{
		tech_error_number = TECH_ERROR_NULL_POINTER;
		return TECH_RETURN_FAILURE;
	}

	for(tech_size_t i = 0; i < menu->menu_item_sub_window_size; i++){
		tech_window_clear(menu->menu_item_sub_windows[i]);
	}


	tech_error_number = TECH_SUCCESS;
	return TECH_RETURN_SUCCESS;
}

tech_return_t tech_menu_refresh(tech_menu_t* menu){
	if (menu == NULL)
	{
		tech_error_number = TECH_ERROR_NULL_POINTER;
		return TECH_RETURN_FAILURE;
	}

	for(tech_size_t i = 0; i < menu->menu_item_sub_window_size; i++){
		tech_window_refresh(menu->menu_item_sub_windows[i]);
	}


	tech_error_number = TECH_SUCCESS;
	return TECH_RETURN_SUCCESS;	
}

tech_return_t tech_menu_driver(tech_menu_t* menu, tech_menu_driver_directive_t directive){

	if(menu == NULL){
		tech_error_number = TECH_ERROR_NULL_POINTER;
		return TECH_RETURN_FAILURE;
	}

	if(menu->menu_item_size == 0){
		tech_error_number = TECH_ERROR_SIZE_ZERO;
		return TECH_RETURN_FAILURE;
	}

	// Calculate the current sub window index
	/*
		subwin index is between 0 and (page_size-1)
	*/
	tech_menu_driver_directive_t current_directive = directive;
	// 1-indexed
	tech_size_t current_page = (menu->menu_item_current_index / menu->menu_page_size) + 1;

	tech_size_t total_pages = (menu->menu_item_size / menu->menu_page_size) + ( menu->menu_item_size % menu->menu_page_size == 0 ? 0 : 1);

	tech_size_t page_local_item_index = menu->menu_item_current_index - ((current_page-1) *menu->menu_page_size);

	tech_size_t last_page_size = (menu->menu_item_size - ((total_pages-1)*menu->menu_page_size));

	switch(current_directive){
		case TECH_MENU_DRIVER_DIRECTIVE_RIGHT:
		case TECH_MENU_DRIVER_DIRECTIVE_NEXT:{


			// Already the last item
			if(page_local_item_index == (menu->menu_page_size-1) || (page_local_item_index == (last_page_size-1) && current_page == total_pages ) ){

				menu->menu_item_current_index = (menu->menu_item_current_index + 1) % (menu->menu_item_size); // This will ensure that the item stays in the limited area

				menu->viewpoint.first_item = menu->menu_item_current_index;
				menu->viewpoint.last_item = (menu->viewpoint.first_item + menu->menu_page_size <= menu->menu_item_size ) ? menu->viewpoint.first_item - 1 + menu->menu_page_size : menu->viewpoint.first_item  + last_page_size - 1;

			}else{
				menu->menu_item_current_index++;
			}



		}break;


		case TECH_MENU_DRIVER_DIRECTIVE_LEFT:
		case TECH_MENU_DRIVER_DIRECTIVE_PREVIOUS:{

			// Already the first item
			if(page_local_item_index == 0){

				if(current_page == 1){

					menu->menu_item_current_index = menu->menu_item_size-1;

					menu->viewpoint.first_item = (total_pages-1)*menu->menu_page_size;

					menu->viewpoint.last_item = menu->viewpoint.first_item + last_page_size-1;


				}else{
					menu->menu_item_current_index--;
					
					menu->viewpoint.first_item = (current_page-2)*menu->menu_page_size;
					menu->viewpoint.last_item = menu->viewpoint.first_item + menu->menu_page_size - 1;

				}

			}else{
				menu->menu_item_current_index--;
			}

		}break;


		case TECH_MENU_DRIVER_DIRECTIVE_FIRST:{

			menu->menu_item_current_index = 0;
			menu->viewpoint.first_item = 0;
			menu->viewpoint.last_item = ( total_pages > 1 ) ? menu->menu_page_size-1 : last_page_size-1;

		}break;


		case TECH_MENU_DRIVER_DIRECTIVE_LAST:{

			menu->menu_item_current_index = menu->menu_item_size-1;

			menu->viewpoint.first_item = (total_pages-1)*menu->menu_page_size;
			menu->viewpoint.last_item = menu->viewpoint.first_item + last_page_size - 1;


		}break;


		case TECH_MENU_DRIVER_DIRECTIVE_UP:{


			tech_size_t current_row = (menu->menu_item_current_index - (current_page-1)*menu->menu_page_size) / menu->menu_col_size;
			tech_size_t current_col = menu->menu_item_current_index % menu->menu_col_size;

			if(current_row > 0){
				menu->menu_item_current_index -= menu->menu_col_size;
			}else{	
				// Row is 0

				if(current_col == 0){
					// Switch page backward

					if(current_page == 1){

						menu->menu_item_current_index = menu->menu_item_size-1;

						menu->viewpoint.first_item = ((total_pages-1)*menu->menu_page_size);
						menu->viewpoint.last_item = menu->viewpoint.first_item + last_page_size-1;


					}else{
						menu->menu_item_current_index--;
						
						menu->viewpoint.first_item = (current_page-2)*menu->menu_page_size;
						menu->viewpoint.last_item = menu->viewpoint.first_item + menu->menu_page_size - 1;

					}					

				}else{
					// Go left and down
					// Bust must check whether the left and down item exists


					tech_size_t item_current_index_candidate = (menu->menu_item_current_index + (menu->menu_col_size* (menu->menu_row_size - 1))) - 1;

					while(item_current_index_candidate > menu->menu_item_size-1 ){
						item_current_index_candidate -= menu->menu_col_size;
					}
				
					menu->menu_item_current_index = item_current_index_candidate;
				
				}		

			}

		}break;


		case TECH_MENU_DRIVER_DIRECTIVE_DOWN:{

			tech_size_t current_row = (menu->menu_item_current_index - (current_page-1)*menu->menu_page_size) / menu->menu_col_size;
			tech_size_t current_col = menu->menu_item_current_index % menu->menu_col_size;




			if( current_row < (menu->menu_row_size-1) ){
				// This is not the last row


				if( (menu->menu_item_current_index + menu->menu_col_size) <= (menu->menu_item_size-1) ){
					// This is not the last row and there is an item at the bottom

					menu->menu_item_current_index += menu->menu_col_size;
				}else{
					// There is no item at the bottom, looking for up right


					if(menu->menu_item_current_index == menu->viewpoint.first_item + last_page_size - 1){
						// This is the last item on the last page

						menu->menu_item_current_index = (menu->menu_item_current_index + 1) % (menu->menu_item_size); // This will ensure that the item stays in the limited area

						menu->viewpoint.first_item = menu->menu_item_current_index;
						menu->viewpoint.last_item = (menu->viewpoint.first_item + menu->menu_page_size <= menu->menu_item_size ) ? menu->viewpoint.first_item - 1 + menu->menu_page_size : menu->viewpoint.first_item  + last_page_size - 1;


					}else{
							// Looking for up right

							tech_size_t item_current_index_candidate = menu->menu_item_current_index - (current_row*menu->menu_col_size ) + 1 ;

							menu->menu_item_current_index = item_current_index_candidate;

					}


			
				}


			}else{
				// We are at the last row possible

				if(current_page == total_pages){
					// The last item is determined by last_page_size

					if(menu->menu_item_current_index == menu->viewpoint.first_item + (last_page_size-1)){
						// The last item is selected
						tech_size_t current_page_index = current_page - 1;
						tech_size_t next_page = ((current_page_index + 1) % total_pages) + 1;

						menu->menu_item_current_index = (next_page-1)*menu->menu_page_size ; // This will ensure that the item stays in the limited area
						menu->viewpoint.first_item = menu->menu_item_current_index;
						menu->viewpoint.last_item = (menu->viewpoint.first_item + menu->menu_page_size <= menu->menu_item_size ) ? menu->viewpoint.first_item - 1 + menu->menu_page_size : menu->viewpoint.first_item  + last_page_size - 1;
					}else{
						// There are still items 

						tech_size_t item_current_index_candidate = menu->menu_item_current_index;
						item_current_index_candidate++;

						while(item_current_index_candidate > ( ((current_page-1)*menu->menu_page_size) + menu->menu_col_size) ){
							item_current_index_candidate -= menu->menu_col_size;
						}


						menu->menu_item_current_index = item_current_index_candidate;	
					}


				}else{
					// The page is full

					if(current_col == (menu->menu_col_size-1)){
						// We are at the right bottom, we need page change

						tech_size_t current_page_index = current_page - 1;
						tech_size_t next_page_index = ((current_page_index + 1) % total_pages);
						tech_size_t next_page = next_page_index + 1;

						menu->menu_item_current_index = (next_page-1)*menu->menu_page_size ; // This will ensure that the item stays in the limited area

						menu->viewpoint.first_item = menu->menu_item_current_index;
						menu->viewpoint.last_item = (menu->viewpoint.first_item + menu->menu_page_size <= menu->menu_item_size ) ? menu->viewpoint.first_item - 1 + menu->menu_page_size : menu->viewpoint.first_item  + last_page_size - 1;
					
					}else{

						// Go up right
						// There are still items at the right side so go up and right
						tech_size_t item_current_index_candidate = menu->menu_item_current_index - ( (menu->menu_row_size-1) * menu->menu_col_size ) + 1 ; 

						menu->menu_item_current_index = item_current_index_candidate;	

					}

				}

			}

		}break;


	}
	tech_menu_clear(menu);
	tech_menu_post(menu);
	tech_error_number = TECH_SUCCESS;
	return TECH_RETURN_SUCCESS;
}

tech_return_t tech_menu_get_current_item_index(tech_menu_t* menu,tech_size_t* current_item_index ){
	if (menu == NULL)
	{
		tech_error_number = TECH_ERROR_NULL_POINTER;
		return TECH_RETURN_FAILURE;
	}
	if(menu->menu_item_size == 0){
		tech_error_number = TECH_ERROR_SIZE_ZERO;
		return TECH_RETURN_FAILURE;
	}
	*current_item_index = menu->menu_item_current_index;
	tech_error_number = TECH_SUCCESS;
	return TECH_RETURN_SUCCESS;
}

tech_return_t tech_menu_resize(tech_menu_t* menu, tech_size_t menu_row_size, tech_size_t menu_col_size, tech_size_t menu_item_row_size, tech_size_t menu_item_col_size){

	// If a size value is zero, then the existing size will be used from the menu
	if (menu == NULL){

		tech_error_number = TECH_ERROR_NULL_POINTER;
		return TECH_RETURN_FAILURE;
	}


	tech_size_t menu_row_size_candidate = (menu_row_size == 0) ? menu->menu_row_size : menu_row_size;
	tech_size_t menu_col_size_candidate = (menu_col_size == 0) ? menu->menu_col_size : menu_col_size;
	tech_size_t menu_item_row_size_candidate = (menu_item_row_size == 0) ? menu->menu_item_row_size : menu_item_row_size;
	tech_size_t menu_item_col_size_candidate = (menu_item_col_size == 0) ? menu->menu_item_col_size : menu_item_col_size;

	tech_size_t menu_item_sub_window_size_candidate = menu_row_size_candidate * menu_col_size_candidate;

	menu->menu_row_size = menu_row_size_candidate;
	menu->menu_col_size = menu_col_size_candidate;

	menu->menu_item_row_size = menu_item_row_size_candidate;
	menu->menu_item_col_size = menu_item_col_size_candidate;

	menu->menu_page_size = menu_row_size_candidate * menu_col_size_candidate;

	// Viewpoint will obey to the sizes defined here


	if(menu_item_sub_window_size_candidate <= menu->menu_item_sub_window_size_reserved){
		// We have enough resource
		menu->menu_item_sub_window_size = menu_item_sub_window_size_candidate;
	}else{

		// New resource must be generated

		for(tech_size_t i = 0; i < menu->menu_item_sub_window_size_reserved; i++){
			tech_window_free(&(menu->menu_item_sub_windows[i]));
		}
		free(menu->menu_item_sub_windows);

		tech_window_t** new_sub_windows = (tech_window_t**)malloc(sizeof(tech_window_t*)*menu_item_sub_window_size_candidate);
	
		if (new_sub_windows == NULL){

			tech_error_number = TECH_ERROR_CANNOT_ALLOC_MEMORY;
			return TECH_RETURN_FAILURE;
		}
		
		menu->menu_item_sub_windows = new_sub_windows;

		tech_size_t window_counter = 0;

		if(tech_window_resize(menu->window, menu_row_size_candidate*menu_item_row_size_candidate, menu_col_size_candidate*menu_item_col_size_candidate)){
			tech_error_number = TECH_ERROR_CANNOT_ALLOC_MEMORY;
			return TECH_RETURN_FAILURE;
		}

		for (tech_size_t i = 0; i < menu_row_size_candidate; i++)
		{

			for (tech_size_t j = 0; j < menu_col_size_candidate; j++)
			{

				// menu[i][j]
				menu->menu_item_sub_windows[window_counter] = tech_window_sub(menu->window, i * menu_item_row_size_candidate, j * menu_item_col_size_candidate, menu_item_row_size_candidate, menu_item_col_size_candidate);
				if (menu->menu_item_sub_windows[window_counter] == NULL)
				{

					tech_error_number = TECH_ERROR_CANNOT_ALLOC_MEMORY;
					return TECH_RETURN_FAILURE;
				}
				window_counter++;
			}
		}

		menu->menu_item_sub_window_size = menu_item_sub_window_size_candidate;
		menu->menu_item_sub_window_size_reserved = menu_item_sub_window_size_candidate;
	}





	// menu->viewpoint.first_item = menu->menu_item_current_index;
	// menu->viewpoint.last_item = (menu->menu_item_size > menu->menu_item_sub_window_size) ? menu->menu_item_sub_window_size-1 : menu->menu_item_size-1;

	tech_size_t current_page = (menu->menu_item_current_index / menu->menu_page_size) + 1;

	tech_size_t total_pages = (menu->menu_item_size / menu->menu_page_size) + ( menu->menu_item_size % menu->menu_page_size == 0 ? 0 : 1);

	tech_size_t last_page_size = (menu->menu_item_size - (total_pages-1)*menu->menu_page_size);


	menu->viewpoint.first_item = ((current_page-1)*menu->menu_page_size);

	if(current_page == total_pages){
		menu->viewpoint.last_item = menu->viewpoint.first_item + last_page_size - 1;
	}else{
		menu->viewpoint.last_item = menu->viewpoint.first_item + menu->menu_page_size - 1;

	}
	tech_error_number = TECH_SUCCESS;
	return TECH_RETURN_SUCCESS;
}

tech_return_t tech_menu_free(tech_menu_t** menu){

	if(menu == NULL){
		tech_error_number = TECH_SUCCESS;
		return TECH_RETURN_SUCCESS;
	}

	if(*menu == NULL){
		tech_error_number = TECH_SUCCESS;
		return TECH_RETURN_SUCCESS;
	}


	for(tech_size_t i = 0; i < (*menu)->menu_item_sub_window_size_reserved; i++){
		tech_window_free(&((*menu)->menu_item_sub_windows[i]));
	}
	free((*menu)->menu_item_sub_windows );

	for(tech_size_t i = 0; i < (*menu)->menu_item_size_reserved; i++){
		free((*menu)->menu_items[i]);
	}
	free((*menu)->menu_items);

	tech_window_free(&((*menu)->window));

	free(*menu);
	*menu = NULL;
	tech_error_number = TECH_SUCCESS;
	return TECH_RETURN_SUCCESS;
}

tech_return_t tech_menu_assign_item(tech_menu_t* menu, tech_size_t index, tech_menu_item_t* new_item){
	if (menu == NULL){
		tech_error_number = TECH_ERROR_NULL_POINTER;
		return TECH_RETURN_FAILURE;
	}

	if(new_item == NULL){
		tech_error_number = TECH_ERROR_NULL_POINTER;
		return TECH_RETURN_FAILURE;
	}


	if(index >= menu->menu_item_size){
		tech_error_number = TECH_ERROR_SIZE_EXCEED;
		return TECH_RETURN_FAILURE;
	}


	free(menu->menu_items[index]);

	menu->menu_items[index] = new_item;

	tech_error_number = TECH_SUCCESS;
	return TECH_RETURN_SUCCESS;
}

tech_return_t tech_menu_append_item(tech_menu_t* menu,tech_menu_item_t* new_item){
	// This will add the item to the end of the item list
	if (menu == NULL){
		tech_error_number = TECH_ERROR_NULL_POINTER;
		return TECH_RETURN_FAILURE;
	}

	
	tech_menu_item_t* new_item_candidate = (tech_menu_item_t*)malloc(sizeof(tech_menu_item_t));
	*new_item_candidate = *new_item;


	if(menu->menu_item_size == menu->menu_item_size_reserved){
		// Need room for one more
		tech_menu_item_t** new_item_list = (tech_menu_item_t**)malloc(sizeof(tech_menu_item_t*)*(menu->menu_item_size_reserved+1));

		for(tech_size_t i = 0; i < menu->menu_item_size; i++){
			new_item_list[i] = menu->menu_items[i];
		}
		
		new_item_list[menu->menu_item_size] = new_item_candidate;

		free(menu->menu_items);

		menu->menu_items = new_item_list;
		menu->menu_item_size_reserved++;


	}else{
		// Enough room

		menu->menu_items[menu->menu_item_size] = new_item_candidate;

	}


	if(menu->viewpoint.last_item - menu->viewpoint.first_item < (menu->menu_page_size-1) && menu->menu_item_size > 0){

		menu->viewpoint.last_item++;
	}

	menu->menu_item_size++;
	tech_error_number = TECH_SUCCESS;
	return TECH_RETURN_SUCCESS;
}

tech_return_t tech_menu_remove_item(tech_menu_t* menu, tech_size_t index){
	// Removing does not change the reserved size, but rotates everything to left
	if (menu == NULL){
		tech_error_number = TECH_ERROR_NULL_POINTER;
		return TECH_RETURN_FAILURE;
	}

	if(menu->menu_item_size == 0){
		tech_error_number = TECH_ERROR_SIZE_ZERO;
		return TECH_RETURN_FAILURE;
	}

	if(index >= menu->menu_item_size){
		// Removing items out of index is not allowed
		tech_error_number = TECH_ERROR_SIZE_EXCEED;
		return TECH_RETURN_FAILURE;
	}


	free(menu->menu_items[index]);

	for(tech_size_t i = index; i < menu->menu_item_size-1; i++){
		menu->menu_items[i] = menu->menu_items[i+1];
	}




	// Change viewpoint


	// Check if there is more data
	if((menu->menu_item_size-1) == menu->viewpoint.last_item){

		// We are on the last page
		// Viewpoint must be decreased

		if(menu->viewpoint.first_item == menu->viewpoint.last_item){
			// Deletion of a specific item does not matter
			// Only thing that matters is the viewpoint
			// Page change required

			if(menu->viewpoint.first_item != 0){
				
				// There is a page behind
				menu->viewpoint.first_item -= (menu->menu_page_size);
				menu->viewpoint.last_item = menu->viewpoint.first_item + (menu->menu_page_size-1);
			}	

		}else{
			// decrease only by one
			menu->viewpoint.last_item--;
		}

	}

	menu->menu_item_size--;
	menu->menu_item_size_reserved--;

		// Do not change
	

	tech_error_number = TECH_SUCCESS;
	return TECH_RETURN_SUCCESS;
}

tech_return_t tech_menu_insert_item(tech_menu_t* menu, tech_size_t index, tech_menu_item_t* new_item){
	if (menu == NULL){
		tech_error_number = TECH_ERROR_NULL_POINTER;
		return TECH_RETURN_FAILURE;
	}




	if(index >= menu->menu_item_size){
		if(tech_menu_append_item(menu,new_item) == TECH_RETURN_SUCCESS){
			tech_error_number = TECH_SUCCESS;
			return TECH_RETURN_SUCCESS;
		}else{
			return TECH_RETURN_FAILURE;
		}
	
	}else{

		tech_menu_item_t* new_item_candidate = (tech_menu_item_t*)malloc(sizeof(tech_menu_item_t));
		*new_item_candidate = *new_item;

		tech_menu_item_t** new_item_list = (tech_menu_item_t**)malloc(sizeof(tech_menu_item_t*)*(menu->menu_item_size_reserved+1));

		for(tech_size_t i = 0,j = 0; i < menu->menu_item_size; j++){

			if(j == index){
				new_item_list[j] = new_item_candidate;
			}else{
				new_item_list[j] = menu->menu_items[i];
				i++;
			}

		}

		free(menu->menu_items);
		menu->menu_items = new_item_list;

		if(menu->viewpoint.last_item - menu->viewpoint.first_item < (menu->menu_page_size-1) && menu->menu_item_size > 0){
			menu->viewpoint.last_item++;
		}

		menu->menu_item_size++;
		menu->menu_item_size_reserved++;
	}



	tech_error_number = TECH_SUCCESS;
	return TECH_RETURN_SUCCESS;	
}

tech_menu_item_t* tech_menu_get_item(tech_menu_t* menu, tech_size_t index){
	// This returns a reference
	if (menu == NULL){
		tech_error_number = TECH_ERROR_NULL_POINTER;
		return TECH_RETURN_NULL;
	}

	if(index >= menu->menu_item_size){
		tech_error_number = TECH_ERROR_SIZE_EXCEED;
		return TECH_RETURN_NULL;
	}


	tech_error_number = TECH_SUCCESS;
	return menu->menu_items[index];
}

tech_return_t tech_menu_get_item_size(tech_menu_t* menu, tech_size_t* item_size){
	if (menu == NULL){
		tech_error_number = TECH_ERROR_NULL_POINTER;
		return TECH_RETURN_FAILURE;
	}
	if (item_size == NULL){
		tech_error_number = TECH_ERROR_NULL_POINTER;
		return TECH_RETURN_FAILURE;
	}


	*item_size = menu->menu_item_size;

	tech_error_number = TECH_SUCCESS;
	return TECH_RETURN_SUCCESS;
}
