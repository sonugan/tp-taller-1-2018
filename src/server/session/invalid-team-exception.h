#ifndef INVALIDTEAMEXCEPTION_H_INCLUDED
#define INVALIDTEAMEXCEPTION_H_INCLUDED

#include <string>
#include <stdexcept>

class InvalidTeamException: public std::runtime_error
{
    public:
        explicit InvalidTeamException(const std::string& error_message):
            std::runtime_error(error_message) {}
        virtual ~InvalidTeamException() {}
};


#endif
