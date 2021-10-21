 //===================================================================================================//
/**
 *  WRITER: TechnicaluserX
 *  
 *  C/C++ Dynamic Memory Based List Implementation
 *  Please note that this library is intended mainly for C but you can 
 *  use this library with C++
 *  
 *  LICENSE: This library is currently not under any license and it is free to modify/distribute. 
 * 
 * 
 *  IMPORTANT: This library uses the name "list" in order to represent the list data type.
 *  This might cause conflicts with the C++ data type "list", please do not use both types together.
 *  If you are using C++, proceed with caution.
 *  
 * 
 *  ERRORS: If you want to disable list error messages, #define TECHLIB_LIST_DISABLE_ERRORS
 *  You can change the null return value of list_get_string function by changing
 *  LIST_GET_STRING_RETURN_NULL down below. 
 * 
 * 
 *  Please do not forget to de-allocate the memory reserved for the list with the list_clear() function,
 *  you can also use the "function pointer" version of this function.
 * 
 *  
 */
 //===================================================================================================//


// INCLUDE //

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#ifndef _TECHLIB_LIST_H
#define _TECHLIB_LIST_H


#define LIST_GET_STRING_RETURN_NULL "(NULL)"



// Error messages //

#define LIST_ERROR_ALLOCATION                       "List Error: Memory couldn't have been allocated."
#define LIST_ERROR_GET_OUT_OF_RANGE                 "List Error: get() index out of range."
#define LIST_ERROR_GET_TYPE_MISMATCH                "List Error: get() data type mismatch."
#define LIST_ERROR_SET_OUT_OF_RANGE                 "List Error: set() index out of range."
#define LIST_ERROR_REMOVE_OUT_OF_RANGE              "List Error: remove() index out of range."
#define LIST_ERROR_INSERT_OUT_OF_RANGE              "List Error: insert() index out of range."
#define LIST_ERROR_INCORRECT_TYPE_INITIALIZATION    "List Error: Incorrect list type initialzation -> (Unknown type)."
#define LIST_ERROR_AT_OUT_OF_RANGE                  "List Error: at() index out of range."
#define LIST_ERROR_SORT_TYPE_INCONSISTENT           "List Error: Cannot sort due to type inconsistency."


/// Type Definitions ///

typedef struct list list;


typedef enum list_type{
    LIST_TYPE_SEQUENTIAL,
    LIST_TYPE_SINGLE_LINKED,
    LIST_TYPE_DOUBLE_LINKED
}list_type;


typedef enum list_object_type{
    LIST_INT,
    LIST_UINT,
    LIST_SHORT,
    LIST_USHORT,
    LIST_LONGLONG,
    LIST_ULONGLONG,
    LIST_FLOAT,
    LIST_DOUBLE,
    LIST_LONGDOUBLE,
    LIST_CHAR,
    LIST_UCHAR,
    LIST_STRING
}list_object_type;



typedef enum list_sort_type{
    LIST_SORT_TYPE_ASCENDING,
    LIST_SORT_TYPE_DESCENDING
}list_sort_type;


typedef struct list_object{

    void* data;
    list_object_type type;
    
    struct list_object* next;
    struct list_object* prev;

}list_object;

typedef struct list_append{
    void (*_int_)(struct list* l,int element);
    void (*_uint_)(struct list* l,unsigned int element);
    void (*_short_)(struct list* l,short element);
    void (*_ushort_)(struct list* l,unsigned short element);
    void (*_longlong_)(struct list* l,long long element);
    void (*_ulonglong_)(struct list* l,unsigned long long element);
    void (*_float_)(struct list* l,float element);
    void (*_double_)(struct list* l,double element);
    void (*_longdouble_)(struct list* l,long double element);
    void (*_char_)(struct list* l,char element);
    void (*_uchar_)(struct list* l,unsigned char element);
    void (*_string_)(struct list* l,const char* element);
        
}list_append;

typedef struct list_prepend{
    void (*_int_)(struct list* l, int element);
    void (*_uint_)(struct list* l, unsigned int element);
    void (*_short_)(struct list* l, short element);
    void (*_ushort_)(struct list* l, unsigned short element);
    void (*_longlong_)(struct list* l, long long element);
    void (*_ulonglong_)(struct list* l, unsigned long long element);
    void (*_float_)(struct list* l, float element);
    void (*_double_)(struct list* l, double element);
    void (*_longdouble_)(struct list* l, long double element);
    void (*_char_)(struct list* l, char element);
    void (*_uchar_)(struct list* l, unsigned char element);
    void (*_string_)(struct list* l, const char* element);


}list_prepend;

typedef struct list_insert{
    void (*_int_)(struct list* l,int index, int element);
    void (*_uint_)(struct list* l,int index, unsigned int element);
    void (*_short_)(struct list* l,int index, short element);
    void (*_ushort_)(struct list* l,int index, unsigned short element);
    void (*_longlong_)(struct list* l,int index, long long element);
    void (*_ulonglong_)(struct list* l,int index, unsigned long long element);
    void (*_float_)(struct list* l,int index, float element);
    void (*_double_)(struct list* l,int index, double element);
    void (*_longdouble_)(struct list* l,int index, long double element);
    void (*_char_)(struct list* l,int index, char element);
    void (*_uchar_)(struct list* l,int index, unsigned char element);
    void (*_string_)(struct list* l,int index, const char* element);
}list_insert;


typedef struct list_get{
    int                 (*_int_)(struct list* l, int index);
    unsigned int        (*_uint_)(struct list* l, int index);
    short               (*_short_)(struct list* l, int index);
    unsigned short      (*_ushort_)(struct list* l, int index);
    long long           (*_longlong_)(struct list* l, int index);
    unsigned long long  (*_ulonglong_)(struct list* l, int index);
    float               (*_float_)(struct list* l, int index);
    double              (*_double_)(struct list* l, int index);
    long double         (*_longdouble_)(struct list* l, int index);
    char                (*_char_)(struct list* l, int index);
    unsigned char       (*_uchar_)(struct list* l, int index);
    char*               (*_string_)(struct list* l, int index);
}list_get;

typedef struct list_set{
    void (*_int_)(struct list* l, int index, int element);
    void (*_uint_)(struct list* l, int index, unsigned int element);
    void (*_short_)(struct list* l, int index, short element);
    void (*_ushort_)(struct list* l, int index, unsigned short element);
    void (*_longlong_)(struct list* l, int index, long long element);
    void (*_ulonglong_)(struct list* l, int index, unsigned long long element);
    void (*_float_)(struct list* l, int index, float element);
    void (*_double_)(struct list* l, int index, double element);
    void (*_longdouble_)(struct list* l, int index, long double element);
    void (*_char_)(struct list* l, int index, char element);
    void (*_uchar_)(struct list* l, int index, unsigned char element);
    void (*_string_)(struct list* l, int index, const char* element);
    void (*_element_)(struct list*l, int index, void* element);

}list_set;



/// LIST CLASS ///

typedef struct list{
    list_object*    objects;
    size_t          size;
    list_type       type;
    // Inner structures
    list_append*    append;
    list_prepend*   prepend;
    list_insert*    insert;
    list_get*       get;
    list_set*       set;


    // Misc functions
    void*   (*at)           (struct list* l, int index);
    void    (*clear)        (struct list* l);
    void    (*remove)       (struct list* l, int index);
    void    (*print_all)    (struct list* l);
    int     (*sort)         (struct list* l,list_sort_type t);

}list;




/// Append Functions ///

void list_append_int(list* l,int element){


    if(l->type == LIST_TYPE_SEQUENTIAL){
        list_object* new_object_list = (list_object*)malloc(sizeof(list_object)*(l->size +1));

        if(new_object_list != NULL){   
        
            for ( int i = 0; i < l->size; i++){
                new_object_list[i] = l->objects[i];
            }
            free(l->objects);
            l->objects = new_object_list;

        }
        else{
            printf("%s\n",LIST_ERROR_ALLOCATION);
            exit(EXIT_FAILURE);
        }




        int* new_data = (int*)malloc(sizeof(int));
        *new_data = element;

        list_object new_object;
        new_object.data = (void*)new_data;
        new_object.type = LIST_INT; 


        l->objects[l->size] = new_object;

        l->size += 1;
        return;
    }
    else if( l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){

        if ( l->objects == NULL){
            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            new_object->type = LIST_INT;

            int* new_data = (int*)malloc(sizeof(int));
            *new_data = element;

            new_object->data = (void*)new_data;

            new_object->next = NULL;
            new_object->prev = NULL;

            l->objects = new_object;

            l->size+=1;

            return;
        }
        else{

            list_object* current_object;
            
            for(current_object = l->objects; current_object->next != NULL; current_object = current_object->next){}


            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            new_object->type = LIST_INT;           
            
            int* new_data = (int*)malloc(sizeof(int));
            *new_data = element;

            new_object->data = (void*)new_data;

            new_object->next = NULL;

            if (l->type == LIST_TYPE_DOUBLE_LINKED)
                new_object->prev = current_object;
            else
                new_object->prev = NULL;

            current_object->next = new_object;

            l->size+=1;
            return;
        }


    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }

}

void list_append_uint(list* l,unsigned int element){

    if(l->type == LIST_TYPE_SEQUENTIAL){
        list_object* new_object_list = (list_object*)malloc(sizeof(list_object)*(l->size +1));

        if(new_object_list != NULL){   
        
            for ( int i = 0; i < l->size; i++){
                new_object_list[i] = l->objects[i];
            }
            free(l->objects);
            l->objects = new_object_list;

        }
        else{
            printf("%s\n",LIST_ERROR_ALLOCATION);
            exit(EXIT_FAILURE);
        }




        unsigned int* new_data = (unsigned int*)malloc(sizeof(unsigned int));
        *new_data = element;

        list_object new_object;
        new_object.data = (void*)new_data;
        new_object.type = LIST_UINT; 


        l->objects[l->size] = new_object;

        l->size += 1;


    }
    else if( l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){

        if ( l->objects == NULL){
            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            new_object->type = LIST_UINT;

            unsigned int* new_data = (unsigned int*)malloc(sizeof(unsigned int));
            *new_data = element;

            new_object->data = (void*)new_data;

            new_object->next = NULL;
            new_object->prev = NULL;

            l->objects = new_object;

            l->size+=1;

            return;
        }
        else{

            list_object* current_object;
           
            for(current_object = l->objects; current_object->next != NULL; current_object = current_object->next){}


            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            new_object->type = LIST_UINT;           
            
            unsigned int* new_data = (unsigned int*)malloc(sizeof(unsigned int));
            *new_data = element;

            new_object->data = (void*)new_data;

            new_object->next = NULL;

            if (l->type == LIST_TYPE_DOUBLE_LINKED)
                new_object->prev = current_object;
            else
                new_object->prev = NULL;

            current_object->next = new_object;

            l->size+=1;
            return;
        }


    }
    else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }




}

void list_append_short(list* l,short element){

    if(l->type == LIST_TYPE_SEQUENTIAL){
        list_object* new_object_list = (list_object*)malloc(sizeof(list_object)*(l->size +1));

        if(new_object_list != NULL){   
        
            for ( int i = 0; i < l->size; i++){
                new_object_list[i] = l->objects[i];
            }
            free(l->objects);
            l->objects = new_object_list;

        }
        else{
            printf("%s\n",LIST_ERROR_ALLOCATION);
            exit(EXIT_FAILURE);
        }




        short* new_data = (short*)malloc(sizeof(short));
        *new_data = element;

        list_object new_object;
        new_object.data = (void*)new_data;
        new_object.type = LIST_SHORT; 


        l->objects[l->size] = new_object;

        l->size += 1;

    }
    else if( l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){

        if ( l->objects == NULL){
            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            new_object->type = LIST_SHORT;

            short* new_data = (short*)malloc(sizeof(short));
            *new_data = element;

            new_object->data = (void*)new_data;

            new_object->next = NULL;
            new_object->prev = NULL;

            l->objects = new_object;

            l->size+=1;

            return;
        }
        else{

            list_object* current_object;
            
            for(current_object = l->objects; current_object->next != NULL; current_object = current_object->next){}


            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            new_object->type = LIST_SHORT;           
            
            short* new_data = (short*)malloc(sizeof(short));
            *new_data = element;

            new_object->data = (void*)new_data;

            new_object->next = NULL;

            if (l->type == LIST_TYPE_DOUBLE_LINKED)
                new_object->prev = current_object;
            else
                new_object->prev = NULL;

            current_object->next = new_object;

            l->size+=1;
            return;
        }


    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }



}

void list_append_ushort(list* l,unsigned short element){

    if(l->type == LIST_TYPE_SEQUENTIAL){
        list_object* new_object_list = (list_object*)malloc(sizeof(list_object)*(l->size +1));

        if(new_object_list != NULL){   
        
            for ( int i = 0; i < l->size; i++){
                new_object_list[i] = l->objects[i];
            }
            free(l->objects);
            l->objects = new_object_list;

        }
        else{
            printf("%s\n",LIST_ERROR_ALLOCATION);
            exit(EXIT_FAILURE);
        }




        unsigned short* new_data = (unsigned short*)malloc(sizeof(unsigned short));
        *new_data = element;

        list_object new_object;
        new_object.data = (void*)new_data;
        new_object.type = LIST_USHORT; 


        l->objects[l->size] = new_object;

        l->size += 1;

    }
    else if( l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){

        if ( l->objects == NULL){
            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            new_object->type = LIST_USHORT;

            unsigned short* new_data = (unsigned short*)malloc(sizeof(unsigned short));
            *new_data = element;

            new_object->data = (void*)new_data;

            new_object->next = NULL;
            new_object->prev = NULL;

            l->objects = new_object;

            l->size+=1;

            return;
        }
        else{

            list_object* current_object;
            
            for(current_object = l->objects; current_object->next != NULL; current_object = current_object->next){}


            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            new_object->type = LIST_USHORT;           
            
            unsigned short* new_data = (unsigned short*)malloc(sizeof(unsigned short));
            *new_data = element;

            new_object->data = (void*)new_data;

            new_object->next = NULL;

            if (l->type == LIST_TYPE_DOUBLE_LINKED)
                new_object->prev = current_object;
            else
                new_object->prev = NULL;

            current_object->next = new_object;

            l->size+=1;
            return;
        }


    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }



}

