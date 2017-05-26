#ifndef KNIGHT_H
#define KNIGHT_H

#include <iostream>
#include "Animation.h"
#include "Graphics.h"
#include "Map.h"
#include <vector>
#include <queue>
#include <stack>
class Knight {
private:
	Animation an;
	Sprite Sprites[10];
	Bitmap Bmps[10];

	const int dx[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
	const int dy[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };

	int x, y, current_state;
	string name;

public:

	Knight(string path, string name, int x, int y);

	Sprite* getSprite();
	Bitmap* getBitmap();
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

	void go(stack<pair<int, int>> &path);

	void draw(Graphics &g,int x,int y);

	bool interior(int i, int j, int n) {
		if (i < n && i >= 0 && j >= 0 && j < n)
			return 1;
		return 0;
	}

	stack<pair<int, int>> get_path(Map &map, int dest_x, int dest_y);

};


#endif