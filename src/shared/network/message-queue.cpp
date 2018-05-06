#include "message-queue.h"

MessageQueue::MessageQueue()
{
    this->has_max_length = false;
    this->max_length = 0;
}

MessageQueue::MessageQueue(unsigned max_length)
{
    this->has_max_length = true;
    this->max_length = max_length;
}

MessageQueue::~MessageQueue()
{
    for(unsigned i = 0; i < this->messages.size(); i++)
    {
        delete this->messages[i];
    }
}

void MessageQueue::Append(Message* m)
{
    if(!this->has_max_length || this->max_length < this->messages.size())
    {
        this->messages.push_back(m);
    }
}

Message* MessageQueue::Next()
{
    if(this->HasNext())
    {
        Message* first_message = this->messages.front();
        this->messages.pop_back();
        return first_message;
    }
    return NULL;
}

bool MessageQueue::HasNext()
{
    return this->messages.size() > 0;
}
