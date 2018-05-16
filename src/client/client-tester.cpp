#include "client-tester.h"

ClientTester::ClientTester(Configuration* config)
{
    this->client = new Client(config);
}

ClientTester::~ClientTester()
{
    delete this->client;
}

void ClientTester::TestCompleteFlow()
{
    client->Init("127.0.0.1");

    Login* login_request = new Login();
    login_request->SetUsername("gperez");
    login_request->SetPassword("1234");
    login_request->SetTeam("team_a");
    login_request->SetServerIp("127.0.0.1");
    client->LogIn(login_request);

    client->Close();
}
