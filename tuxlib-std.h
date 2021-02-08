/*
 *	TechnicalUserX C/C++ Library
 */


#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#define and &&
#define or ||
#define not !
#define PI 3.1415926535897932384

/* If you want to use color macros inside Linux,
 * type: #define LINUX before including tuxstdlib.h
*/
#if defined(TUXLIB_WINDOWS)
	#include <windows.h>
	
	WORD WHITE_B = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
	WORD WHITE_F = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
	WORD BLACK_B = 0;


	WORD LGRAY_B = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
	WORD GRAY_B = BACKGROUND_INTENSITY;
	WORD GRAY_F = FOREGROUND_INTENSITY;
	WORD LGRAY_F = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

	WORD BLUE_B = BACKGROUND_BLUE;
	WORD BLUE_F = FOREGROUND_BLUE;
	WORD LBLUE_B = BACKGROUND_BLUE | BACKGROUND_INTENSITY;
	WORD LBLUE_F = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
	
	WORD GREEN_B = BACKGROUND_GREEN;
	WORD GREEN_F = FOREGROUND_GREEN;
	WORD LGREEN_B = BACKGROUND_GREEN | BACKGROUND_INTENSITY;
	WORD LGREEN_F = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	
	WORD RED_B = BACKGROUND_RED;
	WORD RED_F = FOREGROUND_RED;
	WORD LRED_B = BACKGROUND_RED | BACKGROUND_INTENSITY;
	WORD LRED_F = FOREGROUND_RED | FOREGROUND_INTENSITY;
	
	WORD AQUA_B = BACKGROUND_BLUE | BACKGROUND_GREEN;
	WORD AQUA_F = FOREGROUND_BLUE | FOREGROUND_GREEN;
	WORD LAQUA_B = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
	WORD LAQUA_F = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;	
	
	WORD YELLOW_B = BACKGROUND_RED | BACKGROUND_GREEN;
	WORD YELLOW_F = FOREGROUND_RED | FOREGROUND_GREEN;
	WORD LYELLOW_B = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
	WORD LYELLOW_F = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;	
	
	WORD PURPLE_B = BACKGROUND_RED | BACKGROUND_BLUE;
	WORD PURPLE_F = FOREGROUND_RED | FOREGROUND_BLUE;
	WORD LPURPLE_B = BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
	WORD LPURPLE_F = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		
#endif
#if defined(TUXLIB_LINUX) 
	#define COLOR "\033["
	#define RESET "0;"
	#define BOLD "1;"
	#define UNDERLINE "4;"
	#define INVERSE "7;"
	#define BOLDOFF "21;"
	#define UNDERLINEOFF "24;"
	#define INVERSEOFF "27;"
	#define CLEAR "\033[0m"
	
	#define BLACK "30m"
	#define RED "31m"
	#define GREEN "32m"
	#define YELLOW "33m"
	#define BLUE "34m"
	#define MAGENTA "35m"
	#define CYAN "36m"
	#define WHITE "37m"
	
	#define BLACK_B "40;"
	#define RED_B "41;"
	#define GREEN_B "42;"
	#define YELLOW_B "43;"
	#define BLUE_B "44;"
	#define MAGENTA_B "45;"
	#define CYAN_B "46;"
	#define WHITE_B "47;"
	#define GRAY_B "100;"
	#define LRED_B "101;"
	#define LGREEN_B "102;"
	#define LYELLOW_B "103;"
	#define LBLUE_B "104;"
	#define LPURPLE "105;"
	#define TEAL_B "106;"
	
#endif

//// C Custom String Functions ////
//// C Custom String Functions ////
//// C Custom String Functions ////

// String reversal function
// First paramter is the char pointer, second is the length of string.
char * strrev(char * word,int size){
    char *tmp = (char*)malloc((size+1)*sizeof(char));
    int length = strlen(word);
    for (int i = 0; i<strlen(word);i++){
        tmp[i] = word[length-1-i];
    }

    return tmp;
}


//// C Custom String Functions ////
//// C Custom String Functions ////
//// C Custom String Functions ////



// Supports decimal, max 8 Bytes.
char * convert_binary(long long l){
    int first_value = l;
    char * final = (char*)malloc(64*sizeof(char));
    strcpy(final,"");
    
    while(l) {
         
    if (l & 1 == 1)
        strcat(final, "1");
    else
        strcat(final, "0");


    l >>= 1;
    }
    

    return strrev(final,64);
}



// Sorts a string array within the given borders
void lex_order(int start,int end,char** list){
    bool not_sorted = true;
    while (not_sorted){
        not_sorted = false;
        char temp[10];
        for (int i = start;i<end;i++){
            int result = strcmp(list[i],list[i+1]);
            if ( result >0){
              
                    strcpy(temp,list[i+1]);
                    strcpy(list[i+1],list[i]);
                    strcpy(list[i],temp);
                    not_sorted = true;
                    strcpy(temp,"");

            }else if (result < 0){
            }
  
        }

    }


}


