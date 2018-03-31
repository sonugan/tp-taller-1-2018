#ifndef CONFIGURATIONPARSER_H
#define CONFIGURATIONPARSER_H

#include "yaml-cpp/yaml.h"
#include <string>

using namespace std;

class ConfigurationParser
{
    public:
        ConfigurationParser();
        virtual ~ConfigurationParser();

        void ReadFile(string file_path);

    protected:

    private:
        const string DEFAULT_CONFIG_FILE = "src/configuration/default-config.yml";
        void ReadDefaultConfig();
};

#endif // CONFIGURATIONPARSER_H
