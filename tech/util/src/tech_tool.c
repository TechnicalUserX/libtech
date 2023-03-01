#include <tech/util/include/tech_tool.h>

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