void list_append_longlong(list* l,long long element){

    if(l->type == LIST_TYPE_SEQUENTIAL){
        list_object* new_object_list = (list_object*)malloc(sizeof(list_object)*(l->size +1));

            if(new_object_list != NULL){   
            
                for ( int i = 0; i < l->size; i++){
                    new_object_list[i] = l->objects[i];
                }
                free(l->objects);
                l->objects = new_object_list;

            }
            else{
                printf("%s\n",LIST_ERROR_ALLOCATION);
                exit(EXIT_FAILURE);
            }




            long long* new_data = (long long*)malloc(sizeof(long long));
            *new_data = element;

            list_object new_object;
            new_object.data = (void*)new_data;
            new_object.type = LIST_LONGLONG; 


            l->objects[l->size] = new_object;

            l->size += 1;        
    }
    else if( l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){

        if ( l->objects == NULL){
            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            new_object->type = LIST_LONGLONG;

            long long* new_data = (long long*)malloc(sizeof(long long));
            *new_data = element;

            new_object->data = (void*)new_data;

            new_object->next = NULL;
            new_object->prev = NULL;

            l->objects = new_object;

            l->size+=1;

            return;
        }
        else{

            list_object* current_object;
            
            for(current_object = l->objects; current_object->next != NULL; current_object = current_object->next){}


            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            new_object->type = LIST_LONGLONG;           

            long long* new_data = (long long*)malloc(sizeof(long long));
            *new_data = element;

            new_object->data = (void*)new_data;

            new_object->next = NULL;

            if (l->type == LIST_TYPE_DOUBLE_LINKED)
                new_object->prev = current_object;
            else
                new_object->prev = NULL;

            current_object->next = new_object;

            l->size+=1;
            return;
        }


    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }  

}

void list_append_ulonglong(list* l,unsigned long long element){

    if(l->type == LIST_TYPE_SEQUENTIAL){
        list_object* new_object_list = (list_object*)malloc(sizeof(list_object)*(l->size +1));

        if(new_object_list != NULL){   
        
            for ( int i = 0; i < l->size; i++){
                new_object_list[i] = l->objects[i];
            }
            free(l->objects);
            l->objects = new_object_list;

        }
        else{
            printf("%s\n",LIST_ERROR_ALLOCATION);
            exit(EXIT_FAILURE);
        }




        unsigned long long* new_data = (unsigned long long*)malloc(sizeof(unsigned long long));
        *new_data = element;

        list_object new_object;
        new_object.data = (void*)new_data;
        new_object.type = LIST_ULONGLONG; 


        l->objects[l->size] = new_object;

        l->size += 1;        
    }
    else if( l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){

        if ( l->objects == NULL){
            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            new_object->type = LIST_ULONGLONG;

            unsigned long long* new_data = (unsigned long long*)malloc(sizeof(unsigned long long));
            *new_data = element;

            new_object->data = (void*)new_data;

            new_object->next = NULL;
            new_object->prev = NULL;

            l->objects = new_object;

            l->size+=1;

            return;
        }
        else{

            list_object* current_object;
            
            for(current_object = l->objects; current_object->next != NULL; current_object = current_object->next){}


            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            new_object->type = LIST_ULONGLONG;           
            
            unsigned long long* new_data = (unsigned long long*)malloc(sizeof(unsigned long long));
            *new_data = element;

            new_object->data = (void*)new_data;

            new_object->next = NULL;

            if (l->type == LIST_TYPE_DOUBLE_LINKED)
                new_object->prev = current_object;
            else
                new_object->prev = NULL;

            current_object->next = new_object;

            l->size+=1;
            return;
        }


    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }    

}

void list_append_float(list* l,float element){

    if(l->type == LIST_TYPE_SEQUENTIAL){
        list_object* new_object_list = (list_object*)malloc(sizeof(list_object)*(l->size +1));

        if(new_object_list != NULL){   
        
            for ( int i = 0; i < l->size; i++){
                new_object_list[i] = l->objects[i];
            }
            free(l->objects);
            l->objects = new_object_list;

        }
        else{
            printf("%s\n",LIST_ERROR_ALLOCATION);
            exit(EXIT_FAILURE);
        }


        float* new_data = (float*)malloc(sizeof(float));
        *new_data = element;

        list_object new_object;
        new_object.data = (void*)new_data;
        new_object.type = LIST_FLOAT; 


        l->objects[l->size] = new_object;

        l->size += 1;

    }
    else if( l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){

        if ( l->objects == NULL){
            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            new_object->type = LIST_FLOAT;

            float* new_data = (float*)malloc(sizeof(float));
            *new_data = element;

            new_object->data = (void*)new_data;

            new_object->next = NULL;
            new_object->prev = NULL;

            l->objects = new_object;

            l->size+=1;

            return;
        }
        else{

            list_object* current_object;
            
            for(current_object = l->objects; current_object->next != NULL; current_object = current_object->next){}


            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            new_object->type = LIST_FLOAT;           
            
            float* new_data = (float*)malloc(sizeof(float));
            *new_data = element;

            new_object->data = (void*)new_data;

            new_object->next = NULL;

            if (l->type == LIST_TYPE_DOUBLE_LINKED)
                new_object->prev = current_object;
            else
                new_object->prev = NULL;

            current_object->next = new_object;

            l->size+=1;
            return;
        }


    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }



}

void list_append_double(list* l,double element){

    if(l->type == LIST_TYPE_SEQUENTIAL){
        list_object* new_object_list = (list_object*)malloc(sizeof(list_object)*(l->size +1));

            if(new_object_list != NULL){   
            
                for ( int i = 0; i < l->size; i++){
                    new_object_list[i] = l->objects[i];
                }
                free(l->objects);
                l->objects = new_object_list;

            }
            else{
                printf("%s\n",LIST_ERROR_ALLOCATION);
                exit(EXIT_FAILURE);
            }




            double* new_data = (double*)malloc(sizeof(double));
            *new_data = element;

            list_object new_object;
            new_object.data = (void*)new_data;
            new_object.type = LIST_DOUBLE; 


            l->objects[l->size] = new_object;

            l->size += 1;

    }
    else if( l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){

        if ( l->objects == NULL){
            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            new_object->type = LIST_DOUBLE;

            double* new_data = (double*)malloc(sizeof(double));
            *new_data = element;

            new_object->data = (void*)new_data;

            new_object->next = NULL;
            new_object->prev = NULL;

            l->objects = new_object;

            l->size+=1;

            return;
        }
        else{

            list_object* current_object;

            for(current_object = l->objects; current_object->next != NULL; current_object = current_object->next){}


            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            new_object->type = LIST_DOUBLE;           
            
            double* new_data = (double*)malloc(sizeof(double));
            *new_data = element;

            new_object->data = (void*)new_data;

            new_object->next = NULL;

            if (l->type == LIST_TYPE_DOUBLE_LINKED)
                new_object->prev = current_object;
            else
                new_object->prev = NULL;

            current_object->next = new_object;

            l->size+=1;
            return;
        }


    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }
    

}

void list_append_longdouble(list* l,long double element){

    if(l->type == LIST_TYPE_SEQUENTIAL){
        list_object* new_object_list = (list_object*)malloc(sizeof(list_object)*(l->size +1));

            if(new_object_list != NULL){   
            
                for ( int i = 0; i < l->size; i++){
                    new_object_list[i] = l->objects[i];
                }
                free(l->objects);
                l->objects = new_object_list;

            }
            else{
                printf("%s\n",LIST_ERROR_ALLOCATION);
                exit(EXIT_FAILURE);
            }




            long double* new_data = (long double*)malloc(sizeof(long double));
            *new_data = element;

            list_object new_object;
            new_object.data = (void*)new_data;
            new_object.type = LIST_LONGDOUBLE; 


            l->objects[l->size] = new_object;

            l->size += 1;


    }
    else if( l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){

        if ( l->objects == NULL){
            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            new_object->type = LIST_LONGDOUBLE;

            long double* new_data = (long double*)malloc(sizeof(long double));
            *new_data = element;

            new_object->data = (void*)new_data;

            new_object->next = NULL;
            new_object->prev = NULL;

            l->objects = new_object;

            l->size+=1;

            return;
        }
        else{

            list_object* current_object;

            for(current_object = l->objects; current_object->next != NULL; current_object = current_object->next){}


            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            new_object->type = LIST_LONGDOUBLE;
            
            long double* new_data = (long double*)malloc(sizeof(long double));
            *new_data = element;

            new_object->data = (void*)new_data;

            new_object->next = NULL;

            if (l->type == LIST_TYPE_DOUBLE_LINKED)
                new_object->prev = current_object;
            else
                new_object->prev = NULL;

            current_object->next = new_object;

            l->size+=1;
            return;
        }


    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }

}

void list_append_char(list* l,char element){

    if(l->type == LIST_TYPE_SEQUENTIAL){
        list_object* new_object_list = (list_object*)malloc(sizeof(list_object)*(l->size +1));

            if(new_object_list != NULL){   
            
                for ( int i = 0; i < l->size; i++){
                    new_object_list[i] = l->objects[i];
                }
                free(l->objects);
                l->objects = new_object_list;

            }
            else{
                printf("%s\n",LIST_ERROR_ALLOCATION);
                exit(EXIT_FAILURE);
            }




            char* new_data = (char*)malloc(sizeof(char));
            *new_data = element;

            list_object new_object;
            new_object.data = (void*)new_data;
            new_object.type = LIST_CHAR; 


            l->objects[l->size] = new_object;

            l->size += 1;
    
    }
    else if( l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){

        if ( l->objects == NULL){
            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            new_object->type = LIST_CHAR;

            char* new_data = (char*)malloc(sizeof(char));
            *new_data = element;

            new_object->data = (void*)new_data;

            new_object->next = NULL;
            new_object->prev = NULL;

            l->objects = new_object;

            l->size+=1;

            return;
        }
        else{

            list_object* current_object;
            
            for(current_object = l->objects; current_object->next != NULL; current_object = current_object->next){}


            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            new_object->type = LIST_CHAR;           
            
            char* new_data = (char*)malloc(sizeof(char));
            *new_data = element;

            new_object->data = (void*)new_data;

            new_object->next = NULL;

            if (l->type == LIST_TYPE_DOUBLE_LINKED)
                new_object->prev = current_object;
            else
                new_object->prev = NULL;

            current_object->next = new_object;

            l->size+=1;
            return;
        }


    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }   
    

}

void list_append_uchar(list* l,unsigned char element){

    if(l->type == LIST_TYPE_SEQUENTIAL){
        list_object* new_object_list = (list_object*)malloc(sizeof(list_object)*(l->size +1));

        if(new_object_list != NULL){   
        
            for ( int i = 0; i < l->size; i++){
                new_object_list[i] = l->objects[i];
            }
            free(l->objects);
            l->objects = new_object_list;

        }
        else{
            printf("%s\n",LIST_ERROR_ALLOCATION);
            exit(EXIT_FAILURE);
        }




        unsigned char* new_data = (unsigned char*)malloc(sizeof(unsigned char));
        *new_data = element;

        list_object new_object;
        new_object.data = (void*)new_data;
        new_object.type = LIST_UCHAR; 


        l->objects[l->size] = new_object;

        l->size += 1;
    }
    else if( l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){

        if ( l->objects == NULL){
            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            new_object->type = LIST_UCHAR;

            unsigned char* new_data = (unsigned char*)malloc(sizeof(unsigned char));
            *new_data = element;

            new_object->data = (void*)new_data;

            new_object->next = NULL;
            new_object->prev = NULL;

            l->objects = new_object;

            l->size+=1;

            return;
        }
        else{

            list_object* current_object;
            
            for(current_object = l->objects; current_object->next != NULL; current_object = current_object->next){}


            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            new_object->type = LIST_UCHAR;           
            
            unsigned char* new_data = (unsigned char*)malloc(sizeof(unsigned char));
            *new_data = element;

            new_object->data = (void*)new_data;

            new_object->next = NULL;

            if (l->type == LIST_TYPE_DOUBLE_LINKED)
                new_object->prev = current_object;
            else
                new_object->prev = NULL;

            current_object->next = new_object;

            l->size+=1;
            return;
        }


    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }    

}

void list_append_string(list* l, const char* element){

    if(l->type == LIST_TYPE_SEQUENTIAL){
        list_object* new_object_list = (list_object*)malloc(sizeof(list_object)*(l->size +1));

            if(new_object_list != NULL){   
            
                for ( int i = 0; i < l->size; i++){
                    new_object_list[i] = l->objects[i];
                }
                free(l->objects);
                l->objects = new_object_list;

            }
            else{
                printf("%s\n",LIST_ERROR_ALLOCATION);
                exit(EXIT_FAILURE);
            }

            char* new_data = (char*)malloc(sizeof(char)*strlen(element)+1);
            strcpy(new_data,element);
            list_object new_object;
            new_object.data = (void*)new_data;
            new_object.type = LIST_STRING;

            l->objects[l->size] = new_object;

            l->size += 1;

    }
    else if( l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){

        if ( l->objects == NULL){
            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            new_object->type = LIST_STRING;

            char* new_data = (char*)malloc(sizeof(char)*strlen(element)+1);
            strcpy(new_data,element);

            new_object->data = (void*)new_data;

            new_object->next = NULL;
            new_object->prev = NULL;

            l->objects = new_object;

            l->size+=1;

            return;
        }
        else{

            list_object* current_object;
            
            for(current_object = l->objects; current_object->next != NULL; current_object = current_object->next){}


            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            new_object->type = LIST_STRING;           
            
            char* new_data = (char*)malloc(sizeof(char)*strlen(element)+1);
            strcpy(new_data,element);

            new_object->data = (void*)new_data;

            new_object->next = NULL;

            if (l->type == LIST_TYPE_DOUBLE_LINKED)
                new_object->prev = current_object;
            else
                new_object->prev = NULL;

            current_object->next = new_object;

            l->size+=1;
            return;
        }


    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }
    
}



/// Prepend Function ///

