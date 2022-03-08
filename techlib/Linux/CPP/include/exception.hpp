 //===================================================================================================//
/**
 *  WRITER: TechnicaluserX
 *  
 *  DESCRIPTION: Defines exception handling capabilities for C++ programs.
 *  
 *  LICENSE: This library is not currently under any license and it is free to modify/distribute. 
 * 
 */
 //===================================================================================================//


#ifndef _TECHLIB_EXCEPTION_HPP
#define _TECHLIB_EXCEPTION_HPP


#include <string>
#include <iostream>

namespace techlib{
namespace exception{

enum error_code{

    CUSTOM_EXCEPTION = 1,
    OUT_OF_RANGE,
    BAD_ALLOCATION,
    RUNTIME_EXCEPTION,
    TYPE_MISMATCH,
    BAD_INITIALIZATION,
    TYPE_INCONSISTENCY
};


class exception_t{

public:
    enum error_code code;
    std::string description = "";

    exception_t(error_code code);
    exception_t(std::string description,error_code code);


};





// EXCEPTIONS //

class custom_exception: public exception_t{
public:
    custom_exception();
    custom_exception(std::string description);

};

class out_of_range: public exception_t{
public:
    out_of_range();
    out_of_range(std::string description);

};

class bad_allocation: public exception_t{
public:
    bad_allocation();
    bad_allocation(std::string description);

};


class runtime_exception: public exception_t{
public:
    runtime_exception();
    runtime_exception(std::string description);

};

class type_mismatch: public exception_t{
public:
    type_mismatch();
    type_mismatch(std::string description);

};

class bad_initialization: public exception_t{
public:
    bad_initialization();
    bad_initialization(std::string description);

};

class type_inconsistency: public exception_t{
public:
    type_inconsistency();
    type_inconsistency(std::string description);

};



};};

#endif
