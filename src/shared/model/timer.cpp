#include "timer.h"

Timer::Timer()
{
    this->start_time = time(NULL);
}

Timer::~Timer()
{
    //dtor
}

std::string Timer::GetElapsedMinutes()
{
    time_t t = time(NULL) - this->start_time;
    tm* timePtr = localtime(&t);

    std::string elapsed_time = std::to_string(timePtr->tm_min);
    elapsed_time += ":";

    if (timePtr->tm_sec < 10)
    {
        elapsed_time += "0";
    }

    elapsed_time += std::to_string(timePtr->tm_sec);

    return elapsed_time;
}

void Timer::Restart()
{
    this->start_time = time(NULL);
}
