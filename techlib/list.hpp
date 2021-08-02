//===================================================================================================//
/**
 *  WRITER: TechnicaluserX
 *  
 *  C++ Dynamic Memory Based List Implementation
 *  Please note that this library is intended mainly for C++.
 *  
 *  LICENSE: This library is currently not under any license and it is free to modify/distribute. 
 * 
 * 
 *  IMPORTANT: This library uses the name "list" in order to represent the list data type.
 *  This might cause conflicts with the C++ data type "list", please do not use both types together.
 *  
 * 
 *  ERRORS: If you want to disable list error messages, #define TECHLIB_LIST_DISABLE_ERRORS
 *  You can change the null return value of list_get_string function by changing
 *  LIST_GET_STRING_RETURN_NULL down below. 
 * 
 *  
 */
 //===================================================================================================//






#ifndef _TECHLIB_LIST_HPP
#define _TECHLIB_LIST_HPP 1

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <typeinfo>
#include <string>
#include <cstring>

#define LIST_ERROR_ALLOCATION                       "List Error: Memory couldn't have been allocated."
#define LIST_ERROR_GET_OUT_OF_RANGE                 "List Error: get() index out of range."
#define LIST_ERROR_GET_TYPE_MISMATCH                "List Error: get() data type mismatch."
#define LIST_ERROR_SET_OUT_OF_RANGE                 "List Error: set() index out of range."
#define LIST_ERROR_REMOVE_OUT_OF_RANGE              "List Error: remove() index out of range."
#define LIST_ERROR_INSERT_OUT_OF_RANGE              "List Error: insert() index out of range."
#define LIST_ERROR_INCORRECT_TYPE_INITIALIZATION    "List Error: Incorrect list type initialzation -> (Unknown type)."
#define LIST_ERROR_AT_OUT_OF_RANGE                  "List Error: at() index out of range."
#define LIST_ERROR_SORT_TYPE_INCONSISTENT           "List Error: Cannot sort due to type inconsistency."

#define LIST_GET_STRING_RETURN_NULL "(NULL)"


#define LIST_TYPE_DEFAULT           LIST_TYPE_DOUBLE_LINKED
#define LIST_SORT_METHOD_DEFAULT    LIST_SORT_METHOD_ASCENDING



#ifndef TECHLIB_LIST_DISABLE_ERRORS
#define LIST_PANIC(reason,ret) { printf("%s\n",reason); return ret; }
#else
#define LIST_PANIC(reason,ret) {return ret;}
#endif


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
    LIST_LONG,
    LIST_ULONG,
    LIST_LONGLONG,
    LIST_ULONGLONG,
    LIST_FLOAT,
    LIST_DOUBLE,
    LIST_LONGDOUBLE,
    LIST_CHAR,
    LIST_UCHAR,
    LIST_BOOL,
    LIST_STRING,
    LIST_CUSTOM
}list_object_type;

list_object_type list_runtime_get_type(const std::size_t hash);

typedef enum list_sort_method{
    LIST_SORT_METHOD_ASCENDING,
    LIST_SORT_METHOD_DESCENDING
}list_sort_method;

class list_object{

public:

    void*                   data;    
    class list_object*      next;
    class list_object*      prev;
    list_object_type        type;
    std::size_t             hash_code;
    
};



//typedef class list_object list_object;

typedef class list{

public:
    class list_object* objects;    
    std::size_t     size;
    list_type       type;

    // Constructor-Destructor
        list(list_type type = LIST_TYPE_DEFAULT);
        ~list();
        
        template <typename list_append_type> int append(list_append_type element);
        template <typename list_prepend_type> int prepend(list_prepend_type element);
        template <typename list_insert_type> int insert(list_insert_type element,int index);

        list_object* operator[](int index);

        template <typename list_get_type>   list_get_type get(int index);
        template <typename list_set_type>   int set(list_set_type element, int index);

        // Miscallenous
        int clear();
        int print(int index);
        int print_all();
        int remove(int index);
        template <typename list_sort_type> int sort(list_sort_method method = LIST_SORT_METHOD_DEFAULT);
        int modify_data(int index, void* element);


}list;


