#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H

#include <deque>

#include "message.h"

using namespace std;

class MessageQueue
{
    public:
        MessageQueue();
        MessageQueue(unsigned max_length);
        virtual ~MessageQueue();
        void Append(Message* m);
        Message* Next();
        bool HasNext();
    protected:
    private:
        bool has_max_length;
        unsigned max_length;
        deque<Message*> messages;
};

#endif // MESSAGEQUEUE_H
