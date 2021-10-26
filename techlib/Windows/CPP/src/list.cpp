#include "../include/list.hpp"


TECHLIB_WINDLL_API techlib::list::list_t::list_t(techlib::list::list_type type){
    this->size = 0;
    this->type = type;
    this->objects = NULL;
}

TECHLIB_WINDLL_API techlib::list::list_t::~list_t(){
    this->clear();
}

TECHLIB_WINDLL_API techlib::list::list_object_type techlib::list::list_runtime_get_type(const std::size_t hash){

    
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
    else if(hash == typeid(const char*).hash_code())
        return LIST_CSTRING;
    else
        return LIST_CUSTOM;

}

TECHLIB_WINDLL_API int techlib::list::list_t::clear(){



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

TECHLIB_WINDLL_API techlib::list::list_object* techlib::list::list_t::operator[](int index){

    if(this->size <=index || index < 0)
        LIST_PANIC(TECHLIB_LIST_ERROR_GET_OUT_OF_RANGE,nullptr);


    if(this->type == LIST_TYPE_SEQUENTIAL){

        return &(this->objects[index]);

    }else if(this->type == LIST_TYPE_SINGLE_LINKED || this->type == LIST_TYPE_DOUBLE_LINKED){

        list_object* current_object;
        int i;
        for(current_object = this->objects,i = 0; i != index; current_object=current_object->next,i++){}
        
        return current_object;

    }else
        LIST_PANIC(TECHLIB_LIST_ERROR_INCORRECT_TYPE_INITIALIZATION,NULL);

    


}

TECHLIB_WINDLL_API int techlib::list::list_t::print(int index){

    
    list_object_type temp_type;

    if(this->size <=index || index < 0)
        LIST_PANIC(TECHLIB_LIST_ERROR_GET_OUT_OF_RANGE,-1);

    if(this->type == LIST_TYPE_SEQUENTIAL){

        temp_type = this->objects[index].type;

    }else if(this->type == LIST_TYPE_SINGLE_LINKED || this->type == LIST_TYPE_DOUBLE_LINKED){

        list_object* current_object;
        int i;
        for(current_object = this->objects,i = 0; i != index; current_object=current_object->next,i++){}
        
        temp_type = current_object->type;

    }else
        LIST_PANIC(TECHLIB_LIST_ERROR_INCORRECT_TYPE_INITIALIZATION,-1);

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
        case LIST_CSTRING:
            std::cout << "\"" << this->get<const char*>(index) << "\"";
            break; 
        default:
            std::cout << "[?]";

    }



    return 0;
}

TECHLIB_WINDLL_API int techlib::list::list_t::print_all(){

    std::cout << "[";
    for(int i = 0; i < this->size; i++){

        this->print(i);
        if(i != this->size-1)
            std::cout << ", ";

    }
    std::cout << "]\n";

    return 0;
}

TECHLIB_WINDLL_API int techlib::list::list_t::remove(int index){

    if(this->size == 0)
        return 0;


    int converted_index = (index == -1) ? this->size -1 : index;

    if(this->size <= converted_index || index < -1)
        LIST_PANIC(TECHLIB_LIST_ERROR_REMOVE_OUT_OF_RANGE,-1);



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
        LIST_PANIC(TECHLIB_LIST_ERROR_INCORRECT_TYPE_INITIALIZATION,-1);



}

TECHLIB_WINDLL_API int techlib::list::list_t::modify_data(int index, void* element){

if(index >= (long long)this->size || index < -1)
LIST_PANIC(TECHLIB_LIST_ERROR_SET_OUT_OF_RANGE,-1);



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
LIST_PANIC(TECHLIB_LIST_ERROR_INCORRECT_TYPE_INITIALIZATION,-1);

return 0;
}

