#ifndef TECH_MENU_H
#define TECH_MENU_H

#include <tech/config/tech_features.h>
#include <tech/shared/tech_include.h>
#include <tech/shared/tech_types.h>

#include <tech/terminal/tech_terminal.h>
#include <tech/terminal/graphics/include/tech_window.h>
#include <tech/util/include/tech_error.h>


#define TECH_MENU_ITEM_LINE_BUFFER_MAX_SIZE 256 // 64*4 -> 64 wide characters

#define TECH_MENU_ITEM_LINE_COUNT_MAX_SIZE 8

typedef struct tech_menu_item_line_struct_t
{
	tech_terminal_attribute_t attribute;
	tech_size_t line_buffer_size;
	char line_buffer[TECH_MENU_ITEM_LINE_BUFFER_MAX_SIZE];
} tech_menu_item_line_t;

typedef struct tech_menu_item_struct_t
{
	// First line is called identifier
	// Other lines are called details
	tech_size_t line_count;
	tech_menu_item_line_t lines[TECH_MENU_ITEM_LINE_COUNT_MAX_SIZE];

} tech_menu_item_t;

typedef struct tech_menu_struct_t
{
	// Window for the menu
	tech_window_t *window; 

	// Dimensions for an individual item
	tech_size_t menu_item_row_size;
	tech_size_t menu_item_col_size;

	// Dimensions for menu
	tech_size_t menu_row_size;
	tech_size_t menu_col_size;



	// menu_row_size * menu_col_size
	tech_size_t menu_page_size;

	// Items
	tech_size_t menu_item_size;
	tech_menu_item_t** menu_items;
	tech_size_t menu_item_size_reserved;

	tech_size_t menu_item_sub_window_size;
	tech_window_t** menu_item_sub_windows;
	tech_size_t menu_item_sub_window_size_reserved;

	tech_terminal_attribute_t menu_cursor_identifier;
	tech_terminal_attribute_t menu_cursor_details;

	// Viewpoint
	struct tech_menu_viewpoint_struct_t
	{
		tech_size_t first_item; // Lower index
		tech_size_t last_item;	// Higher index
	} viewpoint;

	tech_size_t menu_item_current_index;

} tech_menu_t;

typedef enum tech_menu_driver_directive_enum_t{
	TECH_MENU_DRIVER_DIRECTIVE_NEXT,
	TECH_MENU_DRIVER_DIRECTIVE_PREVIOUS,
	TECH_MENU_DRIVER_DIRECTIVE_UP,
	TECH_MENU_DRIVER_DIRECTIVE_DOWN,
	TECH_MENU_DRIVER_DIRECTIVE_LEFT,
	TECH_MENU_DRIVER_DIRECTIVE_RIGHT,
	TECH_MENU_DRIVER_DIRECTIVE_FIRST,
	TECH_MENU_DRIVER_DIRECTIVE_LAST
}tech_menu_driver_directive_t;

tech_menu_t* tech_menu_new(tech_size_t origin_row, tech_size_t origin_col, tech_size_t menu_row_size, tech_size_t menu_col_size, tech_size_t menu_item_row_size, tech_size_t menu_item_col_size, tech_size_t menu_item_size, tech_menu_item_t **menu_items, tech_terminal_attribute_t* menu_cursor_identifier,tech_terminal_attribute_t* menu_cursor_details);

tech_menu_item_t* tech_menu_item_new(tech_size_t line_buffer_size, tech_size_t line_count, const tech_menu_item_line_t *lines);

tech_return_t tech_menu_post(tech_menu_t *menu);

tech_return_t tech_menu_clear(tech_menu_t* menu);

tech_return_t tech_menu_refresh(tech_menu_t* menu);

tech_return_t tech_menu_driver(tech_menu_t* menu, tech_menu_driver_directive_t directive);

tech_return_t tech_menu_get_current_item(tech_menu_t* menu,tech_size_t* current_item );

tech_return_t tech_menu_resize(tech_menu_t* menu, tech_size_t menu_row_size, tech_size_t menu_col_size, tech_size_t menu_item_row_size, tech_size_t menu_item_col_size);

tech_return_t tech_menu_free(tech_menu_t** menu);

tech_return_t tech_menu_modify_item(tech_menu_t* menu, tech_size_t index, tech_menu_item_t* new_item);

tech_return_t tech_menu_append_item(tech_menu_t* menu,tech_menu_item_t* new_item);

tech_return_t tech_menu_remove_item(tech_menu_t* menu, tech_size_t index);

tech_return_t tech_menu_insert_item(tech_menu_t* menu, tech_size_t index, tech_menu_item_t* new_item);

tech_menu_item_t* tech_menu_get_item(tech_menu_t* menu, tech_size_t index);

tech_return_t tech_menu_get_item_size(tech_menu_t* menu, tech_size_t* item_size);


#endif