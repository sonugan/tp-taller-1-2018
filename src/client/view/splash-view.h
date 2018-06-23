/*
 * splash-view.h
 *
 *  Created on: Jun 22, 2018
 *      Author: swandelow
 */

#ifndef SRC_CLIENT_VIEW_SPLASH_VIEW_H_
#define SRC_CLIENT_VIEW_SPLASH_VIEW_H_

#include "abstract-view.h"
#include "../../shared/model/match-state.h"
#include "sprites-provider.h"

class SplashView : public AbstractView
{
public:
	SplashView(MatchState* match_state);
	virtual ~SplashView();
	void Render(int x_camera, int y_camera, int max_x, int max_y);
private:
	MatchState* match_state = NULL;
};

#endif /* SRC_CLIENT_VIEW_SPLASH_VIEW_H_ */