list::list(list_type type){
    this->size = 0;
    this->type = type;
    this->objects = NULL;
}

list::~list(){
    this->clear();
}



// Generic Functions //

template <typename list_append_type> int list::append(list_append_type element){

    //list_append_type* new_data = (list_append_type*)malloc(sizeof(list_append_type));
    list_append_type* new_data = new list_append_type;
    *new_data = element;

    if(this->type == LIST_TYPE_SEQUENTIAL){
        
        //list_object* new_object_list = (list_object*)malloc(sizeof(list_object)*(this->size +1));
        
        list_object* new_object_list = new list_object[this->size + 1];

        if(new_object_list != NULL){
            for(int i = 0; i < this->size; i++){
                new_object_list[i] = this->objects[i];
            }
            //free(this->objects);
            delete this->objects;
            this->objects = new_object_list;
        }
        else
            LIST_PANIC(LIST_ERROR_ALLOCATION,-1);
        
        list_object new_object;
        new_object.data = new_data;
        new_object.type = list_runtime_get_type(typeid(list_append_type).hash_code());
        new_object.hash_code = typeid(list_append_type).hash_code();

        this->objects[this->size] = new_object;
        this->size++;
        return 0;


    }else if ( this->type == LIST_TYPE_SINGLE_LINKED || this->type == LIST_TYPE_DOUBLE_LINKED){
        
        //list_object* new_object = (list_object*)malloc(sizeof(list_object));

        list_object* new_object = new list_object;

        new_object->type = list_runtime_get_type(typeid(list_append_type).hash_code());
        new_object->data = new_data;
        new_object->hash_code = typeid(list_append_type).hash_code();
        

        if(this->objects == NULL){

            new_object->prev = NULL;
            new_object->next = NULL;
            this->objects = new_object;
            this->size++;      

        }else{

            list_object* current_object;
            for(current_object = this->objects; current_object->next != NULL; current_object = current_object->next);

            new_object->next = NULL;

            if(this->type == LIST_TYPE_DOUBLE_LINKED)
                new_object->prev = current_object;
            else
                new_object->prev = NULL;

            current_object->next = new_object;
            this->size++;
            
        }

        return 0;
    }else
        LIST_PANIC(LIST_ERROR_INCORRECT_TYPE_INITIALIZATION,-1);



}

template <typename list_prepend_type> int list::prepend(list_prepend_type element){


    // list_prepend_type* new_data = (list_prepend_type*)malloc(sizeof(list_prepend_type));

    list_prepend_type* new_data = new list_prepend_type;
    *new_data = element;

    
    
    if(this->type == LIST_TYPE_SEQUENTIAL){
        // list_object* new_object_list = (list_object*)malloc(sizeof(list_object)*(this->size +1));
        list_object* new_object_list = new list_object[this->size + 1];

        if(new_object_list != NULL){

            for ( int i = 0,j=1; i < this->size; i++,j++){
                new_object_list[j] = this->objects[i];
            }
            // free(this->objects);
            delete this->objects;
            this->objects = new_object_list;


        }else
            LIST_PANIC(LIST_ERROR_ALLOCATION,-1);

        list_object new_object;
        new_object.data = (void*)new_data;
        new_object.type = list_runtime_get_type(typeid(list_prepend_type).hash_code());
        new_object.hash_code = typeid(list_prepend_type).hash_code();


        this->objects[0] = new_object;
        this->size++;        
    }else if(this->type == LIST_TYPE_SINGLE_LINKED || this->type == LIST_TYPE_DOUBLE_LINKED){
 
        // list_object* new_object = (list_object*)malloc(sizeof(list_object));
        list_object* new_object = new list_object;

        new_object->data = (void*)new_data;
        new_object->type = list_runtime_get_type(typeid(list_prepend_type).hash_code());
        new_object->hash_code = typeid(list_prepend_type).hash_code();



        if(this->objects != NULL){

            list_object* next_object;
            next_object = this->objects;

            this->objects = new_object;

            new_object->next = next_object;
            new_object->prev = NULL;

            if(this->type == LIST_TYPE_DOUBLE_LINKED)
                next_object->prev = new_object;
            else
                next_object->prev = NULL;

            this->size++;
            return 0;

        }else{

            new_object->next = NULL;
            new_object->prev = NULL;
            this->objects = new_object;
            this->size++;
            return 0;
        }






    }


    return 0;
}

