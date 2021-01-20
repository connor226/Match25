#include "functions.h"
#include <iostream>

using namespace std;

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *number[30];

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;

char* operator + (const char* &s, const int &n){
	int value = n;
	char *ans = s, *tmp = "";
	while(value >= 1){
		tmp += ('0' + value % 10);
		value /= 10;
	}
	for(int i = tmp.size() - 1; i >= 0; i--){
		ans += tmp[i];
	}
	return ans;
}

void Match25_INIT(){
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	window = SDL_CreateWindow("Match25", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);	
}

void LoadMedia(){
	char *prefix = "num", *suffix = ".png";
	for(int i = 0; i < 26; i++){
		number[i] = SDL_CreateTextureFromSurface(renderer, IMG_Load(prefix + i + suffix));
	}
}