void list_prepend_int(list*l,int element){

    if(l->type == LIST_TYPE_SEQUENTIAL){
        list_object* new_object_list = (list_object*)malloc(sizeof(list_object)*(l->size +1));

        if(new_object_list != NULL){   
        
            for ( int i = 0,j=1; i < l->size; i++,j++){
                new_object_list[j] = l->objects[i];
            }
            free(l->objects);
            l->objects = new_object_list;

        }
        else{
            printf("%s\n",LIST_ERROR_ALLOCATION);
            exit(EXIT_FAILURE);
        }

        int* new_data = (int*)malloc(sizeof(int));
        *new_data = element;

        list_object new_object;
        new_object.data = (void*)new_data;
        new_object.type = LIST_INT; 


        l->objects[0] = new_object;

        l->size += 1;   
    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){

        if(l->objects != NULL){
            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            int* new_data = (int*)malloc(sizeof(int));
            *new_data = element;        

            new_object->data = (void*)new_data;
            new_object->type = LIST_INT;


            list_object* next_object;
            next_object = l->objects;
            

            l->objects = new_object;

            new_object->next = next_object;
            new_object->prev = NULL;
            
            if (l->type == LIST_TYPE_DOUBLE_LINKED)
                next_object->prev = new_object;
            else
                next_object->prev = NULL;  

            l->size+=1;

            return;
        }else {
            list_object* new_object = (list_object*)malloc(sizeof(list_object));

           int* new_data = (int*)malloc(sizeof(int));
            *new_data = element;      

            new_object->data = (void*)new_data;
            new_object->type = LIST_INT;

            new_object->next = NULL;
            new_object->prev = NULL;

            l->objects = new_object;

            l->size+=1;

            return;
        }



    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }



}

void list_prepend_uint(list*l,unsigned int element){
    

    if(l->type == LIST_TYPE_SEQUENTIAL){
        list_object* new_object_list = (list_object*)malloc(sizeof(list_object)*(l->size +1));

        if(new_object_list != NULL){   
        
            for ( int i = 0,j=1; i < l->size; i++,j++){
                new_object_list[j] = l->objects[i];
            }
            free(l->objects);
            l->objects = new_object_list;

        }
        else{
            printf("%s\n",LIST_ERROR_ALLOCATION);
            exit(EXIT_FAILURE);
        }

        unsigned int* new_data = (unsigned int*)malloc(sizeof(unsigned int));
        *new_data = element;

        list_object new_object;
        new_object.data = (void*)new_data;
        new_object.type = LIST_UINT; 


        l->objects[0] = new_object;

        l->size += 1;

    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){

        if(l->objects != NULL){
            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            unsigned int* new_data = (unsigned int*)malloc(sizeof(unsigned int));
            *new_data = element;        

            new_object->data = (void*)new_data;
            new_object->type = LIST_UINT;


            list_object* next_object;
            next_object = l->objects;
            

            l->objects = new_object;

            new_object->next = next_object;
            new_object->prev = NULL;
            
            if (l->type == LIST_TYPE_DOUBLE_LINKED)
                next_object->prev = new_object;
            else
                next_object->prev = NULL;  

            l->size+=1;

            return;
        }else {
            list_object* new_object = (list_object*)malloc(sizeof(list_object));

           unsigned int* new_data = (unsigned int*)malloc(sizeof(unsigned int));
            *new_data = element;      

            new_object->data = (void*)new_data;
            new_object->type = LIST_UINT;

            new_object->next = NULL;
            new_object->prev = NULL;

            l->objects = new_object;

            l->size+=1;

            return;
        }



    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }    


}

void list_prepend_short(list*l,short element){
    

    if(l->type == LIST_TYPE_SEQUENTIAL){
        list_object* new_object_list = (list_object*)malloc(sizeof(list_object)*(l->size +1));

        if(new_object_list != NULL){   
        
            for ( int i = 0,j=1; i < l->size; i++,j++){
                new_object_list[j] = l->objects[i];
            }
            free(l->objects);
            l->objects = new_object_list;

        }
        else{
            printf("%s\n",LIST_ERROR_ALLOCATION);
            exit(EXIT_FAILURE);
        }

        short* new_data = (short*)malloc(sizeof(short));
        *new_data = element;

        list_object new_object;
        new_object.data = (void*)new_data;
        new_object.type = LIST_SHORT; 


        l->objects[0] = new_object;

        l->size += 1;

    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){

        if(l->objects != NULL){
            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            short* new_data = (short*)malloc(sizeof(short));
            *new_data = element;        

            new_object->data = (void*)new_data;
            new_object->type = LIST_SHORT;


            list_object* next_object;
            next_object = l->objects;
            

            l->objects = new_object;

            new_object->next = next_object;
            new_object->prev = NULL;
            
            if (l->type == LIST_TYPE_DOUBLE_LINKED)
                next_object->prev = new_object;
            else
                next_object->prev = NULL;  

            l->size+=1;

            return;
        }else {
            list_object* new_object = (list_object*)malloc(sizeof(list_object));

           short* new_data = (short*)malloc(sizeof(short));
            *new_data = element;      

            new_object->data = (void*)new_data;
            new_object->type = LIST_SHORT;

            new_object->next = NULL;
            new_object->prev = NULL;

            l->objects = new_object;

            l->size+=1;

            return;
        }



    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }    


}

void list_prepend_ushort(list*l,unsigned short element){
    
    if(l->type == LIST_TYPE_SEQUENTIAL){
        list_object* new_object_list = (list_object*)malloc(sizeof(list_object)*(l->size +1));

        if(new_object_list != NULL){   
        
            for ( int i = 0,j=1; i < l->size; i++,j++){
                new_object_list[j] = l->objects[i];
            }
            free(l->objects);
            l->objects = new_object_list;

        }
        else{
            printf("%s\n",LIST_ERROR_ALLOCATION);
            exit(EXIT_FAILURE);
        }

        unsigned short* new_data = (unsigned short*)malloc(sizeof(unsigned short));
        *new_data = element;

        list_object new_object;
        new_object.data = (void*)new_data;
        new_object.type = LIST_USHORT; 


        l->objects[0] = new_object;

        l->size += 1;

    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){

        if(l->objects != NULL){
            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            unsigned short* new_data = (unsigned short*)malloc(sizeof(unsigned short));
            *new_data = element;        

            new_object->data = (void*)new_data;
            new_object->type = LIST_USHORT;


            list_object* next_object;
            next_object = l->objects;
            

            l->objects = new_object;

            new_object->next = next_object;
            new_object->prev = NULL;
            
            if (l->type == LIST_TYPE_DOUBLE_LINKED)
                next_object->prev = new_object;
            else
                next_object->prev = NULL;  

            l->size+=1;

            return;
        }else {
            list_object* new_object = (list_object*)malloc(sizeof(list_object));

           unsigned short* new_data = (unsigned short*)malloc(sizeof(unsigned short));
            *new_data = element;      

            new_object->data = (void*)new_data;
            new_object->type = LIST_USHORT;

            new_object->next = NULL;
            new_object->prev = NULL;

            l->objects = new_object;

            l->size+=1;

            return;
        }



    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }


}

void list_prepend_longlong(list*l,long long element){
    

    if(l->type == LIST_TYPE_SEQUENTIAL){
        list_object* new_object_list = (list_object*)malloc(sizeof(list_object)*(l->size +1));

        if(new_object_list != NULL){   
        
            for ( int i = 0,j=1; i < l->size; i++,j++){
                new_object_list[j] = l->objects[i];
            }
            free(l->objects);
            l->objects = new_object_list;

        }
        else{
            printf("%s\n",LIST_ERROR_ALLOCATION);
            exit(EXIT_FAILURE);
        }

        long long* new_data = (long long*)malloc(sizeof(long long));
        *new_data = element;

        list_object new_object;
        new_object.data = (void*)new_data;
        new_object.type = LIST_ULONGLONG; 


        l->objects[0] = new_object;

        l->size += 1;

    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){

        if(l->objects != NULL){
            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            long long* new_data = (long long*)malloc(sizeof(long long));
            *new_data = element;        

            new_object->data = (void*)new_data;
            new_object->type = LIST_LONGLONG;


            list_object* next_object;
            next_object = l->objects;
            

            l->objects = new_object;

            new_object->next = next_object;
            new_object->prev = NULL;
            
            if (l->type == LIST_TYPE_DOUBLE_LINKED)
                next_object->prev = new_object;
            else
                next_object->prev = NULL;  

            l->size+=1;

            return;
        }else {
            list_object* new_object = (list_object*)malloc(sizeof(list_object));

           long long* new_data = (long long*)malloc(sizeof(long long));
            *new_data = element;      

            new_object->data = (void*)new_data;
            new_object->type = LIST_LONGLONG;

            new_object->next = NULL;
            new_object->prev = NULL;

            l->objects = new_object;

            l->size+=1;

            return;
        }



    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }



}

void list_prepend_ulonglong(list*l,unsigned long long element){
    
    if(l->type == LIST_TYPE_SEQUENTIAL){
        list_object* new_object_list = (list_object*)malloc(sizeof(list_object)*(l->size +1));

        if(new_object_list != NULL){   
        
            for ( int i = 0,j=1; i < l->size; i++,j++){
                new_object_list[j] = l->objects[i];
            }
            free(l->objects);
            l->objects = new_object_list;

        }
        else{
            printf("%s\n",LIST_ERROR_ALLOCATION);
            exit(EXIT_FAILURE);
        }

        unsigned long long* new_data = (unsigned long long*)malloc(sizeof(unsigned long long));
        *new_data = element;

        list_object new_object;
        new_object.data = (void*)new_data;
        new_object.type = LIST_ULONGLONG; 


        l->objects[0] = new_object;

        l->size += 1;

    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){

        if(l->objects != NULL){
            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            unsigned long long* new_data = (unsigned long long*)malloc(sizeof(unsigned long long));
            *new_data = element;        

            new_object->data = (void*)new_data;
            new_object->type = LIST_ULONGLONG;


            list_object* next_object;
            next_object = l->objects;
            

            l->objects = new_object;

            new_object->next = next_object;
            new_object->prev = NULL;
            
            if (l->type == LIST_TYPE_DOUBLE_LINKED)
                next_object->prev = new_object;
            else
                next_object->prev = NULL;  

            l->size+=1;

            return;
        }else {
            list_object* new_object = (list_object*)malloc(sizeof(list_object));

           unsigned long long* new_data = (unsigned long long*)malloc(sizeof(unsigned long long));
            *new_data = element;      

            new_object->data = (void*)new_data;
            new_object->type = LIST_ULONGLONG;

            new_object->next = NULL;
            new_object->prev = NULL;

            l->objects = new_object;

            l->size+=1;

            return;
        }



    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }


}

void list_prepend_float(list*l,float element){
    
    if(l->type == LIST_TYPE_SEQUENTIAL){
        list_object* new_object_list = (list_object*)malloc(sizeof(list_object)*(l->size +1));

        if(new_object_list != NULL){   
        
            for ( int i = 0,j=1; i < l->size; i++,j++){
                new_object_list[j] = l->objects[i];
            }
            free(l->objects);
            l->objects = new_object_list;

        }
        else{
            printf("%s\n",LIST_ERROR_ALLOCATION);
            exit(EXIT_FAILURE);
        }

        float* new_data = (float*)malloc(sizeof(float));
        *new_data = element;

        list_object new_object;
        new_object.data = (void*)new_data;
        new_object.type = LIST_FLOAT; 


        l->objects[0] = new_object;

        l->size += 1;

    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){

        if(l->objects != NULL){
            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            float* new_data = (float*)malloc(sizeof(float));
            *new_data = element;        

            new_object->data = (void*)new_data;
            new_object->type = LIST_FLOAT;


            list_object* next_object;
            next_object = l->objects;
            

            l->objects = new_object;

            new_object->next = next_object;
            new_object->prev = NULL;
            
            if (l->type == LIST_TYPE_DOUBLE_LINKED)
                next_object->prev = new_object;
            else
                next_object->prev = NULL;  

            l->size+=1;

            return;
        }else {
            list_object* new_object = (list_object*)malloc(sizeof(list_object));

           float* new_data = (float*)malloc(sizeof(float));
            *new_data = element;      

            new_object->data = (void*)new_data;
            new_object->type = LIST_FLOAT;

            new_object->next = NULL;
            new_object->prev = NULL;

            l->objects = new_object;

            l->size+=1;

            return;
        }



    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }


}

void list_prepend_double(list*l,double element){
    
    if(l->type == LIST_TYPE_SEQUENTIAL){
    list_object* new_object_list = (list_object*)malloc(sizeof(list_object)*(l->size +1));

        if(new_object_list != NULL){   
        
            for ( int i = 0,j=1; i < l->size; i++,j++){
                new_object_list[j] = l->objects[i];
            }
            free(l->objects);
            l->objects = new_object_list;

        }
        else{
            printf("%s\n",LIST_ERROR_ALLOCATION);
            exit(EXIT_FAILURE);
        }

        double* new_data = (double*)malloc(sizeof(double));
        *new_data = element;

        list_object new_object;
        new_object.data = (void*)new_data;
        new_object.type = LIST_DOUBLE; 


        l->objects[0] = new_object;

        l->size += 1;

    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){

        if(l->objects != NULL){
            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            double* new_data = (double*)malloc(sizeof(double));
            *new_data = element;        

            new_object->data = (void*)new_data;
            new_object->type = LIST_DOUBLE;


            list_object* next_object;
            next_object = l->objects;
            

            l->objects = new_object;

            new_object->next = next_object;
            new_object->prev = NULL;
            
            if (l->type == LIST_TYPE_DOUBLE_LINKED)
                next_object->prev = new_object;
            else
                next_object->prev = NULL;  

            l->size+=1;

            return;
        }else {
            list_object* new_object = (list_object*)malloc(sizeof(list_object));

           double* new_data = (double*)malloc(sizeof(double));
            *new_data = element;      

            new_object->data = (void*)new_data;
            new_object->type = LIST_DOUBLE;

            new_object->next = NULL;
            new_object->prev = NULL;

            l->objects = new_object;

            l->size+=1;

            return;
        }



    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }


}