template <typename list_insert_type> int list::insert(list_insert_type element,int index){

    if(index < -1)
        LIST_PANIC(LIST_ERROR_INSERT_OUT_OF_RANGE,-1);

    if(index == -1 || this->size <= index){
        this->append<list_insert_type>(element);
        return 0;
    }

    if(index == 0){
        this->prepend<list_insert_type>(element);
        return 0;
    }

    list_insert_type* new_data = new list_insert_type;
    *new_data = element;

    if(this->type == LIST_TYPE_SEQUENTIAL){

        list_object* new_object_list = new list_object[this->size + 1];

        if(new_object_list != NULL){

            for(int i = 0, j = 0; i < this->size; j++,i++){

                if (i == index){
                    new_object_list[++j] = this->objects[i];
                }else{
                    new_object_list[j] = this->objects[i];
                }

            }

            delete this->objects;
            this->objects = new_object_list;
            
            list_object new_object;
            new_object.data = (void*)new_data;
            new_object.type = list_runtime_get_type(typeid(list_insert_type).hash_code());
            new_object.hash_code = typeid(list_insert_type).hash_code();

            this->objects[index] = new_object;
            this->size++;



        }else
            LIST_PANIC(LIST_ERROR_ALLOCATION,-1);


    }else if(this->type == LIST_TYPE_SINGLE_LINKED || this->type == LIST_TYPE_DOUBLE_LINKED){

        list_object* new_object = new list_object;

        new_object->data = new_data;
        new_object->type = list_runtime_get_type(typeid(list_insert_type).hash_code());
        new_object->hash_code = typeid(list_insert_type).hash_code();

        list_object* current_object, *prev_object;
        int i;
        for( prev_object = this->objects,current_object=this->objects->next, i=1; i != index ; i++,prev_object=prev_object->next,current_object=current_object->next){}        
        
        prev_object->next = new_object;
        new_object->next = current_object;

        if(this->type == LIST_TYPE_DOUBLE_LINKED){
            new_object->prev = prev_object;
            current_object->prev = new_object;

        }else{
            new_object->prev = NULL;
            current_object->prev = NULL;
        }

        this->size++;
        return 0;

    }else
        LIST_PANIC(LIST_ERROR_INCORRECT_TYPE_INITIALIZATION,-1);


    return 0;
}

template <typename list_get_type> list_get_type list::get(int index){

   if(this->size <=index || index < 0)
        LIST_PANIC(LIST_ERROR_GET_OUT_OF_RANGE,list_get_type());

    if(this->type == LIST_TYPE_SEQUENTIAL){

        if(this->objects[index].hash_code != typeid(list_get_type).hash_code())
            LIST_PANIC(LIST_ERROR_GET_TYPE_MISMATCH,list_get_type());



        return *((list_get_type*)this->objects[index].data);
        


    }else if(this->type == LIST_TYPE_SINGLE_LINKED || this->type == LIST_TYPE_DOUBLE_LINKED){

        list_object* current_object;
        int i;
        for(current_object = this->objects,i = 0; i != index; current_object=current_object->next,i++){}
        

        if(current_object->hash_code != typeid(list_get_type).hash_code())
            LIST_PANIC(LIST_ERROR_GET_TYPE_MISMATCH,list_get_type());


        return *((list_get_type*)current_object->data);

    }else
        LIST_PANIC(LIST_ERROR_INCORRECT_TYPE_INITIALIZATION,list_get_type());

    return list_get_type();
}

