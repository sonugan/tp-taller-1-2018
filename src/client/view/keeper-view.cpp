#include "keeper-view.h"
#include "../../shared/logger.h"

KeeperView::KeeperView(Keeper* keeper) // @suppress("Class members should be properly initialized")
{
	Logger::getInstance()->debug("CREANDO KEEPERVIEW");
    this->width = 62;
    this->height = 62;

    this->frame = 0;
    this->keeper = keeper;

    std::vector<SDL_Rect*> run_clips;

    //Run sprites
    SDL_Rect* run_sprite_1 = new SDL_Rect();
    run_sprite_1->x = 0;
    run_sprite_1->y = 64;
    run_sprite_1->w = this->width;
    run_sprite_1->h = this->height;
    run_clips.push_back(run_sprite_1);

    SDL_Rect* run_sprite_2 = new SDL_Rect();
    run_sprite_2->x = 64;
    run_sprite_2->y = 64;
    run_sprite_2->w = this->width;
    run_sprite_2->h = this->height;
    run_clips.push_back(run_sprite_2);

    SDL_Rect* run_sprite_3 = new SDL_Rect();
    run_sprite_3->x = 128;
    run_sprite_3->y = 64;
    run_sprite_3->w = this->width;
    run_sprite_3->h = this->height;
    run_clips.push_back(run_sprite_3);

    SDL_Rect* run_sprite_4 = new SDL_Rect();
    run_sprite_4->x = 192;
    run_sprite_4->y = 64;
    run_sprite_4->w = this->width;
    run_sprite_4->h = this->height;
    run_clips.push_back(run_sprite_4);

    animations.push_back(new Animation("run", run_clips, FRAMES_PER_EVENT));

    std::vector<SDL_Rect*> still_clips;

    //Still sprites
    SDL_Rect* still_sprite_1 = new SDL_Rect();
    still_sprite_1->x = 0;
    still_sprite_1->y = 1;
    still_sprite_1->w = this->width;
    still_sprite_1->h = this->height;
    still_clips.push_back(still_sprite_1);

    SDL_Rect* still_sprite_2 = new SDL_Rect();
    still_sprite_2->x = 64;
    still_sprite_2->y = 1;
    still_sprite_2->w = this->width;
    still_sprite_2->h = this->height;
    still_clips.push_back(still_sprite_2);

    SDL_Rect* still_sprite_3 = new SDL_Rect();
    still_sprite_3->x = 128;
    still_sprite_3->y = 1;
    still_sprite_3->w = this->width;
    still_sprite_3->h = this->height;
    still_clips.push_back(still_sprite_3);

    SDL_Rect* still_sprite_4 = new SDL_Rect();
    still_sprite_4->x = 192;
    still_sprite_4->y = 1;
    still_sprite_4->w = this->width;
    still_sprite_4->h = this->height;
    still_clips.push_back(still_sprite_4);

    animations.push_back(new Animation("still", still_clips, FRAMES_PER_EVENT));

    std::vector<SDL_Rect*> kick_clips;

    // Kick sprites
//    SDL_Rect* kick_sprite_1 = new SDL_Rect();
//    kick_sprite_1->x = 0;
//    kick_sprite_1->y = 128;
//    kick_sprite_1->w = this->width;
//    kick_sprite_1->h = this->height;
//    kick_clips.push_back(kick_sprite_1);
//
//    SDL_Rect* kick_sprite_2 = new SDL_Rect();
//    kick_sprite_2->x = 64;
//    kick_sprite_2->y = 128;
//    kick_sprite_2->w = this->width;
//    kick_sprite_2->h = this->height;
//    kick_clips.push_back(kick_sprite_2);
//
//    SDL_Rect* kick_sprite_3 = new SDL_Rect();
//    kick_sprite_3->x = 128;
//    kick_sprite_3->y = 128;
//    kick_sprite_3->w = this->width;
//    kick_sprite_3->h = this->height;
//    kick_clips.push_back(kick_sprite_3);

    SDL_Rect* kick_sprite_4 = new SDL_Rect();
    kick_sprite_4->x = 192;
    kick_sprite_4->y = 128;
    kick_sprite_4->w = this->width;
    kick_sprite_4->h = this->height;
    kick_clips.push_back(kick_sprite_4);

    animations.push_back(new Animation("kick", kick_clips, FRAMES_PER_EVENT));

    std::vector<SDL_Rect*> jump_clips;

    // Recovering ball sprites
    SDL_Rect* recover_sprite_1 = new SDL_Rect();
    recover_sprite_1->x = 0;
    recover_sprite_1->y = 192;
    recover_sprite_1->w = this->width;
    recover_sprite_1->h = this->height;
    jump_clips.push_back(recover_sprite_1);

    SDL_Rect* recover_sprite_2 = new SDL_Rect();
    recover_sprite_2->x = 64;
    recover_sprite_2->y = 192;
    recover_sprite_2->w = this->width;
    recover_sprite_2->h = this->height;
    jump_clips.push_back(recover_sprite_2);

    SDL_Rect* recover_sprite_3 = new SDL_Rect();
    recover_sprite_3->x = 128;
    recover_sprite_3->y = 192;
    recover_sprite_3->w = this->width;
    recover_sprite_3->h = this->height;
    jump_clips.push_back(recover_sprite_3);

    SDL_Rect* recover_sprite_4 = new SDL_Rect();
    recover_sprite_4->x = 192;
    recover_sprite_4->y = 192;
    recover_sprite_4->w = this->width;
    recover_sprite_4->h = this->height;
    jump_clips.push_back(recover_sprite_4);

    SDL_Rect* recover_sprite_5 = new SDL_Rect();
    recover_sprite_5->x = 0;
    recover_sprite_5->y = 256;
    recover_sprite_5->w = this->width;
    recover_sprite_5->h = this->height;
    jump_clips.push_back(recover_sprite_5);

    SDL_Rect* recover_sprite_6 = new SDL_Rect();
    recover_sprite_6->x = 64;
    recover_sprite_6->y = 256;
    recover_sprite_6->w = this->width;
    recover_sprite_6->h = this->height;
    jump_clips.push_back(recover_sprite_6);

    SDL_Rect* recover_sprite_7 = new SDL_Rect();
    recover_sprite_7->x = 128;
    recover_sprite_7->y = 256;
    recover_sprite_7->w = this->width;
    recover_sprite_7->h = this->height;
    jump_clips.push_back(recover_sprite_7);
    
    SDL_Rect* recover_sprite_8 = new SDL_Rect();
    recover_sprite_8->x = 192;
    recover_sprite_8->y = 256;
    recover_sprite_8->w = this->width;
    recover_sprite_8->h = this->height;
    jump_clips.push_back(recover_sprite_8);
    
    SDL_Rect* recover_sprite_9 = new SDL_Rect();
    recover_sprite_9->x = 0;
    recover_sprite_9->y = 1;
    recover_sprite_9->w = this->width;
    recover_sprite_9->h = this->height;
    still_clips.push_back(recover_sprite_9);

    SDL_Rect* recover_sprite_10 = new SDL_Rect();
    recover_sprite_10->x = 64;
    recover_sprite_10->y = 1;
    recover_sprite_10->w = this->width;
    recover_sprite_10->h = this->height;
    still_clips.push_back(recover_sprite_10);

    animations.push_back(new Animation("jump", jump_clips, FRAMES_PER_EVENT));

    current_animation_index = 0;

    Location* current_location = this->keeper->GetLocation();
    previous_location = new Location(current_location->GetX(), current_location->GetY(), current_location->GetZ());
 
    if (this->keeper->PlaysForTeamA()) {
		this->sprite_sheet = SpritesProvider::GetDefaultSheet(TEAM_A_KEEPER);
    } else {
    	this->sprite_sheet = SpritesProvider::GetDefaultSheet(TEAM_B_KEEPER);
    }

}

