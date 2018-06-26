/*
 * timer2.h
 *
 *  Created on: Jun 23, 2018
 *      Author: swandelow
 */

#ifndef SRC_SHARED_MODEL_TIMER_H_
#define SRC_SHARED_MODEL_TIMER_H_

#include <chrono>
#include <iostream>

using namespace std;

class Timer
{
public:
	Timer(string game_duration);
	virtual ~Timer();
    string GetRemainingTime();
    void Restart();
    bool IsTimeUp();
    void Start();
    void Stop();
private:
    int game_duration_sec;
    string game_duration;
	bool is_ticking;
	int acum;
	chrono::time_point<chrono::system_clock> time_stamp;

	string TimeToString(int seconds);
	int StringToSeconds(string time);
	int GetPlayedSeconds();
};

#endif /* SRC_SHARED_MODEL_TIMER_H_ */
