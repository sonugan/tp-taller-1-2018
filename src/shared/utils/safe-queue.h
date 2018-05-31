#ifndef SAFESafeQueue_H
#define SAFESafeQueue_H

#include <deque>
#include <mutex>
#include <condition_variable>

using namespace std;

template <class T>
class SafeQueue
{
public:
    SafeQueue<T>();
    SafeQueue<T>(unsigned max_length);
    virtual ~SafeQueue();
    void Append(T* m);
    T* Next();
    bool HasNext();
protected:
private:
    bool has_max_length;
    unsigned max_length;
    deque<T*> items;
    std::mutex mutex;
    std::condition_variable cond;

};

template <class T>
SafeQueue<T>::SafeQueue()
{
    this->has_max_length = false;
    this->max_length = 0;
}

template <class T>
SafeQueue<T>::SafeQueue(unsigned max_length)
{
    this->has_max_length = true;
    this->max_length = max_length;
}

template <class T>
SafeQueue<T>::~SafeQueue()
{
    for(unsigned i = 0; i < this->items.size(); i++)
    {
        delete this->items[i];
    }
}

template <class T>
void SafeQueue<T>::Append(T* m)
{
    std::unique_lock<std::mutex> mlock(mutex);
    if(!this->has_max_length || this->max_length < this->items.size())
    {
        this->items.push_back(m);
    }
    mlock.unlock();
    cond.notify_one();
}

template <class T>
T* SafeQueue<T>::Next()
{
    if(this->HasNext())
    {
        std::unique_lock<std::mutex> mlock(mutex);
        while(this->items.empty())
        {
            cond.wait(mlock);
        }
        T* first = this->items.front();
        this->items.pop_back();
        return first;
    }
    return nullptr;
}

template <class T>
bool SafeQueue<T>::HasNext()
{
    std::unique_lock<std::mutex> mlock(mutex);
    return this->items.size() > 0;
}

#endif // SAFESafeQueue_H
