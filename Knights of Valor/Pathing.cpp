#include "Pathing.h"

Pathing::Pathing() {
	GreenArrow[0].Load("pathing/gpcruce.bmp", 1, 1);
	GreenArrow[1].Load("pathing/gpright.bmp", 1, 1);
	GreenArrow[2].Load("pathing/gpleft.bmp", 1, 1);
	GreenArrow[3].Load("pathing/gpup.bmp", 1, 1);
	GreenArrow[4].Load("pathing/gpdown.bmp", 1, 1);
	GreenArrow[5].Load("pathing/gpup_right.bmp", 1, 1);
	GreenArrow[6].Load("pathing/gpup_left.bmp", 1, 1);
	GreenArrow[7].Load("pathing/gpdown_right.bmp", 1, 1);
	GreenArrow[8].Load("pathing/gpdown_left.bmp", 1, 1);

	RedArrow[0].Load("pathing/rpcruce.bmp", 1, 1);
	RedArrow[1].Load("pathing/rpright.bmp", 1, 1);
	RedArrow[2].Load("pathing/rpleft.bmp", 1, 1);
	RedArrow[3].Load("pathing/rpup.bmp", 1, 1);
	RedArrow[4].Load("pathing/rpdown.bmp", 1, 1);
	RedArrow[5].Load("pathing/rpup_right.bmp", 1, 1);
	RedArrow[6].Load("pathing/rpup_left.bmp", 1, 1);
	RedArrow[7].Load("pathing/rpdown_right.bmp", 1, 1);
	RedArrow[8].Load("pathing/rpdown_left.bmp", 1, 1);

	Bmps[0].Load("pathing/pcruceMask.bmp");
	Bmps[1].Load("pathing/prightMask.bmp");
	Bmps[2].Load("pathing/pleftMask.bmp");
	Bmps[3].Load("pathing/pupMask.bmp");
	Bmps[4].Load("pathing/pdownMask.bmp");
	Bmps[5].Load("pathing/pup_rightMask.bmp");
	Bmps[6].Load("pathing/pup_leftMask.bmp");
	Bmps[7].Load("pathing/pdown_rightMask.bmp");
	Bmps[8].Load("pathing/pdown_leftMask.bmp");
}

void Pathing::draw_Green(Graphics &g, stack<pair<int, int>> path, int x, int y) {
	while (!path.empty()) {
		int next_x = path.top().first;
		int next_y = path.top().second;

		path.pop();

		if (path.size() == 0) {
			g.draw(&GreenArrow[0], 0, next_x - 32, next_y - 32, 64, 64, &Bmps[0], true, 0);
			return;
		}


		if (next_x > x) {
			if (next_y == y) {
				g.draw(&GreenArrow[1], 0, next_x - 32, next_y - 32, 64, 64, &Bmps[1], true, 0);
			}
			else if (next_y > y) {
				g.draw(&GreenArrow[7], 0, next_x - 32, next_y - 32, 64, 64, &Bmps[7], true, 0);
			}
			else {
				g.draw(&GreenArrow[5], 0, next_x - 32, next_y - 32, 64, 64, &Bmps[5], true, 0);
			}
		}
		else if (next_x < x) {
			if (next_y == y) {
				g.draw(&GreenArrow[2], 0, next_x - 32, next_y - 32, 64, 64, &Bmps[2], true, 0);
			}
			else if (next_y > y) {
				g.draw(&GreenArrow[8], 0, next_x - 32, next_y - 32, 64, 64, &Bmps[8], true, 0);
			}
			else {
				g.draw(&GreenArrow[6], 0, next_x - 32, next_y - 32, 64, 64, &Bmps[6], true, 0);
			}
		}
		else {
			if (next_y > y) {
				g.draw(&GreenArrow[4], 0, next_x - 32, next_y - 32, 64, 64, &Bmps[4], true, 0);
			}
			else if (next_y < y) {
				g.draw(&GreenArrow[3], 0, next_x - 32, next_y - 32, 64, 64, &Bmps[3], true, 0);
			}
		}
		x = next_x;
		y = next_y;
	}
}

void Pathing::draw_Red(Graphics &g, stack<pair<int, int>> path, int x, int y) {
	while (!path.empty()) {
		int next_x = path.top().first;
		int next_y = path.top().second;

		path.pop();

		if (path.size() == 0) {
			g.draw(&RedArrow[0], 0, next_x - 32, next_y - 32, 64, 64, &Bmps[0], true, 0);
			return;
		}


		if (next_x > x) {
			if (next_y == y) {
				g.draw(&RedArrow[1], 0, next_x - 32, next_y - 32, 64, 64, &Bmps[1], true, 0);
			}
			else if (next_y > y) {
				g.draw(&RedArrow[7], 0, next_x - 32, next_y - 32, 64, 64, &Bmps[7], true, 0);
			}
			else {
				g.draw(&RedArrow[5], 0, next_x - 32, next_y - 32, 64, 64, &Bmps[5], true, 0);
			}
		}
		else if (next_x < x) {
			if (next_y == y) {
				g.draw(&RedArrow[2], 0, next_x - 32, next_y - 32, 64, 64, &Bmps[2], true, 0);
			}
			else if (next_y > y) {
				g.draw(&RedArrow[8], 0, next_x - 32, next_y - 32, 64, 64, &Bmps[8], true, 0);
			}
			else {
				g.draw(&RedArrow[6], 0, next_x - 32, next_y - 32, 64, 64, &Bmps[6], true, 0);
			}
		}
		else {
			if (next_y > y) {
				g.draw(&RedArrow[4], 0, next_x - 32, next_y - 32, 64, 64, &Bmps[4], true, 0);
			}
			else {
				g.draw(&RedArrow[3], 0, next_x - 32, next_y - 32, 64, 64, &Bmps[3], true, 0);
			}
		}
		x = next_x;
		y = next_y;
	}
}