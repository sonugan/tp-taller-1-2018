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

    protected:

    private:
        string log_level;
        string formation;
        string shirt;
};



#endif // CONFIGURATION_H
