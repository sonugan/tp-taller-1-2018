#ifndef CLIOPTIONS_H
#define CLIOPTIONS_H

#include <string>
using namespace std;

class CLIOptions
{
    public:
        CLIOptions(string config_path, string log_level, string ip, string port, string mode = "server");
        virtual ~CLIOptions();
        string GetConfigPath();
        string GetLogLevel();
        string GetMode();
        string GetIp();
        string GetPort();

        static CLIOptions* GetOptions(int argc, char* args[]);

    protected:

    private:
        string config_path;
        string log_level;
        string mode;
        string ip;
        string port;
};

#endif // CLIOPTIONS_H