void list_prepend_longdouble(list*l,long double element){
    
    if(l->type == LIST_TYPE_SEQUENTIAL){
        list_object* new_object_list = (list_object*)malloc(sizeof(list_object)*(l->size +1));

        if(new_object_list != NULL){   
        
            for ( int i = 0,j=1; i < l->size; i++,j++){
                new_object_list[j] = l->objects[i];
            }
            free(l->objects);
            l->objects = new_object_list;

        }
        else{
            printf("%s\n",LIST_ERROR_ALLOCATION);
            exit(EXIT_FAILURE);
        }

        long double* new_data = (long double*)malloc(sizeof(long double));
        *new_data = element;

        list_object new_object;
        new_object.data = (void*)new_data;
        new_object.type = LIST_LONGDOUBLE; 


        l->objects[0] = new_object;

        l->size += 1;       
        return;
    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){

        if(l->objects != NULL){
            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            long double* new_data = (long double*)malloc(sizeof(long double));
            *new_data = element;        

            new_object->data = (void*)new_data;
            new_object->type = LIST_LONGDOUBLE;


            list_object* next_object;
            next_object = l->objects;
            

            l->objects = new_object;

            new_object->next = next_object;
            new_object->prev = NULL;
            
            if (l->type == LIST_TYPE_DOUBLE_LINKED)
                next_object->prev = new_object;
            else
                next_object->prev = NULL;  

            l->size+=1;

            return;
        }else {
            list_object* new_object = (list_object*)malloc(sizeof(list_object));

           long double* new_data = (long double*)malloc(sizeof(long double));
            *new_data = element;      

            new_object->data = (void*)new_data;
            new_object->type = LIST_LONGDOUBLE;

            new_object->next = NULL;
            new_object->prev = NULL;

            l->objects = new_object;

            l->size+=1;

            return;
        }



    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }


}

void list_prepend_char(list*l,char element){
    
    if(l->type == LIST_TYPE_SEQUENTIAL){
        list_object* new_object_list = (list_object*)malloc(sizeof(list_object)*(l->size +1));

        if(new_object_list != NULL){   
        
            for ( int i = 0,j=1; i < l->size; i++,j++){
                new_object_list[j] = l->objects[i];
            }
            free(l->objects);
            l->objects = new_object_list;

        }
        else{
            printf("%s\n",LIST_ERROR_ALLOCATION);
            exit(EXIT_FAILURE);
        }

        char* new_data = (char*)malloc(sizeof(char));
        *new_data = element;

        list_object new_object;
        new_object.data = (void*)new_data;
        new_object.type = LIST_CHAR; 


        l->objects[0] = new_object;

        l->size += 1;

        return;
    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){

        if(l->objects != NULL){
            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            char* new_data = (char*)malloc(sizeof(char));
            *new_data = element;        

            new_object->data = (void*)new_data;
            new_object->type = LIST_CHAR;


            list_object* next_object;
            next_object = l->objects;
            

            l->objects = new_object;

            new_object->next = next_object;
            new_object->prev = NULL;
            
            if (l->type == LIST_TYPE_DOUBLE_LINKED)
                next_object->prev = new_object;
            else
                next_object->prev = NULL;  

            l->size+=1;

            return;
        }else {
            list_object* new_object = (list_object*)malloc(sizeof(list_object));

           char* new_data = (char*)malloc(sizeof(char));
            *new_data = element;      

            new_object->data = (void*)new_data;
            new_object->type = LIST_CHAR;

            new_object->next = NULL;
            new_object->prev = NULL;

            l->objects = new_object;

            l->size+=1;

            return;
        }



    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }

}

void list_prepend_uchar(list*l,unsigned char element){
    
    if(l->type == LIST_TYPE_SEQUENTIAL){
        list_object* new_object_list = (list_object*)malloc(sizeof(list_object)*(l->size +1));

        if(new_object_list != NULL){   
        
            for ( int i = 0,j=1; i < l->size; i++,j++){
                new_object_list[j] = l->objects[i];
            }
            free(l->objects);
            l->objects = new_object_list;

        }
        else{
            printf("%s\n",LIST_ERROR_ALLOCATION);
            exit(EXIT_FAILURE);
        }

        unsigned char* new_data = (unsigned char*)malloc(sizeof(unsigned char));
        *new_data = element;

        list_object new_object;
        new_object.data = (void*)new_data;
        new_object.type = LIST_UCHAR; 


        l->objects[0] = new_object;

        l->size += 1;

    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){

        if(l->objects != NULL){
            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            unsigned char* new_data = (unsigned char*)malloc(sizeof(unsigned char));
            *new_data = element;        

            new_object->data = (void*)new_data;
            new_object->type = LIST_UCHAR;


            list_object* next_object;
            next_object = l->objects;
            

            l->objects = new_object;

            new_object->next = next_object;
            new_object->prev = NULL;
            
            if (l->type == LIST_TYPE_DOUBLE_LINKED)
                next_object->prev = new_object;
            else
                next_object->prev = NULL;  

            l->size+=1;

            return;
        }else {
            list_object* new_object = (list_object*)malloc(sizeof(list_object));

           unsigned char* new_data = (unsigned char*)malloc(sizeof(unsigned char));
            *new_data = element;      

            new_object->data = (void*)new_data;
            new_object->type = LIST_UCHAR;

            new_object->next = NULL;
            new_object->prev = NULL;

            l->objects = new_object;

            l->size+=1;

            return;
        }



    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }


}

void list_prepend_string(list*l,const char* element){
    
    if(l->type == LIST_TYPE_SEQUENTIAL){
        list_object* new_object_list = (list_object*)malloc(sizeof(list_object)*(l->size +1));

        if(new_object_list != NULL){   
        
            for ( int i = 0,j=1; i < l->size; i++,j++){
                new_object_list[j] = l->objects[i];
            }
            free(l->objects);
            l->objects = new_object_list;

        }
        else{
            printf("%s\n",LIST_ERROR_ALLOCATION);
            exit(EXIT_FAILURE);
        }

        char* new_data = (char*)malloc((sizeof(char)*strlen(element))+1 );
        strcpy(new_data,element);

        list_object new_object;
        new_object.data = (void*)new_data;
        new_object.type = LIST_STRING; 


        l->objects[0] = new_object;

        l->size += 1;        
    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){

        if(l->objects != NULL){
            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            char* new_data = (char*)malloc((sizeof(char)*strlen(element))+1);
            strcpy(new_data,element);     

            new_object->data = (void*)new_data;
            new_object->type = LIST_STRING;


            list_object* next_object;
            next_object = l->objects;
            

            l->objects = new_object;

            new_object->next = next_object;
            new_object->prev = NULL;
            
            if (l->type == LIST_TYPE_DOUBLE_LINKED)
                next_object->prev = new_object;
            else
                next_object->prev = NULL;  

            l->size+=1;

            return;
        }else {
            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            char* new_data = (char*)malloc((sizeof(char)*strlen(element))+1);
            strcpy(new_data,element);     

            new_object->data = (void*)new_data;
            new_object->type = LIST_STRING;

            new_object->next = NULL;
            new_object->prev = NULL;

            l->objects = new_object;

            l->size+=1;

            return;
        }



    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }


}





/// Insert Functions ///

void list_insert_int(list* l, int index, int element){

    if(index < -1){
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INSERT_OUT_OF_RANGE);
        #endif
        return;
    }
    
    if(index == -1 || (long long)l->size <= index){
        l->append->_int_(l,element);
        return;
    }


    if(l->type == LIST_TYPE_SEQUENTIAL){
        list_object* new_object_list = (list_object*)malloc(sizeof(list_object)*(l->size +1));

        if(new_object_list != NULL){


            for (int i = 0,j = 0; i < l->size; j++,i++){

                if ( i == index){
                    new_object_list[++j] = l->objects[i];
                }else{
                    new_object_list[j] = l->objects[i];
                }

            }

            free(l->objects);
            l->objects = new_object_list;
            int* new_data = (int*)malloc(sizeof(int));
            *new_data = element;

            list_object new_object;
            new_object.data = (void*)new_data;
            new_object.type = LIST_INT;
            l->objects[index] = new_object;
            l->size+=1;


        }
        else{
            printf("%s\n",LIST_ERROR_ALLOCATION);
            exit(EXIT_FAILURE);
        }

    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){


        
        if(index == 0){
            l->prepend->_int_(l,element);
            return;
        }else {
            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            int* new_data = (int*)malloc(sizeof(int));
            *new_data = element;
            
            new_object->data = (void*)new_data;
            new_object->type = LIST_INT;
            int i;


            list_object* current_object,*prev_object;

            for( prev_object = l->objects,current_object=l->objects->next, i=1; i != index ; i++,prev_object=prev_object->next,current_object=current_object->next){}        

            prev_object->next = new_object;
            new_object->next = current_object;

            if(l->type == LIST_TYPE_DOUBLE_LINKED){
                new_object->prev = prev_object;
                current_object->prev = new_object;

            }else{
                new_object->prev = NULL;
                current_object->prev = NULL;
            }



            l->size+=1;
            return;
        }
        
        
    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }



}

void list_insert_uint(list* l, int index, unsigned int element){

    if(index < -1){
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INSERT_OUT_OF_RANGE);
        #endif
        return;
    }
    
    if(index == -1 || (long long)l->size <= index){
        l->append->_uint_(l,element);
        return;
    }

    if(l->type == LIST_TYPE_SEQUENTIAL){
        list_object* new_object_list = (list_object*)malloc(sizeof(list_object)*(l->size +1));
        
        if(new_object_list != NULL){

        
            for (int i = 0,j = 0; i < l->size; j++,i++){
                
                if ( i == index){
                    new_object_list[++j] = l->objects[i];
                }else{
                    new_object_list[j] = l->objects[i];
                }

            }
            free(l->objects);
            l->objects = new_object_list;
            unsigned int* new_data = (unsigned int*)malloc(sizeof(unsigned int));
            *new_data = element;

            list_object new_object;
            new_object.data = (void*)new_data;
            new_object.type = LIST_UINT;
            l->objects[index] = new_object;
            l->size+=1;


        }
        else{
            printf("%s\n",LIST_ERROR_ALLOCATION);
            exit(EXIT_FAILURE);
        }

    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){


        
        if(index == 0){
            l->prepend->_uint_(l,element);
            return;
        }else {
            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            unsigned int* new_data = (unsigned int*)malloc(sizeof(unsigned int));
            *new_data = element;
            
            new_object->data = (void*)new_data;
            new_object->type = LIST_UINT;
            int i;


            list_object* current_object,*prev_object;

            for( prev_object = l->objects,current_object=l->objects->next, i=1; i != index ; i++,prev_object=prev_object->next,current_object=current_object->next){}        

            prev_object->next = new_object;
            new_object->next = current_object;

            if(l->type == LIST_TYPE_DOUBLE_LINKED){
                new_object->prev = prev_object;
                current_object->prev = new_object;

            }else{
                new_object->prev = NULL;
                current_object->prev = NULL;
            }



            l->size+=1;
            return;
        }
        
        
    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }


}

void list_insert_short(list* l, int index, short element){

    if(index < -1){
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INSERT_OUT_OF_RANGE);
        #endif
        return;
    }
    
    if(index == -1 || (long long)l->size <= index){
        l->append->_short_(l,element);
        return;
    }

    if(l->type == LIST_TYPE_SEQUENTIAL){
        list_object* new_object_list = (list_object*)malloc(sizeof(list_object)*(l->size +1));
        
        if(new_object_list != NULL){

        
            for (int i = 0,j = 0; i < l->size; j++,i++){
                
                if ( i == index){
                    new_object_list[++j] = l->objects[i];
                }else{
                    new_object_list[j] = l->objects[i];
                }

            }
            free(l->objects);
            l->objects = new_object_list;
            short* new_data = (short*)malloc(sizeof(short));
            *new_data = element;

            list_object new_object;
            new_object.data = (void*)new_data;
            new_object.type = LIST_SHORT;
            l->objects[index] = new_object;
            l->size+=1;


        }
        else{
            printf("%s\n",LIST_ERROR_ALLOCATION);
            exit(EXIT_FAILURE);
        }

    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){


        
        if(index == 0){
            l->prepend->_short_(l,element);
            return;
        }else {
            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            short* new_data = (short*)malloc(sizeof(short));
            *new_data = element;
            
            new_object->data = (void*)new_data;
            new_object->type = LIST_SHORT;
            int i;


            list_object* current_object,*prev_object;

            for( prev_object = l->objects,current_object=l->objects->next, i=1; i != index ; i++,prev_object=prev_object->next,current_object=current_object->next){}        

            prev_object->next = new_object;
            new_object->next = current_object;

            if(l->type == LIST_TYPE_DOUBLE_LINKED){
                new_object->prev = prev_object;
                current_object->prev = new_object;

            }else{
                new_object->prev = NULL;
                current_object->prev = NULL;
            }



            l->size+=1;
            return;
        }
        
        
    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }   


}

void list_insert_ushort(list* l, int index, unsigned short element){

    if(index < -1){
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INSERT_OUT_OF_RANGE);
        #endif
        return;
    }
    
    if(index == -1 || (long long)l->size <= index){
        l->append->_ushort_(l,element);
        return;
    }

    if(l->type == LIST_TYPE_SEQUENTIAL){
        list_object* new_object_list = (list_object*)malloc(sizeof(list_object)*(l->size +1));
        
        if(new_object_list != NULL){

        
            for (int i = 0,j = 0; i < l->size; j++,i++){
                
                if ( i == index){
                    new_object_list[++j] = l->objects[i];
                }else{
                    new_object_list[j] = l->objects[i];
                }

            }
            free(l->objects);
            l->objects = new_object_list;
            unsigned short* new_data = (unsigned short*)malloc(sizeof(unsigned short));
            *new_data = element;

            list_object new_object;
            new_object.data = (void*)new_data;
            new_object.type = LIST_USHORT;
            l->objects[index] = new_object;
            l->size+=1;


        }
        else{
            printf("%s\n",LIST_ERROR_ALLOCATION);
            exit(EXIT_FAILURE);
        }

    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){


        
        if(index == 0){
            l->prepend->_ushort_(l,element);
            return;
        }else {
            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            unsigned short* new_data = (unsigned short*)malloc(sizeof(unsigned short));
            *new_data = element;
            
            new_object->data = (void*)new_data;
            new_object->type = LIST_USHORT;
            int i;


            list_object* current_object,*prev_object;

            for( prev_object = l->objects,current_object=l->objects->next, i=1; i != index ; i++,prev_object=prev_object->next,current_object=current_object->next){}        

            prev_object->next = new_object;
            new_object->next = current_object;

            if(l->type == LIST_TYPE_DOUBLE_LINKED){
                new_object->prev = prev_object;
                current_object->prev = new_object;

            }else{
                new_object->prev = NULL;
                current_object->prev = NULL;
            }



            l->size+=1;
            return;
        }
        
        
    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }


}

