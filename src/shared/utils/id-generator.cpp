#include "id-generator.h"

IdGenerator::IdGenerator()
{

}

IdGenerator::~IdGenerator()
{

}

string IdGenerator::GetNext()
{
    string new_id = letters[current_letter_index] + to_string(current_number);

    current_letter_index++;
    if(current_letter_index >= letters.size())
    {
        current_letter_index = 0;
    }

    current_number++;
    if(current_number >= MAX_NUMBER)
    {
        current_number = 0;
    }
    return new_id;
}

bool IdGenerator::Equals(string id1, string id2)
{
    return id1 == id2;
}
