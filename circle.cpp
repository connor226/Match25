#ifndef INC_FUNCTIONS_H
#define INC_FUNCTIONS_H
#include "functions.h"
#endif

#define X first
#define Y second 

using namespace std;

const int CIRCLE_SIZE = 100;

CIRCLE::CIRCLE(int num){
	pic = number[num];
	quad.w = CIRCLE_SIZE;
	quad.h = CIRCLE_SIZE;
	quad.x = -CIRCLE_SIZE;
	quad.y = -CIRCLE_SIZE;
}

void CIRCLE::SetPos(int X, int Y){
	quad.x = X;
	quad.y = Y;
}

pair<int, int> CIRCLE::pos(){
	return {quad.x, quad.y};
}

pair<int, int> CIRCLE::center(){
	return {quad.x + CIRCLE_SIZE / 2, quad.y + CIRCLE_SIZE / 2};
}

double CIRCLE::dist(CIRCLE *c){
	double my_posX = pos().X;
	double my_posY = pos().Y;
	double c_posX = c->pos().X;
	double c_posY = c->pos().Y;
	return sqrt((my_posX - c_posX) * (my_posX - c_posX) + (my_posY - c_posY) * (my_posY - c_posY));
}

bool Mouse_On_Circle(SDL_Point p, CIRCLE *c){
	int c_X = c->center().X;
	int c_Y = c->center().Y;
	return ((p.x - c_X) * (p.x - c_X) + (p.y - c_Y) * (p.y - c_Y) < (CIRCLE_SIZE / 2) * (CIRCLE_SIZE / 2));
}
