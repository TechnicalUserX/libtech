#ifndef _TECHLIB_SOCKET_HPP
#define _TECHLIB_SOCKET_HPP
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <cerrno>
#include "log.h"


#define TECHLIB_SOCKET_MAX_BUFFER_SIZE 1024


class socket_connection_t{

public:

    struct sockaddr_in  socket_info;
    uint16_t            port;
    std::string         ip;
    sa_family_t         family;
    int                 socket_descriptor;
    pthread_t           thread_descriptor = -1;


    ssize_t con_receive(void* buffer, size_t buffer_size, int flags);
    ssize_t con_send(void* buffer, size_t buffer_size, int flags);
    int     con_shutdown(int how);


};

class socket_t{
private:

    struct sockaddr_in  socket_address;
    int         socket_descriptor;
    // Domain and Family are same things
    int         domain; 
    int         type;
    int         protocol;
    uint16_t    port;
    socklen_t   socket_length;
    bool        is_listen_socket = false;


public:
    socket_t(int domain,int type,int protocol, uint16_t port, std::string ip);
    socket_t();
    int socket_create(int domain,int type,int protocol, uint16_t port, std::string ip);
    int socket_bind();
    int socket_listen(int queue_count);
    socket_connection_t socket_accept();
    socket_connection_t socket_connect();
    int socket_shutdown(int how);
    
};


// "socket_t" Functions



socket_t::socket_t(int domain,int type,int protocol, uint16_t port, std::string ip){
    
    this->socket_length = sizeof(this->socket_address);
    this->socket_create(domain, type, protocol, port, ip);
}

socket_t::socket_t(){
    this->socket_length = sizeof(this->socket_address);

}

int socket_t::socket_create(int domain, int type, int protocol,uint16_t port, std::string ip){

    if( (this->socket_descriptor = socket(domain,type,protocol)) == -1)
        PANIC_FATAL("socket_create()",-1);

    this->socket_address.sin_family = domain;
    this->socket_address.sin_port = htons(port);
    this->socket_address.sin_addr.s_addr = inet_addr(ip.data());    
    this->domain = domain;
    this->type = type;
    this->protocol = protocol;

    return this->socket_descriptor;
}

int socket_t::socket_bind(){

    if( bind(this->socket_descriptor, (struct sockaddr*)&this->socket_address, this->socket_length ))
        PANIC_FATAL("socket_bind()",-1);

    return 0;
}

int socket_t::socket_listen(int queue_count){
    this->is_listen_socket = true;
    if(listen(this->socket_descriptor,queue_count) == -1)
        PANIC_FATAL("socket_listen()",-1);
    return 0;
}

int socket_t::socket_shutdown(int how){
    if(shutdown(this->socket_descriptor,how) == -1)
        PANIC_FATAL("socket_shutdown()",-1);

    return 0;
}

int socket_connection_t::con_shutdown(int how){
    
    /*
     * Shutdown methods:
     *
     *  SHUT_RD     -   Shuts down read
     *  SHUT_WR     -   Shuts down write
     *  SHUT_RDWR   -   Shuts down both read and write 
     * 
     */
    if(shutdown(this->socket_descriptor,how) == -1)
        PANIC_THROW_ERROR("shutdown()",-1);

    return 0;
}

socket_connection_t socket_t::socket_connect(){
    
    socket_connection_t new_connection;

    

    if(connect(this->socket_descriptor,(struct sockaddr*)&this->socket_address,this->socket_length) == -1)
        PANIC_THROW_ERROR("socket_connect()",-1);
    
    
    
    char buffer[20];
    strcpy(buffer,inet_ntoa(this->socket_address.sin_addr));
    
    new_connection.family = this->domain;
    new_connection.ip = std::string(buffer);
    new_connection.port =  ntohs(this->socket_address.sin_port);
    new_connection.socket_descriptor = this->socket_descriptor;
    new_connection.socket_info = this->socket_address;
    

    return new_connection;
}

socket_connection_t socket_t::socket_accept(){

    struct sockaddr_in client_info;
    socket_connection_t new_connection;

    int client_socket_descriptor = accept(this->socket_descriptor,(struct sockaddr*)&client_info,&(this->socket_length));
    
    
    if(client_socket_descriptor == -1)
        PANIC_THROW_ERROR("accept()",-1);
    

    new_connection.family = client_info.sin_family;
    new_connection.socket_descriptor = client_socket_descriptor;

    char buffer[1024];
    strcpy(buffer,inet_ntoa(client_info.sin_addr));
    new_connection.ip = std::string(buffer);
    new_connection.port = ntohs(client_info.sin_port);
    
    return new_connection;
}




// "socket_connection_t" Functions

ssize_t socket_connection_t::con_receive(void* buffer, size_t buffer_size, int flags){

    ssize_t read_bytes = recv(this->socket_descriptor,buffer,buffer_size,flags);
    return read_bytes;
}

ssize_t socket_connection_t::con_send(void* buffer, size_t buffer_size, int flags){
    
    ssize_t send_bytes = send(this->socket_descriptor,buffer,buffer_size,flags);
    return send_bytes;
}



#endif