// Searches a string in a string array and returns the index number
int find_index(char* word,char** s,int length){
    
    for (int i =0;i<length;i++){
        
        if (!strcmp(word,s[i]))
            return i;
    }
    return -1;
}


// Searches a string within the given borders and returns the index number
int find_index_n(int start,int end,char* word,char** s){
    
    for (int i =start;i<end;i++){
        
        if (!strcmp(word,s[i]))
            return i;
    }
    return -1;
}

// Searches a string array for an index and returns the string value
char *find_member(int index,int size,char**s){
    for (int i =0;i<size;i++){
        
        if (index==i){
            char *temp = (char*)malloc(11*sizeof(char));
            strcpy(temp,s[i]);
            return temp;
        }
        
    }
    
    return "None";
}



//// C LIST IMPLEMENTATION //// [=================================================]
//// C LIST IMPLEMENTATION //// [=================================================]
//// C LIST IMPLEMENTATION //// [=================================================]

enum list_type{
	LIST_SINGLE = 1,
	LIST_DOUBLE = 2
};

typedef struct list{
	// Please initialize like: list* sample = NULL;
	struct list* next;
	struct list* prev;
	int value;
	bool type;
} list;

// List Functions

bool list_check_init(list* input_list){

	if ( input_list != NULL && input_list->type != LIST_SINGLE && input_list->type != LIST_DOUBLE )
		return 1;
	else 
		return 0;

}

void list_reverse(list** input_list){
	if (list_check_init(*input_list)){
		printf("List is not properly initialized, please use list* <name> = NULL\n");
		return;
	}
	if ( *input_list == NULL){
		printf("List is empty\n");
		return;
	}
	
	list* previous = NULL;
	list* current = (*input_list);

	while(current != NULL){

		list* next= current->next;

		current->next = previous;
		if (current->type)
			current->prev = next;
		previous = current;
		current=next;

	

	}
	(*input_list) = previous;
	

}

void list_print(list** input_list, int index){
	if (list_check_init(*input_list)){
		printf("List is not properly initialized, please use list* <name> = NULL\n");
		return;
	}
	
	if (*input_list== NULL){
		printf("List is empty\n");
		return;
	}
	list* current;
	int i;
	for (current = (*input_list),i = 0; current != NULL; current=current->next,i++){
		if (i == index){
			printf("%d\n", current->value);
			return;
		}


	}
	printf("Index out of range\n");
	return;
}

void list_print_all(list** input_list){
	if (list_check_init(*input_list)){
		printf("List is not properly initialized, please use list* <name> = NULL\n");
		return;
	}

	if (*input_list== NULL){
		printf("List is empty\n");
		return;
	}
	
	
	list* current;
	int i;
	for (current = (*input_list),i = 0; current != NULL; current=current->next,i++){
		
			printf("%d\n", current->value);
			

	}	
}

void list_free(list* input_list){
	if (list_check_init(input_list)){
		printf("List is not properly initialized, please use list* <name> = NULL\n");
		return;
	}

	if (input_list == NULL){
		return;
	}
	list* free_next = input_list->next;
	free(input_list);
	list_free(free_next);

}

void list_remove(list** input_list,int index){
	if (list_check_init(*input_list)){
		printf("List is not properly initialized, please use list* <name> = NULL\n");
		return;
	}
	if (input_list == NULL){
		printf("List is empty\n");
		return;
	}

	list* current;
	int i;
	for (i = 0,current=(*input_list); current != NULL; current=current->next,i++){
		
		if (index == 0 && i == 0){
			list* remove = current;
			(*input_list) = current->next;
			if (current->next->type)
				current->next->prev = NULL;

			free(remove);
			return;

		}


		if (index == i+1 && current->next != NULL){
			list* remove = current->next;
			
				if (current->next->next != NULL)
					if (current->next->next->type)
						current->next->next->prev = current;

				current->next = current->next->next;
			free(remove);
			return;
		}


	}
	printf("Index out of range\n");
	return;


}

void list_sort(list** input_list){
	if (   (*input_list) != NULL && (*input_list)->type != LIST_DOUBLE && (*input_list)->type != LIST_SINGLE ){
		printf("List is not properly initialized, please use NULL\n");
		return;		
	}
	
	bool not_sorted;
	list* current;
	while (not_sorted)
	{
		not_sorted = false;
		for (current = (*input_list); current->next != NULL; current=current->next){

				if (current->value > current->next->value){
					int temp = current->value;
					current->value = current->next->value;
					current->next->value = temp;
					not_sorted = true;
					break;
				}



		}


	} 
	



}

