#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H

#include <deque>

using namespace std;

template <class T>
class Queue
{
    public:
        Queue();
        Queue(unsigned max_length);
        virtual ~Queue();
        void Append(T* m);
        T* Next();
        bool HasNext();
    protected:
    private:
        bool has_max_length;
        unsigned max_length;
        deque<T*> items;
};

#endif // MESSAGEQUEUE_H