void list_insert_longlong(list* l, int index, long long element){

    if(index < -1){
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INSERT_OUT_OF_RANGE);
        #endif
        return;
    }
    
    if(index == -1 || (long long)l->size <= index){
        l->append->_longlong_(l,element);
        return;
    }

    if(l->type == LIST_TYPE_SEQUENTIAL){
        list_object* new_object_list = (list_object*)malloc(sizeof(list_object)*(l->size +1));
            
            if(new_object_list != NULL){

            
                for (int i = 0,j = 0; i < l->size; j++,i++){
                    
                    if ( i == index){
                        new_object_list[++j] = l->objects[i];
                    }else{
                        new_object_list[j] = l->objects[i];
                    }

                }
                free(l->objects);
                l->objects = new_object_list;
                long long* new_data = (long long*)malloc(sizeof(long long));
                *new_data = element;

                list_object new_object;
                new_object.data = (void*)new_data;
                new_object.type = LIST_LONGLONG;
                l->objects[index] = new_object;
                l->size+=1;


            }
            else{
                printf("%s\n",LIST_ERROR_ALLOCATION);
                exit(EXIT_FAILURE);
            }

    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){


        
        if(index == 0){
            l->prepend->_longlong_(l,element);
            return;
        }else {
            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            long long* new_data = (long long*)malloc(sizeof(long long));
            *new_data = element;
            
            new_object->data = (void*)new_data;
            new_object->type = LIST_LONGLONG;
            int i;


            list_object* current_object,*prev_object;

            for( prev_object = l->objects,current_object=l->objects->next, i=1; i != index ; i++,prev_object=prev_object->next,current_object=current_object->next){}        

            prev_object->next = new_object;
            new_object->next = current_object;

            if(l->type == LIST_TYPE_DOUBLE_LINKED){
                new_object->prev = prev_object;
                current_object->prev = new_object;

            }else{
                new_object->prev = NULL;
                current_object->prev = NULL;
            }



            l->size+=1;
            return;
        }
        
        
    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }
    


}

void list_insert_ulonglong(list* l, int index, unsigned long long element){

    if(index < -1){
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INSERT_OUT_OF_RANGE);
        #endif
        return;
    }
    
    if(index == -1 || (long long)l->size <= index){
        l->append->_ulonglong_(l,element);
        return;
    }

    if(l->type == LIST_TYPE_SEQUENTIAL){
        list_object* new_object_list = (list_object*)malloc(sizeof(list_object)*(l->size +1));
        
        if(new_object_list != NULL){

        
            for (int i = 0,j = 0; i < l->size; j++,i++){
                
                if ( i == index){
                    new_object_list[++j] = l->objects[i];
                }else{
                    new_object_list[j] = l->objects[i];
                }

            }
            free(l->objects);
            l->objects = new_object_list;
            unsigned long long* new_data = (unsigned long long*)malloc(sizeof(unsigned long long));
            *new_data = element;

            list_object new_object;
            new_object.data = (void*)new_data;
            new_object.type = LIST_ULONGLONG;
            l->objects[index] = new_object;
            l->size+=1;


        }
        else{
            printf("%s\n",LIST_ERROR_ALLOCATION);
            exit(EXIT_FAILURE);
        }

    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){


        
        if(index == 0){
            l->prepend->_ulonglong_(l,element);
            return;
        }else {
            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            unsigned long long* new_data = (unsigned long long*)malloc(sizeof(unsigned long long));
            *new_data = element;
            
            new_object->data = (void*)new_data;
            new_object->type = LIST_ULONGLONG;
            int i;


            list_object* current_object,*prev_object;

            for( prev_object = l->objects,current_object=l->objects->next, i=1; i != index ; i++,prev_object=prev_object->next,current_object=current_object->next){}        

            prev_object->next = new_object;
            new_object->next = current_object;

            if(l->type == LIST_TYPE_DOUBLE_LINKED){
                new_object->prev = prev_object;
                current_object->prev = new_object;

            }else{
                new_object->prev = NULL;
                current_object->prev = NULL;
            }



            l->size+=1;
            return;
        }
        
        
    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    } 


}

void list_insert_float(list* l, int index, float element){

    if(index < -1){
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INSERT_OUT_OF_RANGE);
        #endif
        return;
    }
    
    if(index == -1 || (long long)l->size <= index){
        l->append->_float_(l,element);
        return;
    }

    if(l->type == LIST_TYPE_SEQUENTIAL){
        list_object* new_object_list = (list_object*)malloc(sizeof(list_object)*(l->size +1));
        
        if(new_object_list != NULL){

        
            for (int i = 0,j = 0; i < l->size; j++,i++){
                
                if ( i == index){
                    new_object_list[++j] = l->objects[i];
                }else{
                    new_object_list[j] = l->objects[i];
                }

            }
            free(l->objects);
            l->objects = new_object_list;
            float* new_data = (float*)malloc(sizeof(float));
            *new_data = element;

            list_object new_object;
            new_object.data = (void*)new_data;
            new_object.type = LIST_FLOAT;
            l->objects[index] = new_object;
            l->size+=1;


        }
        else{
            printf("%s\n",LIST_ERROR_ALLOCATION);
            exit(EXIT_FAILURE);
        }

    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){


        
        if(index == 0){
            l->prepend->_float_(l,element);
            return;
        }else {
            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            float* new_data = (float*)malloc(sizeof(float));
            *new_data = element;
            
            new_object->data = (void*)new_data;
            new_object->type = LIST_FLOAT;
            int i;


            list_object* current_object,*prev_object;

            for( prev_object = l->objects,current_object=l->objects->next, i=1; i != index ; i++,prev_object=prev_object->next,current_object=current_object->next){}        

            prev_object->next = new_object;
            new_object->next = current_object;

            if(l->type == LIST_TYPE_DOUBLE_LINKED){
                new_object->prev = prev_object;
                current_object->prev = new_object;

            }else{
                new_object->prev = NULL;
                current_object->prev = NULL;
            }



            l->size+=1;
            return;
        }
        
        
    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }    


}

void list_insert_double(list* l, int index, double element){

    if(index < -1){
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INSERT_OUT_OF_RANGE);
        #endif
        return;
    }
    
    if(index == -1 || (long long)l->size <= index){
        l->append->_double_(l,element);
        return;
    }

    if(l->type == LIST_TYPE_SEQUENTIAL){
        list_object* new_object_list = (list_object*)malloc(sizeof(list_object)*(l->size +1));
        
        if(new_object_list != NULL){

        
            for (int i = 0,j = 0; i < l->size; j++,i++){
                
                if ( i == index){
                    new_object_list[++j] = l->objects[i];
                }else{
                    new_object_list[j] = l->objects[i];
                }

            }
            free(l->objects);
            l->objects = new_object_list;
            double* new_data = (double*)malloc(sizeof(double));
            *new_data = element;

            list_object new_object;
            new_object.data = (void*)new_data;
            new_object.type = LIST_DOUBLE;
            l->objects[index] = new_object;
            l->size+=1;


        }
        else{
            printf("%s\n",LIST_ERROR_ALLOCATION);
            exit(EXIT_FAILURE);
        }
        
    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){


        
        if(index == 0){
            l->prepend->_double_(l,element);
            return;
        }else {
            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            double* new_data = (double*)malloc(sizeof(double));
            *new_data = element;
            
            new_object->data = (void*)new_data;
            new_object->type = LIST_DOUBLE;
            int i;


            list_object* current_object,*prev_object;

            for( prev_object = l->objects,current_object=l->objects->next, i=1; i != index ; i++,prev_object=prev_object->next,current_object=current_object->next){}        

            prev_object->next = new_object;
            new_object->next = current_object;

            if(l->type == LIST_TYPE_DOUBLE_LINKED){
                new_object->prev = prev_object;
                current_object->prev = new_object;

            }else{
                new_object->prev = NULL;
                current_object->prev = NULL;
            }



            l->size+=1;
            return;
        }
        
        
    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }    


}

void list_insert_longdouble(list* l, int index, long double element){

    if(index < -1){
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INSERT_OUT_OF_RANGE);
        #endif
        return;
    }
    
    if(index == -1 || (long long)l->size <= index){
        l->append->_longdouble_(l,element);
        return;
    }

    if(l->type == LIST_TYPE_SEQUENTIAL){
        list_object* new_object_list = (list_object*)malloc(sizeof(list_object)*(l->size +1));
        
        if(new_object_list != NULL){

        
            for (int i = 0,j = 0; i < l->size; j++,i++){
                
                if ( i == index){
                    new_object_list[++j] = l->objects[i];
                }else{
                    new_object_list[j] = l->objects[i];
                }

            }
            free(l->objects);
            l->objects = new_object_list;
            long double* new_data = (long double*)malloc(sizeof(long double));
            *new_data = element;

            list_object new_object;
            new_object.data = (void*)new_data;
            new_object.type = LIST_LONGDOUBLE;
            l->objects[index] = new_object;
            l->size+=1;


        }
        else{
            printf("%s\n",LIST_ERROR_ALLOCATION);
            exit(EXIT_FAILURE);
        }  
    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){


        
        if(index == 0){
            l->prepend->_longdouble_(l,element);
            return;
        }else {
            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            long double* new_data = (long double*)malloc(sizeof(long double));
            *new_data = element;
            
            new_object->data = (void*)new_data;
            new_object->type = LIST_LONGDOUBLE;
            int i;


            list_object* current_object,*prev_object;

            for( prev_object = l->objects,current_object=l->objects->next, i=1; i != index ; i++,prev_object=prev_object->next,current_object=current_object->next){}        

            prev_object->next = new_object;
            new_object->next = current_object;

            if(l->type == LIST_TYPE_DOUBLE_LINKED){
                new_object->prev = prev_object;
                current_object->prev = new_object;

            }else{
                new_object->prev = NULL;
                current_object->prev = NULL;
            }



            l->size+=1;
            return;
        }
        
        
    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }    


}

void list_insert_char(list* l, int index, char element){

    if(index < -1){
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INSERT_OUT_OF_RANGE);
        #endif
        return;
    }
    
    if(index == -1 || (long long)l->size <= index){
        l->append->_char_(l,element);
        return;
    }

    if(l->type == LIST_TYPE_SEQUENTIAL){
        list_object* new_object_list = (list_object*)malloc(sizeof(list_object)*(l->size +1));
        
        if(new_object_list != NULL){

        
            for (int i = 0,j = 0; i < l->size; j++,i++){
                
                if ( i == index){
                    new_object_list[++j] = l->objects[i];
                }else{
                    new_object_list[j] = l->objects[i];
                }

            }
            free(l->objects);
            l->objects = new_object_list;
            char* new_data = (char*)malloc(sizeof(char));
            *new_data = element;

            list_object new_object;
            new_object.data = (void*)new_data;
            new_object.type = LIST_CHAR;
            l->objects[index] = new_object;
            l->size+=1;


        }
        else{
            printf("%s\n",LIST_ERROR_ALLOCATION);
            exit(EXIT_FAILURE);
        }

    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){


        
        if(index == 0){
            l->prepend->_char_(l,element);
            return;
        }else {
            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            char* new_data = (char*)malloc(sizeof(char));
            *new_data = element;
            
            new_object->data = (void*)new_data;
            new_object->type = LIST_CHAR;
            int i;


            list_object* current_object,*prev_object;

            for( prev_object = l->objects,current_object=l->objects->next, i=1; i != index ; i++,prev_object=prev_object->next,current_object=current_object->next){}        

            prev_object->next = new_object;
            new_object->next = current_object;

            if(l->type == LIST_TYPE_DOUBLE_LINKED){
                new_object->prev = prev_object;
                current_object->prev = new_object;

            }else{
                new_object->prev = NULL;
                current_object->prev = NULL;
            }



            l->size+=1;
            return;
        }
        
        
    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }    


}

void list_insert_uchar(list* l, int index, unsigned char element){

    if(index < -1){
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INSERT_OUT_OF_RANGE);
        #endif
        return;
    }
    
    if(index == -1 || (long long)l->size <= index){
        l->append->_uchar_(l,element);
        return;
    }

    if(l->type == LIST_TYPE_SEQUENTIAL){
        list_object* new_object_list = (list_object*)malloc(sizeof(list_object)*(l->size +1));
        
        if(new_object_list != NULL){

        
            for (int i = 0,j = 0; i < l->size; j++,i++){
                
                if ( i == index){
                    new_object_list[++j] = l->objects[i];
                }else{
                    new_object_list[j] = l->objects[i];
                }

            }
            free(l->objects);
            l->objects = new_object_list;
            unsigned char* new_data = (unsigned char*)malloc(sizeof(unsigned char));
            *new_data = element;

            list_object new_object;
            new_object.data = (void*)new_data;
            new_object.type = LIST_UCHAR;
            l->objects[index] = new_object;
            l->size+=1;


        }
        else{
            printf("%s\n",LIST_ERROR_ALLOCATION);
            exit(EXIT_FAILURE);
        }

    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){


        
        if(index == 0){
            l->prepend->_uchar_(l,element);
            return;
        }else {
            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            unsigned char* new_data = (unsigned char*)malloc(sizeof(unsigned char));
            *new_data = element;
            
            new_object->data = (void*)new_data;
            new_object->type = LIST_UCHAR;
            int i;


            list_object* current_object,*prev_object;

            for( prev_object = l->objects,current_object=l->objects->next, i=1; i != index ; i++,prev_object=prev_object->next,current_object=current_object->next){}        

            prev_object->next = new_object;
            new_object->next = current_object;

            if(l->type == LIST_TYPE_DOUBLE_LINKED){
                new_object->prev = prev_object;
                current_object->prev = new_object;

            }else{
                new_object->prev = NULL;
                current_object->prev = NULL;
            }



            l->size+=1;
            return;
        }
        
        
    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }    


}

