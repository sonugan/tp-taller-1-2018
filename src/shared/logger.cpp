#include "logger.h"
#include <fstream>
#include <time.h>

Logger* Logger::instance = NULL;

Logger::Logger() {
	this->mode = LogMode::DEBUG; //Por defecto se pone en debug
	this->SetFileName();
}

Logger::~Logger() {
}

void Logger::setMode(LogMode mode) {
	this->mode = mode;
}

Logger *Logger::getInstance() {
	if (instance == NULL) {
		instance = new Logger();
	}

	return instance;
}

void Logger::error(string msg) {
    this->log(LogMode::ERROR, msg);
}

void Logger::debug(string msg) {
    log(LogMode::DEBUG, msg);
}

void Logger::info(string msg) {
    log(LogMode::INFO, msg);
}

void Logger::log(LogMode mode, string msg) {
	this->SetFileName();
	if (this->logFileName == "" || !this->checkPermissionsByMode(mode)) {
		return;
	}

	string tagMode = "";
	switch (mode) {
		case LogMode::DEBUG: tagMode = "DEBUG"; break;
		case LogMode::INFO: tagMode = "INFO"; break;
		case LogMode::ERROR: tagMode = "ERROR"; break;
	}

	ofstream logFile;
	logFile.open(this->logFileName, ofstream::app);
	logFile <<	this->dateAndTime() << "[" << tagMode << "]" << " - " << msg << endl;
	logFile.close();
}

bool Logger::checkPermissionsByMode(LogMode mode) {
	return (this->mode >= mode);
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
