#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <exception>
#include <vector>
#include "view/sprite-sheet.h"
#include "view/sprites-provider.h"
#include "../shared/model/pitch.h"
#include "view/pitch-view.h"
#include "view/ball-view.h"
#include "view/mini-ball-view.h"
#include "view/player-view.h"
#include "view/keeper-view.h"
#include "view/timer-view.h"
#include "view/splash-view.h"
#include "view/score-view.h"
#include "view/match-time-view.h"
#include "view/mini-player-view.h"
#include "view/info-panel-view.h"
#include "view/game-statistics-view.h"
#include "view/camera.h"
#include "sound/game-music.h"
#include "sound/sound-manager.h"
#include "../shared/model/match.h"
#include "../shared/model/player.h"
#include "controller/player-controller.h"
#include "../shared/model/team.h"
#include "../shared/model/keeper.h"
#include "controller/team-controller.h"
#include "../shared/model/formation.h"
#include "../shared/configuration/configuration.h"
#include "controller/game-controller.h"
#include "controller/game-music-controller.h"
#include "client.h"
#include "../shared/model/user.h"
#include <map>

class GameController; //  forward declaration
class TeamController; //  forward declaration

class Configuration;

class Game
{
public:
    Game(Configuration* initial_configuration);
    virtual ~Game();
    void Start();
    void End();
    void Quit();
    bool IsCorrectlyInitialized();
    void LogIn();
    User* GetUser();

	static const int SCREEN_WIDTH = 800;
	static const int SCREEN_HEIGHT = 600;
	static const unsigned int PITCH_WIDTH = 1920;
	static const unsigned int PITCH_HEIGHT = 1158;
	static const int INFO_PANEL_HEIGHT = 78;

protected:

private:

    Configuration* initial_configuration;
    SDL_Window* window;
    SDL_Renderer* renderer;
    Match* match;
    Camera* camera;
    TimerView* timer_view;
    ScoreView* score_view;
    MatchTimeView* match_time_view;
    GameStatisticsView* game_statistics_view;
    User* user;
    Client* client;
    GameMusic* game_music;
    SoundManager* sound_manager;

	static const int FRAMES_PER_SECOND = 30;
    u_int STOP_LOOP_MILLISECONDS = 30;

    TeamController* team_controller;
    PlayerController* player_controller;
    GameController* game_controller;
    GameMusicController* music_controller;

    bool quit;
    bool correctly_initialized;

    void CreateModel(std::string serialized_model);
    void CreateViews();
    void CreateGameMusic();
    void CreateControllers();
    void DestroyModel();
    void DestroyViews();
    void DestroyGameMusic();
    void DestroyControllers();
    void InitSDL();
    void CloseSDL();
    void RenderViews();
    void RenderGameStatisticsView();
    void PlaySounds();
    void PlayGoalSound();
    bool MatchStateHasChanged(int last_match_state);

};

#endif // GAME_H
