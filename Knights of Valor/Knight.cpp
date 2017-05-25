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

void Knight::go(stack<pair<int, int>> &path) {
	if (path.empty()) {
		Move_Idle();
		return;
	}

	int next_x = path.top().first;
	int next_y = path.top().second;

	if (x == next_x && y == next_y) {
		path.pop();
	}
	else {
		if (next_x > this->x) {
			if (next_y == this->y) {
				Move_Right();
			}
			else if (next_y > this->y) {
				Move_Down_Right();
			}
			else {
				Move_Up_Right();
			}
		}
		else if (next_x < this->x) {
			if (next_y == this->y) {
				Move_Left();
			}
			else if (next_y > this->y) {
				Move_Down_Left();
			}
			else {
				Move_Up_Left();
			}
		}
		else {
			if (next_y > this->y) {
				Move_Down();
			}
			else {
				Move_Up();
			}
		}
	}
}

stack<pair<int, int>> Knight::get_path(vector<vector<int>> &map, int dest_x, int dest_y) {
	int n = map.size();

	dest_x = (dest_x - 32) / 64;
	dest_y = (dest_y - 32) / 64;

	int viz[100][100];
	for (int i = 0; i < map.size(); ++i) {
		for (int j = 0; j < map.size(); ++j) {
			viz[i][j] = -10;
		}
	}

	queue<pair<int, int>> q;

	int X = (this->x - 32) / 64;
	int Y = (this->y - 32) / 64;
	q.push({ X, Y });
	viz[X][Y] = 0;

	int ok = 0;

	while (!q.empty()) {
		int cur_x = q.front().first;
		int cur_y = q.front().second;

		if (cur_x == dest_x && cur_y == dest_y) {
			ok = 1;
			break;
		}

		q.pop();

		for (int i = 0; i < 8; ++i) {
			if (interior(cur_x + dx[i], cur_y + dy[i], n) &&
				map[cur_y + dy[i]][cur_x + dx[i]] > 0 && 
				viz[cur_y + dy[i]][cur_x + dx[i]] < 0) {

				q.push({ cur_x + dx[i], cur_y + dy[i] });
				viz[cur_y + dy[i]][cur_x + dx[i]] = viz[cur_y][cur_x] + 1;
			}
		}
	}


	stack<pair<int, int>> path;

	//General widht and height on map tile. map.tileWidth() and map.tileHeight()

	if (ok == 1) {
		while (!(dest_x == X && dest_y == Y)) {
			path.push({ dest_x * 64 + 32, dest_y * 64 + 32 });
			for (int i = 0; i < 8; ++i) {
				if (viz[dest_y + dy[i]][dest_x + dx[i]] == viz[dest_y][dest_x] - 1) {
					dest_x = dest_x + dx[i];
					dest_y = dest_y + dy[i];
					break;
				}
			}
		}
	}

	return path;
}

void Knight::draw(Graphics &g) {
	g.draw(an.getSprite(), an.getFrame(), this->x - 32, this->y - 32, 64, 48, &Bmps[current_state], true, 0);
	an.runAnimation();
}