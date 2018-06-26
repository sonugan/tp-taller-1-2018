/*
 * timer2.cpp
 *
 *  Created on: Jun 23, 2018
 *      Author: swandelow
 */

#include "timer.h"

#include <vector>
#include "../logger.h"
#include "../utils/string-utils.h"


Timer::Timer(string game_duration)
{
	this->acum = 0;
	this->game_duration = game_duration;
	this->game_duration_sec = StringToSeconds(game_duration);
}

Timer::~Timer()
{
	// TODO Auto-generated destructor stub
}

string Timer::GetRemainingTime() {
	int remaining_sec = this->game_duration_sec - GetPlayedSeconds();
	return remaining_sec <= 0 ? "00:00" : TimeToString(remaining_sec);
}

void Timer::Restart() {
	Logger::getInstance()->debug("(Timer:Restart)");
	this->acum = 0;
	this->is_ticking = false;
}

bool Timer::IsTimeUp() {
	return GetPlayedSeconds() > this->game_duration_sec;
}

void Timer::Start() {
	Logger::getInstance()->debug("(Timer:Start)");
	if(!is_ticking) {
		this->is_ticking = true;
		this->time_stamp = chrono::system_clock::now();
	}
}

void Timer::Stop() {
	Logger::getInstance()->debug("(Timer:Stop)");
	if(is_ticking) {
		this->is_ticking = false;
		int elapsed_seconds = chrono::duration_cast<chrono::seconds>(chrono::system_clock::now() - this->time_stamp).count();
		this->acum += elapsed_seconds;
	}
}

string Timer::TimeToString(int seconds) {
	string time_str = "";
	int min, sec;
	min = seconds / 60;
	sec = seconds % 60;
	time_str += min < 10 ? ("0" + to_string(min)) : to_string(min);
	time_str += ":";
	time_str += sec < 10 ? ("0" + to_string(sec)) : to_string(sec);
	return time_str;
}

 int Timer::StringToSeconds(string time) {
	int seconds = 0;
	vector<std::string> data = StringUtils::Split(time, ':');
	seconds += stoi(data[0]) * 60;
	seconds += stoi(data[1]);
	return seconds;
}

 int Timer::GetPlayedSeconds() {
	 int elapsed_seconds = chrono::duration_cast<chrono::seconds>(chrono::system_clock::now() - this->time_stamp).count();
	return is_ticking ? this->acum + elapsed_seconds : this->acum;
}
