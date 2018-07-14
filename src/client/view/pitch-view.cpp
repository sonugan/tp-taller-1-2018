#include "pitch-view.h"
#include "../../shared/logger.h"

PitchView::PitchView(Pitch* pitch)
{
    this->pitch = pitch;

    SDL_Rect* sprite1 = new SDL_Rect();
    sprite1->x = 0;
    sprite1->y = 0;
    sprite1->w = 800;
    sprite1->h = 600;

    std::vector<SDL_Rect*> clips;
    clips.push_back(sprite1);

    animations.push_back(new Animation("pitch", clips));
    current_animation_index = 0;
    
    SDL_Rect* goal_zone_sprite_1 = new SDL_Rect();
    goal_zone_sprite_1->x = 0;
    goal_zone_sprite_1->y = 0;
    goal_zone_sprite_1->w = 50;
    goal_zone_sprite_1->h = 150;
    std::vector<SDL_Rect*> goal_zone_clips;
    goal_zone_clips.push_back(goal_zone_sprite_1);

    animations.push_back(new Animation("goal_zone", goal_zone_clips));

	this->sprite_sheet = SpritesProvider::GetDefaultSheet(PITCH);
	this->goal_zone_sheet = SpritesProvider::GetDefaultSheet(GOAL_ZONE);
}

PitchView::~PitchView()
{
    Logger::getInstance()->debug("DESTRUYENDO LA VISTA DEL CAMPO");

    for (unsigned int i = 0; i < animations.size(); i++) {
        delete (animations[i]);
    }
}

void PitchView::Render(int x_camera, int y_camera, int max_x, int max_y)
{
    SDL_Rect* current_clip = this->animations[current_animation_index]->NextClip();
    current_clip->x = x_camera;
    current_clip->y = y_camera;
    sprite_sheet->Render( 0, 0, current_clip );
    
    int goal_zone_y_offset = 10;
    
    int west_goal_zone_x = this->pitch->GetWestGoalZone()->GetTopLeftCorner()->GetX() - x_camera -1;
    int west_goal_zone_y = this->pitch->GetWestGoalZone()->GetTopLeftCorner()->GetY() - y_camera - goal_zone_y_offset;
    
    goal_zone_sheet->Render(west_goal_zone_x, west_goal_zone_y, animations[1]->NextClip(), (west_goal_zone_x < 1000)? 180 : 0);

    int east_goal_zone_x = this->pitch->GetEastGoalZone()->GetTopLeftCorner()->GetX() - x_camera -14;
    int east_goal_zone_y = this->pitch->GetEastGoalZone()->GetTopLeftCorner()->GetY() - y_camera - goal_zone_y_offset;
    
    goal_zone_sheet->Render(east_goal_zone_x, east_goal_zone_y, animations[1]->NextClip(), (east_goal_zone_x < 1000)? 0 : 180);

}
