#include "session-manager.h"

#include "../../shared/logger.h"
#include "authentication-exception.h"

SessionManager::SessionManager(map<string, string> credentials)
{
    this->credentials = credentials;
}

SessionManager::~SessionManager()
{
    //dtor
}

User* SessionManager::Authenticate(ClientSocket* client, LoginRequest* login_request)
{
//    if(IsAuthenticated(login_request))
//    {
//        string log_msg = "(SessionManager:Authenticate) El usuario: " + login_request->GetUsername() + " ya se encuentra autenticado.";
//        Logger::getInstance()->info(log_msg);
//        return this->authenticated_users.find(login_request->GetUsername())->second;
//    }

    if(IsValidUser(login_request->GetUsername(), login_request->GetPassword()))
    {
        Logger::getInstance()->info("(SessionManager:Authenticate) Usuario válido. Se conectó: " + login_request->GetUsername());
        //TODO: pedir team al login request
        User* user = new User(login_request->GetUsername(), login_request->GetPassword(), 1, USER_COLOR::RED);
        this->authenticated_users[user->GetUsername()] = user;
        this->clientsocket_user_association[client->socket_id] = user;

        return user;
    } else {
        Logger::getInstance()->debug("(SessionManager:Authenticate) No se pudo autenticar usuario. Credenciales inválidas.");
        throw AuthenticationException("Invalid credentials.");
    }
}

void SessionManager::RemoveSession(string username)
{
    Logger::getInstance()->info("(SessionManager:RemoveSession) Removiendo usuario: " + username);
    this->authenticated_users.erase(username);
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
