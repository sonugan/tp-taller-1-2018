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

    protected:

    private:
        const string CONFIG_OPTION_PATTERN = "^--config=(.+)$";
        const string LOG_LEVEL_OPTION_PATTERN = "^--loglevel=(.+)$";
};

#endif // CLIOPTIONSPARSER_H