void list_insert_string(list* l, int index, const char* element){

    if(index < -1){
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INSERT_OUT_OF_RANGE);
        #endif
        return;
    }
    
    if(index == -1 || (long long)l->size <= index){
        l->append->_string_(l,element);
        return;
    }

    if(l->type == LIST_TYPE_SEQUENTIAL){
        list_object* new_object_list = (list_object*)malloc(sizeof(list_object)*(l->size +1));
        
        if(new_object_list != NULL){

        
            for (int i = 0,j = 0; i < l->size; j++,i++){
                
                if ( i == index){
                    new_object_list[++j] = l->objects[i];
                }else{
                    new_object_list[j] = l->objects[i];
                }

            }
            free(l->objects);
            l->objects = new_object_list;
            char* new_data = (char*)malloc( (sizeof(char)*strlen(element))+1 );
            strcpy(new_data,element);

            list_object new_object;
            new_object.data = (void*)new_data;
            new_object.type = LIST_STRING;
            l->objects[index] = new_object;
            l->size+=1;


        }
        else{
            printf("%s\n",LIST_ERROR_ALLOCATION);
            exit(EXIT_FAILURE);
        }

    }
else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){


        
        if(index == 0){
            l->prepend->_string_(l,element);
            return;
        }else {
            list_object* new_object = (list_object*)malloc(sizeof(list_object));

            char* new_data = (char*)malloc((sizeof(char)*strlen(element))+1);
            strcpy(new_data,element);
            
            new_object->data = (void*)new_data;
            new_object->type = LIST_STRING;
            int i;


            list_object* current_object,*prev_object;

            for( prev_object = l->objects,current_object=l->objects->next, i=1; i != index ; i++,prev_object=prev_object->next,current_object=current_object->next){}        

            prev_object->next = new_object;
            new_object->next = current_object;

            if(l->type == LIST_TYPE_DOUBLE_LINKED){
                new_object->prev = prev_object;
                current_object->prev = new_object;

            }else{
                new_object->prev = NULL;
                current_object->prev = NULL;
            }



            l->size+=1;
            return;
        }
        
        
    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }


}




/// Miscallenous Functions ///

void* list_at(list* l, int index){
    if((long long)l->size <= index || index < -1){
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_AT_OUT_OF_RANGE);
        #endif
        return NULL;
    }    
    
    int converted_index = (index == -1) ? l->size -1 : index;
    
    if(l->type == LIST_TYPE_SEQUENTIAL){
        return (l->objects[converted_index].data);
    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){
        list_object* current_object;
        int i;
        for(current_object = l->objects,i=0; i != converted_index; current_object=current_object->next,i++);
        return (current_object->data);

    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return NULL;        
    }
    
}

void list_clear(list* l){
    
    if(l == NULL){
        return;
    }



    if( (l)->type == LIST_TYPE_SEQUENTIAL ){
        if((l)->objects != NULL)
            for (int i = 0; i < (l)->size; i++)
                free((l)->objects[i].data);


    free((l)->objects);    

    }else if( (l)->type == LIST_TYPE_SINGLE_LINKED ||  (l)->type == LIST_TYPE_DOUBLE_LINKED){

        if((l)->objects != NULL){
            list_object* current_object,*next_object;

            for(current_object = (l)->objects; current_object != NULL;){
                next_object = current_object->next;

                free(current_object->data);
                free(current_object);
                current_object = next_object;

            }
            

        }


    }



        
     
    
    
    free((l)->append);
    free((l)->prepend);
    free((l)->insert);
    free((l)->get);
    free((l)->set);
    free(l);
    l = NULL;
}

void list_print_all(list* l){
    if(l->type == LIST_TYPE_SEQUENTIAL){
        for ( size_t i = 0; i < l->size; i++){
            switch(l->objects[i].type){
                case LIST_INT:
                    printf("(%d) ",l->get->_int_(l,i));
                    break;
                case LIST_UINT:
                    printf("(%u) ",l->get->_uint_(l,i));
                    break;       

                case LIST_SHORT:
                    printf("(%hd) ",l->get->_short_(l,i));
                    break;
                case LIST_USHORT:
                    printf("(%hu) ",l->get->_ushort_(l,i));
                    break;

                case LIST_LONGLONG:
                    printf("(%lld) ",l->get->_longlong_(l,i));
                    break;
                case LIST_ULONGLONG:
                    printf("(%llu) ",l->get->_ulonglong_(l,i));
                    break;
                case LIST_FLOAT:
                    printf("(%f) ",l->get->_float_(l,i));
                    break;
                case LIST_DOUBLE:
                    printf("(%lf) ",l->get->_double_(l,i));
                    break;
                case LIST_LONGDOUBLE:
                    printf("(%Lf) ",l->get->_longdouble_(l,i));
                    break;
                case LIST_CHAR:
                    printf("('%c') ",l->get->_char_(l,i));
                    break;
                case LIST_UCHAR:
                    printf("('%c') ",l->get->_uchar_(l,i));
                    break;
                case LIST_STRING:
                    printf("(\"%s\") ",l->get->_string_(l,i));
                    break;

            }


        }

    }else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){
        list_object* current_object;
        int i;
        for ( current_object=l->objects,i=0; current_object != NULL; current_object=current_object->next,i++){
            switch(current_object->type){
                case LIST_INT:
                    printf("(%d) ",l->get->_int_(l,i));
                    break;
                case LIST_UINT:
                    printf("(%u) ",l->get->_uint_(l,i));
                    break;       

                case LIST_SHORT:
                    printf("(%hd) ",l->get->_short_(l,i));
                    break;
                case LIST_USHORT:
                    printf("(%hu) ",l->get->_ushort_(l,i));
                    break;

                case LIST_LONGLONG:
                    printf("(%lld) ",l->get->_longlong_(l,i));
                    break;
                case LIST_ULONGLONG:
                    printf("(%llu) ",l->get->_ulonglong_(l,i));
                    break;
                case LIST_FLOAT:
                    printf("(%f) ",l->get->_float_(l,i));
                    break;
                case LIST_DOUBLE:
                    printf("(%lf) ",l->get->_double_(l,i));
                    break;
                case LIST_LONGDOUBLE:
                    printf("(%Lf) ",l->get->_longdouble_(l,i));
                    break;
                case LIST_CHAR:
                    printf("('%c') ",l->get->_char_(l,i));
                    break;
                case LIST_UCHAR:
                    printf("('%c') ",l->get->_uchar_(l,i));
                    break;
                case LIST_STRING:
                    printf("(\"%s\") ",l->get->_string_(l,i));
                    break;

            }


        }

    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }

    printf("\n");

}

int list_sort(list* l, list_sort_type t){
    list_object_type dummy = (list_object_type)-1;

    // Returns 0 when the list is empty
    if(l->size < 2)
        return 0;

    // Type checking before sorting
    if(l->type == LIST_TYPE_SEQUENTIAL){
        dummy = l->objects[0].type;
        for(int i = 1; i < l->size; i++){
            if(l->objects[i].type != dummy){
                printf("%s\n",LIST_ERROR_SORT_TYPE_INCONSISTENT);
                return -1;
            }

        }

    }else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){

        dummy = l->objects->type;

        list_object* iterator = NULL;

        for(iterator = l->objects->next; ;iterator = iterator->next){

            if(iterator->type != dummy){
                printf("%s\n",LIST_ERROR_SORT_TYPE_INCONSISTENT);
                return -1;
            }
            if(iterator->next == NULL)
                break;

        }

    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return -1;        
    }





        for(int i = 0; i < l->size-1; i++){
            int swap_index = i;

            void* swap_element = (void*)l->at(l,i);

            for(int j = i+1; j < l->size; j++){

                void* current_element = l->at(l,j);
                
                switch(t){
                    case LIST_SORT_TYPE_ASCENDING:

                        switch(dummy){

                            case LIST_UCHAR:
                            if( *((unsigned char*)swap_element) > *((unsigned char*)current_element) ){
                                swap_element = current_element;
                                swap_index = j;
                            }
                            break;


                            case LIST_CHAR:
                            if( *((char*)swap_element) > *((char*)current_element) ){
                                swap_element = current_element;
                                swap_index = j;
                            }
                            break;

                            case LIST_LONGDOUBLE:
                            if( *((long double*)swap_element) > *((long double*)current_element) ){
                                swap_element = current_element;
                                swap_index = j;
                            }
                            break;


                            case LIST_DOUBLE:
                            if( *((double*)swap_element) > *((double*)current_element) ){
                                swap_element = current_element;
                                swap_index = j;
                            }
                            break;


                            case LIST_FLOAT:
                            if( *((float*)swap_element) > *((float*)current_element) ){
                                swap_element = current_element;
                                swap_index = j;
                            }
                            break;


                            case LIST_ULONGLONG:
                            if( *((unsigned long long*)swap_element) > *((unsigned long long*)current_element) ){
                                swap_element = current_element;
                                swap_index = j;
                            }
                            break;

                            case LIST_LONGLONG:
                            if( *((long long*)swap_element) > *((long long*)current_element) ){
                                swap_element = current_element;
                                swap_index = j;
                            }
                            break;
                            case LIST_USHORT:
                            if( *((unsigned short*)swap_element) > *((unsigned short*)current_element) ){
                                swap_element = current_element;
                                swap_index = j;
                            }
                            break;
                            case LIST_SHORT:
                            if( *((short*)swap_element) > *((short*)current_element) ){
                                swap_element = current_element;
                                swap_index = j;
                            }
                            break;


                            case LIST_UINT:
                            if( *((unsigned int*)swap_element) > *((unsigned int*)current_element) ){
                                swap_element = current_element;
                                swap_index = j;
                            }
                            break;


                            case LIST_INT:
                            if( *((int*)swap_element) > *((int*)current_element) ){
                                swap_element = current_element;
                                swap_index = j;
                            }
                            break;   

                            case LIST_STRING:
                            if( strcmp((char*)swap_element,(char*)current_element) > 0 ){
                                swap_element = current_element;
                                swap_index = j;
                            }
                            break;



                        }
 
                        break;


                    case LIST_SORT_TYPE_DESCENDING:

                        switch(dummy){

                            case LIST_UCHAR:
                            if( *((unsigned char*)swap_element) < *((unsigned char*)current_element) ){
                                swap_element = current_element;
                                swap_index = j;
                            }
                            break;


                            case LIST_CHAR:
                            if( *((char*)swap_element) < *((char*)current_element) ){
                                swap_element = current_element;
                                swap_index = j;
                            }
                            break;

                            case LIST_LONGDOUBLE:
                            if( *((long double*)swap_element) < *((long double*)current_element) ){
                                swap_element = current_element;
                                swap_index = j;
                            }
                            break;


                            case LIST_DOUBLE:
                            if( *((double*)swap_element) < *((double*)current_element) ){
                                swap_element = current_element;
                                swap_index = j;
                            }
                            break;


                            case LIST_FLOAT:
                            if( *((float*)swap_element) < *((float*)current_element) ){
                                swap_element = current_element;
                                swap_index = j;
                            }
                            break;


                            case LIST_ULONGLONG:
                            if( *((unsigned long long*)swap_element) < *((unsigned long long*)current_element) ){
                                swap_element = current_element;
                                swap_index = j;
                            }
                            break;

                            case LIST_LONGLONG:
                            if( *((long long*)swap_element) < *((long long*)current_element) ){
                                swap_element = current_element;
                                swap_index = j;
                            }
                            break;
                            case LIST_USHORT:
                            if( *((unsigned short*)swap_element) < *((unsigned short*)current_element) ){
                                swap_element = current_element;
                                swap_index = j;
                            }
                            break;
                            case LIST_SHORT:
                            if( *((short*)swap_element) < *((short*)current_element) ){
                                swap_element = current_element;
                                swap_index = j;
                            }
                            break;


                            case LIST_UINT:
                            if( *((unsigned int*)swap_element) < *((unsigned int*)current_element) ){
                                swap_element = current_element;
                                swap_index = j;
                            }
                            break;


                            case LIST_INT:
                            if( *((int*)swap_element) < *((int*)current_element) ){
                                swap_element = current_element;
                                swap_index = j;
                            }
                            break;   

                            case LIST_STRING:
                            if( strcmp((char*)swap_element,(char*)current_element) < 0 ){
                                swap_element = current_element;
                                swap_index = j;
                            }
                            break;



                        }


                        break;
                }

            }

            if(swap_index == i)
                continue;
            // Change the order //
            void* temp = l->at(l,i);
            l->set->_element_(l,i,l->at(l,swap_index));
            l->set->_element_(l,swap_index,temp);
            

            
            //l->objects[i].data = l->objects[swap_index].data;
            
            //l->objects[swap_index].data = temp;

        }


    return 1;
}



/// Set Functions ///

void list_set_int(list*l, int index, int element){

    if(index >= (long long)l->size || index < -1){
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_SET_OUT_OF_RANGE);
        #endif
        return;        
    }

    if(index == -1){
        list_append_int(l,element);
        return;
    }

    if(l->type == LIST_TYPE_SEQUENTIAL){
        free(l->objects[index].data);
        int* new_data = (int*)malloc(sizeof(int)); 
        *new_data = element;
        l->objects[index].data = new_data;
        l->objects[index].type = LIST_INT;

    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){
        int converted_index = (index == -1) ? l->size -1 : index;
        list_object* current_object;
        int i;
        for(current_object = l->objects,i=0; i != converted_index; current_object=current_object->next,i++);
        
        free(current_object->data);
         int* new_data = (int*)malloc(sizeof(int)); 
        *new_data = element;
        current_object->data = new_data;
        current_object->type = LIST_INT;       

    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }



    return;
}

void list_set_uint(list*l, int index, unsigned int element){

    if(index >= (long long)l->size || index < -1){
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_SET_OUT_OF_RANGE);
        #endif
        return;        
    }

    if(index == -1){
        list_append_uint(l,element);
        return;
    }

    if(l->type == LIST_TYPE_SEQUENTIAL){
        free(l->objects[index].data);
        unsigned int* new_data = (unsigned int*)malloc(sizeof(unsigned int)); 
        *new_data = element;
        l->objects[index].data = new_data;
        l->objects[index].type = LIST_UINT;

    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){
        int converted_index = (index == -1) ? l->size -1 : index;
        list_object* current_object;
        int i;
        for(current_object = l->objects,i=0; i != converted_index; current_object=current_object->next,i++);
        
        free(current_object->data);
        unsigned int* new_data = (unsigned int*)malloc(sizeof(unsigned int)); 
        *new_data = element;
        current_object->data = new_data;
        current_object->type = LIST_UINT;       

    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }


    return;
}

