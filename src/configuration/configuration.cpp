#include "configuration.h"

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
}

string Configuration::GetFormation()
{
    return this->formation;
}

void Configuration::SetFormation(string formation)
{
    this->formation = formation;
}

string Configuration::GetShirt()
{
    return this->shirt;
}

void Configuration::SetShirt(string shirt)
{
    this->shirt = shirt;
}
