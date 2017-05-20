#include "Knight.h"

Knight::Knight(string path, string name, int x, int y) {
	Sprites[0].Load((path + "/idle.bmp").c_str(), 1, 1);
	Sprites[1].Load((path + "/right.bmp").c_str(), 8, 1);
	Sprites[2].Load((path + "/left.bmp").c_str(), 8, 1);
	Sprites[3].Load((path + "/up.bmp").c_str(), 8, 1);
	Sprites[4].Load((path + "/down.bmp").c_str(), 8, 1);
	Sprites[5].Load((path + "/up_right.bmp").c_str(), 8, 1);
	Sprites[6].Load((path + "/up_left.bmp").c_str(), 8, 1);
	Sprites[7].Load((path + "/down_right.bmp").c_str(), 8, 1);
	Sprites[8].Load((path + "/down_left.bmp").c_str(), 8, 1);

	Bmps[0].Load((path + "/idleMask.bmp").c_str());
	Bmps[1].Load((path + "/rightMask.bmp").c_str());
	Bmps[2].Load((path + "/leftMask.bmp").c_str());
	Bmps[3].Load((path + "/upMask.bmp").c_str());
	Bmps[4].Load((path + "/downMask.bmp").c_str());
	Bmps[5].Load((path + "/up_rightMask.bmp").c_str());
	Bmps[6].Load((path + "/up_leftMask.bmp").c_str());
	Bmps[7].Load((path + "/down_rightMask.bmp").c_str());
	Bmps[8].Load((path + "/down_leftMask.bmp").c_str());

	this->x = x;
	this->y = y;
	this->name = name;

	current_state = 0;

	an.setSprite(&Sprites[0]);
	an.setRepeat(true);
	an.setDuration(100);
}

Sprite* Knight::getSprite() {
	return an.getSprite();
}

int Knight::getFrame() {
	return an.getFrame();
}

void Knight::runAnimation() {
	an.runAnimation();
}

int Knight::getX() {
	return x;
}

int Knight::getY() {
	return y;
}

Bitmap* Knight::getBitmap() {
	return &Bmps[current_state];
}

void Knight::Move_Idle() {
	if (an.getSprite() != &Sprites[0]) {
		an.restart();
		an.setSprite(&Sprites[0]);
		current_state = 0;
	}
}

void Knight::Move_Right() {
	if (an.getSprite() != &Sprites[1]) {
		an.restart();
		an.setSprite(&Sprites[1]);
		current_state = 1;
	}

	++x;
}

void Knight::Move_Left() {
	if (an.getSprite() != &Sprites[2]) {
		an.restart();
		an.setSprite(&Sprites[2]);
		current_state = 2;
	}

	--x;
}

void Knight::Move_Up() {
	if (an.getSprite() != &Sprites[3]) {
		an.restart();
		an.setSprite(&Sprites[3]);
		current_state = 3;
	}

	--y;
}

void Knight::Move_Down() {
	if (an.getSprite() != &Sprites[4]) {
		an.restart();
		an.setSprite(&Sprites[4]);
		current_state = 4;
	}

	++y;
}

void Knight::Move_Up_Right() {
	if (an.getSprite() != &Sprites[5]) {
		an.restart();
		an.setSprite(&Sprites[5]);
		current_state = 5;
	}

	--y;
	++x;
}

void Knight::Move_Up_Left() {
	if (an.getSprite() != &Sprites[6]) {
		an.restart();
		an.setSprite(&Sprites[6]);
		current_state = 6;
	}

	--y;
	--x;
}

void Knight::Move_Down_Right() {
	if (an.getSprite() != &Sprites[7]) {
		an.restart();
		an.setSprite(&Sprites[7]);
		current_state = 7;
	}

	++y;
	++x;
}

void Knight::Move_Down_Left() {
	if (an.getSprite() != &Sprites[8]) {
		an.restart();
		an.setSprite(&Sprites[8]);
		current_state = 8;
	}

	++y;
	--x;
}