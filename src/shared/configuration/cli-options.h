#ifndef CLIOPTIONS_H
#define CLIOPTIONS_H

#include <string>
using namespace std;

class CLIOptions
{
    public:
        CLIOptions(string config_path, string log_level);
        virtual ~CLIOptions();
        string GetConfigPath();
        string GetLogLevel();

        static CLIOptions* GetOptions(int argc, char* args[]);

    protected:

    private:
        string config_path;
        string log_level;
};

#endif // CLIOPTIONS_H
