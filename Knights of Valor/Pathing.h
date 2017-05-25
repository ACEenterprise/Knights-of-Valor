#ifndef PATHING_H
#define PATHING_H

#include <iostream>
#include "Sprite.h"
#include "Graphics.h"
#include "Knight.h"
#include "Bitmap.h"
#include <string.h>
#include <stack>

class Pathing {
private:
	stack<pair<int, int>> path;
	Sprite GreenArrow[10];
	Sprite RedArrow[10];
	Bitmap Bmps[10];

public:

	Pathing();

	void draw_Green(Graphics &g, stack<pair<int, int>> path, int x, int y);
	void draw_Red(Graphics &g, stack<pair<int, int>> path, int x, int y);

};

#endif
