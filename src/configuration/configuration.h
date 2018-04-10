#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>
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

        static Configuration* Load(string config_path, string log_level);

    protected:

    private:
        string log_level;
        string formation;
        string shirt;
        string sprites_path;
        string team_name;
};



#endif // CONFIGURATION_H
