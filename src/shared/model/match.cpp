#include "match.h"
#include "../logger.h"


Match::Match(Pitch* pitch, Team* team_a, Team* team_b, Ball* ball) {
    this->team_a = team_a;
    this->team_b = team_b;
    this->team_a->SetMatch(this);
    if (team_b != NULL) {
        this->team_b->SetMatch(this);
    }
    this->pitch = pitch;
    this->ball = ball;
}

Match::~Match() {
    Logger::getInstance()->debug("DESTRUYENDO EL MATCH");
    delete pitch;
    delete team_a;
    delete team_b;
    delete ball;
}

Team* Match::GetTeamA() {
    return team_a;
}

Team* Match::GetTeamB() {
    return team_b;
}

Pitch* Match::GetPitch() {
    return pitch;
}

Ball* Match::GetBall() {
    return ball;
}

string Match::Serialize() {
    Logger::getInstance()->debug("(Match:Serialize) Serializando Match...");

    string result;
    //  MESSAGE TYPE
    result.append(std::to_string(MESSAGE_TYPE::GAME_STATE_RESPONSE));
    result.append("|");

    //  BALL
    //  X
    result.append(std::to_string(ball->GetLocation()->GetX()));
    result.append("|");
    //  Y
    result.append(std::to_string(ball->GetLocation()->GetY()));
    result.append("|");
    //  Z
//    result.append(std::to_string(ball->GetLocation()->GetZ()));
//    result.append("|");

    //  TEAM A
    for (unsigned int i = 0; i < Team::TEAM_SIZE; i++) {
        //  PLAYER i
        Player* player = GetTeamA()->GetPlayers()[i];
        //  DIRECTION
        result.append(std::to_string((int) player->GetDirection()));
        result.append("|");
        //  COLOR
        result.append(std::to_string((int) player->GetPlayerColor()));
        result.append("|");
        // KICKING
        result.append(std::to_string((int) player->IsKicking()));
        result.append("|");
        // KICKING
        result.append(std::to_string((int) player->IsRecoveringBall()));
        result.append("|");
        //  X
        result.append(std::to_string(player->GetLocation()->GetX()));
        result.append("|");
        //  Y
        result.append(std::to_string(player->GetLocation()->GetY()));
        result.append("|");
        //  Z
//        result.append(std::to_string(player->GetLocation()->GetZ()));
//        result.append("|");
    }

    //  TEAM B
    for (unsigned int i = 0; i < Team::TEAM_SIZE; i++) {
        //  PLAYER i
        Player* player = GetTeamB()->GetPlayers()[i];
        //  DIRECTION
        result.append(std::to_string((int) player->GetDirection()));
        result.append("|");
        //  COLOR
        result.append(std::to_string((int) player->GetPlayerColor()));
        result.append("|");
        // KICKING
        result.append(std::to_string((int) player->IsKicking()));
        result.append("|");
        // KICKING
        result.append(std::to_string((int) player->IsRecoveringBall()));
        result.append("|");
        //  X
        result.append(std::to_string(player->GetLocation()->GetX()));
        result.append("|");
        //  Y
        result.append(std::to_string(player->GetLocation()->GetY()));
        result.append("|");
        //  Z
//        result.append(std::to_string(player->GetLocation()->GetZ()));
//        result.append("|");
    }

    result.append(std::to_string((int) GetTeamA()->GetFormation()->GetValue()));
    result.append("|");
    result.append(std::to_string((int) GetTeamB()->GetFormation()->GetValue()));
    result.append("|");
    result.append(GetTeamA()->GetShirt());
    result.append("|");
    result.append(GetTeamB()->GetShirt());

//    Logger::getInstance()->debug("(Match:Serialize) Serialize result: " + result);
    return result;
}

void Match::DeserializeAndUpdate(string serialized) {
    Logger::getInstance()->debug("(Match:DeserializeAndUpdate) Deserializando Match...");
    std::vector<std::string> data = StringUtils::Split(serialized, '|');

    //  BALL
    ball->GetLocation()->Update(SafeStoi(data[1]), SafeStoi(data[2]), 0);
//    Logger::getInstance()->debug("(Match:DeserializeAndUpdate) Ball location: " + ball->GetLocation()->ToString());

    //  TEAM A
    for (unsigned int i = 0; i < Team::TEAM_SIZE; i++) {

        Logger::getInstance()->debug("(Match:DeserializeAndUpdate) Team A - Player: " + to_string(i));

        int base_index = 3 + (i*6);
        Player* player = GetTeamA()->GetPlayers()[i];
//        Logger::getInstance()->debug("(Match:DeserializeAndUpdate) direction");
        player->SetDirection(static_cast<DIRECTION>(SafeStoi(data[base_index])));

//        Logger::getInstance()->debug("(Match:DeserializeAndUpdate) color");
        player->SetPlayerColor(static_cast<USER_COLOR>(SafeStoi(data[base_index + 1])));

//        Logger::getInstance()->debug("(Match:DeserializeAndUpdate) is_kicking");
        player->SetKicking((bool)(SafeStoi(data[base_index + 2])));

//        Logger::getInstance()->debug("(Match:DeserializeAndUpdate) is_recovering_ball");
        player->SetRecoveringBall((bool)(SafeStoi(data[base_index + 3])));

//        Logger::getInstance()->debug("(Match:DeserializeAndUpdate) location");
        player->GetLocation()->Update(SafeStoi(data[base_index + 4]), SafeStoi(data[base_index + 5]), 0);

    }

    //  TEAM B
    for (unsigned int i = 0; i < Team::TEAM_SIZE; i++) {

        Logger::getInstance()->debug("(Match:DeserializeAndUpdate) Team B - Player: " + to_string(i));
        int base_index = 3 + 42 + (i*6);
        Player* player = GetTeamB()->GetPlayers()[i];

//        Logger::getInstance()->debug("(Match:DeserializeAndUpdate) direction");
        player->SetDirection(static_cast<DIRECTION>(SafeStoi(data[base_index])));

        player->SetPlayerColor(static_cast<USER_COLOR>(SafeStoi(data[base_index + 1])));

//        Logger::getInstance()->debug("(Match:DeserializeAndUpdate) is_kicking");
        player->SetKicking((bool)(SafeStoi(data[base_index + 2])));
//        Logger::getInstance()->debug("(Match:DeserializeAndUpdate) is_recovering_ball");
        player->SetRecoveringBall((bool)(SafeStoi(data[base_index + 3])));
//        Logger::getInstance()->debug("(Match:DeserializeAndUpdate) location");
        player->GetLocation()->Update(SafeStoi(data[base_index + 4]), SafeStoi(data[base_index + 5]), 0);

    }

    int base_index = 87;

    Formation* formation_a = new Formation(static_cast<FORMATION>(SafeStoi(data[base_index])), TEAM_NUMBER::TEAM_A);
    GetTeamA()->SetFormation(formation_a);
    Formation* formation_b = new Formation(static_cast<FORMATION>(SafeStoi(data[base_index + 1])), TEAM_NUMBER::TEAM_B);
    GetTeamB()->SetFormation(formation_b);

    GetTeamA()->SetShirt(data[base_index + 2]);
    GetTeamB()->SetShirt(data[base_index + 3]);


    Logger::getInstance()->debug("(Match:DeserializeAndUpdate) Match deserializado");
}

int Match::SafeStoi(const string& str)
{
    try
    {
        return stoi(str);
    }
    catch (...)
    {
        Logger::getInstance()->error("(Match:SafeStoi) Error con argumento: " + str);
    }
}
