#ifndef INC_SDL
#define INC_SDL
#include <SDL.h>
#include <SDL2/SDL_image.h>
#endif

#ifndef INC_UTILITY
#define INC_UTILITY
#include <utility>
#include <cmath>
#endif

using namespace std;

extern const int CIRCLE_SIZE;

class CIRCLE{
	public:
		CIRCLE(int num);
		void SetPos(int X, int Y);
		pair<int, int> pos();
		pair<int, int> center();
		double dist(CIRCLE *c);
		SDL_Texture *pic;
		SDL_Rect quad;
		
	private:
		
};

bool Mouse_On_Circle(SDL_Point p, CIRCLE *c);
