#ifndef CLIOPTIONS_H
#define CLIOPTIONS_H

#include <string>
using namespace std;

class CLIOptions
{
    public:
        CLIOptions(string config_path, string log_level, string mode = "server");
        virtual ~CLIOptions();
        string GetConfigPath();
        string GetLogLevel();
        string GetMode();

        static CLIOptions* GetOptions(int argc, char* args[]);

    protected:

    private:
        string config_path;
        string log_level;
        string mode;
};

#endif // CLIOPTIONS_H
