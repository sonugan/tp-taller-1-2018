#include "logger.h"
#include <fstream>
#include <time.h>

Logger* Logger::instance = NULL;

Logger::Logger() {
	this->mode = LogMode::DEBUG; //Por defecto se pone en debug
	this->logFileName = this->dateAndTime() + ".txt"; //Cada log se guarda con el nombre de la fecha y hora en la cual se creo la instancia
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

    strftime(dateTime, 20, "%Y-%m-%d %T", localtime(&t));

    return dateTime;
}
