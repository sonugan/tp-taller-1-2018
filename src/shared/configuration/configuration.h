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

    LogLevel GetLogLevel();

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

    static void Load(Configuration* config, string config_path, string log_level, string mode);

    bool IsValidConfigValue(string parameter, string value);

    bool InitModeIsServer();

    bool InitModeIsClient();

    map<string, string> GetCredentials();

    void AddValidCredential(string username, string password);

    bool IsValidCredential(string username, string password);

    u_int GetPort();

    void SetPort(u_int port);

    u_int GetMaxPlayers();

    void SetMaxPlayers(u_int max_players);

    void SetServerHostname(string hostname);

    string GetServerHostname();

protected:

private:
    LogLevel log_level;
    string formation;
    string shirt;
    string sprites_path;
    string team_name;
    string init_mode;
    TEAM_NUMBER team_number = TEAM_NUMBER::TEAM_A; // esto dsp lo tiene que tomar del archivo de config
    u_int port;
    u_int max_players;
    string server_hostname;

    // Para almacenar las credenciales validas => <user,password>
    map<string, string> valid_credentials = {};

    map<string, vector<string>> valid_configurations =
    {
        {"level", { "info", "debug", "error" }},
        {"formation", { "3-3", "3-1-2", "3-2-1" }},
        {"shirt", { "home", "away" }},
        {"init_mode", { "client", "server" }},
    };
    const map<string, LogLevel> LOG_LEVEL_MAP =
    {
        {"error", LogLevel::ERROR},
        {"info", LogLevel::INFO},
        {"debug", LogLevel::DEBUG}
    };
    LogLevel ToLogLevel(string log_level_str);

};



#endif // CONFIGURATION_H
