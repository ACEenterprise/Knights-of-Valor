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

	Knight knight("cavaler1dreaptajos.bmp", 32, 32);
	
	Bitmap* bm = new Bitmap();
	bm->Load("cavaler1miscaredreaptamasca.bmp");

	int y = 0;

	while (window.pollEvent().first != Window::Window_event::close)
	{
		g.draw(0, 0, 800, 600, RGB(0, 0, 0));
		g.draw(knight.getSprite(), knight.getFrame(), knight.getX(), knight.getY(), 96, 64, bm, true, 0);

		knight.runAnimation();
		g.invalidate();

		if (++y % 50 == 0) {
			knight.Move_Right();
		}
	}

	return 0;
}