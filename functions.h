#ifndef INC_SDL
#define INC_SDL
#include <SDL.h>
#include <SDL2/SDL_image.h>
#endif

#ifndef INC_IOSTREAM
#define INC_IOSTREAM
#include <iostream>
#endif

#ifndef INC_CTIME
#define INC_CTIME
#include <ctime>
#endif 

#ifndef INC_CIRCLE_H
#define INC_CIRCLE_H
#include "circle.h"
#endif

#ifndef INC_DATA_H
#define INC_DATA_H
#include "data.h"
#endif

#ifndef INC_BANNER_H
#define INC_BANNER_H
#include "banner.h"
#endif

#ifndef INC_PAGE_H
#define INC_PAGE_H
#include "page.h"
#endif

#ifndef INC_VECTOR
#define INC_VECTOR
#include <vector>
#include <algorithm>
#include <cmath>
#endif

using namespace std;

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Surface *tmp_surface;
extern SDL_Texture *background, *aim, *cross, *green, *blue, *black, *number[40], *text[40], *hint[5];
extern SDL_Event evt;
extern SDL_Point mouse_pos;

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int BANNER_HEIGHT;
extern const int COLUMN;
extern const int ROW;
extern const int COLUMN_WIDTH;
extern const int ROW_WIDTH;
extern const double OMEGA;

extern bool start, quit, ToNextLevel;
extern int CurrentCircle;
extern double angle, rotate_angle;
extern string path;
extern vector<pair<int, int> > wrong_message;

extern CIRCLE *circles[30];
extern BANNER *banner;

string operator + (const string &s, const int &n);

void Match25_INIT();
void LoadMedia();
void GenerateMap(int phase);
void Play();
void DrawLine(pair<int, int> A, pair<int, int> B, SDL_Texture *src);
void TheEnd();
void Match25_CLOSE();
void ClearMap();

template<typename T>
bool Not_In_Vec(vector<T> v, T element);
