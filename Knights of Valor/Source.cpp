#include <iostream>
#include"Graphics.h"
#include"Animation.h"
#include "Knight.h"
#include <stack>
using namespace std;

vector<vector<int>> v;

int main() 
{
	Window window;

	window.create_window("Knights of Valor", 0, 0, 1920, 1080);
	Graphics g;
	g.create(window, 1920, 1080);

	Knight knight("cavaler1", "HADRIAN", 48, 48);

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
	
	stack<pair<int, int>> path = knight.get_path(v, 912, 912);

	while (window.pollEvent().first != Window::Window_event::close)
	{
		g.draw(knight.getSprite(), knight.getFrame(), knight.getX(), knight.getY(), 96, 64, knight.getBitmap(), true, 0);

		y++;
		if (y % 10 == 0) {
			knight.go(path);
		} 


		knight.runAnimation();
		g.invalidate();
	}

	return 0;
}