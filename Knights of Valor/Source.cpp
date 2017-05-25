#include <iostream>
#include"Graphics.h"
#include"Animation.h"
#include "Knight.h"
#include <stack>
#include "Pathing.h"
using namespace std;

vector<vector<int>> v;

int main() 
{
	Window window;

	window.create_window("Knights of Valor", 0, 0, 1920, 1080);
	Graphics g;
	g.create(window, 1920, 1080);

	Knight knight("cavaler1", "HADRIAN", 32, 32);
	int y = 0;
	
	Map map(70, 70, 64, 64);
	stack<pair<int, int>> path = knight.get_path(map, 608, 608);
	
	Pathing p;

	while (window.pollEvent().first != Window::Window_event::close)
	{
		g.draw(0, 0, 1920, 1080, RGB(0, 0, 0), false, RGB(0, 0, 0));
		knight.draw(g);
		p.draw_Green(g, path, knight.getX(), knight.getY());
		y++;
		if (knight.getX() == 608 && knight.getY() == 608) {
			path = knight.get_path(map, 32, 32);
		}
		if (y % 10 == 0) {
			knight.go(path);
		} 

		g.invalidate();
	}

	return 0;
}