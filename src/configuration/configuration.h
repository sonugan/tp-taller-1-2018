#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>
#include <map>
#include <vector>
using namespace std;


class Configuration
{
    public:
        Configuration();
        Configuration(string formation, string shirt, string log_level);
        virtual ~Configuration();

        string GetLogLevel();

        void SetLogLevel(string log_level);

        string GetFormation();

        void SetFormation(string formation);

        string GetShirt();

        void SetShirt(string shirt);

        string GetSpritesPath();

        void SetTeamName(string name);

        string GetTeamName();

        void SetSpritesPath(string sprites_path);

        static void Load(Configuration* config, string config_path, string log_level);

        bool IsValidConfigValue(string parameter, string value);

    protected:

    private:
        string log_level;
        string formation;
        string shirt;
        string sprites_path;
        string team_name;
        map<string, vector<string>> valid_configurations = {
            {"level", { "info", "debug", "error" }},
            {"formation", { "3-3", "3-1-2", "3-2-1" }},
            {"shirt", { "home", "away" }}
        };
};



#endif // CONFIGURATION_H