template <typename list_set_type> int list::set(list_set_type element, int index){
    
    list_set_type* new_data = new list_set_type;
    *new_data = element;

   if(this->size <=index || index < 0)
        LIST_PANIC(LIST_ERROR_GET_OUT_OF_RANGE,-1);

    if(this->type == LIST_TYPE_SEQUENTIAL){

        
        delete this->objects[index].data;
        this->objects[index].data = new_data;
        this->objects[index].hash_code = typeid(list_set_type).hash_code();
        this->objects[index].type = list_runtime_get_type(typeid(list_set_type).hash_code());
        return 0;


    }else if(this->type == LIST_TYPE_SINGLE_LINKED || this->type == LIST_TYPE_DOUBLE_LINKED){

        list_object* current_object;
        int i;
        for(current_object = this->objects,i = 0; i != index; current_object=current_object->next,i++){}
        

        delete current_object->data;

        current_object->data = new_data;
        current_object->hash_code = typeid(list_set_type).hash_code();
        current_object->type = list_runtime_get_type(typeid(list_set_type).hash_code());
        return 0;


    }else
        LIST_PANIC(LIST_ERROR_INCORRECT_TYPE_INITIALIZATION,-1);

}

template <typename list_sort_type> int list::sort(list_sort_method method ){


    if(this->size < 2)
        return 0;

    list_object_type dummy = list_runtime_get_type(typeid(list_sort_type).hash_code());

    if(this->type == LIST_TYPE_SEQUENTIAL){
        for(int i = 0; i < this->size; i++){
            if(this->objects[i].type != dummy){
                LIST_PANIC(LIST_ERROR_SORT_TYPE_INCONSISTENT,-1);
            }

        }

    }else if(this->type == LIST_TYPE_SINGLE_LINKED || this->type == LIST_TYPE_DOUBLE_LINKED){

        list_object* iterator = NULL;

        for(iterator = this->objects; ;iterator = iterator->next){

            if(iterator->type != dummy){
                LIST_PANIC(LIST_ERROR_SORT_TYPE_INCONSISTENT,-1);
            }
            if(iterator->next == NULL)
                break;

        }

    }else
        LIST_PANIC(LIST_ERROR_INCORRECT_TYPE_INITIALIZATION,-1);        



        for(int i = 0; i < this->size-1; i++){

            int swap_index = i;
            list_sort_type swap_element = *((list_sort_type*)(this->operator[](i)->data));



            for(int j = i + 1; j < this->size; j++){

                list_sort_type current_element = *((list_sort_type*)(this->operator[](j)->data));
                
                switch((int)method){
                    case LIST_SORT_METHOD_ASCENDING:
                        if(swap_element > current_element){
                            swap_element = current_element;
                            swap_index = j;
                        }
                        break;
                    case LIST_SORT_METHOD_DESCENDING:
                        if(swap_element < current_element){
                            swap_element = current_element;
                            swap_index = j;
                        }
                        break;
                }


            }


            if(swap_index == i)
                continue;
            
            void* temp = (this->operator[](i))->data;
            this->modify_data(i,(this->operator[](swap_index))->data);
            this->modify_data(swap_index,temp);


        }




    


    return 0;




}



// Miscellaneous Functions

