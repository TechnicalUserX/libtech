 //===================================================================================================//
/**
 *  WRITER: TechnicaluserX
 * 
 *  VERSION: 1.0.0
 *  
 *  DESCRIPTION: C Dynamic Memory Based List Implementation
 *  
 *  LICENSE: This library is not currently under any license and it is free to modify/distribute. 
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

void list_append_int(list* l,int element);

void list_append_uint(list* l,unsigned int element);

void list_append_short(list* l,short element);

void list_append_ushort(list* l,unsigned short element);

void list_append_longlong(list* l,long long element);

void list_append_ulonglong(list* l,unsigned long long element);

void list_append_float(list* l,float element);

void list_append_double(list* l,double element);

void list_append_longdouble(list* l,long double element);

void list_append_char(list* l,char element);

void list_append_uchar(list* l,unsigned char element);

void list_append_string(list* l, const char* element);



/// Prepend Function ///

void list_prepend_int(list*l,int element);

void list_prepend_uint(list*l,unsigned int element);

void list_prepend_short(list*l,short element);

void list_prepend_ushort(list*l,unsigned short element);

void list_prepend_longlong(list*l,long long element);

void list_prepend_ulonglong(list*l,unsigned long long element);

void list_prepend_float(list*l,float element);

void list_prepend_double(list*l,double element);

void list_prepend_longdouble(list*l,long double element);

void list_prepend_char(list*l,char element);

void list_prepend_uchar(list*l,unsigned char element);

void list_prepend_string(list*l,const char* element);




/// Insert Functions ///

void list_insert_int(list* l, int index, int element);

void list_insert_uint(list* l, int index, unsigned int element);

void list_insert_short(list* l, int index, short element);

void list_insert_ushort(list* l, int index, unsigned short element);

void list_insert_longlong(list* l, int index, long long element);

void list_insert_ulonglong(list* l, int index, unsigned long long element);

void list_insert_float(list* l, int index, float element);

void list_insert_double(list* l, int index, double element);

void list_insert_longdouble(list* l, int index, long double element);

void list_insert_char(list* l, int index, char element);

void list_insert_uchar(list* l, int index, unsigned char element);

void list_insert_string(list* l, int index, const char* element);



/// Miscallenous Functions ///

void* list_at(list* l, int index);

void list_clear(list* l);

void list_print_all(list* l);

int list_sort(list* l, list_sort_type t);


/// Set Functions ///

void list_set_int(list*l, int index, int element);

void list_set_uint(list*l, int index, unsigned int element);

void list_set_short(list*l, int index, short element);

void list_set_ushort(list*l, int index, unsigned short element);

void list_set_longlong(list*l, int index, long long element);

void list_set_ulonglong(list*l, int index, unsigned long long element);

void list_set_float(list*l, int index, float element);

void list_set_double(list*l, int index, double element);

void list_set_longdouble(list*l, int index, long double element);

void list_set_char(list*l, int index, char element);

void list_set_uchar(list*l, int index, unsigned char element);

void list_set_string(list*l, int index, const char* element);

void list_set_element(list*l,int index,void* element);



/// Get Functions ///

int list_get_int(list* l, int index);

unsigned int list_get_uint(list* l, int index);

short list_get_short(list* l, int index);

unsigned short list_get_ushort(list* l, int index);

long long list_get_longlong(list* l, int index);

unsigned long long list_get_ulonglong(list* l, int index);

float list_get_float(list* l, int index);

double list_get_double(list* l, int index);

long double list_get_longdouble(list* l, int index);

char list_get_char(list* l, int index);

unsigned char list_get_uchar(list* l, int index);

char* list_get_string(list* l, int index);





/// Remove Functions ///

void list_remove(list* l, int index);



/// Create A New List /// 

list* list_new(list_type type);

#endif // techlib-list.h
