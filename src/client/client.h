#ifndef CLIENT_H
#define CLIENT_H

#include "../shared/configuration/configuration.h"
#include "../shared/network/client-socket.h"
#include "../shared/network/messages/login-request.h"
#include "../shared/network/messages/quit-request.h"
#include "../shared/network/messages/kick-ball-request.h"
#include "../shared/network/messages/pass-ball-request.h"
#include "../shared/network/messages/recover-ball-request.h"
#include "../shared/network/messages/move-request.h"
#include "../shared/network/messages/change-player-request.h"

#include <string>

class Client
{
    public:
        Client(Configuration * configuration);
        virtual ~Client();
        void Init(std::string server_ip);
        bool LogIn(LoginRequest* login_request);
        bool WaitForGameStart();
        bool Quit(QuitRequest* quit_request);
        void Close();
        bool KickBall(KickBallRequest* kick_ball_request);
        bool PassBall(PassBallRequest* pass_ball_request);
        bool RecoverBall(RecoverBallRequest* recover_ball_request);
        bool Move(MoveRequest* move_request);
        bool ChangePlayer(ChangePlayerRequest* change_player_request);

        // TODO: Tipar mensaje. esto es solo para una prueba
        void SendEvent();

    protected:

    private:
        Configuration* config;
        ClientSocket* clientSocket;
};

#endif // CLIENT_H
