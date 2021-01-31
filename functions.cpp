#ifndef INC_FUNCTIONS_H
#define INC_FUNCTIONS_H
#include "functions.h"
#endif

#define X first
#define Y second
#define PI 3.14159

using namespace std;

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *background, *aim, *cross, *green, *blue, *black, *number[40], *text[15];

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 700;
const int BANNER_HEIGHT = 100;
const int COLUMN = 8;
const int ROW = 5;
const int COLUMN_WIDTH = SCREEN_WIDTH / COLUMN;
const int ROW_WIDTH = (SCREEN_HEIGHT - BANNER_HEIGHT) / ROW;
const double OMEGA = 0.2;

bool start, quit;
int CurrentCircle;
double rotate_angle;

CIRCLE *circles[30];
BANNER *banner;

string operator + (const string &s, const int &n){
	int value = n;
	string tmp = "", ans = s;
	while(value >= 10){
		tmp += ('0' + value % 10);
		value /= 10;
	}
	tmp += ('0' + value);
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
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	quit = false;
}

void LoadMedia(){
	background = SDL_CreateTextureFromSurface(renderer, IMG_Load("img/art.png"));
	aim = SDL_CreateTextureFromSurface(renderer, IMG_Load("img/aim.png"));
	cross = SDL_CreateTextureFromSurface(renderer, IMG_Load("img/cross.png"));
	green = SDL_CreateTextureFromSurface(renderer, IMG_Load("img/green.png"));
	blue = SDL_CreateTextureFromSurface(renderer, IMG_Load("img/blue.png"));
	black = SDL_CreateTextureFromSurface(renderer, IMG_Load("img/banner.png"));
	string prefix = "img/num", suffix = ".png";
	for(int i = 0; i < 38; i++){
		string path = prefix + i + suffix;
		number[i] = SDL_CreateTextureFromSurface(renderer, IMG_Load(path.c_str()));
	}
	prefix = "img/text";
	for(int i = 0; i < 13; i++){
		string path = prefix + i + suffix;
		text[i] = SDL_CreateTextureFromSurface(renderer, IMG_Load(path.c_str()));
	}
}

void GenerateMap(int phase){
	for(int i = 0; i < 26; i++){
		if(phase == 1)  circles[i] = new CIRCLE(i);
		else  circles[i] = new CIRCLE((i + 1) / 2 + 25 * ((i + 1) % 2));
	}
	vector<int> vacancy;
	vector<pair<int, int> > chosen;
	srand(time(NULL));
	for(int i = 0; i < COLUMN * ROW; i++){
		vacancy.push_back(i);
	}
	for(int i = 1; i <= 25; i++){
		int pick = vacancy[rand() % vacancy.size()];
		chosen.push_back({((pick % COLUMN) * COLUMN_WIDTH + (rand() % (COLUMN_WIDTH - CIRCLE_SIZE))), (pick / COLUMN) * ROW_WIDTH + (rand() % (ROW_WIDTH - CIRCLE_SIZE))});
		vector<int> tmp;
		for(auto j:vacancy){
			if(j != pick){
				tmp.push_back(j);
			}
		}
		vacancy.clear();
		vacancy = tmp;
	}
	for(int i = 1; i <= 25; i++){
		int pick = 0;
		circles[i]->SetPos(chosen[pick].X, chosen[pick].Y);
		if(i > 1){
			for(int j = 1; j < chosen.size(); j++){
				circles[0]->SetPos(chosen[j].X,chosen[j].Y);
				if(circles[i-1]->dist(circles[0]) < circles[i-1]->dist(circles[i])){
					pick = j;
					circles[i]->SetPos(chosen[pick].X, chosen[pick].Y);
				}
			}
		}
		circles[i]->SetPos(chosen[pick].X, chosen[pick].Y);
		vector<pair<int, int> > tmp;
		for(int j = 0; j < chosen.size(); j++){
			if(j != pick)  tmp.push_back(chosen[j]);
		}
		chosen.clear();
		chosen = tmp;
	}
	banner = new BANNER();
}

