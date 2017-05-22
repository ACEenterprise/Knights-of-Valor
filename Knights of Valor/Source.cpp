#include <iostream>
#include"Graphics.h"
#include"Animation.h"
#include "Knight.h"
#include <stack>
using namespace std;

int main() 
{
	Window window;

	window.create_window("Knights of Valor", 0, 0, 1920, 1080);
	Graphics g;
	g.create(window, 1920, 1080);

	Knight knight("cavaler1", "HADRIAN", 132, 132);

	int y = 0;

	stack<pair<int, int>> path;

	path.push({ 132, 132 });
	path.push({ 68, 198 });
	path.push({ 132, 198 });
	path.push({ 132, 262 });
	path.push({ 198, 198 });
	path.push({ 198, 132 });

	while (window.pollEvent().first != Window::Window_event::close)
	{
		g.draw(0, 0, 1920, 1080, RGB(255, 255, 255));
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