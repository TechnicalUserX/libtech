#include "../include/expandingbytes.hpp"


techlib::expandingbytes::expandingbytes_t::expandingbytes_t(){}

techlib::expandingbytes::expandingbytes_t::expandingbytes_t(byte_t single_byte){
    this->expand(single_byte);
}


techlib::expandingbytes::expandingbytes_t::expandingbytes_t(void* byte_address, size_t byte_count){
    this->expand(byte_address,byte_count);
}


techlib::expandingbytes::expandingbytes_t::~expandingbytes_t(){

    this->clear();
}

techlib::expandingbytes::byte_t* techlib::expandingbytes::expandingbytes_t::stream(){

    return this->bytes;
}


size_t techlib::expandingbytes::expandingbytes_t::size(){

    return this->stream_size;

}

size_t techlib::expandingbytes::expandingbytes_t::capacity(){
    return this->stream_capacity;
}

int techlib::expandingbytes::expandingbytes_t::expand(byte_t single_byte){

    byte_t* new_address = nullptr;
    if( this->stream_capacity == this->stream_size ){
        this->stream_capacity *= 2;
        new_address = new byte_t[this->stream_capacity];
        for(size_t i = 0; i < this->stream_size; i++)
            new_address[i] = bytes[i];
        new_address[stream_size] = single_byte;
        delete[](this->bytes);
        this->bytes = new_address;
    }else{
        this->bytes[this->stream_size] = single_byte;
    }

    this->stream_size++;
    return 0;
}

int techlib::expandingbytes::expandingbytes_t::expand(void* byte_address, size_t byte_count){
    
    if(byte_count < 0){
        return -1;
    }
    if(byte_address == NULL){
        return -2;
    }
    
    byte_t* new_address = nullptr;

    if(this->stream_capacity == this->stream_size or this->stream_size + byte_count > this->stream_capacity){

        while(this->stream_size + byte_count > this->stream_capacity){
            this->stream_capacity *=2;
        }

        new_address = new byte_t[this->stream_capacity];

        for(size_t i = 0; i < this->stream_size; i++)
            new_address[i] = bytes[i];

        for(size_t i = this->stream_size, j = 0; j < byte_count; i++,j++){
            new_address[i] = ((byte_t*)byte_address)[j];
        }
        delete(this->bytes);
        this->bytes = new_address;
        this->stream_size += byte_count;
        return 0;
    }else{

        for(size_t i = 0; i < byte_count; i++){
            this->bytes[this->stream_size+i] = ((byte_t*)byte_address)[i];
        }
        return 0;
    }



}

techlib::expandingbytes::byte_t& techlib::expandingbytes::expandingbytes_t::operator[](int index){

    if(index < 0 or index >= this->stream_size){
        throw techlib::exception::out_of_range(TECHLIB_EXPANDINGBYTES_ERROR_OUT_OF_RANGE);
    }

    return (*(this->bytes+index));
}

techlib::expandingbytes::expandingbytes_t& techlib::expandingbytes::expandingbytes_t::operator=(const techlib::expandingbytes::expandingbytes_t& exb){
    this->stream_size = exb.stream_size;
    this->stream_capacity = exb.stream_capacity;
    byte_t* new_bytes = new byte_t[exb.stream_capacity];

    for(size_t i = 0; i < exb.stream_size; i++){
        new_bytes[i] = exb.bytes[i];
    }
    if(this->stream_size > 0){
        delete[](this->bytes);
    }

    this->bytes = new_bytes;

    return *this;
}

techlib::expandingbytes::expandingbytes_t::expandingbytes_t(const techlib::expandingbytes::expandingbytes_t& exb){


    this->stream_size = exb.stream_size;
    this->stream_capacity = exb.stream_capacity;
    byte_t* new_bytes = new byte_t[exb.stream_capacity];

    for(size_t i = 0; i < exb.stream_capacity; i++){
        new_bytes[i] = exb.bytes[i];
    }
    if(this->stream_size > 0){
        delete[](this->bytes);
    }

    this->bytes = new_bytes;

}

void techlib::expandingbytes::expandingbytes_t::clear(){
    delete[](this->bytes);
    this->bytes = new byte_t[1];
    this->bytes[0] = 0x0;
    this->stream_size = 0;
    this->stream_capacity = 1;
}