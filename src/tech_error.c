#include "../include/tech_thread.h"
#include "../include/tech_error.h"


tech_thread_local_t enum tech_error_t tech_error_number;

const char* tech_error_what(enum tech_error_t error){

    switch(error){
        case TECH_SUCCESS:
            return "Success";
        case TECH_ERROR_NULL_POINTER:
            return "NULL pointer detected";
        default:
            return "Unkown error";
    }

}

