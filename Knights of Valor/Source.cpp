#include <iostream>
#include"Graphics.h"
#include"Gui.h"
using namespace std;

int main() 
{
	Window window;
	

	window.create_window("testing", 30, 30, 800, 600);
	pair<int, int > pr;
	while ((pr = window.pollEvent()).first!=Window::Window_event::close)
	{
		if (pr.first == Window::Mouse_event::left_released)
		{
			cout << (pr.second & 0xFFFF)<<" "<<(pr.second>>16)<<" ";
		}
	}

	return 0;
}