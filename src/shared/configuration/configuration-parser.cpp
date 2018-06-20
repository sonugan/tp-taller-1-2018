#include "configuration-parser.h"
#include "yaml-cpp/yaml.h"
#include <iostream>
#include "../logger.h"

const string LOGGER_NODE = "logger";
const string LOGGER_LEVEL_NODE = "level";
const string TEAM_NODE = "team";
const string TEAM_FORMATION_NODE = "formation";
const string TEAM_NAME_NODE = "name";
const string TEAM_SHIRT_NODE = "shirt";
const string INIT_MODE_NODE = "init_mode";
const string MAX_PLAYERS_NODE = "max_players";
const string SERVER_HOSTNAME = "server_hostname";
const string PORT_NODE = "port";
const string USERS_NODE = "users";
const string GAME_DURATION = "game_duration";
const string SPRITES_PATH = "sprites_path";
const string DEFAULT_LOG_MODE = "debug";
const string DEFAULT_INIT_MODE = "client";
const unsigned int DEFAULT_MAX_PLAYERS = 2;
const unsigned int DEFAULT_PORT_NODE = 51717;
const string DEFAUT_SERVER_HOSTNAME = "localhost";
const string DEFAULT_FORMATION = "3-3";
const string DEFAULT_SHIRT = "home";
const string DEFAULT_SPRITES_PATH = "src/sprites";
const string DEFAULT_GAME_DURATION = "01:00";

