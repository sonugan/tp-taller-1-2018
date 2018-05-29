#include "session-manager.h"

#include "../../shared/logger.h"
#include "authentication-exception.h"
#include "max-allowed-user-exception.h"
#include "invalid-team-exception.h"

SessionManager::SessionManager(map<string, string> credentials, int max_allowed_users)
{
    this->credentials = credentials;
    this->max_allowed_users = max_allowed_users;

    colors.push(USER_COLOR::BLUE);
    colors.push(USER_COLOR::GREEN);
    colors.push(USER_COLOR::RED);
    colors.push(USER_COLOR::YELLOW);
}

SessionManager::~SessionManager()
{
    //dtor
}

User* SessionManager::Authenticate(ClientSocket* client, LoginRequest* login_request)
{
    if(GetAutheticatedUsersCount() == this->max_allowed_users)
    {
        throw MaxAllowedUsersException("No es posible agregar más usuarios al juego.");
    }

    if(IsValidUser(login_request->GetUsername(), login_request->GetPassword()))
    {
        if(!IsAuthenticated(login_request))
        {
            Logger::getInstance()->info("(SessionManager:Authenticate) Usuario válido. Se conectó: " + login_request->GetUsername());

            USER_COLOR color = this->GetColorToAssign();

            User* user = new User(login_request->GetUsername(), login_request->GetPassword(), this->ParseSelectedTeam(login_request->GetTeam()), color);

            this->authenticated_users[user->GetUsername()] = user;
            this->clientsocket_user_association[client->socket_id] = user;

            string created_user = "Usuario creado: " + user->GetUsername() + " color: "+ to_string((int) user->GetUserColor());
            Logger::getInstance()->info(created_user);

            return user;
        }
        else
        {
            Logger::getInstance()->debug("(SessionManager:Authenticate) No se pudo autenticar usuario. El usuario ya se encuentra autenticado.");
            throw AuthenticationException("Invalid user.");
        }
    }
    else
    {
        Logger::getInstance()->debug("(SessionManager:Authenticate) No se pudo autenticar usuario. Credenciales inválidas.");
        throw AuthenticationException("Invalid credentials.");
    }
}

void SessionManager::RemoveSession(string username)
{
    Logger::getInstance()->info("(SessionManager:RemoveSession) Removiendo usuario: " + username);
    map<string, User*>::iterator it = this->authenticated_users.find(username);
    if(it != this->authenticated_users.end())
    {
        // Recupero color de usuario para poder reasignarlo
        User* user = it->second;
        Logger::getInstance()->debug("(SessionManager:RemoveSession) Sesion encontrada. user: " + user->GetUsername());
        USER_COLOR user_color = user->GetUserColor();
        this->colors.push(user_color);

        // Remuevo seleccion del player.
        Logger::getInstance()->debug("(SessionManager:RemoveSession) quitando seleccion al player");
        user->GetSelectedPlayer()->SetPlayerColor(USER_COLOR::NO_COLOR);


        Logger::getInstance()->debug("(SessionManager:RemoveSession) Borrando user de coleccion de autenticados.");
        // Lo elimino de la colección de usuarios autenticados.
        this->authenticated_users.erase(username);

        delete user;
    }
}


int SessionManager::GetAutheticatedUsersCount()
{
    return this->authenticated_users.size();
}

User* SessionManager::GetUserBySocketID(int socket_id)
{
    map<int, User*>::iterator it = this->clientsocket_user_association.find(socket_id);
    if(it != this->clientsocket_user_association.end())
    {
        return it->second;
    }
    return NULL;
}

User* SessionManager::GetUserByColor(USER_COLOR color)
{
    for (const auto& any : clientsocket_user_association) {
        User* user = any.second;
        if (color == user->GetUserColor()) {
            return user;
        }
    }

    return NULL;
}

bool SessionManager::IsReadyToStart()
{
    return this->GetAutheticatedUsersCount() == this->max_allowed_users;
}

bool SessionManager::IsAuthenticatedClient(ClientSocket* client)
{
    return GetUserBySocketID(client->socket_id) != NULL;
}

void SessionManager::CloseSession(ClientSocket* client)
{
    User* user = GetUserBySocketID(client->socket_id);

    if(user != NULL)
    {
        Logger::getInstance()->debug("(SessionManager:CloseSession) Sesión encontrada. User: " + user->GetUsername());
        USER_COLOR user_color = user->GetUserColor();
        this->colors.push(user_color);

        // Remuevo seleccion del player.
        Logger::getInstance()->debug("(SessionManager:CloseSession) Quitando selección al player");
        user->GetSelectedPlayer()->SetPlayerColor(USER_COLOR::NO_COLOR);

        Logger::getInstance()->debug("(SessionManager:CloseSession) Borrando user de colección de autenticados.");
        // Lo elimino de la colección de usuarios autenticados.
        this->authenticated_users.erase(user->GetUsername());

        this->clientsocket_user_association.erase(client->socket_id);

        delete user;
    }

}

/* Private Methods */

bool SessionManager::IsValidUser(string username, string password)
{
    map<string,string>::iterator it = this->credentials.find(username);

    if (it != this->credentials.end())
    {
        // Encontro el usuario, comparo las passwords
        string stored_password = it->second;
        return stored_password.compare(password) == 0;
    }

    return false; // No existe ese usuario
}

bool SessionManager::IsAuthenticated(LoginRequest* login_request)
{
    map<string, User*>::iterator it = this->authenticated_users.find(login_request->GetUsername());

    if (it != this->authenticated_users.end())
    {
        // Encontro el usuario, comparo las passwords
        User* user = it->second;
        return user->GetPassword().compare(login_request->GetPassword()) == 0;
    }

    return false; // No existe ese usuario
}

USER_COLOR SessionManager::GetColorToAssign()
{
    USER_COLOR color = this->colors.top();
    this->colors.pop();
    return color;
}

TEAM_NUMBER SessionManager::ParseSelectedTeam(string selected_team)
{
    if("a" == selected_team)
    {
        return TEAM_NUMBER::TEAM_A;
    }
    else if ("b" == selected_team)
    {
        return TEAM_NUMBER::TEAM_B;
    }

    Logger::getInstance()->debug("(SessionManager:ParseSelectedTeam) Equipo seleccionado invalido.");
    throw InvalidTeamException("Invalid team.");
}
