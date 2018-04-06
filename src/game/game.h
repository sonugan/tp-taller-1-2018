#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <exception>
#include <vector>
#include "../common/sprite-sheet.h"
#include "../pitch/pitch.h"
#include "../pitch/pitch-view.h"
#include "../player/player.h"
#include "../player/player-view.h"
#include "../camera/camera.h"
#include "../match/match.h"
#include "../team/team.h"
#include "../team/formation.h"
#include <map>

class Game
{
    public:
        Game();
        virtual ~Game();
        void Start();
        void End();
        static const int SCREEN_WIDTH = 800;
        static const int SCREEN_HEIGHT = 600;
        static const unsigned int PITCH_WIDTH = 1920;
        static const unsigned int PITCH_HEIGHT = 1080;
    protected:

    private:

        SDL_Window* window;
        SDL_Renderer* renderer;
        Match* match;
        Player* selected_player;
        Camera* camera;
        static const int FRAMES_PER_SECOND = 200;
        std::map <unsigned int, PlayerView*> player_views_map;

        void CreateModel();
        void CreateViews();
        void DestroyModel();
        void DestroyViews();
        void InitSDL();
        void CloseSDL();
        void RenderViews();
        void MovePlayer(const Uint8 *keyboard_state_array);
        void MoveUnselectedPlayersToDefaultPositions();
        void ChangePlayerSelection(const Uint8 *keyboard_state_array);
        Uint8 GetSelectedKey(const Uint8* keyboard_state_array);
        bool UpKeySelected(const Uint8 *keyboard_state_array);
        bool RightKeySelected(const Uint8 *keyboard_state_array);
        bool LeftKeySelected(const Uint8 *keyboard_state_array);
        bool DownKeySelected(const Uint8 *keyboard_state_array);
        bool CKeySelected(const Uint8 *keyboard_state_array);
        Player* FindNextPlayerToSelect();

};

#endif // GAME_H
