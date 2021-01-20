#include <SDL.h>
#include <SDL2/SDL_image.h>

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Texture *number[30];
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT; 

char* operator + (const char* &s, const int &n);

void Match25_INIT();
void LoadMedia();
