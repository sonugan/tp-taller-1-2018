#ifndef QUEUE_H
#define QUEUE_H

#include <deque>

using namespace std;

template <class T>
class Queue
{
    public:
        Queue<T>();
        Queue<T>(unsigned max_length);
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

template <class T>
Queue<T>::Queue()
{
    this->has_max_length = false;
    this->max_length = 0;
}

template <class T>
Queue<T>::Queue(unsigned max_length)
{
    this->has_max_length = true;
    this->max_length = max_length;
}

template <class T>
Queue<T>::~Queue()
{
    for(unsigned i = 0; i < this->items.size(); i++)
    {
        delete this->items[i];
    }
}

template <class T>
void Queue<T>::Append(T* m)
{
    if(!this->has_max_length || this->max_length < this->items.size())
    {
        this->items.push_back(m);
    }
}

template <class T>
T* Queue<T>::Next()
{
    if(this->HasNext())
    {
        T* first = this->items.front();
        this->items.pop_back();
        return first;
    }
    return nullptr;
}

template <class T>
bool Queue<T>::HasNext()
{
    return this->items.size() > 0;
}

#endif // QUEUE_H
