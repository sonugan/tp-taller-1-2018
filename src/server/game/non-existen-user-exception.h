#ifndef NONEXISTENTUSEREXCEPTION_H
#define NONEXISTENTUSEREXCEPTION_H

#include <string>
#include <stdexcept>

class NonExistentUserException: public std::runtime_error
{
    public:
        explicit NonExistentUserException(const std::string& error_message):
            std::runtime_error(error_message) {}
        virtual ~NonExistentUserException() {}
};


#endif // NONEXISTENTUSEREXCEPTION_H
