#include "../include/sockets.hpp"


techlib::sockets::socket_t::socket_t(int domain, int type,int protocol, uint16_t port, std::string ip){
    this->socket_length = sizeof(this->socket_address);
    this->socket_create(domain, type, protocol, port, ip);
}

techlib::sockets::socket_t::socket_t(){
    this->socket_length = sizeof(this->socket_address);

}

int techlib::sockets::socket_t::socket_create(int domain, int type, int protocol,uint16_t port, std::string ip){

    if( (this->socket_descriptor = socket(domain,type,protocol)) == -1)
        return -1;

    this->socket_address.sin_family = domain;
    this->socket_address.sin_port = htons(port);
    this->socket_address.sin_addr.s_addr = inet_addr(ip.data());    
    this->domain = domain;
    this->type = type;
    this->protocol = protocol;

    return this->socket_descriptor;
}

int techlib::sockets::socket_t::socket_bind(){
    return bind(this->socket_descriptor, (struct sockaddr*)&this->socket_address, this->socket_length);
}

int techlib::sockets::socket_t::socket_listen(int queue_count){
    this->is_listen_socket = true;
    return listen(this->socket_descriptor,queue_count);
}


int techlib::sockets::socket_t::socket_shutdown(int how){
    /*
     * Shutdown methods:
     *
     *  SHUT_RD     -   Shuts down read
     *  SHUT_WR     -   Shuts down write
     *  SHUT_RDWR   -   Shuts down both read and write 
     * 
     */
    return shutdown(this->socket_descriptor,how);
}

int techlib::sockets::socket_connection_t::con_shutdown(int how){
    /*
     * Shutdown methods:
     *
     *  SHUT_RD     -   Shuts down read
     *  SHUT_WR     -   Shuts down write
     *  SHUT_RDWR   -   Shuts down both read and write 
     * 
     */
    return shutdown(this->socket_descriptor,how);

}

int techlib::sockets::socket_t::socket_connect(techlib::sockets::socket_connection_t& connection){
    
    socket_connection_t new_connection;

    

    if(connect(this->socket_descriptor,(struct sockaddr*)&this->socket_address,this->socket_length) == -1)
        return -1;
    
    
    
    char buffer[20];
    strcpy(buffer,inet_ntoa(this->socket_address.sin_addr));
    
    new_connection.family = this->domain;
    new_connection.ip = std::string(buffer);
    new_connection.port =  ntohs(this->socket_address.sin_port);
    new_connection.socket_descriptor = this->socket_descriptor;
    new_connection.socket_info = this->socket_address;
    

    connection = new_connection;

    return 0;
}

int techlib::sockets::socket_t::socket_accept(techlib::sockets::socket_connection_t& connection){

    struct sockaddr_in client_info;
    socket_connection_t new_connection;

    int client_socket_descriptor = accept(this->socket_descriptor,(struct sockaddr*)&client_info,&(this->socket_length));
    
    
    if(client_socket_descriptor == -1)
        return -1;
    

    new_connection.family = client_info.sin_family;
    new_connection.socket_descriptor = client_socket_descriptor;

    char buffer[1024];
    strcpy(buffer,inet_ntoa(client_info.sin_addr));
    new_connection.ip = std::string(buffer);
    new_connection.port = ntohs(client_info.sin_port);
    
    connection = new_connection;

    return 0;
}


// "socket_connection_t" Functions
ssize_t techlib::sockets::socket_connection_t::con_receive(void* buffer, size_t buffer_size, int flags){

    ssize_t read_bytes = recv(this->socket_descriptor,buffer,buffer_size,flags);
    return read_bytes;
}

ssize_t techlib::sockets::socket_connection_t::con_send(void* buffer, size_t buffer_size, int flags){
    
    ssize_t send_bytes = send(this->socket_descriptor,buffer,buffer_size,flags);
    return send_bytes;
}
