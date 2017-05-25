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

	/*
	path.push({ 132, 132 });
	path.push({ 68, 198 });
	path.push({ 132, 198 });
	path.push({ 132, 262 });
	path.push({ 198, 198 });
	path.push({ 198, 132 });
	*/
	
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		vector<int> tmp;
		v.push_back(tmp);
		for (int j = 0; j < n; ++j) {
			v[i].push_back(0);
		}
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> v[i][j];
		}
	}
	
	stack<pair<int, int>> path = knight.get_path(v, 608, 608);
	
	Pathing p;

	while (window.pollEvent().first != Window::Window_event::close)
	{
		g.draw(0, 0, 1920, 1080, RGB(0, 0, 0), false, RGB(0, 0, 0));
		knight.draw(g);
		p.draw_Green(g, path, knight.getX(), knight.getY());
		y++;
		if (knight.getX() == 608 && knight.getY() == 608) {
			path = knight.get_path(v, 32, 32);
		}
		if (y % 10 == 0) {
			knight.go(path);
		} 

		g.invalidate();
	}

	return 0;
}