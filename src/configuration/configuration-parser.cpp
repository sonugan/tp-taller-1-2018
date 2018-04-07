#include "configuration-parser.h"
#include "yaml-cpp/yaml.h"
#include <iostream>

const string LOGGER_NODE = "logger";
const string LOGGER_LEVEL_NODE = "level";
const string TEAM_NODE = "team";
const string TEAM_FORMATION_NODE = "formation";
const string TEAM_SHIRT_NODE = "shirt";
const string SPRITES_PATH = "sprites_path";

/** Helper functions **/
Configuration* parseConfigFile(YAML::Node config_file)
{
    Configuration* configuration = new Configuration();

    if(config_file[LOGGER_NODE]) {
        YAML::Node logger_node = config_file[LOGGER_NODE];
        if(logger_node[LOGGER_LEVEL_NODE]) {
            configuration->SetLogLevel(logger_node[LOGGER_LEVEL_NODE].as<string>());
        }
    }

    if(config_file[TEAM_NODE]) {
        YAML::Node team_node = config_file[TEAM_NODE];
        if(team_node[TEAM_FORMATION_NODE]) {
            configuration->SetFormation(team_node[TEAM_FORMATION_NODE].as<string>());
        }
        if(team_node[TEAM_SHIRT_NODE]) {
            configuration->SetShirt(team_node[TEAM_SHIRT_NODE].as<string>());
        }
    }

    if(config_file[SPRITES_PATH]){
        configuration->SetSpritesPath(config_file[SPRITES_PATH].as<string>());
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

Configuration* ConfigurationParser::ReadFile(string file_path) {
    try {
        YAML::Node config_file = YAML::LoadFile(file_path);
        return parseConfigFile(config_file);
    } catch (YAML::BadFile e) {
        std::cout << "No se pudo leer archivo de configuración. Usando configuración default" << "\n";
        return this->ReadDefaultConfig();
    }
}

Configuration* ConfigurationParser::ReadDefaultConfig() {
    YAML::Node config_file = YAML::LoadFile(DEFAULT_CONFIG_FILE);
    return parseConfigFile(config_file);
}