list_object_type list_runtime_get_type(const std::size_t hash){

    
    if(hash == typeid(int).hash_code())
        return LIST_INT;
    else if(hash == typeid(unsigned int).hash_code())
        return LIST_UINT;
    else if(hash == typeid(short).hash_code())
        return LIST_SHORT;
    else if(hash == typeid(unsigned short).hash_code())
        return LIST_USHORT;
    else if(hash == typeid(long).hash_code())
        return LIST_LONG;
    else if(hash == typeid(unsigned long).hash_code())
        return LIST_ULONG;
    else if(hash == typeid(long long).hash_code())
        return LIST_LONGLONG;
    else if(hash == typeid(unsigned long long).hash_code())
        return LIST_ULONGLONG;
    else if(hash == typeid(char).hash_code())
        return LIST_CHAR;
    else if(hash == typeid(unsigned char).hash_code())
        return LIST_UCHAR;
    else if(hash == typeid(float).hash_code())
        return LIST_FLOAT;
    else if(hash == typeid(double).hash_code())
        return LIST_DOUBLE;
    else if(hash == typeid(long double).hash_code())
        return LIST_LONGDOUBLE;
    else if(hash == typeid(std::string).hash_code())
        return LIST_STRING;
    else if(hash == typeid(bool).hash_code())
        return LIST_BOOL;
    else 
        return LIST_CUSTOM;

}

int list::clear(){



    if ( this->type == LIST_TYPE_SEQUENTIAL){
        if(this->objects != NULL){
            for (int i = 0; i < this->size; i++)
                delete((char*)this->objects[i].data);
            
             delete this->objects;
        }else{
            return 0;
        }


       

    }else if(this->type == LIST_TYPE_SINGLE_LINKED || this->type == LIST_TYPE_DOUBLE_LINKED){

        if(this->objects != NULL){
            list_object *current_object, *next_object;


            for(current_object = this->objects; current_object != NULL;){
                next_object = current_object->next;

                delete((char*)current_object->data);
                delete current_object;
                current_object = next_object;

            }
            
        }else{
            return 0;
        }



    }

    this->objects = NULL;
    this->size = 0;
    return 0;
}

list_object* list::operator[](int index){

    if(this->size <=index || index < 0)
        LIST_PANIC(LIST_ERROR_GET_OUT_OF_RANGE,nullptr);


    if(this->type == LIST_TYPE_SEQUENTIAL){

        return &(this->objects[index]);

    }else if(this->type == LIST_TYPE_SINGLE_LINKED || this->type == LIST_TYPE_DOUBLE_LINKED){

        list_object* current_object;
        int i;
        for(current_object = this->objects,i = 0; i != index; current_object=current_object->next,i++){}
        
        return current_object;

    }else
        LIST_PANIC(LIST_ERROR_INCORRECT_TYPE_INITIALIZATION,NULL);



}

int list::print(int index){

    
    list_object_type temp_type;

    if(this->size <=index || index < 0)
        LIST_PANIC(LIST_ERROR_GET_OUT_OF_RANGE,-1);

    if(this->type == LIST_TYPE_SEQUENTIAL){

        temp_type = this->objects[index].type;

    }else if(this->type == LIST_TYPE_SINGLE_LINKED || this->type == LIST_TYPE_DOUBLE_LINKED){

        list_object* current_object;
        int i;
        for(current_object = this->objects,i = 0; i != index; current_object=current_object->next,i++){}
        
        temp_type = current_object->type;

    }else
        LIST_PANIC(LIST_ERROR_INCORRECT_TYPE_INITIALIZATION,-1);

    switch(temp_type){
        case LIST_INT:
            std::cout << this->get<int>(index);
            break;
        case LIST_UINT:
            std::cout << this->get<unsigned int>(index);
            break;
        case LIST_SHORT:
            std::cout << this->get<short>(index);
            break;
        case LIST_USHORT:
            std::cout << this->get<unsigned short>(index);
            break;
        case LIST_LONG:
            std::cout << this->get<long>(index);
            break;
        case LIST_ULONG:
            std::cout << this->get<unsigned long>(index);
            break;
        case LIST_LONGLONG:
            std::cout << this->get<long long>(index);
            break;
        case LIST_ULONGLONG:
            std::cout << this->get<unsigned long long>(index);
            break;
        case LIST_FLOAT:
            std::cout << this->get<float>(index);
            break;
        case LIST_DOUBLE:
            std::cout << this->get<double>(index);
            break;
        case LIST_LONGDOUBLE:
            std::cout << this->get<long double>(index);
            break;
        case LIST_CHAR:
            std::cout << "\'" << this->get<char>(index) << "\'";
            break;
        case LIST_UCHAR:
            std::cout << "\'" << this->get<unsigned char>(index) << "\'";
            break;
        case LIST_BOOL:
            std::cout << this->get<bool>(index);
            break;
        case LIST_STRING:
            std::cout << "\"" << this->get<std::string>(index) << "\"";
            break;
        default:
            std::cout << "[?]";

    }



    return 0;
}

