#ifndef TIMER_H
#define TIMER_H

#include <ctime>
#include <iostream>

class Timer
{
    public:
        Timer();
        virtual ~Timer();
        std::string GetElapsedMinutes();
        void Restart();
    protected:
    private:
        std::tm* clock;
        time_t start_time;

};

#endif // TIMER_H
