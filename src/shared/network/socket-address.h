#ifndef SOCKETADDRESS_H
#define SOCKETADDRESS_H

#include <unistd.h>
#include <cstring>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

//http://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/socket.html
class SocketAddress
{
    public:
        ///SocketAddress
        //port: However, instead of simply copying the port number to this field, it is necessary to
        //  convert this to network byte order using the function htons() which converts a port number
        //  in host byte order to a port number in network byte order.
        //family: contains a code for the address family. It should always be set to the symbolic
        //  constant AF_INET
        //addr: This field contains the IP address of the host.
        //  For server code, this will always be the IP address of the machine on which the
        //  server is running, and there is a symbolic constant INADDR_ANY which gets this address
        SocketAddress(u_int port, short family = AF_INET, u_long addr = INADDR_ANY);
        SocketAddress(u_int port, const char* hostname, short family = AF_INET);
        SocketAddress(u_int port, std::string server_ip);
        SocketAddress(sockaddr_in addr);
        SocketAddress();
        sockaddr_in GetFormatted();
    protected:
    private:
        sockaddr_in address;
};

#endif // SOCKETADDRESS_H
