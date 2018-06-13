#ifndef TIMER_H
#define TIMER_H

#include <ctime>
#include <iostream>
#include <string>
#include "../logger.h"
#include "../utils/string-utils.h"

class Timer
{
    public:
        Timer(std::string finish_time_mm_ss);
        virtual ~Timer();
        std::string GetRemainingMinutes();
        void Restart();
        void SetFinishTime(std::string finish_time_mm_ss);
        std::string GetFinishTime();

    protected:
        std::string ToString();
        time_t AddTimeToNow(std::string finish_time_mm_ss);
    private:
        time_t finish_time;
        std::string initial_config_finish_time;
};

#endif // TIMER_H
