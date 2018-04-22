#pragma once
#include <string>
#include <sys/stat.h>
#include "string-builder.h"

using namespace std;

enum LogMode { ERROR = 1, INFO = 2, DEBUG = 3 };

class Logger {

public:
	static Logger* getInstance();
	void setMode(LogMode modo);
	void error(string msg);
	void debug(string msg);
	void info(string msg);
private:
    LogMode mode;
	static Logger* instance;
	string logFileName;

	Logger();
	~Logger();
	void log(LogMode modo, string msg);
	bool checkPermissionsByMode(LogMode modo);
	string dateAndTime();
	bool CreateDirectory(std::string relative_path);
	void SetFileName();
	static constexpr const char* LOGFILES_DIRECTORY = "log";
};
