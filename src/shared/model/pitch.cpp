#include "pitch.h"
#include "ball.h"

Pitch::Pitch(Team* team_a, Team* team_b)
{
    int goal_height = 60;
    //Creando arcos: Resto el tamaño de la pelota para que sea gol "cuando pase completa" ("tiro para atras" el area de gol)
    this->east_goal = new GoalZone(team_a, new Location(145, 554, 0), new Location(185 - Ball::BALL_TRIDIMENSIONAL_OFFSET, 684, goal_height));
    this->west_goal = new GoalZone(team_b, new Location(1734 +  Ball::BALL_TRIDIMENSIONAL_OFFSET, 554, 0), new Location(1774, 684, goal_height));

    //Creando zonas de lateral
    int throw_in_height = 150;
    throw_in_zones[0] = new ThrowInZone(new Location(186, 78, 0), new Location(1734, 99, throw_in_height));
    throw_in_zones[1] = new ThrowInZone(new Location(186, 1139, 0), new Location(1734, 1158, throw_in_height));

    //Creando zonas de fin de linea (saque de arco)
    end_line_zones[0] = new EndLineZone(team_a, new Location(0, 100, 0), new Location(185 - Ball::BALL_TRIDIMENSIONAL_OFFSET, 550, goal_height + 4));
    end_line_zones[1] = new EndLineZone(team_a, new Location(0, 100, goal_height + 4), new Location(185 - Ball::BALL_TRIDIMENSIONAL_OFFSET, 1138, throw_in_height));
    end_line_zones[2] = new EndLineZone(team_a, new Location(0, 688, 0), new Location(185 - Ball::BALL_TRIDIMENSIONAL_OFFSET, 1138, goal_height + 4));

    /*end_line_zones[3] = new EndLineZone(team_b, new Location(186, 1139, 0), new Location(1734, 1158, throw_in_height));
    end_line_zones[4] = new EndLineZone(team_b, new Location(186, 1139, 0), new Location(1734, 1158, throw_in_height));
    end_line_zones[5] = new EndLineZone(team_b, new Location(186, 1139, 0), new Location(1734, 1158, throw_in_height));*/
}

Pitch::~Pitch()
{
    delete this->east_goal;
    delete this->west_goal;

    delete this->throw_in_zones[0];
    delete this->throw_in_zones[1];

    for (int i = 0; i <= 5; i++)
    {
        delete this->end_line_zones[i];
    }
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

Team* Pitch::BallTouchingEndLineZone(Ball* ball)
{
    for (int i = 0; i <= 2; i++)
    {
        if (this->end_line_zones[i]->IsTouching(ball))
        {
            return this->end_line_zones[i]->GetTeam();
        }
    }

    return NULL;
}
