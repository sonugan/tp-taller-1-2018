#ifndef ID_GENERATOR_H
#define ID_GENERATOR_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class IdGenerator
{
    public:
        IdGenerator();
        virtual ~IdGenerator();
        string GetNext();
        bool Equals(string id1, string id2);
    protected:
    private:
        u_int current_letter_index = 0;
        u_int current_number = 0;
        vector<string> letters = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L",
            "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
        static const u_int MAX_NUMBER = 999;
};

#endif // ID_GENERATOR_H
