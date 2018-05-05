#include "socket-address.h"

SocketAddress::SocketAddress(u_int port, short family, u_long addr)
{
    // clear address structure
    memset((char *) &(this->address), 0, sizeof(this->address));//TODO: ver si funciona con esto
    this->address.sin_family = family;
    this->address.sin_addr.s_addr = addr;
    this->address.sin_port = htons(port);
}

SocketAddress::SocketAddress(u_int port, char* hostname, short family)
{
    memset((char *) &(this->address), 0, sizeof(this->address));//TODO: ver si funciona con esto
    this->address.sin_family = family;
    this->address.sin_port = htons(port);
    struct hostent *host = gethostbyname(hostname);
    bcopy((char *)host->h_addr,
         (char *)&this->address.sin_addr.s_addr,
         host->h_length);
}

SocketAddress::SocketAddress(sockaddr_in addr)
{
    this->address = addr;
}

SocketAddress::SocketAddress()
{
    
}

sockaddr_in SocketAddress::GetFormatted()
{
    return this->address;
}
