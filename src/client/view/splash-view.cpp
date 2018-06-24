/*
 * splash-view.cpp
 *
 *  Created on: Jun 22, 2018
 *      Author: swandelow
 */

#include "splash-view.h"

SplashView::SplashView(MatchState* match_state)
{
	this->match_state = match_state;

	SDL_Rect* playing_1 = new SDL_Rect();
    playing_1->x = 0;
    playing_1->y = 0;
    playing_1->w = 277;
    playing_1->h = 88;

    std::vector<SDL_Rect*> playing_clips;
    playing_clips.push_back(playing_1);

    animations.push_back(new Animation("playing", playing_clips));

    SDL_Rect* kick_off_1 = new SDL_Rect();
    kick_off_1->x = 0;
    kick_off_1->y = 88;
    kick_off_1->w = 277;
    kick_off_1->h = 88;

    std::vector<SDL_Rect*> kick_off_clips;
    kick_off_clips.push_back(kick_off_1);

    animations.push_back(new Animation("kick_off", kick_off_clips));

    SDL_Rect* time_up_1 = new SDL_Rect();
    time_up_1->x = 0;
    time_up_1->y = 176;
    time_up_1->w = 277;
    time_up_1->h = 88;

    std::vector<SDL_Rect*> time_up_clips;
    time_up_clips.push_back(time_up_1);

    animations.push_back(new Animation("time_up", time_up_clips));

    SDL_Rect* goal_1 = new SDL_Rect();
    goal_1->x = 0;
    goal_1->y = 264;
    goal_1->w = 277;
    goal_1->h = 88;

    std::vector<SDL_Rect*> goal_clips;
    goal_clips.push_back(goal_1);

    animations.push_back(new Animation("goal", goal_clips));

    SDL_Rect* goal_kick_1 = new SDL_Rect();
    goal_kick_1->x = 0;
    goal_kick_1->y = 352;
    goal_kick_1->w = 277;
    goal_kick_1->h = 88;

    std::vector<SDL_Rect*> goal_kick_clips;
    goal_kick_clips.push_back(goal_kick_1);

    animations.push_back(new Animation("goal_kick", goal_kick_clips));

    /* En vez de mostrar splash de game over, muestro pantalla de estadisticas
    SDL_Rect* game_over_1 = new SDL_Rect();
    game_over_1->x = 0;
    game_over_1->y = 440;
    game_over_1->w = 277;
    game_over_1->h = 88;

    std::vector<SDL_Rect*> game_over_clips;
    game_over_clips.push_back(game_over_1);

    animations.push_back(new Animation("game_over", game_over_clips));
    */

    current_animation_index = 0;

	this->sprite_sheet = SpritesProvider::GetDefaultSheet(SPLASH);
}

SplashView::~SplashView()
{
	// TODO Auto-generated destructor stub
}

void SplashView::Render(int x_camera, int y_camera, int max_x, int max_y) {

	MATCH_STATE_TYPE state = this->match_state->GetType();
	if (state == MATCH_STATE_TYPE::PLAYING) {
		current_animation_index = 0;
	} else if (state == MATCH_STATE_TYPE::KICKOFF) {
		current_animation_index = 1;
	} else if (state == MATCH_STATE_TYPE::TIME_UP) {
		current_animation_index = 2;
	} else if (state == MATCH_STATE_TYPE::GOAL) {
		current_animation_index = 3;
	} else if (state == MATCH_STATE_TYPE::GOAL_KICK) {
		current_animation_index = 4;
	/*} else if (state == MATCH_STATE_TYPE::FINISHED) {
		current_animation_index = 5;*/
	}

	SDL_Rect* current_clip = this->animations[current_animation_index]->NextClip();

	int x = (max_x / 2) - (277 / 2);
	sprite_sheet->Render(x, 200, current_clip);
}
