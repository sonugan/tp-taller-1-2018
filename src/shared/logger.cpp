#include "logger.h"
#include <fstream>
#include <time.h>
#include <iostream>

Logger* Logger::instance = NULL;

Logger::Logger() {
	this->level = LogLevel::DEBUG; //Por defecto se pone en debug
	this->SetFileName();
}

Logger::~Logger() {
}

void Logger::setLogLevel(LogLevel level) {
	this->level = level;
}

Logger* Logger::getInstance() {
	if (instance == NULL) {
		instance = new Logger();
	}

	return instance;
}

void Logger::error(string msg) {
    this->log(LogLevel::ERROR, msg);
}

void Logger::debug(string msg) {
    log(LogLevel::DEBUG, msg);
}

void Logger::info(string msg) {
    log(LogLevel::INFO, msg);
}

void Logger::log(LogLevel level, string msg) {

	if (this->logFileName == "")
    {
        this->SetFileName();
    }

	if (this->logFileName == "" || !this->checkPermissionsByMode(level)) {
		return;
	}

	string tag_log_level = "";
	switch (level) {
		case LogLevel::DEBUG: tag_log_level = "DEBUG"; break;
		case LogLevel::INFO: tag_log_level = "INFO"; break;
		case LogLevel::ERROR: tag_log_level = "ERROR"; break;
	}

	ofstream logFile;
	string log_entry = this->dateAndTime() + " [" + tag_log_level + "] - " + msg;

	// agrego un lock para evitar problemas con cout y multiples hilos.
	unique_lock<mutex> logger_lock(this->logger_mutex);

	logFile.open(this->logFileName, ofstream::app);
	logFile <<	log_entry << endl;
	logFile.close();
	if (this->is_cout_enabled)
	{
	    cout << log_entry << endl;
	}
}

bool Logger::checkPermissionsByMode(LogLevel level) {
	return (this->level >= level);
}

string Logger::dateAndTime() {
	time_t t = time(NULL);
    char dateTime[20];

    strftime(dateTime, 20, "%Y-%m-%d-%T", localtime(&t));

    return dateTime;
}

bool Logger::CreateDirectory(std::string relative_path)
{
	struct stat st;
	if(stat(relative_path.c_str(), &st) == 0)
	{
		return true;
	}
	const int error = mkdir(relative_path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	if(error == -1)
	{
		return false;
	}
	return true;
}

void Logger::SetFileName()
{
	StringBuilder string_builder;

	if(this->CreateDirectory(Logger::LOGFILES_DIRECTORY))
	{
		string_builder.Append(Logger::LOGFILES_DIRECTORY);
		string_builder.Append("/");
	}

	string_builder.Append(this->dateAndTime() + ".txt"); //Cada log se guarda con el nombre de la fecha y hora en la cual se creo la instancia);
	this->logFileName = string_builder.Build();
}
