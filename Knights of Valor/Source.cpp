#include <iostream>
#include"Graphics.h"
#include"Animation.h"
using namespace std;

int main() 
{
	Window window;

	window.create_window("val", 20, 20, 800, 600);
	Graphics g;
	g.create(window, 800, 600);

	Sprite sp;
	sp.Load("cavaler1.bmp",45,1);
	Animation an;
	an.setSprite(&sp);
	an.setDuration(700);
	an.setRepeat(true);
	
	while (window.pollEvent().first != Window::Window_event::close)
	{
		g.draw(an.getSprite(),an.getFrame(), 10, 10, 200, 200,NULL,true,40*3.14/180);

		an.runAnimation();
		g.invalidate();
	}

	return 0;
}