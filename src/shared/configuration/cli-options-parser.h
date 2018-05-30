#ifndef CLIOPTIONSPARSER_H
#define CLIOPTIONSPARSER_H

#include <string>
using namespace std;

class CLIOptionsParser
{
    public:
        CLIOptionsParser();
        virtual ~CLIOptionsParser();

        string GetConfigPath(int argc, char* args[]);
        string GetLogLevel(int argc, char* args[]);
        string GetMode(int argc, char* args[]);
        string GetIp(int argc, char* args[]);
        string GetPort(int argc, char* args[]);

    protected:

    private:
        const string CONFIG_OPTION_PATTERN = "^--config=(.+)$";
        const string LOG_LEVEL_OPTION_PATTERN = "^--loglevel=(.+)$";
        const string MODE_OPTION_PATTERN = "^--mode=(.+)$";
        const string IP_OPTION_PATTERN = "^--ip=(.+)$";
        const string PORT_OPTION_PATTERN = "^--port=(.+)$";
};

#endif // CLIOPTIONSPARSER_H