int list::print_all(){

    std::cout << "[";
    for(int i = 0; i < this->size; i++){

        this->print(i);
        if(i != this->size-1)
            std::cout << ", ";

    }
    std::cout << "]\n";

    return 0;
}

int list::remove(int index){

    if(this->size == 0)
        return 0;


    int converted_index = (index == -1) ? this->size -1 : index;

    if(this->size <= converted_index || index < -1)
        LIST_PANIC(LIST_ERROR_REMOVE_OUT_OF_RANGE,-1);



    if(this->type == LIST_TYPE_SEQUENTIAL){
    
        //list_object* new_objects = (list_object*)malloc((sizeof(list_object)*(this->size))-1);
        list_object* new_objects = new list_object[this->size-1];
        for(int i = 0,j=0; i < this->size; i++){

            if(i != converted_index){
                new_objects[j] = this->objects[i];
                j++;
            }
    
        }
        delete( (char*)(this->objects[converted_index].data));
        delete( (char*)(this->objects));
        this->objects = new_objects;
        this->size-=1;
        return 0;

    }else if(this->type == LIST_TYPE_SINGLE_LINKED || this->type == LIST_TYPE_DOUBLE_LINKED){

        if(converted_index == 0){

            list_object* next_object = this->objects->next;

            delete((char*)(this->objects->data));
            delete((char*)(this->objects));
            this->objects = next_object;

            if(next_object != NULL)
                next_object->prev = NULL;
            

            this->size-=1;
            return 0;
        }else{

            list_object* prev_object,*current_object,*next_object;
            int i;
            prev_object = this->objects;
            current_object = this->objects->next;

            for(i = 1; i<converted_index; i++ ){
                prev_object = prev_object->next;
                current_object = current_object->next;
            }


            next_object = current_object->next;

           

            delete((char*)(current_object->data));
            delete((char*)(current_object));

            prev_object->next = next_object;

            if(this->type == LIST_TYPE_DOUBLE_LINKED){
                if(next_object != NULL)
                    next_object->prev = prev_object;  
            }else{
                if(next_object != NULL)
                    next_object->prev = NULL;               
            }



          
            this->size-=1;
            return 0;
        }


    }else
        LIST_PANIC(LIST_ERROR_INCORRECT_TYPE_INITIALIZATION,-1);



}

int list::modify_data(int index, void* element){

    if(index >= (long long)this->size || index < -1)
        LIST_PANIC(LIST_ERROR_SET_OUT_OF_RANGE,-1);



    if(this->type == LIST_TYPE_SEQUENTIAL){
        this->objects[index].data = element;

    }
    else if(this->type == LIST_TYPE_SINGLE_LINKED || this->type == LIST_TYPE_DOUBLE_LINKED){

        int converted_index = (index == -1) ? this->size -1 : index;
        list_object* current_object;
        int i;
        for(current_object = this->objects,i=0; i != converted_index; current_object=current_object->next,i++);
        
        current_object->data = element;

    }else
        LIST_PANIC(LIST_ERROR_INCORRECT_TYPE_INITIALIZATION,-1);

    return 0;
}




#endif // techlib-list.hpp
