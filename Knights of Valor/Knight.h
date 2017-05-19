#ifndef KNIGHT_H
#define KNIGHT

#include <iostream>
#include "Animation.h"
#include <vector>

class Knight {
private:
	Animation an;
	vector<Sprite> Sprites;
	vector<Bitmap> Bmps;

	int x, y;

public:

	Knight(string path, int x, int y);

	Sprite* getSprite();
	int getFrame();
	void runAnimation();

	int getX();
	int getY();

	void Move_Idle();
	void Move_Right();
	void Move_Left();
	void Move_Up();
	void Move_Down();
	void Move_Up_Right();
	void Move_Up_Left();
	void Move_Down_Right();
	void Move_Down_Left();

};


#endif