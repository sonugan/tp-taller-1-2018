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
