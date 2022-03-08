 //===================================================================================================//
/**
 *  WRITER: TechnicaluserX
 *  
 *  DESCRIPTION: C++ Dynamic Memory Based List Implementation.
 *  
 *  LICENSE: This library is currently not under any license and it is free to modify/distribute. 
 * 
 */
 //===================================================================================================//





#ifndef _TECHLIB_LIST_HPP
#define _TECHLIB_LIST_HPP

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <typeinfo>
#include <string>
#include <cstring>
#include "exception.hpp"

namespace techlib{
namespace list{



#define TECHLIB_LIST_ERROR_ALLOCATION                       "List Error: Memory couldn't have been allocated."
#define TECHLIB_LIST_ERROR_GET_OUT_OF_RANGE                 "List Error: get() index out of range."
#define TECHLIB_LIST_ERROR_GET_TYPE_MISMATCH                "List Error: get() data type mismatch."
#define TECHLIB_LIST_ERROR_SET_OUT_OF_RANGE                 "List Error: set() index out of range."
#define TECHLIB_LIST_ERROR_REMOVE_OUT_OF_RANGE              "List Error: remove() index out of range."
#define TECHLIB_LIST_ERROR_INSERT_OUT_OF_RANGE              "List Error: insert() index out of range."
#define TECHLIB_LIST_ERROR_INCORRECT_TYPE_INITIALIZATION    "List Error: Incorrect list type initialzation -> (Unknown type)."
#define TECHLIB_LIST_ERROR_AT_OUT_OF_RANGE                  "List Error: at() index out of range."
#define TECHLIB_LIST_ERROR_SORT_TYPE_INCONSISTENT           "List Error: Cannot sort due to type inconsistency."

#define TECHLIB_LIST_GET_STRING_RETURN_NULL "(NULL)"



#define TECHLIB_LIST_TYPE_DEFAULT           LIST_TYPE_DOUBLE_LINKED
#define TECHLIB_LIST_SORT_METHOD_DEFAULT    LIST_SORT_METHOD_ASCENDING






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
        LIST_CSTRING,
        LIST_CUSTOM
    }list_object_type;


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
        template <typename list_set_type>       list_set_type operator=(list_set_type element);

    };

    typedef class list_t{

    public:
        class list_object* objects;    
        std::size_t     size;
        list_type       type;

        // Constructor-Destructor
            list_t(list_type type = TECHLIB_LIST_TYPE_DEFAULT);
            ~list_t();
            
            template <typename list_append_type>    int append(list_append_type element);
            template <typename list_prepend_type>   int prepend(list_prepend_type element);
            template <typename list_insert_type>    int insert(list_insert_type element,int index);

            list_object* list_get_pointer_to_object(int index);
            list_object& operator[](int index);


            template <typename list_get_type>       list_get_type get(int index);
            template <typename list_set_type>       int set(list_set_type element, int index);
            

            // Miscallenous
            int clear();
            int print(int index);
            int print_all();
            int remove(int index);
            template <typename list_sort_type> int sort(list_sort_method method = TECHLIB_LIST_SORT_METHOD_DEFAULT);
            int modify_data(int index, void* element);


    }list_t;

    list_object_type list_runtime_get_type(const std::size_t hash);

    template <typename list_append_type>    int             techlib::list::list_t::append(list_append_type element){

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
                throw techlib::exception::bad_allocation(TECHLIB_LIST_ERROR_ALLOCATION);
            
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
            throw techlib::exception::bad_initialization(TECHLIB_LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);



    }

    template <typename list_prepend_type>   int             techlib::list::list_t::prepend(list_prepend_type element){


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
                throw techlib::exception::bad_allocation(TECHLIB_LIST_ERROR_ALLOCATION);

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

    template <typename list_insert_type>    int             techlib::list::list_t::insert(list_insert_type element,int index){

        if(index < -1)
            throw techlib::exception::out_of_range(TECHLIB_LIST_ERROR_INSERT_OUT_OF_RANGE);

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
                throw techlib::exception::bad_allocation(TECHLIB_LIST_ERROR_ALLOCATION);


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
            throw techlib::exception::bad_initialization(TECHLIB_LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);


        return 0;
    }

    template <typename list_get_type>       list_get_type   techlib::list::list_t::get(int index){

    if(this->size <=index || index < 0)
            throw techlib::exception::out_of_range(TECHLIB_LIST_ERROR_GET_OUT_OF_RANGE);

        if(this->type == LIST_TYPE_SEQUENTIAL){

            if(this->objects[index].hash_code != typeid(list_get_type).hash_code())
                throw techlib::exception::type_mismatch(TECHLIB_LIST_ERROR_GET_TYPE_MISMATCH);



            return *((list_get_type*)this->objects[index].data);
            


        }else if(this->type == LIST_TYPE_SINGLE_LINKED || this->type == LIST_TYPE_DOUBLE_LINKED){

            list_object* current_object;
            int i;
            for(current_object = this->objects,i = 0; i != index; current_object=current_object->next,i++){}
            

            if(current_object->hash_code != typeid(list_get_type).hash_code())
                throw techlib::exception::type_mismatch(TECHLIB_LIST_ERROR_GET_TYPE_MISMATCH);


            return *((list_get_type*)current_object->data);

        }else
            throw techlib::exception::bad_initialization(TECHLIB_LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);

        return list_get_type();
    }

    template <typename list_set_type>       int             techlib::list::list_t::set(list_set_type element, int index){
        
        list_set_type* new_data = new list_set_type;
        *new_data = element;

    if(this->size <=index || index < 0)
            throw techlib::exception::out_of_range(TECHLIB_LIST_ERROR_GET_OUT_OF_RANGE);

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
            throw techlib::exception::bad_initialization(TECHLIB_LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);

    }

    template <typename list_sort_type>      int             techlib::list::list_t::sort(list_sort_method method ){


    if(this->size < 2)
        return 0;

    list_object_type dummy = list_runtime_get_type(typeid(list_sort_type).hash_code());

    if(this->type == LIST_TYPE_SEQUENTIAL){
        for(int i = 0; i < this->size; i++){
            if(this->objects[i].type != dummy){
                throw techlib::exception::type_inconsistency(TECHLIB_LIST_ERROR_SORT_TYPE_INCONSISTENT);
            }

        }

    }else if(this->type == LIST_TYPE_SINGLE_LINKED || this->type == LIST_TYPE_DOUBLE_LINKED){

        list_object* iterator = NULL;

        for(iterator = this->objects; ;iterator = iterator->next){

            if(iterator->type != dummy){
                throw techlib::exception::type_inconsistency(TECHLIB_LIST_ERROR_SORT_TYPE_INCONSISTENT);
            }
            if(iterator->next == NULL)
                break;

        }

    }else
        throw techlib::exception::bad_initialization(TECHLIB_LIST_ERROR_INCORRECT_TYPE_INITIALIZATION);        



        for(int i = 0; i < this->size-1; i++){

            int swap_index = i;
            list_sort_type swap_element = *((list_sort_type*)(this->list_get_pointer_to_object(i)->data));



            for(int j = i + 1; j < this->size; j++){

                list_sort_type current_element = *((list_sort_type*)(this->list_get_pointer_to_object(j)->data));
                
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
            
            void* temp = (this->list_get_pointer_to_object(i))->data;
            this->modify_data(i,(this->list_get_pointer_to_object(swap_index))->data);
            this->modify_data(swap_index,temp);


        }




    


    return 0;




}

    template <typename list_set_type>       list_set_type techlib::list::list_object::operator=(list_set_type element){

        list_set_type* new_data = new list_set_type;
        *new_data = element;

        delete(this->data);
        this->data = new_data;
        this->hash_code = typeid(list_set_type).hash_code();
        this->type = list_runtime_get_type(typeid(list_set_type).hash_code());
        return element;
    }


};
};


#endif // techlib/list.hpp
