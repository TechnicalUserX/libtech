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

    return this->current_byte_size;

}

size_t techlib::expandingbytes::expandingbytes_t::capacity(){
    return this->stream_capacity;
}


int techlib::expandingbytes::expandingbytes_t::expand(byte_t single_byte){

    byte_t* new_address = nullptr;
    if( this->stream_capacity == this->current_byte_size ){
        this->stream_capacity *= 2;
        new_address = new byte_t[this->stream_capacity];
        for(size_t i = 0; i < this->current_byte_size; i++)
            new_address[i] = bytes[i];
        new_address[current_byte_size] = single_byte;
        delete[](this->bytes);
        this->bytes = new_address;
    }else{
        this->bytes[this->current_byte_size] = single_byte;
    }

    this->current_byte_size++;
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

    if(this->stream_capacity == this->current_byte_size or this->current_byte_size + byte_count > this->stream_capacity){

        while(this->current_byte_size + byte_count > this->stream_capacity){
            this->stream_capacity *=2;
        }

        new_address = new byte_t[this->stream_capacity];

        for(size_t i = 0; i < this->current_byte_size; i++)
            new_address[i] = bytes[i];

        for(size_t i = this->current_byte_size, j = 0; j < byte_count; i++,j++){
            new_address[i] = ((byte_t*)byte_address)[j];
        }
        delete[](this->bytes);
        this->bytes = new_address;
        this->current_byte_size += byte_count;
        return 0;
    }else{

        for(size_t i = 0; i < byte_count; i++){
            this->bytes[this->current_byte_size+i] = ((byte_t*)byte_address)[i];
        }
        this->current_byte_size += byte_count;
        return 0;
    }



}

techlib::expandingbytes::byte_t& techlib::expandingbytes::expandingbytes_t::operator[](int index){

    if(index < 0 or index >= this->current_byte_size){
        throw techlib::exception::out_of_range(TECHLIB_EXPANDINGBYTES_ERROR_OUT_OF_RANGE);
    }

    return (*(this->bytes+index));
}

techlib::expandingbytes::byte_t techlib::expandingbytes::expandingbytes_t::operator=(byte_t single_byte){
    *(this->bytes) = single_byte;
    return +single_byte;    
}

techlib::expandingbytes::expandingbytes_t& techlib::expandingbytes::expandingbytes_t::operator=(const techlib::expandingbytes::expandingbytes_t& exb){
    this->current_byte_size = exb.current_byte_size;
    this->stream_capacity = exb.stream_capacity;
    byte_t* new_bytes = new byte_t[exb.stream_capacity];

    for(size_t i = 0; i < exb.current_byte_size; i++){
        new_bytes[i] = exb.bytes[i];
    }
    if(this->current_byte_size > 0){
        delete[](this->bytes);
    }

    this->bytes = new_bytes;

    return *this;
}

techlib::expandingbytes::expandingbytes_t::expandingbytes_t(const techlib::expandingbytes::expandingbytes_t& exb){


    this->current_byte_size = exb.current_byte_size;
    this->stream_capacity = exb.stream_capacity;
    byte_t* new_bytes = new byte_t[exb.stream_capacity];

    for(size_t i = 0; i < exb.stream_capacity; i++){
        new_bytes[i] = exb.bytes[i];
    }
    if(this->current_byte_size > 0){
        delete[](this->bytes);
    }

    this->bytes = new_bytes;

}

void techlib::expandingbytes::expandingbytes_t::clear(){

    if(this->bytes == NULL)
        return;

    delete[](this->bytes);
    this->bytes = NULL;
}