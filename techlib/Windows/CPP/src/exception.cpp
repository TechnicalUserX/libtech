#include "../include/exception.hpp"

TECHLIB_WINDLL_API techlib::exception::exception_t::exception_t(error_code code){
    this->code = code;
}
TECHLIB_WINDLL_API techlib::exception::exception_t::exception_t(std::string description,error_code code){
    this->description = description;
    this->code = code;
};



TECHLIB_WINDLL_API techlib::exception::custom_exception::custom_exception(): exception_t(error_code::CUSTOM_EXCEPTION){}
TECHLIB_WINDLL_API techlib::exception::custom_exception::custom_exception(std::string description): exception_t(description,error_code::CUSTOM_EXCEPTION){}


TECHLIB_WINDLL_API techlib::exception::out_of_range::out_of_range(): exception_t(error_code::OUT_OF_RANGE){}
TECHLIB_WINDLL_API techlib::exception::out_of_range::out_of_range(std::string description): exception_t(description,error_code::OUT_OF_RANGE){}


TECHLIB_WINDLL_API techlib::exception::bad_allocation::bad_allocation(): exception_t(error_code::BAD_ALLOCATION){}
TECHLIB_WINDLL_API techlib::exception::bad_allocation::bad_allocation(std::string description): exception_t(description,error_code::BAD_ALLOCATION){}


TECHLIB_WINDLL_API techlib::exception::runtime_exception::runtime_exception(): exception_t(error_code::RUNTIME_EXCEPTION){}
TECHLIB_WINDLL_API techlib::exception::runtime_exception::runtime_exception(std::string description): exception_t(description,error_code::RUNTIME_EXCEPTION){}


TECHLIB_WINDLL_API techlib::exception::type_mismatch::type_mismatch(): exception_t(error_code::TYPE_MISMATCH){}
TECHLIB_WINDLL_API techlib::exception::type_mismatch::type_mismatch(std::string description): exception_t(description,error_code::TYPE_MISMATCH){}

TECHLIB_WINDLL_API techlib::exception::bad_initialization::bad_initialization(): exception_t(error_code::BAD_INITIALIZATION){}
TECHLIB_WINDLL_API techlib::exception::bad_initialization::bad_initialization(std::string description): exception_t(description,error_code::BAD_INITIALIZATION){}

TECHLIB_WINDLL_API techlib::exception::type_inconsistency::type_inconsistency(): exception_t(error_code::BAD_INITIALIZATION){}
TECHLIB_WINDLL_API techlib::exception::type_inconsistency::type_inconsistency(std::string description): exception_t(description,error_code::BAD_INITIALIZATION){}

