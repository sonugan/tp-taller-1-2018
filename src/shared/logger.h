#pragma once
#include <string>
#include <sys/stat.h>
#include "utils/string-builder.h"
#include <mutex>

using namespace std;

enum LogLevel { ERROR = 1, INFO = 2, DEBUG = 3 };

class Logger {

public:
	static Logger* getInstance();
	void setLogLevel(LogLevel level);
	void error(string msg);
	void debug(string msg);
	void info(string msg);
private:
    LogLevel level;
	static Logger* instance;
	string logFileName;
	bool is_cout_enabled = true;
	mutex logger_mutex;

	Logger();
	~Logger();
	void log(LogLevel level, string msg);
	bool checkPermissionsByMode(LogLevel level);
	string dateAndTime();
	bool CreateDirectory(std::string relative_path);
	void SetFileName();
	static constexpr const char* LOGFILES_DIRECTORY = "log";
};