void list_insert_start(list** input_list, int value,enum list_type type){

	if (list_check_init(*input_list)){
		printf("List is not properly initialized, please use list* <name> = NULL\n");
		return;
	}

	
	


		
		if (type == LIST_SINGLE){
			list *current = (*input_list);
			list *new_list = (list*)malloc(sizeof(list));
			new_list->value = value;
			new_list->type = LIST_SINGLE;
			new_list->next = current;
			*input_list = new_list;
			return;

		}else if (type == LIST_DOUBLE){
			list *current = (*input_list);
			list *new_list = (list*)malloc(sizeof(list));
			new_list->value = value;
			new_list->type = LIST_DOUBLE;
			new_list->next = current;
			new_list->prev = NULL;
			*input_list = new_list;
			return;			

		}else {
			printf("Please enter a valid list type\n");
			return;
		}


	return;
}

void list_insert_end(list** input_list, int value,enum list_type type){
	if (list_check_init(*input_list)){
		printf("List is not properly initialized, please use list* <name> = NULL\n");
		return;
	}


	
	if ( (*input_list) == NULL){
		

		if (type == LIST_SINGLE){
			list *current = (*input_list);
			list *new_list = (list*)malloc(sizeof(list));
			new_list->value = value;
			new_list->type = LIST_SINGLE;
			new_list->next = current;
			*input_list = new_list;
			return;

		}
		else if (type == LIST_DOUBLE){
			list *current = (*input_list);
			list *new_list = (list*)malloc(sizeof(list));
			new_list->value = value;
			new_list->type = LIST_DOUBLE;
			new_list->next = current;
			new_list->prev = NULL;
			*input_list = new_list;
			return;			

		}
		else {
			printf("Please enter a valid list type\n");
			return;
		}


		return;
	}






	list *current;
	for (current = *(input_list); current != NULL; current = current->next){
		if (current->next == NULL){
			current->next = (list*)malloc(sizeof(list));
			current->next->value = value;
			current->next->next = NULL;

			if (type == LIST_SINGLE){
				current->next->type = LIST_SINGLE;
			}
			else if (type == LIST_DOUBLE){
				current->next->type = LIST_DOUBLE;
				current->next->prev = current;				
			}
			else {
				printf("List is not properly initialized, please use NULL\n");
				return;
			}
			return;
		}
	}



}

void list_insert_after(list* input_list, int value, enum list_type type){
	if (list_check_init(input_list)){
		printf("List is not properly initialized, please use list* <name> = NULL\n");
		return;
	}
	
	
	if (input_list==NULL){
		printf("List is empty\n");
		return;
	}



	if (type == LIST_SINGLE){
		list* new_node = (list*)malloc(sizeof(list));
		new_node->value = value;
		new_node->type = LIST_SINGLE;
		new_node->next = input_list->next;
		input_list->next = new_node;
		return;
	}
	else if (type == LIST_DOUBLE){
		list* new_node = (list*)malloc(sizeof(list));
		new_node->value = value;
		new_node->type = LIST_DOUBLE;
		new_node->prev = input_list;
		new_node->next = input_list->next;
		input_list->next = new_node;
		return;
	}
	else {
			printf("Please enter a valid list type\n");
			return;
	}



}

bool list_is_looping(list** input_list){
	if ((*input_list) == NULL){
		printf("List is empty\n");
		return false;
	}
	
	list* first,*second;
	first = (*input_list);
	second = (*input_list)->next;
	while(second != NULL){

		if (first == second)
			return true;


		if (second->next != NULL)
			second=second->next->next;
		else
			return false;

			first=first->next;


	}
	return false;



}

int list_count(list** input_list){
	int c = 0;
	list* temp = NULL;
	for (temp = (*input_list); temp != NULL; temp=temp->next){
		c++;
	}
	
	return c;



}


//// C LIST IMPLEMENTATION //// [=================================================]
//// C LIST IMPLEMENTATION //// [=================================================]
//// C LIST IMPLEMENTATION //// [=================================================]




// Randomization Functions

int rand_int(int start,int end){
	int gap = end-start;
	double n = sin(rand());
	int add = abs(round((double)gap*n));
	return start + add;
}

float rand_float(float start,float end){
	float gap = end-start;
	double n = sin(rand());
	float add = ((double)gap*n);
	if (add < 0)
		add*=-1;
	return start + add;
}

double rand_double(double start,double end){
	double gap = end-start;
	double n = sin(rand());
	double add = ((double)gap*n);
	if (add < 0)
		add*=-1;
	return start + add;
}



// Freeing Function

void pfree(void** reference){
	free(*reference);
	*reference = NULL;
}





