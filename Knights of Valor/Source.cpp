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

	window.create_window("Knights of Valor", 0, 0, 1280, 720);
	Graphics g;
	g.create(window, 1280, 720);

	Knight knight("cavaler1", "HADRIAN", 32, 64 * 3 + 32);
	Knight knight1("cavaler1", "HADRIAN1", 32, 64 * 6 + 32);
	int y = 0;
	
	Map map(70, 70, 64, 64);
	map.Import("data.txt", vec);
	
	stack<pair<int, int>> path;
	Pathing p;
	pair<int, int> ev;

	Camera camera(&map);

	camera.centrate(&knight);
	int f = 0;
	int h = 0;
	
	while ((ev=window.pollEvent()).first != Window::Window_event::close)
	{
		Sleep(10);
		g.draw(0, 0, 1280, 720, RGB(0, 0, 0), false, RGB(0, 0, 0));
		map.drawMap(g);

		if (ev.first == Window::Mouse_event::left_pressed)
		{
			int mouse_x = ev.second & 0xFFFF;
			int mouse_y = ev.second >> 16;

			if(f==0)
				path = knight.get_path(map, ((mouse_x+32) / 64) * 64 + 32 - camera.getX(), ((mouse_y+32) / 64) * 64 - camera.getY() + 32);
			else
				path = knight1.get_path(map, ((mouse_x + 32) / 64) * 64 + 32 - camera.getX(), ((mouse_y + 32) / 64) * 64 - camera.getY() + 32);
			h = 1;

		}

		if (h == 1 && path.empty())
		{
	 
			h = 0;
			f ^= 1;

			if (f == 1)
				camera.centrate(&knight1);
			else
				camera.centrate(&knight);
		
		}


		if (f == 1)
		{
			knight.Move_Idle();
			knight.draw(g, knight.getX() + camera.getX(), knight.getY() + camera.getY());
		}
		else
		{
			knight1.Move_Idle();
			knight1.draw(g, knight1.getX() + camera.getX(), knight1.getY() + camera.getY());
		}

		if (f == 0)
		{
			p.draw_Green(g, path, knight.getX(), knight.getY(), camera);
			knight.go(path);
		}
		else
		{
			p.draw_Green(g, path, knight1.getX(), knight1.getY(), camera);
			knight1.go(path);
		}

		camera.action(g);

		g.invalidate();
	}

	return 0;
}