#ifndef INC_BANNER_H
#define INC_BANNER_H
#include "banner.h"
#endif

#ifndef INC_FUNCTIONS_H
#define INC_FUNCTIONS_H
#include "functions.h"
#endif

const int DIGIT_WIDTH = 75;
const int WRONG_WIDTH = 200;
const int BUTTON_WIDTH = 200;

BANNER::BANNER(){
	timer_x = 0;
	wrong_time_x = DIGIT_WIDTH * 6;
	button_x = SCREEN_WIDTH - BUTTON_WIDTH;
	background = black;
	timer_pic[2] = text[10];
	wrong_time_pic[0] = text[11];
	wrong_time_pic[1] = text[10];
	button_pic = text[12];
	background_rect.w = SCREEN_WIDTH;
	background_rect.h = BANNER_HEIGHT;
	background_rect.x = 0;
	background_rect.y = SCREEN_HEIGHT - BANNER_HEIGHT;
	for(int i = 0; i < 6; i++){
		timer_rect[i].w = DIGIT_WIDTH;
		timer_rect[i].h = BANNER_HEIGHT;
		timer_rect[i].x = DIGIT_WIDTH * i;
		timer_rect[i].y = SCREEN_HEIGHT - BANNER_HEIGHT;
	}
	for(int i = 0; i < 6; i++){
		if(i == 0){
			wrong_time_rect[i].w = WRONG_WIDTH;
			wrong_time_rect[i].x = DIGIT_WIDTH * 6;
		}
		else{
			wrong_time_rect[i].w = DIGIT_WIDTH;
			wrong_time_rect[i].x = WRONG_WIDTH + DIGIT_WIDTH * (i + 5);
		}
		wrong_time_rect[i].h = BANNER_HEIGHT;
		wrong_time_rect[i].y = SCREEN_HEIGHT - BANNER_HEIGHT;
	}
	button_rect.w = BUTTON_WIDTH;
	button_rect.h = BANNER_HEIGHT;
	button_rect.x = SCREEN_WIDTH - BUTTON_WIDTH;
	button_rect.y = SCREEN_HEIGHT - BANNER_HEIGHT;
	SDL_SetTextureAlphaMod(button_pic, 127);
}

void BANNER::update(){
	SDL_RenderCopy(renderer, background, NULL, &background_rect);
	if(!start){
		timer_pic[0] = timer_pic[1] = timer_pic[3] = timer_pic[4] = wrong_time_pic[2] = text[0];
	}
	else{
		int used_time;
		if(CurrentCircle == 26)  used_time = (end_time - start_time) / CLOCKS_PER_SEC;
		else  used_time = (clock() - start_time) / CLOCKS_PER_SEC;
		for(int i = 4; i >= 0; i--){
			if(i != 2){
				if(i == 4)  timer_pic[i] = text[(used_time % 60) % 10];
				if(i == 3)  timer_pic[i] = text[(used_time % 60) / 10];
				if(i == 1)  timer_pic[i] = text[(used_time / 60) % 10];
				if(i == 0)  timer_pic[i] = text[(used_time / 60) / 10];
			}
		}
	}
	for(int i = 0; i < 5; i++)  SDL_RenderCopy(renderer, timer_pic[i], NULL, &timer_rect[i]);
	wrong_time_pic[2] = text[wrong_time / 100];
	if(wrong_time / 100 > 0){
		wrong_time_pic[3] = text[(wrong_time / 10) % 10];
		wrong_time_pic[4] = text[wrong_time % 10];
	}
	else{
		wrong_time_pic[2] = text[wrong_time / 10];
		if(wrong_time / 10 > 0)  wrong_time_pic[3] = text[wrong_time % 10];
		else  wrong_time_pic[2] = text[wrong_time];
	}
	for(int i = 0; i < 5; i++){
		if(i == 3 && wrong_time / 10)  SDL_RenderCopy(renderer, wrong_time_pic[i], NULL, &wrong_time_rect[i]);
		else  if(i == 4 && wrong_time / 100)  SDL_RenderCopy(renderer, wrong_time_pic[i], NULL, &wrong_time_rect[i]);
		else  if(i < 3)  SDL_RenderCopy(renderer, wrong_time_pic[i], NULL, &wrong_time_rect[i]);
	}
	SDL_RenderCopy(renderer, button_pic, NULL, &button_rect);
}

bool ButtonPressed(SDL_Point p){
	return (p.x > SCREEN_WIDTH - BUTTON_WIDTH && p.x < SCREEN_WIDTH && p.y > SCREEN_HEIGHT - BANNER_HEIGHT && p.y < SCREEN_HEIGHT);
}
