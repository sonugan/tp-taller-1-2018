#include "configuration-parser.h"
#include <iostream>

ConfigurationParser::ConfigurationParser()
{
    //ctor
}

ConfigurationParser::~ConfigurationParser()
{
    //dtor
}

void ConfigurationParser::ReadFile(string file_path) {
    try {
        YAML::Node config = YAML::LoadFile(file_path);
        if (config["logger"]) {
            std::cout << "Logger - level: " << config["logger"]["level"].as<std::string>() << "\n";
        }
    } catch (YAML::BadFile e) {
        std::cout << "No se pudo leer archivo de configuracion. Usando configuración default" << "\n";
        this->ReadDefaultConfig();
    }

}

void ConfigurationParser::ReadDefaultConfig() {
    YAML::Node config = YAML::LoadFile(DEFAULT_CONFIG_FILE);
    if (config["logger"]) {
            std::cout << "Logger - level: " << config["logger"]["level"].as<std::string>() << "\n";
    }
}

