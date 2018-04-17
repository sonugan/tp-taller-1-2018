#include "configuration.h"
#include "configuration-parser.h"
#include "logger.h"

#include <algorithm>
#include <sys/stat.h>

using namespace std;

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

bool DirectoryExists(string dir)
{
    struct stat statStruct;

    return stat(dir.c_str(), &statStruct) == 0 && S_ISDIR(statStruct.st_mode);
}

string Configuration::GetLogLevel()
{
    return this->log_level;
}

string str_to_lower(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);

    return str;
}

void Configuration::SetLogLevel(string log_level)
{

    if (IsValidConfigValue("level", str_to_lower(log_level))) {
        this->log_level = log_level;
    }
    else {
        this->log_level = "debug";
        Logger::getInstance()->error("El valor '" + log_level + "' no es valido para el nivel de log. Se procede a tomar el valor por defecto del logger: 'debug'");
    }

    Logger::getInstance()->debug("(Configuracion) NIVEL DE LOG: " + this->log_level);
}

string Configuration::GetFormation()
{
    return this->formation;
}

void Configuration::SetFormation(string formation)
{
    if (IsValidConfigValue("formation", formation)) {
        this->formation = formation;
    }
    else {
        this->formation = "3-3";
        Logger::getInstance()->error("El valor '" + formation + "' no es valido para la formacion. Se procede a tomar el valor por defecto de la formacion: '3-3'");
    }

    Logger::getInstance()->debug("(Configuracion) FORMACION: " + this->formation);
}

string Configuration::GetShirt()
{
    return this->shirt;
}

void Configuration::SetShirt(string shirt)
{
    if (IsValidConfigValue("shirt", shirt)) {
        this->shirt = shirt;
    }
    else {
        this->shirt = "home";
        Logger::getInstance()->error("El valor '" + shirt + "' no es valido para la camiseta. Se procede a tomar el valor por defecto de la camiseta: 'home'");
    }

    Logger::getInstance()->debug("(Configuracion) SHIRT: " + this->shirt);
}

string Configuration::GetSpritesPath()
{
    return this->sprites_path;
}

void Configuration::SetSpritesPath(string sprites_path)
{
    if (DirectoryExists(sprites_path)) {
        this->sprites_path = sprites_path;
    }
    else {
        this->sprites_path = "src/sprites";
        Logger::getInstance()->error("El valor: '" + sprites_path + "' no es valido para la ruta de sprites ya que no existe el directorio. Se procede a tomar el valor por defecto: 'src/sprites'");
    }

    Logger::getInstance()->debug("(Configuracion) SPRITES PATH: " + this->sprites_path);
}

void Configuration::Load(Configuration* config, string config_path, string log_level)
{
    ConfigurationParser* parser = new ConfigurationParser();
    parser->ReadFile(config, config_path);
    if(log_level != "") {
        Logger::getInstance()->debug("(Configuracion-CLI) NIVEL DE LOG: " + log_level);
        config->SetLogLevel(log_level);
    }
    delete parser;
}

string Configuration::GetTeamName()
{
    return this->team_name;
}

void Configuration::SetTeamName(string name)
{
    //Sin validacion porque este directorio esta dentro del sprite_path que pudo no ser seteado antes de configurarse el nombre del equipo
    this->team_name = name;
    Logger::getInstance()->debug("(Configuracion) NOMBRE DE EQUIPO: " + this->team_name);
}

bool Configuration::IsValidConfigValue(string parameter, string value)
{
    vector<string> valid_values = {};
    auto it = this->valid_configurations.find(parameter);

    if (it != this->valid_configurations.end()) {
        valid_values = it->second;
        //Devuelvo TRUE si value esta dentro de los parametros validos y FALSE si no esta
        return (find(valid_values.begin(), valid_values.end(), value) != valid_values.end());
    }

    //El parametro no existe
    return false;
}
