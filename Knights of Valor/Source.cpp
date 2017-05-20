#include <iostream>
#include"Graphics.h"
#include"Animation.h"
#include "Knight.h"
using namespace std;

int main() 
{
	Window window;

	window.create_window("Knights of Valor", 0, 0, 1920, 1080);
	Graphics g;
	g.create(window, 1920, 1080);

	Knight knight("cavaler1", "HADRIAN", 132, 132);

	int y = 0;

	while (window.pollEvent().first != Window::Window_event::close)
	{
		g.draw(0, 0, 1920, 1080, RGB(255, 255, 255));
		g.draw(knight.getSprite(), knight.getFrame(), knight.getX(), knight.getY(), 96, 64, knight.getBitmap(), true, 0);

		y++;
		if (y % 10 == 0 && knight.getX() < 228) {
			knight.Move_Down_Left();
		}


		knight.runAnimation();
		g.invalidate();
	}

	return 0;
}