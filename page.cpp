#ifndef INC_FUNCTIONS_H
#define INC_FUNCTIONS_H
#include "functions.h"
#endif

#ifndef INC_PAGE_H
#define INC_PAGE_H
#include "page.h"
#endif

SDL_Texture *page, *cursor, *MIN, *SEC;
SDL_Rect textbox, button, hint_rect[5];
vector<SDL_Texture*> input_pic, end_hint[2];
vector<SDL_Rect> input_rect, end_rect[2];

int cursor_pos;

const int TEXTBOX_WIDTH = 900;
const int TEXTBOX_HEIGHT = 100;
/*
void Login(){
	ToNextLevel = false;
	tmp_surface = IMG_Load("img/start_page.png");
	page = SDL_CreateTextureFromSurface(renderer, tmp_surface);
	tmp_surface = IMG_Load("img/pos.png");
	cursor = SDL_CreateTextureFromSurface(renderer, tmp_surface);
	SDL_FreeSurface(tmp_surface);
	textbox.w = TEXTBOX_WIDTH;
	textbox.h = TEXTBOX_HEIGHT;
	textbox.x = (SCREEN_WIDTH - TEXTBOX_WIDTH) / 2;;
	textbox.y = (SCREEN_HEIGHT - TEXTBOX_HEIGHT) / 2;
	button.w = BUTTON_WIDTH;
	button.h = BANNER_HEIGHT;
	button.x = SCREEN_WIDTH - BUTTON_WIDTH;
	button.y = SCREEN_HEIGHT - BANNER_HEIGHT;
	hint_rect[3].w = SCREEN_WIDTH;
	hint_rect[3].h = BANNER_HEIGHT;
	hint_rect[3].x = 0;
	hint_rect[3].y = SCREEN_HEIGHT - BANNER_HEIGHT;
	while(!quit){
		while(!SDL_PollEvent(&evt) != 0){
			if(evt.type == SDL_QUIT)  quit = true;
			else  if(evt.type == SDL_MOUSEBUTTONDOWN){
				SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
				if(ButtonPressed(mouse_pos)){
					SDL_SetTextureAlphaMod(text[12], 127);
				}
			}
			else  if(evt.type == SDL_MOUSEBUTTONUP){
				SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
				SDL_SetTextureAlphaMod(text[12], 255);
				if(ButtonPressed(mouse_pos)){
					ToNextLevel = true;
				}
			}
			else  if(evt.type == SDL_KEYDOWN){
				switch(evt.key.keysym.sym){
					case SDLK_ESCAPE:{
						quit = true;
						break;
					}
					case SDLK_RETURN:{
						if(!input_pic.empty())  ToNextLevel = true;
						break;
					}
					case SDLK_RIGHT:{
						if(cursor_pos < input_pic.size())  ++ cursor_pos;
						break;
					}
					case SDLK_LEFT:{
						if(cursor_pos > 0)  -- cursor_pos;
						break;
					}
					case SDLK_BACKSPACE:{
						
						break;
					}
					case SDLK_DELETE:{
						
						break;
					}
				}
			}
		}
		if(ToNextLevel)  break;
		SDL_RenderCopy(renderer, page, NULL, NULL);
		SDL_RenderCopy(renderer, black, NULL, &textbox);
		SDL_RenderCopy(renderer, hint[3], NULL, &hint_rect[3]);
		SDL_RenderCopy(renderer, text[12], NULL, &button);
	}
	SDL_DestroyTexture(page);
	page = NULL;
	SDL_DestroyTexture(cursor);
	cursor = NULL;
}
*/
void TheEnd(){
	tmp_surface = IMG_Load("img/end_page.png");
	page = SDL_CreateTextureFromSurface(renderer, tmp_surface);
	tmp_surface = IMG_Load("img/min.png");
	MIN = SDL_CreateTextureFromSurface(renderer, tmp_surface);
	tmp_surface = IMG_Load("img/sec.png");
	SEC = SDL_CreateTextureFromSurface(renderer, tmp_surface);
	SDL_FreeSurface(tmp_surface);
	hint_rect[0].w = SCREEN_WIDTH;
	hint_rect[0].h = BANNER_HEIGHT;
	hint_rect[0].x = 0;
	hint_rect[0].y = BANNER_HEIGHT;
	hint_rect[1].w = 400;
	hint_rect[1].h = BANNER_HEIGHT;
	hint_rect[1].x = 0;
	hint_rect[1].y = BANNER_HEIGHT * 2;
	hint_rect[2].w = 400;
	hint_rect[2].h = BANNER_HEIGHT;
	hint_rect[2].x = 0;
	hint_rect[2].y = BANNER_HEIGHT * 4;
	for(int i = 0; i < 2; i++){
		end_hint[i].push_back(text[(int(record[i].first) / 60) / 10]);
		end_hint[i].push_back(text[(int(record[i].first) / 60) % 10]);
		end_hint[i].push_back(MIN);
		end_hint[i].push_back(text[(int(record[i].first) % 60) / 10]);
		end_hint[i].push_back(text[(int(record[i].first) % 60) % 10]);
		end_hint[i].push_back(SEC);
		end_hint[i].push_back(text[11]);
		end_hint[i].push_back(text[10]);
		if(record[i].second > 99)  end_hint[i].push_back(text[record[i].second / 100]);
		if(record[i].second > 9)  end_hint[i].push_back(text[(record[i].second / 10) % 10]);
		end_hint[i].push_back(text[record[i].second % 10]);
		SDL_Rect tmp_rect;
		tmp_rect.h = BANNER_HEIGHT;
		if(i == 0)  tmp_rect.y = BANNER_HEIGHT * 3;
		else  tmp_rect.y = BANNER_HEIGHT * 5;
		for(int j = 0; j < 11; j++){
			if(j == 0)  tmp_rect.x = 100;
			else  if(j == 6)  tmp_rect.x = 700;
			else  tmp_rect.x = tmp_rect.x + tmp_rect.w;
			if(j == 2 || j == 5)  tmp_rect.w = 100;
			else  if(j == 6)  tmp_rect.w = 200;
			else  tmp_rect.w = 75;
			end_rect[i].push_back(tmp_rect);
		}
	}
	while(!quit){
		while(SDL_PollEvent(&evt) != 0){
			if(evt.type == SDL_QUIT)  quit = true;
			else  if(evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_ESCAPE)  quit = true;
		}
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, page, NULL, NULL);
		for(int i = 0; i < 3; i++){
			SDL_RenderCopy(renderer, hint[i], NULL, &hint_rect[i]);
		}
		for(int i = 0; i < 2; i++){
			for(int j = 0; j < end_hint[i].size(); j++){
				SDL_RenderCopy(renderer, end_hint[i][j], NULL, &end_rect[i][j]);
			}
		}
		SDL_RenderPresent(renderer);
	}
	for(int i = 0; i < 2; i++){
		end_hint[i].clear();
		end_rect[i].clear();
	}
	SDL_DestroyTexture(page);
	page = NULL;
	SDL_DestroyTexture(MIN);
	MIN = NULL;
	SDL_DestroyTexture(SEC);
	SEC = NULL;
}