/** Helper functions **/
void parseConfigFile(Configuration* configuration, YAML::Node config_file)
{
    if (config_file[INIT_MODE_NODE])
    {
        configuration->SetInitMode(config_file[INIT_MODE_NODE].as<string>());
    }
    else
    {
        Logger::getInstance()->error("No se encontro el parametro '" + INIT_MODE_NODE + "' en la configuracion. Se procede a tomar el valor por defecto: '" + DEFAULT_INIT_MODE + "'.");
        configuration->SetInitMode(DEFAULT_INIT_MODE);
    }

    if (config_file[LOGGER_NODE])
    {
        YAML::Node logger_node = config_file[LOGGER_NODE];
        if (logger_node[LOGGER_LEVEL_NODE])
        {
            configuration->SetLogLevel(logger_node[LOGGER_LEVEL_NODE].as<string>());
        }
        else
        {
            Logger::getInstance()->error("No se encontro el parametro '" + LOGGER_LEVEL_NODE + "' en el nodo '" + LOGGER_NODE + "'. Se procede a tomar el valor por defecto: '" + DEFAULT_LOG_MODE + "'.");
            configuration->SetLogLevel(DEFAULT_LOG_MODE);
        }
    }
    else
    {
        Logger::getInstance()->error("No se encontro el nodo '" + LOGGER_NODE + "' en la configuracion. Se procede a tomar el valor por defecto para su nivel: '" + DEFAULT_LOG_MODE + "'.");
        configuration->SetLogLevel(DEFAULT_LOG_MODE);
    }

    if(configuration->InitModeIsClient())
    {

        if (config_file[TEAM_NODE])
        {
            YAML::Node team_node = config_file[TEAM_NODE];
            if (team_node[TEAM_FORMATION_NODE])
            {
                configuration->SetFormation(team_node[TEAM_FORMATION_NODE].as<string>());
            }
            else
            {
                Logger::getInstance()->error("No se encontro el parametro '" + TEAM_FORMATION_NODE + "' en el nodo '" + TEAM_NODE + "'. Se procede a tomar el valor por defecto: '" + DEFAULT_FORMATION + "'.");
                configuration->SetFormation(DEFAULT_FORMATION);
            }


            if (team_node[TEAM_SHIRT_NODE])
            {
                configuration->SetShirt(team_node[TEAM_SHIRT_NODE].as<string>());
            }
            else
            {
                Logger::getInstance()->error("No se encontro el parametro '" + TEAM_SHIRT_NODE + "' en el nodo '" + TEAM_NODE + "'. Se procede a tomar el valor por defecto: '" + DEFAULT_SHIRT + "'.");
                configuration->SetShirt(DEFAULT_SHIRT);
            }

            if (team_node[TEAM_NAME_NODE])
            {
                configuration->SetTeamName(team_node[TEAM_NAME_NODE].as<string>());
            }

        }
        else
        {
            Logger::getInstance()->error("No se encontro el nodo '" + TEAM_NODE + "' en la configuracion. Se procede a tomar los valores por defecto para formacion y remera: '" + DEFAULT_FORMATION + "' y '" + DEFAULT_SHIRT + "'.");
            configuration->SetFormation(DEFAULT_FORMATION);
            configuration->SetShirt(DEFAULT_SHIRT);
        }

        if (config_file[SPRITES_PATH])
        {
            configuration->SetSpritesPath(config_file[SPRITES_PATH].as<string>());
        }
        else
        {
            Logger::getInstance()->error("No se encontro el parametro '" + SPRITES_PATH + "' en la configuracion. Se procede a tomar el valor por defecto: '" + DEFAULT_SPRITES_PATH + "'.");
            configuration->SetSpritesPath(DEFAULT_SPRITES_PATH);
        }

        if (config_file[SERVER_HOSTNAME])
        {
            configuration->SetServerHostname(config_file[SERVER_HOSTNAME].as<string>());
        }
        else
        {
            Logger::getInstance()->error("No se encontro el parametro '" + SERVER_HOSTNAME + "' en la configuracion. Se procede a tomar el valor por defecto: '" + SERVER_HOSTNAME + "'.");
            configuration->SetServerHostname(DEFAUT_SERVER_HOSTNAME);
        }
    }



    if(configuration->InitModeIsServer())
    {
        if (config_file[TEAM_NODE])
        {
            YAML::Node team_node = config_file[TEAM_NODE];
            if (team_node[TEAM_FORMATION_NODE])
            {
                configuration->SetFormation(team_node[TEAM_FORMATION_NODE].as<string>());
            }
            else
            {
                Logger::getInstance()->error("No se encontro el parametro '" + TEAM_FORMATION_NODE + "' en el nodo '" + TEAM_NODE + "'. Se procede a tomar el valor por defecto: '" + DEFAULT_FORMATION + "'.");
                configuration->SetFormation(DEFAULT_FORMATION);
            }


            if (team_node[TEAM_SHIRT_NODE])
            {
                configuration->SetShirt(team_node[TEAM_SHIRT_NODE].as<string>());
            }
            else
            {
                Logger::getInstance()->error("No se encontro el parametro '" + TEAM_SHIRT_NODE + "' en el nodo '" + TEAM_NODE + "'. Se procede a tomar el valor por defecto: '" + DEFAULT_SHIRT + "'.");
                configuration->SetShirt(DEFAULT_SHIRT);
            }

            if (team_node[TEAM_NAME_NODE])
            {
                configuration->SetTeamName(team_node[TEAM_NAME_NODE].as<string>());
            }

        }
        else
        {
            Logger::getInstance()->error("No se encontro el nodo '" + TEAM_NODE + "' en la configuracion. Se procede a tomar los valores por defecto para formacion y remera: '" + DEFAULT_FORMATION + "' y '" + DEFAULT_SHIRT + "'.");
            configuration->SetFormation(DEFAULT_FORMATION);
            configuration->SetShirt(DEFAULT_SHIRT);
        }

        if(config_file[MAX_PLAYERS_NODE])
        {
            configuration->SetMaxPlayers(config_file[MAX_PLAYERS_NODE].as<int>());//TODO: es necesario validarlo?
        }
        else
        {
            Logger::getInstance()->error("No se encontro el parametro '" + MAX_PLAYERS_NODE + "' en la configuracion. Se procede a tomar el valor por defecto: '" + to_string(DEFAULT_MAX_PLAYERS) + "'.");
            configuration->SetMaxPlayers(DEFAULT_MAX_PLAYERS);
        }

        if (config_file[USERS_NODE])
        {
            // OBTENGO TODOS LOS USUARIOS Y SUS PASSWORDS
            YAML::Node users_node = config_file[USERS_NODE];

            for (unsigned short i = 0; i < users_node.size(); ++i)
            {
                std::string username = users_node[i]["name"].as<std::string>();
                std::string password = users_node[i]["password"].as<std::string>();
                configuration->AddValidCredential(username, password);
            }
        }
    }

    if(config_file[PORT_NODE])
    {
        configuration->SetPort(config_file[PORT_NODE].as<int>());//TODO: es necesario validarlo?
    }
    else
    {
        Logger::getInstance()->error("No se encontro el parametro '" + PORT_NODE + "' en la configuracion. Se procede a tomar el valor por defecto: '" + to_string(DEFAULT_PORT_NODE) + "'.");
        configuration->SetPort(DEFAULT_PORT_NODE);
    }

    if(config_file[GAME_DURATION]) {
    	configuration->SetGameDuration(config_file[GAME_DURATION].as<string>());
    } else {
    	Logger::getInstance()->error("No se encontro el parametro '" + GAME_DURATION + "' en la configuracion. Se procede a tomar el valor por defecto: '" + DEFAULT_GAME_DURATION + "'.");
    	configuration->SetPort(DEFAULT_PORT_NODE);
    }
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

void ConfigurationParser::ReadFile(Configuration* config, string file_path)
{
    Logger::getInstance()->debug("Leyendo archivo de configuracion desde '" + file_path + "'...");
    try
    {
        YAML::Node config_file = YAML::LoadFile(file_path);
        parseConfigFile(config, config_file);
    }
    catch (YAML::BadFile& e)
    {
        Logger::getInstance()->error("No se encontro el archivo '" + file_path + "'. Se procede a cargar el archivo por defecto: '" + DEFAULT_CONFIG_FILE + "'.");
        this->ReadDefaultConfig(config);
    }
}

void ConfigurationParser::ReadDefaultConfig(Configuration* config)
{
    YAML::Node config_file = YAML::LoadFile(DEFAULT_CONFIG_FILE);
    parseConfigFile(config, config_file);
}
