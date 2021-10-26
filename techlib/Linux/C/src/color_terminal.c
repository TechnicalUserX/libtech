#include "../include/color_terminal.h"

	void techlib_color_test_256_colors(void){
		for(int i = 0; i < 256; i++){
			char buf[256] = {0};
			strcpy(buf,"");
			strcat(buf,COLOR "38;5;");
			char code[16] = {0};
			sprintf(code,"%d",i);
			strcat(buf,code);
			strcat(buf,"m");
			printf("%s",buf);
			printf("%d\t",i);
			printf(CLEAR);
			if((i+1) % 16 == 0 && i != 0)
				printf("\n");

		}
    	printf("\n");
	}