void list_set_short(list*l, int index, short element){

    if(index >= (long long)l->size || index < -1){
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_SET_OUT_OF_RANGE);
        #endif
        return;        
    }

    if(index == -1){
        list_append_short(l,element);
        return;
    }
    if(l->type == LIST_TYPE_SEQUENTIAL){
        free(l->objects[index].data);
        short* new_data = (short*)malloc(sizeof(short)); 
        *new_data = element;
        l->objects[index].data = new_data;
        l->objects[index].type = LIST_SHORT;

    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){
        int converted_index = (index == -1) ? l->size -1 : index;
        list_object* current_object;
        int i;
        for(current_object = l->objects,i=0; i != converted_index; current_object=current_object->next,i++);
        
        free(current_object->data);
        short* new_data = (short*)malloc(sizeof(short)); 
        *new_data = element;
        current_object->data = new_data;
        current_object->type = LIST_SHORT;       

    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }


    return;
}

void list_set_ushort(list*l, int index, unsigned short element){

    if(index >= (long long)l->size || index < -1){
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_SET_OUT_OF_RANGE);
        #endif
        return;        
    }

    if(index == -1){
        list_append_ushort(l,element);
        return;
    }
    if(l->type == LIST_TYPE_SEQUENTIAL){
        free(l->objects[index].data);
        unsigned short* new_data = (unsigned short*)malloc(sizeof(unsigned short)); 
        *new_data = element;
        l->objects[index].data = new_data;
        l->objects[index].type = LIST_USHORT;

    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){
        int converted_index = (index == -1) ? l->size -1 : index;
        list_object* current_object;
        int i;
        for(current_object = l->objects,i=0; i != converted_index; current_object=current_object->next,i++);
        
        free(current_object->data);
        unsigned short* new_data = (unsigned short*)malloc(sizeof(unsigned short)); 
        *new_data = element;
        current_object->data = new_data;
        current_object->type = LIST_USHORT;       

    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }


    return;
}

void list_set_longlong(list*l, int index, long long element){

    if(index >= (long long)l->size || index < -1){
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_SET_OUT_OF_RANGE);
        #endif
        return;        
    }

    if(index == -1){
        list_append_longlong(l,element);
        return;
    }
    if(l->type == LIST_TYPE_SEQUENTIAL){
        free(l->objects[index].data);
        long long* new_data = (long long*)malloc(sizeof(long long)); 
        *new_data = element;
        l->objects[index].data = new_data;
        l->objects[index].type = LIST_LONGLONG;

    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){
        int converted_index = (index == -1) ? l->size -1 : index;
        list_object* current_object;
        int i;
        for(current_object = l->objects,i=0; i != converted_index; current_object=current_object->next,i++);
        
        free(current_object->data);
        long long* new_data = (long long*)malloc(sizeof(long long)); 
        *new_data = element;
        current_object->data = new_data;
        current_object->type = LIST_LONGLONG;       

    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }


    return;
}

void list_set_ulonglong(list*l, int index, unsigned long long element){

    if(index >= (long long)l->size || index < -1){
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_SET_OUT_OF_RANGE);
        #endif
        return;        
    }

    if(index == -1){
        list_append_ulonglong(l,element);
        return;
    }
    if(l->type == LIST_TYPE_SEQUENTIAL){
        free(l->objects[index].data);
        unsigned long long* new_data = (unsigned long long*)malloc(sizeof(unsigned long long)); 
        *new_data = element;
        l->objects[index].data = new_data;
        l->objects[index].type = LIST_ULONGLONG;

    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){
        int converted_index = (index == -1) ? l->size -1 : index;
        list_object* current_object;
        int i;
        for(current_object = l->objects,i=0; i != converted_index; current_object=current_object->next,i++);
        
        free(current_object->data);
        unsigned long long* new_data = (unsigned long long*)malloc(sizeof(unsigned long long)); 
        *new_data = element;
        current_object->data = new_data;
        current_object->type = LIST_ULONGLONG;       

    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }


    return;
}

void list_set_float(list*l, int index, float element){

    if(index >= (long long)l->size || index < -1){
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_SET_OUT_OF_RANGE);
        #endif
        return;        
    }

    if(index == -1){
        list_append_float(l,element);
        return;
    }
    if(l->type == LIST_TYPE_SEQUENTIAL){
        free(l->objects[index].data);
        float* new_data = (float*)malloc(sizeof(float)); 
        *new_data = element;
        l->objects[index].data = new_data;
        l->objects[index].type = LIST_FLOAT;

    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){
        int converted_index = (index == -1) ? l->size -1 : index;
        list_object* current_object;
        int i;
        for(current_object = l->objects,i=0; i != converted_index; current_object=current_object->next,i++);
        
        free(current_object->data);
        float* new_data = (float*)malloc(sizeof(float)); 
        *new_data = element;
        current_object->data = new_data;
        current_object->type = LIST_FLOAT;       

    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }


    return;
}

void list_set_double(list*l, int index, double element){

    if(index >= (long long)l->size || index < -1){
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_SET_OUT_OF_RANGE);
        #endif
        return;        
    }

    if(index == -1){
        list_append_double(l,element);
        return;
    }
    if(l->type == LIST_TYPE_SEQUENTIAL){
        free(l->objects[index].data);
        double* new_data = (double*)malloc(sizeof(double)); 
        *new_data = element;
        l->objects[index].data = new_data;
        l->objects[index].type = LIST_DOUBLE;        
    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){
        int converted_index = (index == -1) ? l->size -1 : index;
        list_object* current_object;
        int i;
        for(current_object = l->objects,i=0; i != converted_index; current_object=current_object->next,i++);
        
        free(current_object->data);
        double* new_data = (double*)malloc(sizeof(double)); 
        *new_data = element;
        current_object->data = new_data;
        current_object->type = LIST_DOUBLE;       

    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }


    return;
}

void list_set_longdouble(list*l, int index, long double element){

    if(index >= (long long)l->size || index < -1){
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_SET_OUT_OF_RANGE);
        #endif
        return;        
    }

    if(index == -1){
        list_append_longdouble(l,element);
        return;
    }
    if(l->type == LIST_TYPE_SEQUENTIAL){
        free(l->objects[index].data);
        long double* new_data = (long double*)malloc(sizeof(long double)); 
        *new_data = element;
        l->objects[index].data = new_data;
        l->objects[index].type = LIST_LONGDOUBLE;

    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){
        int converted_index = (index == -1) ? l->size -1 : index;
        list_object* current_object;
        int i;
        for(current_object = l->objects,i=0; i != converted_index; current_object=current_object->next,i++);
        
        free(current_object->data);
        long double* new_data = (long double*)malloc(sizeof(long double)); 
        *new_data = element;
        current_object->data = new_data;
        current_object->type = LIST_LONGDOUBLE;       

    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }


    return;
}

void list_set_char(list*l, int index, char element){

    if(index >= (long long)l->size || index < -1){
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_SET_OUT_OF_RANGE);
        #endif
        return;        
    }

    if(index == -1){
        list_append_char(l,element);
        return;
    }
    if(l->type == LIST_TYPE_SEQUENTIAL){
        free(l->objects[index].data);
        char* new_data = (char*)malloc(sizeof(char)); 
        *new_data = element;
        l->objects[index].data = new_data;
        l->objects[index].type = LIST_CHAR;

    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){
        int converted_index = (index == -1) ? l->size -1 : index;
        list_object* current_object;
        int i;
        for(current_object = l->objects,i=0; i != converted_index; current_object=current_object->next,i++);
        
        free(current_object->data);
        char* new_data = (char*)malloc(sizeof(char)); 
        *new_data = element;
        current_object->data = new_data;
        current_object->type = LIST_CHAR;       

    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }


    return;
}

void list_set_uchar(list*l, int index, unsigned char element){

    if(index >= (long long)l->size || index < -1){
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_SET_OUT_OF_RANGE);
        #endif
        return;        
    }

    if(index == -1){
        list_append_uchar(l,element);
        return;
    }
    if(l->type == LIST_TYPE_SEQUENTIAL){
        free(l->objects[index].data);
        unsigned char* new_data = (unsigned char*)malloc(sizeof(unsigned char)); 
        *new_data = element;
        l->objects[index].data = new_data;
        l->objects[index].type = LIST_UCHAR;

    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){
        int converted_index = (index == -1) ? l->size -1 : index;
        list_object* current_object;
        int i;
        for(current_object = l->objects,i=0; i != converted_index; current_object=current_object->next,i++);
        
        free(current_object->data);
        unsigned char* new_data = (unsigned char*)malloc(sizeof(unsigned char)); 
        *new_data = element;
        current_object->data = new_data;
        current_object->type = LIST_UCHAR;       

    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }


    return;
}

void list_set_string(list*l, int index, const char* element){

    if(index >= (long long)l->size || index < -1){
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_SET_OUT_OF_RANGE);
        #endif
        return;        
    }

    if(index == -1){
        list_append_string(l,element);
        return;
    }

    if(l->type == LIST_TYPE_SEQUENTIAL){
        free(l->objects[index].data);
        char* new_data = (char*)malloc( (sizeof(char)* strlen(element))+1 ); 
        strcpy(new_data,element);
        l->objects[index].data = new_data;
        l->objects[index].type = LIST_STRING;

    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){
        int converted_index = (index == -1) ? l->size -1 : index;
        list_object* current_object;
        int i;
        for(current_object = l->objects,i=0; i != converted_index; current_object=current_object->next,i++);
        
        free(current_object->data);
        char* new_data = (char*)malloc((sizeof(char)* strlen(element))+1); 
        strcpy(new_data,element);
        current_object->data = new_data;
        current_object->type = LIST_STRING;       

    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }


    return;
}

void list_set_element(list*l,int index,void* element){
    if(index >= (long long)l->size || index < -1){
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_SET_OUT_OF_RANGE);
        #endif
        return;        
    }

    if(l->type == LIST_TYPE_SEQUENTIAL){

        l->objects[index].data = element;

    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){

        int converted_index = (index == -1) ? l->size -1 : index;
        list_object* current_object;
        int i;
        for(current_object = l->objects,i=0; i != converted_index; current_object=current_object->next,i++);
        
        current_object->data = element;

    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return;        
    }

}



/// Get Functions ///

int list_get_int(list* l, int index){
    

    if((long long)l->size <= index || index < -1){
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_GET_OUT_OF_RANGE);
        #endif
        return -1;
    }


    int converted_index = ((index == -1) ? l->size-1 : index);

    if(l->type == LIST_TYPE_SEQUENTIAL){
        if(l->objects[converted_index].type != LIST_INT){
            #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
            printf("%s\n",LIST_ERROR_GET_TYPE_MISMATCH);
            #endif
            return -1;
        }
        
            return *(int*)(l->objects[converted_index].data);

    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){
        list_object* current_object;
        int i;
        for(current_object = l->objects,i = 0; i != converted_index; current_object=current_object->next,i++){}

        if(current_object->type != LIST_INT){
            #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
            printf("%s\n",LIST_ERROR_GET_TYPE_MISMATCH);
            #endif
            return -1;            
        }

        return *(int*)(current_object->data);

    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return -1; 
    }
  
}

unsigned int list_get_uint(list* l, int index){
    
    
    if((long long)l->size <= index || index < -1){
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_GET_OUT_OF_RANGE);
        #endif
        return -1;
    }
    int converted_index = ((index == -1) ? l->size-1 : index);

    if(l->type == LIST_TYPE_SEQUENTIAL){
        if(l->objects[converted_index].type != LIST_UINT){
            #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
            printf("%s\n",LIST_ERROR_GET_TYPE_MISMATCH);
            #endif
            return -1;
        }
        
            return *(unsigned int*)(l->objects[converted_index].data);
    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){
        list_object* current_object;
        int i;
        for(current_object = l->objects,i = 0; i != converted_index; current_object=current_object->next,i++){}

        if(current_object->type != LIST_UINT){
            #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
            printf("%s\n",LIST_ERROR_GET_TYPE_MISMATCH);
            #endif
            return -1;            
        }

        return *(unsigned int*)(current_object->data);

    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return -1; 
    }
  


}

short list_get_short(list* l, int index){
    
    
    if((long long)l->size <= index || index < -1){
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_GET_OUT_OF_RANGE);
        #endif
        return -1;
    }
    int converted_index = ((index == -1) ? l->size-1 : index);

    if(l->type == LIST_TYPE_SEQUENTIAL){
        if(l->objects[converted_index].type != LIST_SHORT){
            #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
            printf("%s\n",LIST_ERROR_GET_TYPE_MISMATCH);
            #endif
            return -1;
        }

            return *(short*)(l->objects[converted_index].data);
        
    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){
        list_object* current_object;
        int i;
        for(current_object = l->objects,i = 0; i != converted_index; current_object=current_object->next,i++){}

        if(current_object->type != LIST_SHORT){
            #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
            printf("%s\n",LIST_ERROR_GET_TYPE_MISMATCH);
            #endif
            return -1;            
        }

        return *(short*)(current_object->data);

    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return -1; 
    }


}

unsigned short list_get_ushort(list* l, int index){
    
    
    if((long long)l->size <= index || index < -1){
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_GET_OUT_OF_RANGE);
        #endif
        return -1;
    }
    int converted_index = ((index == -1) ? l->size-1 : index);

    if(l->type == LIST_TYPE_SEQUENTIAL){
        if(l->objects[converted_index].type != LIST_USHORT){
            #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
            printf("%s\n",LIST_ERROR_GET_TYPE_MISMATCH);
            #endif
            return -1;
        }

            return *(unsigned short*)(l->objects[converted_index].data);

    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){
        list_object* current_object;
        int i;
        for(current_object = l->objects,i = 0; i != converted_index; current_object=current_object->next,i++){}

        if(current_object->type != LIST_USHORT){
            #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
            printf("%s\n",LIST_ERROR_GET_TYPE_MISMATCH);
            #endif
            return -1;            
        }

        return *(unsigned short*)(current_object->data);

    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return -1; 
    }


}

