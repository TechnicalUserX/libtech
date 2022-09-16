#ifndef _TECHLIB_SOCKET_HPP
#define _TECHLIB_SOCKET_HPP

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sys/types.h>
#include <stdint.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <cerrno>

namespace techlib{
namespace sockets{


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
    int                     socket_create(int domain,int type,int protocol, uint16_t port, std::string ip);
    int                     socket_bind();
    int                     socket_listen(int queue_count);
    int                     socket_accept(techlib::sockets::socket_connection_t& connection);
    int                     socket_connect(techlib::sockets::socket_connection_t& connection);
    int                     socket_shutdown(int how);
    
};


};
};

#endif