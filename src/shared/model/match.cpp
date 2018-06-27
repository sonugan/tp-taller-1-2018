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
    this->match_time = MATCH_TIME_TYPE::FIRST_TIME;
    this->match_state = new MatchState();
}

Match::~Match() {
    Logger::getInstance()->debug("DESTRUYENDO EL MATCH");
    delete pitch;
    delete team_a;
    delete team_b;
    delete ball;
    delete match_state;
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

MATCH_TIME_TYPE Match::GetMatchTime() {
	return this->match_time;
}

void Match::SetMatchTime(MATCH_TIME_TYPE match_time){
	this->match_time = match_time;
}

MatchState* Match::GetMatchState() {
	return this->match_state;
}

void Match::SetMatchState(MatchState* state) {
	this->match_state = state;
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
    result.append(std::to_string(ball->GetLocation()->GetZ()));
    result.append("|");
    // TRAJECTORY TPYE
    result.append(std::to_string((int) ball->GetTrajectory()->GetTrajectoryType()));
    result.append("|");


    //  TEAM A

    Keeper* keeper_a = GetTeamA()->GetKeeper();
    result.append("0");
    result.append("|");
    result.append("0");
    result.append("|");
    result.append("0");
    result.append("|");
    result.append(std::to_string((int) keeper_a->GetState()));
    result.append("|");
    result.append(std::to_string(keeper_a->GetLocation()->GetX()));
    result.append("|");
    result.append(std::to_string(keeper_a->GetLocation()->GetY()));
    result.append("|");

    for (unsigned int i = 1; i <= Team::TEAM_SIZE; i++) {
        //  PLAYER i
        Player* player = GetTeamA()->GetPlayerByPositionIndex(i);
        //  DIRECTION
        result.append(std::to_string((int) player->GetDirection()));
        result.append("|");
        //  COLOR
        result.append(std::to_string((int) player->GetPlayerColor()));
        result.append("|");
        // CURRENT ACTION
        result.append(std::to_string((int) player->GetCurrentAction()));
        result.append("|");
        //result.append(std::to_string((int) player->IsKicking()));
        //result.append("|");
        // RECOVER
        result.append(std::to_string(player->IsStill()));//TODO:Remover
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

    // dummy keeper
    Keeper* keeper_b = GetTeamB()->GetKeeper();
    result.append("0");
    result.append("|");
    result.append("0");
    result.append("|");
    result.append("0");
    result.append("|");
    result.append(std::to_string((int) keeper_b->GetState()));
    result.append("|");
    result.append(std::to_string(keeper_b->GetLocation()->GetX()));
    result.append("|");
    result.append(std::to_string(keeper_b->GetLocation()->GetY()));
    result.append("|");

    for (unsigned int i = 1; i <= Team::TEAM_SIZE; i++) {
        //  PLAYER i
        Player* player = GetTeamB()->GetPlayerByPositionIndex(i);
        //  DIRECTION
        result.append(std::to_string((int) player->GetDirection()));
        result.append("|");
        //  COLOR
        result.append(std::to_string((int) player->GetPlayerColor()));
        result.append("|");
        // CURRENT ACTION
        result.append(std::to_string((int) player->GetCurrentAction()));
        result.append("|");
        // KICKING
        //result.append(std::to_string((int) player->IsKicking()));
        //result.append("|");
        // KICKING
        result.append(std::to_string(player->IsStill()));//TODO:Remover
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
    result.append("|");
    result.append(std::to_string(GetTeamA()->GetGoals()));
    result.append("|");
    result.append(std::to_string(GetTeamB()->GetGoals()));

    // REMAINING GAME TIME
    result.append("|");
    result.append(GetRemainingTime());
    // MATCH TIME
    result.append("|");
    result.append(std::to_string(GetMatchTime()));
    // MATCH STATE TYPE
    result.append("|");
    result.append(std::to_string(GetMatchState()->GetType()));
    // SCORER TEAM
    result.append("|");
    result.append(std::to_string((int) GetMatchState()->GetGoalScorerTeam()));

//    Logger::getInstance()->debug("(Match:Serialize) Serialize result: " + result);
    return result;
}

void Match::DeserializeAndUpdate(string serialized) {
    Logger::getInstance()->debug("(Match:DeserializeAndUpdate) Deserializando Match...");
    std::vector<std::string> data = StringUtils::Split(serialized, '|');

    //  BALL
    ball->GetLocation()->Update(SafeStoi(data[1]), SafeStoi(data[2]), SafeStoi(data[3]));
    ball->GetTrajectory()->UpdateTrajectoryType(static_cast<TRAJECTORY_TYPE>(SafeStoi(data[4])));

    //  TEAM A
    Keeper* keeper_a = GetTeamA()->GetKeeper();
    keeper_a->UpdateState(static_cast<KEEPER_STATE>(SafeStoi(data[8])));
    keeper_a->GetLocation()->Update(SafeStoi(data[9]), SafeStoi(data[10]), 0);

    for (unsigned int i = 1; i <= Team::TEAM_SIZE; i++) {


        int base_index = 5 + (i*6);
        Player* player = GetTeamA()->GetPlayerByPositionIndex(i);
//        Logger::getInstance()->debug("(Match:DeserializeAndUpdate) direction");
        player->SetDirection(static_cast<DIRECTION>(SafeStoi(data[base_index])));


        player->SetPlayerColor(static_cast<USER_COLOR>(SafeStoi(data[base_index + 1])));

        //player->SetKicking((bool)(SafeStoi(data[base_index + 2])));
        player->SetCurrentAction(static_cast<PLAYER_ACTION>(stoi(data[base_index + 2])));

        player->SetIsStill((bool)(SafeStoi(data[base_index + 3])));

        player->GetLocation()->Update(SafeStoi(data[base_index + 4]), SafeStoi(data[base_index + 5]), 0);

    }

    //  TEAM B
    Keeper* keeper_b = GetTeamB()->GetKeeper();
    keeper_b->UpdateState(static_cast<KEEPER_STATE>(SafeStoi(data[50])));
    keeper_b->GetLocation()->Update(SafeStoi(data[51]), SafeStoi(data[52]), 0);

    for (unsigned int i = 1; i <= Team::TEAM_SIZE; i++) {

        int base_index = 5 + 42 + (i*6);
        Player* player = GetTeamB()->GetPlayerByPositionIndex(i);

        player->SetDirection(static_cast<DIRECTION>(SafeStoi(data[base_index])));

        player->SetPlayerColor(static_cast<USER_COLOR>(SafeStoi(data[base_index + 1])));

        player->SetCurrentAction(static_cast<PLAYER_ACTION>(stoi(data[base_index + 2])));

        //player->SetKicking((bool)(SafeStoi(data[base_index + 2])));

        player->SetIsStill((bool)(SafeStoi(data[base_index + 3])));

        player->GetLocation()->Update(SafeStoi(data[base_index + 4]), SafeStoi(data[base_index + 5]), 0);

        Logger::getInstance()->info("Match::DeserializeAndUpdate GetIsStill" + to_string(player->GetIsStill()));
        Logger::getInstance()->info("Match::DeserializeAndUpdate IsStill" + to_string(player->IsStill()));

    }

    int base_index = 89;

    /*Formation* formation_a = new Formation(static_cast<FORMATION>(SafeStoi(data[base_index])), TEAM_NUMBER::TEAM_A);
    GetTeamA()->SetFormation(formation_a);
    Formation* formation_b = new Formation(static_cast<FORMATION>(SafeStoi(data[base_index + 1])), TEAM_NUMBER::TEAM_B);
    GetTeamB()->SetFormation(formation_b);*/


    GetTeamA()->SetShirt(data[base_index + 2]);
    GetTeamB()->SetShirt(data[base_index + 3]);
    this->GetTeamA()->SetGoals(SafeStoi(data[base_index + 4]));
    this->GetTeamB()->SetGoals(SafeStoi(data[base_index + 5]));

    // DESERIALIZO REMAINING GAME TIME
    this->SetRemainingTime(data[base_index + 6]);
    // MATCH TIME
    this->SetMatchTime(static_cast<MATCH_TIME_TYPE>(SafeStoi(data[base_index + 7])));
    this->match_state->SetType(static_cast<MATCH_STATE_TYPE>(SafeStoi(data[base_index + 8])));
    this->match_state->SetGoalScorerTeam(static_cast<TEAM_NUMBER>(SafeStoi(data[base_index + 9])));

    Logger::getInstance()->debug("(Match:DeserializeAndUpdate) Match deserializado");
}

int Match::SafeStoi(const string& str) // @suppress("No return")
{
    try
    {
        return stoi(str);
    }
    catch (...)
    {
        Logger::getInstance()->error("(Match:SafeStoi) Error con argumento: " + str);
        return -1;
    }
}

std::string Match::GetRemainingTime() {
	return this->remaining_time;
}

void Match::SetRemainingTime(std::string remaining_time) {
	this->remaining_time = remaining_time;
}

Team* Match::GetTeamByNumber(TEAM_NUMBER number)
{
    if (number == this->team_a->GetTeamNumber())
    {
        return this->team_a;
    }

    return this->team_b;
}

Team* Match::GetOppositeTeam(Team* team)
{
    if (team == this->team_a)
    {
        return team_b;
    }

    return team_a;
}

void Match::SetKickOffLocations(TEAM_NUMBER kicker_team) {
    Player* player;
	Formation* formation_a = this->team_a->GetFormation();
	Formation* formation_b = this->team_b->GetFormation();
    for (unsigned int i = 1; i <= Team::TEAM_SIZE; i++)
    {
        player = this->team_a->GetPlayerByPositionIndex(i);
        player->ChangeToStill();
        player->SetIsStill(true);
        player->GetLocation()->Update(formation_a->GetKickoffLocationForPlayer(i, formation_a->GetTeamNumber() == kicker_team));
        player->UpdateCircle();

        player = this->team_b->GetPlayerByPositionIndex(i);
        player->ChangeToStill();
        player->SetIsStill(true);
        player->GetLocation()->Update(formation_b->GetKickoffLocationForPlayer(i, formation_b->GetTeamNumber() == kicker_team));
        player->UpdateCircle();
    }
}

void Match::ChangeTeamSides()
{
    Logger::getInstance()->info("Cambiando los equipos de lado...");
    this->team_a->SetTeamNumber(TEAM_NUMBER::TEAM_B);
	this->team_b->SetTeamNumber(TEAM_NUMBER::TEAM_A);

    this->pitch->ChangeTeamSides(this->team_a, this->team_b);
}
