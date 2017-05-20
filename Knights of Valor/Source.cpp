#include <iostream>
#include"Graphics.h"
#include"Animation.h"
#include "Knight.h"
using namespace std;

int main() 
{
	Window window;

	window.create_window("Knights of Valor", 0, 0, 800, 600);
	Graphics g;
	g.create(window, 800, 600);

	Knight knight("cavaler1", "HADRIAN", 32, 32);

	int y = 0;

	while (window.pollEvent().first != Window::Window_event::close)
	{
		g.draw(0, 0, 800, 600, RGB(0, 0, 0));
		g.draw(knight.getSprite(), knight.getFrame(), knight.getX(), knight.getY(), 96, 64, knight.getBitmap(), true, 0);

		y++;
		if (y % 50 == 0 && knight.getX() < 96) {
			knight.Move_Right();
		}

		if (knight.getX() >= 96) {
			knight.Move_Idle();
		}

		knight.runAnimation();
		g.invalidate();
	}

	return 0;
}