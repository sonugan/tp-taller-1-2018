#ifndef CONFIGURATIONPARSER_H
#define CONFIGURATIONPARSER_H

#include <string>
#include "configuration.h"

using namespace std;


class ConfigurationParser
{
    public:
        ConfigurationParser();
        virtual ~ConfigurationParser();

        Configuration* ReadFile(string file_path);

    protected:

    private:
        const string DEFAULT_CONFIG_FILE = "src/configuration/default-config.yml";
        Configuration* ReadDefaultConfig();
};

#endif // CONFIGURATIONPARSER_H
