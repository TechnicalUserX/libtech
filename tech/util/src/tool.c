#include <tech/util/include/tool.h>


tech_byte_t tech_tool_convert_truecolor_to_xterm256(int r, int g, int b)
{
    int gray = (r == g) && (g == b);

    if (gray)
    {
        if (r < 8)
        {
            return 16;
        }
        if (r > 248)
        {
            return 231;
        }
        return 232 + ((r - 8) / 10);
    }

    int red = (r * 5 + 127) / 255;
    int green = (g * 5 + 127) / 255;
    int blue = (b * 5 + 127) / 255;

    return 16 + (red * 36) + (green * 6) + blue;
}

tech_byte_t tech_tool_convert_xterm256_to_xterm16(tech_byte_t color){

    if(color < 16){
        return (color % 8); // Increase the intensity manually later with bright macro
    }

    if(color < 52){

        if(color == 16){
            return 0;
        }
        if(color == 21){
            return 12;
        }
        for(int i = 16; i < 52; i+=7){
            if(color < i){
                return 4;
            }else if(color == i){
                return 6;
            }
        }
        return 2;
    }
    else if(color < 88){
        if(color == 52){
            return 1;
        }

        for(int i = 52; i < 88; i+=7){
            if(color < i){
                return 5;
            }else if(color == i){
                return 6;
            }
        }

        return 3;
    }else if(color < 124){


        if(color == 88){
            return 1;
        }

        for(int i = 88; i < 124; i+=7){
            if(color < i){
                return 13;
            }else if(color == i){
                return 7;
            }
        }

        return 10;


    }else if(color < 160){

        if(color == 124){
            return 1;
        }

        for(int i = 124; i < 160; i+=7){
            if(color < i){
                return 13;
            }else if(color == i){
                return 7;
            }
        }

        return 11;


    }else if(color < 196){

        if(color == 160){
            return 1;
        }

        for(int i = 160; i < 196; i+=7){
            if(color < i){
                return 13;
            }else if(color == i){
                return 7;
            }
        }

        return 11;

    }else{
        // Gray colors
        int scale = color % 24;

        if(scale < 6){
            return 0;
        }else if(scale < 12){
            return 8;
        }else if(scale < 18){
            return 7;
        }else{
            return 15;
        }

    }


}

tech_size_t tech_tool_multibyte_length(const char* stream){


	tech_size_t size = 0;
	tech_byte_t initial_byte;

	const char* iterator = stream;


	while(1){
		tech_size_t current_byte_size = 0;

		initial_byte = iterator[0];

		if(initial_byte == '\0'){
			return size;
		}

		if ((initial_byte & 0b11111000) == 0b11110000)
		{ // 1111 0000
			// 4 Byte UTF-8 Character
			current_byte_size = 4;
		}
		else if ((initial_byte & 0b11110000) == 0b11100000)
		{ // 1110 0000
			// 3 Byte UTF-8 Character
			current_byte_size = 3;
		}
		else if ((initial_byte & 0b11100000) == 0b11000000)
		{ // 1100 0000
			// 2 Byte UTF-8 Character
			current_byte_size = 2;
		}
		else if ((initial_byte & 0b11000000) == 0b10000000)
		{ // 1000 0000
			// 1 Byte UTF-8 Character
			current_byte_size = 1;
		}
		else
		{
			// 1 Byte ASCII Character
			current_byte_size = 1;
		}

		iterator += current_byte_size;
		size += 1;

	}
}

void tech_tool_hexdump(void* address, int size, int line){

    tech_byte_t* jumper = (tech_byte_t*)address;

    for(int i = 1; i <= size; i++){
        printf("%02X ", jumper[i-1]);
        if(i % line == 0)
            printf("\n");
        
        if(i % line == line/2 )
            printf(" ");
    }
    printf("\n");

}

tech_return_t tech_tool_fd_check_available_data(int fd, bool* check, struct timeval to){
    if (check == NULL)
    {
        tech_error_number = TECH_ERROR_NULL_POINTER;
        return TECH_RETURN_FAILURE;
    }

    bool buffer_available = false;

    struct timeval tv = to;
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(fd, &fds);
    buffer_available = (select(fd + 1, &fds, NULL, NULL, &tv));



    if (buffer_available > 0)
    {
        *check = true;
        tech_error_number = TECH_SUCCESS;
        return TECH_RETURN_SUCCESS;

    }
    else if (buffer_available == 0)
    {
        *check = false;
        tech_error_number = TECH_SUCCESS;
        return TECH_RETURN_SUCCESS;
    }
    else
    {
        tech_error_number = TECH_ERROR_TOOL_FD_CHECK_AVAILABLE_DATA_FAILED;
        return TECH_RETURN_FAILURE;
    }



}


tech_return_t tech_tool_file_basename(const char* path, tech_size_t path_size, char* basename, tech_size_t basename_size){

    if(path == NULL || basename == NULL){
        tech_error_number = TECH_ERROR_NULL_POINTER;
        return TECH_RETURN_FAILURE;
    }

    if(path_size == 0){
        tech_error_number = TECH_ERROR_SIZE_ZERO;
        return TECH_RETURN_FAILURE;
    }


    tech_size_t path_str_size = strnlen(path,path_size);

    // Search until the '/' is found
    for(tech_ssize_t i = path_str_size-1; i >= 0; i--){
        if(path[i] == '/'){
            // Found the location;
            strncpy(basename,path+i+1,basename_size-1);
            break;
        }else if(i == 0){
            strncpy(basename,path,basename_size-1);
            break;
        }

    }

    return TECH_RETURN_SUCCESS;
}

tech_return_t tech_tool_file_dirname(const char* path, tech_size_t path_size, char* dirname, tech_size_t dirname_size){
    
    if(path == NULL || dirname == NULL){
        tech_error_number = TECH_ERROR_NULL_POINTER;
        return TECH_RETURN_FAILURE;
    }

    if(path_size == 0){
        tech_error_number = TECH_ERROR_SIZE_ZERO;
        return TECH_RETURN_FAILURE;
    }
    
    tech_size_t path_str_size = strnlen(path,path_size);

    // Search until the '/' is found
    for(tech_ssize_t i = path_str_size-1; i >= 0; i--){
        if(i == 0){
            // Found the location;

            if(path[i] == '/'){
                strncpy(dirname,"/",dirname_size-1);

            }else{
                strncpy(dirname,".",dirname_size-1);
            }

            break;
        }else if(path[i] == '/'){
            char dir_str[path_str_size];
            bzero(dir_str,path_str_size);
            strncpy(dir_str,path,i);
            strncpy(dirname,dir_str,dirname_size-1);
            break;
        }

    }

    return TECH_RETURN_SUCCESS;
}

