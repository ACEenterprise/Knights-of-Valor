#include "Knight.h"

Knight::Knight(const char* filename, int x, int y) {
	sp = new Sprite();
	sp->Load(filename, 8, 1);
	an.setSprite(sp);
	an.setSprite(sp);
	an.setDuration(700);
	an.setRepeat(true);
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