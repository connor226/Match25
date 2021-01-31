#ifndef INC_FUNCTIONS_H
#define INC_FUNCTIONS_H
#include "functions.h"
#endif

using namespace std;

int main(int argc, char** argv) {
	
//	Login();                  //key in id
	Match25_INIT();           //initialize the interface
	LoadMedia();              //load images or sound effects
	LoadData();               //load data
	GenerateMap(1);           //randomly scatter the circles for phase 1
	Play();                   //game control
	ClearMap();               //delete all circles
	GenerateMap(2);           //randomly scatter the circles for phase 2
	Play();                   //game control
	ClearMap();               //delete all circles
	TheEnd();                 //end scene
	UpdateData();             //write new data to data.txt
	Match25_CLOSE();          //destroy all the SDL things
	
	return 0;
}
