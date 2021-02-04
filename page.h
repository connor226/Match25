#ifndef INC_SDL_H
#define INC_SDL_H
#include <SDL.h>
#include <SDL2/SDL_image.h>
#endif

extern SDL_Texture *page, *cursor, *MIN, *SEC;
extern SDL_Rect textbox, button, hint_rect[5];
extern vector<SDL_Texture*> input_pic, end_hint[2];
extern vector<SDL_Rect> input_rect, end_rect[2];

extern int cursor_pos;

extern const int TEXTBOX_WIDTH;
extern const int TEXTBOX_HEIGHT;

void Login();
void TheEnd();