long long list_get_longlong(list* l, int index){
   
    
    if((long long)l->size <= index || index < -1){
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_GET_OUT_OF_RANGE);
        #endif
        return -1;
    }
    int converted_index = ((index == -1) ? l->size-1 : index);

    if(l->type == LIST_TYPE_SEQUENTIAL){
        if(l->objects[converted_index].type != LIST_LONGLONG){
            #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
            printf("%s\n",LIST_ERROR_GET_TYPE_MISMATCH);
            #endif
            return -1;
        }

            return *(long long*)(l->objects[converted_index].data);

    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){
        list_object* current_object;
        int i;
        for(current_object = l->objects,i = 0; i != converted_index; current_object=current_object->next,i++){}

        if(current_object->type != LIST_LONGLONG){
            #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
            printf("%s\n",LIST_ERROR_GET_TYPE_MISMATCH);
            #endif
            return -1;            
        }

        return *(long long*)(current_object->data);

    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return -1; 
    }


}

unsigned long long list_get_ulonglong(list* l, int index){
    
    
    if((long long)l->size <= index || index < -1){
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_GET_OUT_OF_RANGE);
        #endif
        return -1;
    }
    int converted_index = ((index == -1) ? l->size-1 : index);

    if(l->type == LIST_TYPE_SEQUENTIAL){
        if(l->objects[converted_index].type != LIST_ULONGLONG){
            #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
            printf("%s\n",LIST_ERROR_GET_TYPE_MISMATCH);
            #endif
            return -1;
        }

            return *(unsigned long long*)(l->objects[converted_index].data);

    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){
        list_object* current_object;
        int i;
        for(current_object = l->objects,i = 0; i != converted_index; current_object=current_object->next,i++){}

        if(current_object->type != LIST_ULONGLONG){
            #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
            printf("%s\n",LIST_ERROR_GET_TYPE_MISMATCH);
            #endif
            return -1;            
        }

        return *(unsigned long long*)(current_object->data);

    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return -1; 
    }


}

float list_get_float(list* l, int index){
    
    
    if((long long)l->size <= index || index < -1){
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_GET_OUT_OF_RANGE);
        #endif
        return -1;
    }
    int converted_index = ((index == -1) ? l->size-1 : index);

    if(l->type == LIST_TYPE_SEQUENTIAL){
        if(l->objects[converted_index].type != LIST_FLOAT){
            #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
            printf("%s",LIST_ERROR_GET_TYPE_MISMATCH);
            #endif
            return -1;
        }
        
            return *(float*)(l->objects[converted_index].data);

    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){
        list_object* current_object;
        int i;
        for(current_object = l->objects,i = 0; i != converted_index; current_object=current_object->next,i++){}

        if(current_object->type != LIST_FLOAT){
            #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
            printf("%s\n",LIST_ERROR_GET_TYPE_MISMATCH);
            #endif
            return -1;            
        }

        return *(float*)(current_object->data);

    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return -1; 
    }


}

double list_get_double(list* l, int index){
    
    
    if((long long)l->size <= index || index < -1){
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_GET_OUT_OF_RANGE);
        #endif
        return -1;
    }
    int converted_index = ((index == -1) ? l->size-1 : index);

    if(l->type == LIST_TYPE_SEQUENTIAL){
        if(l->objects[converted_index].type != LIST_DOUBLE){
            #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
            printf("%s\n",LIST_ERROR_GET_TYPE_MISMATCH);
            #endif
            return -1;
        }
    
            return *(double*)(l->objects[converted_index].data);

    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){
        list_object* current_object;
        int i;
        for(current_object = l->objects,i = 0; i != converted_index; current_object=current_object->next,i++){}

        if(current_object->type != LIST_DOUBLE){
            #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
            printf("%s\n",LIST_ERROR_GET_TYPE_MISMATCH);
            #endif
            return -1;            
        }

        return *(double*)(current_object->data);

    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return -1; 
    }


}

long double list_get_longdouble(list* l, int index){
    
    
    if((long long)l->size <= index || index < -1){
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_GET_OUT_OF_RANGE);
        #endif
        return -1;
    }
    int converted_index = ((index == -1) ? l->size-1 : index);

    if(l->type == LIST_TYPE_SEQUENTIAL){
        if(l->objects[converted_index].type != LIST_LONGDOUBLE){
            #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
            printf("%s\n",LIST_ERROR_GET_TYPE_MISMATCH);
            #endif
            return -1;
        }
        
            return *(long double*)(l->objects[converted_index].data);

    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){
        list_object* current_object;
        int i;
        for(current_object = l->objects,i = 0; i != converted_index; current_object=current_object->next,i++){}

        if(current_object->type != LIST_LONGDOUBLE){
            #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
            printf("%s\n",LIST_ERROR_GET_TYPE_MISMATCH);
            #endif
            return -1;            
        }

        return *(long double*)(current_object->data);

    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return -1; 
    }

}

char list_get_char(list* l, int index){
    
    
    if((long long)l->size <= index || index < -1){
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_GET_OUT_OF_RANGE);
        #endif
        return -1;
    }
    int converted_index = ((index == -1) ? l->size-1 : index);

    if(l->type == LIST_TYPE_SEQUENTIAL){
        if(l->objects[converted_index].type != LIST_CHAR){
            #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
            printf("%s\n",LIST_ERROR_GET_TYPE_MISMATCH);
            #endif
            return -1;
        }
        
            return *(char*)(l->objects[converted_index].data);

    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){
        list_object* current_object;
        int i;
        for(current_object = l->objects,i = 0; i != converted_index; current_object=current_object->next,i++){}

        if(current_object->type != LIST_CHAR){
            #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
            printf("%s\n",LIST_ERROR_GET_TYPE_MISMATCH);
            #endif
            return -1;            
        }

        return *(char*)(current_object->data);

    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return -1; 
    }

}

unsigned char list_get_uchar(list* l, int index){
    
    
    if((long long)l->size <= index || index < -1){
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_GET_OUT_OF_RANGE);
        #endif
        return -1;
    }
    int converted_index = ((index == -1) ? l->size-1 : index);

    if(l->type == LIST_TYPE_SEQUENTIAL){
        if(l->objects[converted_index].type != LIST_UCHAR){
            #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
            printf("%s\n",LIST_ERROR_GET_TYPE_MISMATCH);
            #endif
            return -1;
        }
        
            return *(unsigned char*)(l->objects[converted_index].data);

    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){
        list_object* current_object;
        int i;
        for(current_object = l->objects,i = 0; i != converted_index; current_object=current_object->next,i++){}

        if(current_object->type != LIST_UCHAR){
            #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
            printf("%s\n",LIST_ERROR_GET_TYPE_MISMATCH);
            #endif
            return -1;            
        }

        return *(unsigned char*)(current_object->data);

    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return -1; 
    }

}

char* list_get_string(list* l, int index){
    
    
    if((long long)l->size <= index || index < -1){
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_GET_OUT_OF_RANGE);
        #endif
        return LIST_GET_STRING_RETURN_NULL;
    }
    int converted_index = ((index == -1) ? l->size-1 : index);

    if(l->type == LIST_TYPE_SEQUENTIAL){
        if(l->objects[converted_index].type != LIST_STRING){
            #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
            printf("%s\n",LIST_ERROR_GET_TYPE_MISMATCH);
            #endif
            return LIST_GET_STRING_RETURN_NULL;
        }
        
            return (char*)(l->objects[converted_index].data);

    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){
        list_object* current_object;
        int i;
        for(current_object = l->objects,i = 0; i != converted_index; current_object=current_object->next,i++){}

        if(current_object->type != LIST_STRING){
            #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
            printf("%s\n",LIST_ERROR_GET_TYPE_MISMATCH);
            #endif
            return LIST_GET_STRING_RETURN_NULL;            
        }

        return (char*)(current_object->data);

    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return LIST_GET_STRING_RETURN_NULL; 
    }

}





/// Remove Functions ///

void list_remove(list* l, int index){
    if(l->size == 0)
        return;
    
    int converted_index = (index == -1) ? l->size -1 : index;
    

    if((long long)l->size <= index || index < -1){
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_REMOVE_OUT_OF_RANGE);
        #endif
        return;
    }


    if(l->type == LIST_TYPE_SEQUENTIAL){
        list_object* new_objects = (list_object*)malloc((sizeof(list_object)*(l->size))-1);
        
        for(int i = 0,j=0; i < l->size; i++){

            if(i != converted_index){
                new_objects[j] = l->objects[i];
                j++;
            }
            
        }
        free(l->objects[converted_index].data);
        free(l->objects);
        l->objects = new_objects;
        l->size-=1;
        return;

    }
    else if(l->type == LIST_TYPE_SINGLE_LINKED || l->type == LIST_TYPE_DOUBLE_LINKED){
        
        if(converted_index == 0){

            list_object* next_object = l->objects->next;

            free(l->objects->data);
            free(l->objects);
            l->objects = next_object;

            if(next_object != NULL)
                next_object->prev = NULL;
            

            l->size-=1;
            return;
        }else{

            list_object* prev_object,*current_object,*next_object;
            int i;
            prev_object = l->objects;
            current_object = l->objects->next;

            for(i = 1; i<converted_index  ;i++ ){
                prev_object = prev_object->next;
                current_object = current_object->next;
            }


            next_object = current_object->next;

           

            free(current_object->data);
            free(current_object);

            prev_object->next = next_object;

            if(l->type == LIST_TYPE_DOUBLE_LINKED){
                if(next_object != NULL)
                    next_object->prev = prev_object;  
            }else{
                if(next_object != NULL)
                    next_object->prev = NULL;               
            }



          
            l->size-=1;
            return;
        }







    }else{
        #if !defined(TECHLIB_LIST_DISABLE_ERRORS)
        printf("%s\n",LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);
        #endif
        return; 
    }



}




/// Create A New List /// 

list* list_new(list_type type){
    list* list_new = (list*)malloc(sizeof(list));
    list_new->objects = NULL;
    list_new->size = 0;
    list_new->type = type;


    // Create Inner Structures
    list_new->append = (list_append*)malloc(sizeof(list_append));
    list_new->prepend = (list_prepend*)malloc(sizeof(list_prepend));
    list_new->get = (list_get*)malloc(sizeof(list_get));
    list_new->set = (list_set*)malloc(sizeof(list_set));
    list_new->insert = (list_insert*)malloc(sizeof(list_insert));



    // Append Functions
    list_new->append->_int_ = list_append_int;
    list_new->append->_uint_ = list_append_uint;
    list_new->append->_short_ = list_append_short;
    list_new->append->_ushort_ = list_append_ushort;
    list_new->append->_longlong_ = list_append_longlong;
    list_new->append->_ulonglong_ = list_append_ulonglong;
    list_new->append->_float_ = list_append_float;  
    list_new->append->_double_ = list_append_double;
    list_new->append->_longdouble_ = list_append_longdouble;
    list_new->append->_char_ = list_append_char;
    list_new->append->_uchar_ = list_append_uchar;
    list_new->append->_string_ = list_append_string;

    // Prepend Functions
    list_new->prepend->_int_ = list_prepend_int;
    list_new->prepend->_uint_ = list_prepend_uint;
    list_new->prepend->_short_ = list_prepend_short;
    list_new->prepend->_ushort_ = list_prepend_ushort;
    list_new->prepend->_longlong_ = list_prepend_longlong;
    list_new->prepend->_ulonglong_ = list_prepend_ulonglong;
    list_new->prepend->_float_ = list_prepend_float;  
    list_new->prepend->_double_ = list_prepend_double;
    list_new->prepend->_longdouble_ = list_prepend_longdouble;
    list_new->prepend->_char_ = list_prepend_char;
    list_new->prepend->_uchar_ = list_prepend_uchar;
    list_new->prepend->_string_ = list_prepend_string;


    // Insert Functions

    list_new->insert->_int_ = list_insert_int;
    list_new->insert->_uint_ = list_insert_uint;
    list_new->insert->_short_ = list_insert_short;
    list_new->insert->_ushort_ = list_insert_ushort;
    list_new->insert->_longlong_ = list_insert_longlong;
    list_new->insert->_ulonglong_ = list_insert_ulonglong;
    list_new->insert->_float_ = list_insert_float;  
    list_new->insert->_double_ = list_insert_double;
    list_new->insert->_longdouble_ = list_insert_longdouble;
    list_new->insert->_char_ = list_insert_char;
    list_new->insert->_uchar_ = list_insert_uchar;
    list_new->insert->_string_ = list_insert_string;




    // Get Functions
    list_new->get->_int_ = list_get_int;
    list_new->get->_uint_ = list_get_uint;
    list_new->get->_short_ = list_get_short;
    list_new->get->_ushort_ = list_get_ushort;
    list_new->get->_longlong_ = list_get_longlong;
    list_new->get->_ulonglong_ = list_get_ulonglong;
    list_new->get->_float_ = list_get_float;
    list_new->get->_double_ = list_get_double;
    list_new->get->_longdouble_ = list_get_longdouble;
    list_new->get->_char_ = list_get_char;
    list_new->get->_uchar_ = list_get_uchar;
    list_new->get->_string_ = list_get_string;

    // Set Functions
    list_new->set->_int_ = list_set_int;
    list_new->set->_uint_ = list_set_uint;
    list_new->set->_short_ = list_set_short;
    list_new->set->_ushort_ = list_set_ushort;
    list_new->set->_longlong_ = list_set_longlong;
    list_new->set->_ulonglong_ = list_set_ulonglong;
    list_new->set->_float_ = list_set_float;
    list_new->set->_double_ = list_set_double;
    list_new->set->_longdouble_ = list_set_longdouble;
    list_new->set->_char_ = list_set_char;
    list_new->set->_uchar_ = list_set_uchar;
    list_new->set->_string_ = list_set_string;
    list_new->set->_element_ = list_set_element;


    // Remove Functions
    list_new->remove = list_remove;



    // Misc functions
    list_new->at = list_at;
    list_new->clear = list_clear;
    list_new->print_all = list_print_all;
    list_new->sort = list_sort;
    

    return list_new;
}

#endif // techlib-list.h
