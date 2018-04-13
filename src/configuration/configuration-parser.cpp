#include "configuration-parser.h"
#include "yaml-cpp/yaml.h"
#include <iostream>
#include "logger.h"

const string LOGGER_NODE = "logger";
const string LOGGER_LEVEL_NODE = "level";
const string TEAM_NODE = "team";
const string TEAM_FORMATION_NODE = "formation";
const string TEAM_NAME_NODE = "name";
const string TEAM_SHIRT_NODE = "shirt";
const string SPRITES_PATH = "sprites_path";
const string DEFAULT_LOG_MODE = "debug";
const string DEFAULT_FORMATION = "3-3";
const string DEFAULT_SHIRT = "main";
const string DEFAULT_SPRITES_PATH = "src/sprites";

/** Helper functions **/
Configuration* parseConfigFile(YAML::Node config_file)
{
    Configuration* configuration = new Configuration();

    if(config_file[LOGGER_NODE]) {
        YAML::Node logger_node = config_file[LOGGER_NODE];
        if(logger_node[LOGGER_LEVEL_NODE]) {
            configuration->SetLogLevel(logger_node[LOGGER_LEVEL_NODE].as<string>());
        }
        else {
            Logger::getInstance()->error("No se encontro la key '" + LOGGER_LEVEL_NODE + "' en el nodo '" + LOGGER_NODE + "'. Se procede a tomar el valor por defecto: '" + DEFAULT_LOG_MODE + "'.");
            configuration->SetLogLevel(DEFAULT_LOG_MODE);
        }
    }
    else {
        Logger::getInstance()->error("No se encontro el nodo '" + LOGGER_NODE + "' en la configuracion. Se procede a tomar el valor por defecto para su nivel: '" + DEFAULT_LOG_MODE + "'.");
        configuration->SetLogLevel(DEFAULT_LOG_MODE);
    }

    if(config_file[TEAM_NODE]) {
        YAML::Node team_node = config_file[TEAM_NODE];
        if(team_node[TEAM_FORMATION_NODE]) {
            configuration->SetFormation(team_node[TEAM_FORMATION_NODE].as<string>());
        } else {
            Logger::getInstance()->error("No se encontro la key '" + TEAM_FORMATION_NODE + "' en el nodo '" + TEAM_NODE + "'. Se procede a tomar el valor por defecto: '" + DEFAULT_FORMATION + "'.");
            configuration->SetFormation(DEFAULT_FORMATION);
        }


        if(team_node[TEAM_SHIRT_NODE]) {
            configuration->SetShirt(team_node[TEAM_SHIRT_NODE].as<string>());
        } else {
            Logger::getInstance()->error("No se encontro la key '" + TEAM_SHIRT_NODE + "' en el nodo '" + TEAM_NODE + "'. Se procede a tomar el valor por defecto: '" + DEFAULT_SHIRT + "'.");
            configuration->SetShirt(DEFAULT_SHIRT);
        }

        if(team_node[TEAM_NAME_NODE]) {
            configuration->SetTeamName(team_node[TEAM_NAME_NODE].as<string>());
        }

    } else {
        Logger::getInstance()->error("No se encontro el nodo '" + TEAM_NODE + "' en la configuracion. Se procede a tomar los valores por defecto para formacion y remera: '" + DEFAULT_FORMATION + "' y '" + DEFAULT_SHIRT + "'.");
        configuration->SetFormation(DEFAULT_FORMATION);
        configuration->SetShirt(DEFAULT_SHIRT);
    }

    if(config_file[SPRITES_PATH]){
        configuration->SetSpritesPath(config_file[SPRITES_PATH].as<string>());
    } else {
        Logger::getInstance()->error("No se encontro la key '" + SPRITES_PATH + "' en la configuracion. Se procede a tomar el valor por defecto: '" + DEFAULT_SPRITES_PATH + "'.");
        configuration->SetSpritesPath(DEFAULT_SPRITES_PATH);
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
        Logger::getInstance()->error("No se encontro el archivo '" + file_path + "'. Se procede a cargar el archivo por defecto: '" + DEFAULT_CONFIG_FILE + "'.");
        return this->ReadDefaultConfig();
    }
}

Configuration* ConfigurationParser::ReadDefaultConfig() {
    YAML::Node config_file = YAML::LoadFile(DEFAULT_CONFIG_FILE);
    return parseConfigFile(config_file);
}