KeeperView::~KeeperView() {
    Logger::getInstance()->debug("DESTRUYENDO KEEPERVIEW");

    //TODO: delete clips in animation destructor
    for (unsigned int i = 0; i < animations.size(); i++) {
        delete (animations[i]);
    }
    delete previous_location;
}

void KeeperView::GetKeeperAngle()
{
	if (this->keeper->IsStill() || this->keeper->IsKicking()) {
		angle = GetLookAtBallAngle();
	} else if (this->keeper->IsMovingUp()) {
		angle = 0;
	} else if (this->keeper->IsJumpingUp()) {
		angle = 270;
	} else if (this->keeper->IsJumpingDown()) {
		angle = 90;
	} else {
		angle = 180;
	}
}

double KeeperView::GetLookAtBallAngle() {
	Location* keeper_location = this->keeper->GetLocation();
	Location* ball_location = this->keeper->GetTeam()->GetMatch()->GetBall()->GetLocation();
	
	if (keeper_location != NULL && ball_location != NULL) {
		double new_angle = atan2(keeper_location->GetY() - ball_location->GetY(), keeper_location->GetX() - ball_location->GetX());
		new_angle = (new_angle * 180 / 3.1416) - 90;
		return new_angle;
	}
			
	return 0;
}

void KeeperView::Render(int x_camera, int y_camera, int max_x, int max_y)
{
    this->GetKeeperAngle();
    int animation_index = current_animation_index;

	if (this->keeper->IsKicking()) {
		current_animation_index = KICKING_ANIMATION_INDEX;
	} else if (this->keeper->IsJumpingUp() || this->keeper->IsJumpingDown()) {
		current_animation_index = JUMPING_ANIMATION_INDEX;
	} else if(this->keeper->IsStill()) {
		current_animation_index = STILL_ANIMATION_INDEX;
	} else if(this->keeper->IsMovingUp() || this->keeper->IsMovingDown()){
		current_animation_index = RUN_ANIMATION_INDEX;
	} else {
		current_animation_index = STILL_ANIMATION_INDEX;
	}
	if(animation_index != current_animation_index)
	{
		animations[current_animation_index]->Restart();
	}

    SDL_Rect* current_clip = animations[current_animation_index]->NextClip();
    int x, y;

    this->previous_location->UpdateX(keeper->GetLocation()->GetX());
    this->previous_location->UpdateY(keeper->GetLocation()->GetY());

    x = keeper->GetLocation()->GetX() - x_camera;
    y = keeper->GetLocation()->GetY() - y_camera;
    
    SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE;
    if (keeper->IsJumpingUp() && keeper->PlaysOnWestSide()) {
    	flip = SDL_RendererFlip::SDL_FLIP_VERTICAL;
    } else if (keeper->IsJumpingDown() && !keeper->PlaysOnWestSide()) {
    	flip = SDL_RendererFlip::SDL_FLIP_VERTICAL;
    }

    sprite_sheet->Render( x - (SPRITE_WIDTH / 2), y - (SPRITE_HEIGHT / 2), current_clip, this->angle, NULL, flip);

}



Location* KeeperView::GetLocation()
{
    return this->keeper->GetLocation();
}

void KeeperView::SetAnimation(Animation* animation)
{

}

bool KeeperView::IsStill()
{
    Location* location = this->keeper->GetLocation();
    return location->GetX() == previous_location->GetX() &&
        location->GetY() == previous_location->GetY();
}
