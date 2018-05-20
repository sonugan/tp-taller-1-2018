#ifndef AUTHENTICATIONEXCEPTION_H
#define AUTHENTICATIONEXCEPTION_H

#include <string>
#include <stdexcept>

class AuthenticationException: public std::runtime_error
{
    public:
        explicit AuthenticationException(const std::string& error_message):
            std::runtime_error(error_message) {}
        virtual ~AuthenticationException() {}
};


#endif // AUTHENTICATIONEXCEPTION_H
