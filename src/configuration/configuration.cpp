#include "configuration.h"
#include "configuration-parser.h"
#include "logger.h"

Configuration::Configuration()
{
}

Configuration::Configuration(string formation, string shirt, string log_level)
{
    this->formation = formation;
    this->shirt = shirt;
    this->log_level = log_level;
}

Configuration::~Configuration()
{
    //dtor
}

string Configuration::GetLogLevel()
{
    return this->log_level;
}

void Configuration::SetLogLevel(string log_level)
{
    this->log_level = log_level;
    Logger::getInstance()->debug("(Configuracion) NIVEL DE LOG: " + log_level);
}

string Configuration::GetFormation()
{
    return this->formation;
}

void Configuration::SetFormation(string formation)
{
    this->formation = formation;
    Logger::getInstance()->debug("(Configuracion) FORMACION: " + formation);
}

string Configuration::GetShirt()
{
    return this->shirt;
}

void Configuration::SetShirt(string shirt)
{
    this->shirt = shirt;
    Logger::getInstance()->debug("(Configuracion) SHIRT: " + shirt);
}

string Configuration::GetSpritesPath()
{
    return this->sprites_path;
}

void Configuration::SetSpritesPath(string sprites_path)
{
    this->sprites_path = sprites_path;
    Logger::getInstance()->debug("(Configuracion) SPRITES PATH: " + sprites_path);
}

Configuration* Configuration::Load(string config_path, string log_level)
{
    ConfigurationParser* parser = new ConfigurationParser();
    Configuration* config = parser->ReadFile(config_path);
    if(log_level != "") {
        config->SetLogLevel(log_level);
    }

    return config;
}
