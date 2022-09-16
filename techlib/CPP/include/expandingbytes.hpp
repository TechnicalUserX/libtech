// Expanding Byte Stream



#ifndef _TECHLIB_EXPANDINGBYTES_HPP
#define _TECHLIB_EXPANDINGBYTES_HPP

#include <string>
#include <memory.h>
#include <iostream>
#include <cmath>
#include <cstddef>
#include <techlib/CPP/exception.hpp>


#define TECHLIB_EXPANDINGBYTES_ERROR_OUT_OF_RANGE " Expanding Bytes Error: operator[] out of range"


namespace techlib{
namespace expandingbytes{

typedef unsigned char byte_t;


class expandingbytes_t{

private:
    byte_t* bytes = new byte_t[1];
    size_t stream_capacity = 1;
    size_t stream_size = 0;

public:
    expandingbytes_t();

    expandingbytes_t(byte_t single_byte);

    expandingbytes_t(void* byte_address,size_t byte_count);

    expandingbytes_t(const expandingbytes_t& exb);

    ~expandingbytes_t();


    byte_t& operator[](int index);

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