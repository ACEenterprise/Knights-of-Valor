#include "Knight.h"

Knight::Knight(string path, int x, int y) {
	Sprites[0].Load((path + "/idle.bmp").c_str(), 1, 1);
	Sprites[1].Load((path + "/dreapta.bmp").c_str(), 1, 1);
	Sprites[2].Load((path + "/stanga.bmp").c_str(), 1, 1);
	Sprites[3].Load((path + "/sus.bmp").c_str(), 1, 1);
	Sprites[4].Load((path + "/jos.bmp").c_str(), 1, 1);
	Sprites[5].Load((path + "/sus_dreapta.bmp").c_str(), 1, 1);
	Sprites[6].Load((path + "/sus_stanga.bmp").c_str(), 1, 1);
	Sprites[7].Load((path + "/jos_dreapta.bmp").c_str(), 1, 1);
	Sprites[8].Load((path + "/jos_stanga.bmp").c_str(), 1, 1);



	this->x = x;
	this->y = y;

	an.setSprite(&Sprites[0]);
	an.setRepeat(true);
	an.setDuration(500);
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

void Knight::Move_Idle() {
	if (an.getSprite() != &Sprites[0]) {
		an.setSprite(&Sprites[0]);
	}
}

void Knight::Move_Right() {
	if (an.getSprite() != &Sprites[1]) {
		an.setSprite(&Sprites[1]);
	}

	++x;
}

void Knight::Move_Left() {
	if (an.getSprite() != &Sprites[2]) {
		an.setSprite(&Sprites[2]);
	}

	--x;
}

void Knight::Move_Up() {
	if (an.getSprite() != &Sprites[3]) {
		an.setSprite(&Sprites[3]);
	}

	--y;
}

void Knight::Move_Down() {
	if (an.getSprite() != &Sprites[4]) {
		an.setSprite(&Sprites[4]);
	}

	++y;
}

void Knight::Move_Up_Right() {
	if (an.getSprite() != &Sprites[5]) {
		an.setSprite(&Sprites[5]);
	}

	--y;
	++x;
}

void Knight::Move_Up_Left() {
	if (an.getSprite() != &Sprites[6]) {
		an.setSprite(&Sprites[6]);
	}

	--y;
	--x;
}

void Knight::Move_Down_Right() {
	if (an.getSprite() != &Sprites[7]) {
		an.setSprite(&Sprites[7]);
	}

	++y;
	++x;
}

void Knight::Move_Down_Left() {
	if (an.getSprite() != &Sprites[8]) {
		an.setSprite(&Sprites[8]);
	}

	++y;
	--x;
}