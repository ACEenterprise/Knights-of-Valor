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

	Bitmap* bm = new Bitmap();
	bm->Load("cavaler1miscaredreaptamasca.bmp");

	Knight knight("cavaler1miscaredreapta.bmp", 10, 10);
	int x = 0;
	int y = 0;
	while (window.pollEvent().first != Window::Window_event::close)
	{
		g.draw(0, 0, 800, 600, RGB(0, 0, 0));
		g.draw(knight.getSprite(), knight.getFrame(), x + 32, 32, 64, 64, bm, true, 0);
		++y;
		if (y % 50 == 0 && x <= 96) {
			++x;
		}

		knight.runAnimation();
		g.invalidate();
	}

	return 0;
}