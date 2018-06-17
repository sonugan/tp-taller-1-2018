#include "pitch.h"
#include "ball.h"

Pitch::Pitch(Team* team_a, Team* team_b)
{
    int goal_height = 60;
    //Creando arcos: Resto el tamaño de la pelota para que sea gol "cuando pase completa" ("tiro para atras" el area de gol)
    this->east_goal = new GoalZone(team_a, new Location(145, 476, 0), new Location(185 - Ball::BALL_TRIDIMENSIONAL_OFFSET, 606, 0), goal_height);
    this->west_goal = new GoalZone(team_b, new Location(1734 +  Ball::BALL_TRIDIMENSIONAL_OFFSET, 476, 0), new Location(1774, 606, 0), goal_height);

    //Creando zonas de lateral
    int throw_in_height = 150;
    throw_in_zones[0] = new ThrowInZone(new Location(186, 0, 0), new Location(1734, 21, 0), throw_in_height);
    throw_in_zones[1] = new ThrowInZone(new Location(186, 1061, 0), new Location(1734, 1080, 0), throw_in_height);
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

bool Pitch::BallTouchingThrowIn(Ball* ball)
{
    return (this->throw_in_zones[0]->IsTouching(ball) || this->throw_in_zones[1]->IsTouching(ball));
}
