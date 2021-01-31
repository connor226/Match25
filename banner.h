#ifndef INC_DATA_H
#define INC_DATA_H
#include "data.h"
#endif

#ifndef INC_SDL
#define INC_SDL
#include <SDL.h>
#include <SDL2/SDL_image.h>
#endif

extern const int DIGIT_WIDHT;
extern const int WRONG_WIDTH;
extern const int BUTTON_WIDTH;

class BANNER{
	public:
		BANNER();
		int timer_x, wrong_time_x, button_x;
		SDL_Texture *background, *timer_pic[6], *wrong_time_pic[6], *button_pic;
		SDL_Rect background_rect, timer_rect[6], wrong_time_rect[6], button_rect;
		void update();
};

bool ButtonPressed(SDL_Point p);
