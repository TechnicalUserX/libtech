 //===================================================================================================//
/**
 *  WRITER: TechnicaluserX
 *  
 *  DESCRIPTION: Optimized data type for repeatedly inserting bytes into a stream.
 *  
 *  LICENSE: This library is not currently under any license and it is free to modify/distribute. 
 * 
 */
 //===================================================================================================//

#define TECHLIB_WINDLL_API __declspec(dllexport)


#ifndef _TECHLIB_EXPANDINGBYTES_HPP
#define _TECHLIB_EXPANDINGBYTES_HPP

#include <string>
#include <memory.h>
#include <iostream>
#include <cmath>
#include <cstddef>
#include "exception.hpp"



#define TECHLIB_EXPANDINGBYTES_ERROR_OUT_OF_RANGE " Expanding Bytes Error: operator[] out of range"


namespace techlib{
namespace expandingbytes{

typedef unsigned char byte_t;


class expandingbytes_t{

private:
    byte_t* bytes = new byte_t[1];
    size_t stream_capacity = 1;
    size_t current_byte_size = 0;

public:
    expandingbytes_t();

    expandingbytes_t(byte_t single_byte);

    expandingbytes_t(void* byte_address,size_t byte_count);

    expandingbytes_t(const expandingbytes_t& exb);

    ~expandingbytes_t();


    byte_t& operator[](int index);

    byte_t operator=(byte_t single_byte);

    expandingbytes_t& operator=(const expandingbytes_t& exb);


    void clear();

    int expand(void* byte_address, size_t byte_count);

    int expand(byte_t single_byte);

    size_t size();
    size_t capacity();
    byte_t* stream();


};







};};
#endif
