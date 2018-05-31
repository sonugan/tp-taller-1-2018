#ifndef MAXALLOWEDUSEREXCEPTION_H
#define MAXALLOWEDUSEREXCEPTION_H

#include <string>
#include <stdexcept>

class MaxAllowedUsersException: public std::runtime_error
{
    public:
        explicit MaxAllowedUsersException(const std::string& error_message):
            std::runtime_error(error_message) {}
        virtual ~MaxAllowedUsersException() {}
};


#endif // MAXALLOWEDUSEREXCEPTION_H
