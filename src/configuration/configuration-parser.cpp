#include "configuration-parser.h"
#include "yaml-cpp/yaml.h"
#include <iostream>

/** Helper functions **/
Configuration parseConfigFile(YAML::Node config_file)
{
    Configuration configuration = Configuration();

    if(config_file["logger"]) {
        YAML::Node logger_node = config_file["logger"];
        if(logger_node["level"]) {
            configuration.SetLogLevel(logger_node["level"].as<string>());
        }
    }

    if(config_file["team"]) {
        YAML::Node team_node = config_file["team"];
        if(team_node["formation"]) {
            configuration.SetFormation(team_node["formation"].as<string>());
        }
        if(team_node["shirt"]) {
            configuration.SetShirt(team_node["shirt"].as<string>());
        }
    }

    return configuration;
}

/** Configuration class implementation **/

ConfigurationParser::ConfigurationParser()
{
    //ctor
}

ConfigurationParser::~ConfigurationParser()
{
    //dtor
}

Configuration ConfigurationParser::ReadFile(string file_path) {
    try {
        YAML::Node config_file = YAML::LoadFile(file_path);
        return parseConfigFile(config_file);
    } catch (YAML::BadFile e) {
        std::cout << "No se pudo leer archivo de configuración. Usando configuración default" << "\n";
        return this->ReadDefaultConfig();
    }
}

Configuration ConfigurationParser::ReadDefaultConfig() {
    YAML::Node config_file = YAML::LoadFile(DEFAULT_CONFIG_FILE);
    return parseConfigFile(config_file);
}

