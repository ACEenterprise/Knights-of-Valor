#ifndef KNIGHT_H
#define KNIGHT

#include <iostream>
#include "Animation.h"

class Knight {
private:
	Animation an;
	Sprite* sp;
	double x, y;

public:

	Knight(const char* filename, int x, int y);

	Sprite* getSprite();
	int getFrame();
	int getX();
	int getY();
	void runAnimation();

	void Reset(const char* filename);
	void Change_Right(const char* filename, int frames);
	void Move_Right();
};


#endif