#include "timer.h"

Timer::Timer(std::string finish_time_mm_ss)
{
    // finish_time_mm_ss debe estar en formato MM:SS
    this->initial_config_finish_time = finish_time_mm_ss;
    this->is_ticking = false;
}

Timer::~Timer()
{
    //dtor
}

void Timer::Start() {
	this->is_ticking = true;
	if(IsFinishTimeUnset()) {
		this->finish_time = this->AddTimeToNow(this->initial_config_finish_time);
	}
}

void Timer::Stop() {
	this->is_ticking = false;
	this->last_stop_time = time(NULL);
}

std::string Timer::GetRemainingMinutes()
{
    std::string remaining_minutes = "";

    time_t now = GetProperTime();

    if (difftime(this->finish_time, now) <= 0)
    {
        // Si se paso del tiempo del timer, queda en 0
        remaining_minutes += ZERO_MINUTES;
    }
    else
    {
        time_t t = this->finish_time - now;
        tm* timePtr = localtime(&t);

        remaining_minutes += std::to_string(timePtr->tm_min);
        remaining_minutes += ":";

        if (timePtr->tm_sec < 10)
        {
            // Le agrego un 0 adelante, pq si los segundos eran menos de 10
            // se mostraba un solo numero (Ej: 10:4 en vez de 10:04) y quedaba mal
            remaining_minutes += "0";
        }

        remaining_minutes += std::to_string(timePtr->tm_sec);
    }


    return remaining_minutes;
}

void Timer::SetFinishTime(std::string finish_time_mm_ss)
{
    // finish_time_mm_ss debe estar en formato MM:SS
    this->initial_config_finish_time = finish_time_mm_ss;
}

std::string Timer::GetFinishTime()
{
    return this->initial_config_finish_time;
}


void Timer::Restart()
{
    this->finish_time = this->AddTimeToNow(this->initial_config_finish_time);
}

time_t Timer::AddTimeToNow(std::string finish_time_mm_ss)
{
    std::vector<std::string> data = StringUtils::Split(finish_time_mm_ss, ':');
    time_t now = time(NULL);
    tm* timePtr = localtime(&now);

    struct tm response;

    response.tm_year = timePtr->tm_year;
    response.tm_mon = timePtr->tm_mon;
    response.tm_mday = timePtr->tm_mday;
    response.tm_hour = timePtr->tm_hour;
    response.tm_min = timePtr->tm_min + stoi(data[0]);
    response.tm_sec = timePtr->tm_sec + stoi(data[1]);

    return mktime(&response);
}

std::string Timer::ToString()
{
    tm* timePtr = localtime(&this->finish_time);

    // HORA
    std::string response = std::to_string(timePtr->tm_hour);

    // MINUTOS
    response += ":";
    response += std::to_string(timePtr->tm_min);

    // SEGUNDOS
    response += ":";
    if (timePtr->tm_sec < 10)
    {
        response += "0";
    }
    response += std::to_string(timePtr->tm_sec);

    return response;
}

bool Timer::IsTimeUp() {
	return ZERO_MINUTES == GetRemainingMinutes();
}

time_t Timer::GetProperTime() {
	return is_ticking ? time(NULL) : last_stop_time;
}

bool Timer::IsFinishTimeUnset() {
	return this->finish_time < 0;
}
