#include "cli-options.h"
#include "cli-options-parser.h"

CLIOptions::CLIOptions(string config_path, string log_level, string mode)
{
    this->config_path = config_path;
    this->log_level = log_level;
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

CLIOptions* CLIOptions::GetOptions(int argc, char* args[])
{
    CLIOptionsParser* parser = new CLIOptionsParser();
    string config_path = parser->GetConfigPath(argc, args);
    string log_level = parser->GetLogLevel(argc, args);
    string mode = parser->GetMode(argc, args);
    return new CLIOptions(config_path, log_level, mode);
}