void Play(){
	start = false;
	CurrentCircle = 1;
	wrong_time = 0;
	rotate_angle = 0;
	vector<pair<int, int> > wrong_message;
	while(!quit){
		SDL_Event evt;
		SDL_Point mouse_pos;
		while(SDL_PollEvent(&evt) != 0){
			if(evt.type == SDL_QUIT)  quit = true;
			else  if(evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_ESCAPE)  quit = true;
			else  if(evt.type == SDL_MOUSEBUTTONDOWN){
				SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
				if(!start && Mouse_On_Circle(mouse_pos, circles[CurrentCircle])){
					start = true;
					start_time = clock();
				}
			}
		}
		if(start){
			SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
			if(Mouse_On_Circle(mouse_pos, circles[CurrentCircle])){
				SDL_SetTextureAlphaMod(circles[CurrentCircle ++]->pic, 127);
				wrong_message.clear();
			}
			else{
				for(int i = CurrentCircle + 1; i < 26; i++){
					if(Mouse_On_Circle(mouse_pos, circles[i]) && Not_In_Vec(wrong_message, circles[i]->pos())){
						wrong_message.push_back(circles[i]->pos());
						++ wrong_time;
					}
				}
			}
			if(CurrentCircle == 26){
				end_time = clock();
				record.push_back({(end_time - start_time) / CLOCKS_PER_SEC, wrong_time});
				SDL_SetTextureAlphaMod(banner->button_pic, 255);
				break;
			}
		}
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, background, NULL, NULL);
		for(int i = 1; i <= 25; i++)  SDL_RenderCopy(renderer, circles[i]->pic, NULL, &circles[i]->quad);
		for(int i = 1; i < CurrentCircle - 1; i++){
			DrawLine(circles[i]->center(), circles[i+1]->center(), green);
		}
		if(start)  DrawLine({mouse_pos.x, mouse_pos.y}, circles[CurrentCircle - 1]->center(), blue);
		else{
			SDL_Rect tmp_rect;
			tmp_rect.w = tmp_rect.h = 125 + 25 * cos(rotate_angle * OMEGA);
			tmp_rect.x = circles[1]->pos().X - (tmp_rect.w - CIRCLE_SIZE) / 2;
			tmp_rect.y = circles[1]->pos().Y - (tmp_rect.h - CIRCLE_SIZE) / 2;
			SDL_RenderCopyEx(renderer, aim, NULL, &tmp_rect, rotate_angle, NULL, SDL_FLIP_NONE);
			rotate_angle += OMEGA;
		}
		for(auto i : wrong_message){
			SDL_Rect tmp_rect;
			tmp_rect.w = tmp_rect.h = CIRCLE_SIZE;
			tmp_rect.x = i.X;
			tmp_rect.y = i.Y;
			SDL_RenderCopy(renderer, cross, NULL, &tmp_rect);
		}
		banner->update();
		SDL_RenderPresent(renderer);
	}
	while(!quit){
		SDL_Event evt;
		SDL_Point mouse_pos;
		bool ToNextLevel = false;
		while(SDL_PollEvent(&evt) != 0){
			if(evt.type == SDL_QUIT)  quit = true;
			else  if(evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_ESCAPE)  quit = true;
			else  if(evt.type == SDL_MOUSEBUTTONDOWN){
				SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
				if(ButtonPressed(mouse_pos)){
					SDL_SetTextureAlphaMod(banner->button_pic, 127);
				}
			}
			else  if(evt.type == SDL_MOUSEBUTTONUP){
				SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
				SDL_SetTextureAlphaMod(banner->button_pic, 255);
				if(ButtonPressed(mouse_pos)){
					ToNextLevel = true;
				}
			}
		}
		if(ToNextLevel)  break;
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, background, NULL, NULL);
		for(int i = 1; i < CurrentCircle - 1; i++){
			DrawLine(circles[i]->center(), circles[i+1]->center(), green);
		}
		for(int i = 1; i <= 25; i++)  SDL_RenderCopy(renderer, circles[i]->pic, NULL, &circles[i]->quad);
		banner->update();
		SDL_RenderPresent(renderer);
	}
}

void DrawLine(pair<int, int> A, pair<int, int> B, SDL_Texture *src){
	if(A.X > B.X)  swap(A, B);
	else  if(A.X == B.X && A.Y < B.Y)  swap(A, B);
	int length = sqrt((A.X - B.X) * (A.X - B.X) + (A.Y - B.Y) * (A.Y - B.Y));
	double angle;
	if(A.X == B.X)  angle = 90;
	else angle = atan2((A.Y - B.Y), (A.X - B.X)) * 180 / PI;
	SDL_Rect quad;
	quad.w = length;
	quad.h = 3;
	quad.x = B.X;
	quad.y = B.Y;
	SDL_Point P;
	P.x = 0, P.y = 0;
	SDL_RenderCopyEx(renderer, src, NULL, &quad, angle, &P, SDL_FLIP_NONE);
}

void TheEnd(){
	
}

void Match25_CLOSE(){
	SDL_DestroyTexture(background);
	background = NULL;
	SDL_DestroyTexture(aim);
	aim = NULL;
	SDL_DestroyTexture(cross);
	cross = NULL;
	SDL_DestroyTexture(green);
	green = NULL;
	SDL_DestroyTexture(blue);
	blue = NULL;
	SDL_DestroyTexture(black); 
	black = NULL;
	for(int i = 0; i < 38; i++){
		SDL_DestroyTexture(number[i]);
		number[i] = NULL;
	}
	for(int i = 0; i < 13; i++){
		SDL_DestroyTexture(text[i]);
		text[i] = NULL;
	}
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	SDL_DestroyWindow(window);
	window = NULL;
	data.clear();
	record.clear();
	IMG_Quit();
	SDL_Quit();
}

void ClearMap(){
	for(int i = 0; i < 26; i++){
		SDL_SetTextureAlphaMod(circles[i]->pic, 255);
		delete circles[i];
	}
	delete banner;
}

template <typename T>
bool Not_In_Vec(vector<T> v, T element){
	for(auto i:v){
		if(i == element)  return false;
	}
	return true;
}
