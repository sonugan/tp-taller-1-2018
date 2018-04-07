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

        void SetSpritesPath(string sprites_path);

        static Configuration* Load(string config_path, string log_level);

    protected:

    private:
        string log_level;
        string formation;
        string shirt;
        string sprites_path;
};



#endif // CONFIGURATION_H
