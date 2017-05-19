#include "Knight.h"

Knight::Knight(const char* filename, int x, int y) {
	sp = new Sprite();
	sp->Load(filename, 1, 1);

	x = 32;
	y = 32;

	an.setSprite(sp);
	an.setDuration(10);
	an.setRepeat(false);
}

Sprite* Knight::getSprite() {
	return sp;
}

int Knight::getFrame() {
	return an.getFrame();
}

void Knight::runAnimation() {
	an.runAnimation();
}

void Knight::Change_Right(const char* filename, int frames) {
	sp->Load(filename, frames, 1);

	an.setSprite(sp);
	an.setDuration(500);
	an.setRepeat(true);
}

void Knight::Move_Right() {
	x++;
}

void Knight::Reset(const char* filename) {
	sp->Load(filename, 1, 1);

	an.setSprite(sp);
	an.setDuration(10);
	an.setRepeat(false);
}

int Knight::getX() {
	return x;
}

int Knight::getY() {
	return y;
}