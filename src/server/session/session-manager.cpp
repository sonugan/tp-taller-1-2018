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

User* SessionManager::Authenticate(Login* login_request)
{
    if(IsValidUser(login_request->GetUsername(), login_request->GetPassword()))
    {
        Logger::getInstance()->info("(SessionManager:Authenticate) Usuario válido. Se conectó: " + login_request->GetUsername());
        //TODO: pedir team al login request
        User* user = new User(login_request->GetUsername(), "TEAM_A");
        pair<string, User*> user_entry = pair<string, User*>(user->GetUsername(), user);
        this->authenticated_users.insert(user_entry);
        return user;
    } else {
        Logger::getInstance()->debug("(SessionManager:Authenticate) No se pudo autenticar usuario. Credenciales inválidas.");
        throw AuthenticationException("Invalid credentials.");
    }
}

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
