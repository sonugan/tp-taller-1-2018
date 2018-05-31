#include "cli-options.h"
#include "cli-options-parser.h"

CLIOptions::CLIOptions(string config_path, string log_level, string ip, string port, string mode)
{
    this->config_path = config_path;
    this->log_level = log_level;
    this->ip = ip;
    this->port = port;
    this->mode = mode;
}

CLIOptions::~CLIOptions()
{
    //dtor
}

string CLIOptions::GetConfigPath()
{
    return this->config_path;
}

string CLIOptions::GetLogLevel()
{
    return this->log_level;
}

string CLIOptions::GetMode()
{
    return this->mode;
}

string CLIOptions::GetIp()
{
    return this->ip;
}

string CLIOptions::GetPort()
{
    return this->port;
}

CLIOptions* CLIOptions::GetOptions(int argc, char* args[])
{
    CLIOptionsParser* parser = new CLIOptionsParser();
    string config_path = parser->GetConfigPath(argc, args);
    string log_level = parser->GetLogLevel(argc, args);
    string mode = parser->GetMode(argc, args);
    string ip = parser->GetIp(argc, args);
    string port = parser->GetPort(argc, args);
    return new CLIOptions(config_path, log_level, ip, port, mode);
}

