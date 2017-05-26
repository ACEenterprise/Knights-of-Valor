#include <iostream>
#include"Graphics.h"
#include"Animation.h"
#include "Knight.h"
#include"Camera.h"
#include <stack>
#include "Pathing.h"
using namespace std;

vector<vector<int>> v;
vector<Sprite> vec;
int main() 
{
	Window window;

	window.create_window("Knights of Valor", 0, 0, 1920, 1080);
	Graphics g;
	g.create(window, 1920, 1080);

	Knight knight("cavaler1", "HADRIAN", 32, 64 * 3 + 32);
	int y = 0;
	
	Map map(70, 70, 64, 64);
	map.Import("data.txt", vec);
	
	stack<pair<int, int>> path;
	Pathing p;
	pair<int, int> ev;

	Camera camera(&map);

	camera.centrate(&knight);

	while ((ev=window.pollEvent()).first != Window::Window_event::close)
	{
		
		g.draw(0, 0, 1920, 1080, RGB(0, 0, 0), false, RGB(0, 0, 0));
		map.drawMap(g);

		if (ev.first == Window::Mouse_event::left_pressed)
		{
			int mouse_x = ev.second & 0xFFFF;
			int mouse_y = ev.second >> 16;

			path = knight.get_path(map, ((mouse_x+32) / 64) * 64 + 32 - camera.getX(), ((mouse_y+32) / 64) * 64 - camera.getY() + 32);

		}

		p.draw_Green(g, path, knight.getX(), knight.getY(),camera);
		knight.go(path);

		camera.action(g);

		g.invalidate();
	}

	return 0;
}