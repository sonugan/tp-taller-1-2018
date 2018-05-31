#include "cli-options-parser.h"

#include <iostream>
#include <string>
#include <regex>

CLIOptionsParser::CLIOptionsParser()
{
    //ctor
}

CLIOptionsParser::~CLIOptionsParser()
{
    //dtor
}

string parse_option(string option_pattern, int argc, char* args[])
{
    regex option_regex(option_pattern);
    if(argc < 2)
    {
        return "";
    }

    for(int i = 1; i < argc; i++)
    {
        string cli_option (args[i]);
        smatch option_match;
        if(regex_match(cli_option, option_match, option_regex))
        {
            ssub_match option_sub_match = option_match[1];
            string option = option_sub_match.str();
            return option;

        }
    }
    return "";
}

string CLIOptionsParser::GetConfigPath(int argc, char* args[])
{
    return parse_option(CONFIG_OPTION_PATTERN, argc, args);
}

string CLIOptionsParser::GetLogLevel(int argc, char* args[])
{
    return parse_option(LOG_LEVEL_OPTION_PATTERN, argc, args);
}

string CLIOptionsParser::GetMode(int argc, char* args[])
{
    return parse_option(MODE_OPTION_PATTERN, argc, args);
}

string CLIOptionsParser::GetIp(int argc, char* args[])
{
    return parse_option(IP_OPTION_PATTERN, argc, args);
}

string CLIOptionsParser::GetPort(int argc, char* args[])
{
    return parse_option(PORT_OPTION_PATTERN, argc, args);
}
