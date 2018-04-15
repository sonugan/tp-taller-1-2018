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

        void ReadFile(Configuration* configuration, string file_path);

    protected:

    private:
        const string DEFAULT_CONFIG_FILE = "src/configuration/default-config.yml";
        void ReadDefaultConfig(Configuration* configuration);
};

#endif // CONFIGURATIONPARSER_H
