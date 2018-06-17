#include "pitch.h"
#include "ball.h"

Pitch::Pitch(Team* team_a, Team* team_b)
{
    int goal_height = 60;
    //Creando arcos: Resto el tamaño de la pelota para que sea gol "cuando pase completa" ("tiro para atras" el area de gol)
    this->east_goal = new GoalZone(team_a, new Location(145, 476, 0), new Location(185 - Ball::BALL_TRIDIMENSIONAL_OFFSET, 606, 0), goal_height);
    this->west_goal = new GoalZone(team_b, new Location(1734 +  Ball::BALL_TRIDIMENSIONAL_OFFSET, 476, 0), new Location(1774, 606, 0), goal_height);
}

Pitch::~Pitch()
{
    //dtor
}

/** Devuelve el equipo del arco en el que estan convirtiendo*/
Team* Pitch::ScoringAtSomeGoal(Ball* ball)
{
    if (this->IsGoalOnEastGoal(ball))
    {
        return this->east_goal->GetTeam();
    }
    else if (this->IsGoalOnWestGoal(ball))
    {
        return this->west_goal->GetTeam();
    }

    return NULL;
}

bool Pitch::IsGoalOnEastGoal(Ball* ball)
{
    return this->east_goal->IsGoal(ball);
}

bool Pitch::IsGoalOnWestGoal(Ball* ball)
{
    return this->west_goal->IsGoal(ball);
}

