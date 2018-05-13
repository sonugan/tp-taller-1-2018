#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>
#include <map>
#include <vector>
#include "../logger.h"

using namespace std;

class Formation;

enum class TEAM_NUMBER {TEAM_A = 1, TEAM_B = 2};

class Configuration
{
public:


    Configuration();

    virtual ~Configuration();

    LogMode GetLogLevel();

    void SetLogLevel(string log_level);

    string GetFormation();

    void SetFormation(string formation);

    string GetShirt();

    void SetShirt(string shirt);

    string GetSpritesPath();

    void SetTeamName(string name);

    string GetTeamName();

    void SetInitMode(string init_mode);

    string GetInitMode();

    void SetTeamNumber(TEAM_NUMBER team_number);

    TEAM_NUMBER GetTeamNumber();

    void SetSpritesPath(string sprites_path);

    static void Load(Configuration* config, string config_path, string log_level);

    bool IsValidConfigValue(string parameter, string value);

    bool InitModeIsServer();

    bool InitModeIsClient();

    void AddValidCredential(string username, string password);

    bool IsValidCredential(string username, string password);

protected:

private:
    LogMode log_level;
    string formation;
    string shirt;
    string sprites_path;
    string team_name;
    string init_mode;
    TEAM_NUMBER team_number = TEAM_NUMBER::TEAM_A; // esto dsp lo tiene que tomar del archivo de config

    // Para almacenar las credenciales validas => <user,password>
    map<string, string> valid_credentials = {};

    map<string, vector<string>> valid_configurations =
    {
        {"level", { "info", "debug", "error" }},
        {"formation", { "3-3", "3-1-2", "3-2-1" }},
        {"shirt", { "home", "away" }},
        {"init_mode", { "server", "client" }},
    };
    const map<string, LogMode> LOG_MODE_MAP =
    {
        {"error", LogMode::ERROR},
        {"info", LogMode::INFO},
        {"debug", LogMode::DEBUG}
    };
    LogMode ToLogMode(string log_level_str);

};



#endif // CONFIGURATION_H
