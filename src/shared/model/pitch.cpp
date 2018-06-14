#include "pitch.h"

Pitch::Pitch()
{
    int goal_height = 30;
    //Creando arcos: Resto el tamaño de la pelota para que sea gol "cuando pase completa" ("tiro para atras" el area de gol)
    /*this->east_goal = new GoalZone(new Location(145, 476, 0), new Location(185 - Ball::BALL_TRIDIMENSIONAL_OFFSET, 606, 0), goal_height);
    this->west_goal = new GoalZone(new Location(1734 +  Ball::BALL_TRIDIMENSIONAL_OFFSET, 476, 0), new Location(1774, 606, 0), goal_height);*/
}

Pitch::~Pitch()
{
    //dtor
}
/*
bool Pitch::IsGoalOnEastGoal(Ball* ball)
{
    return this->east_goal->IsBallInZone(ball);
}

bool Pitch::IsGoalOnWestGoal(Ball* ball)
{
    return this->west_goal->IsBallInZone(ball);
}
*/
