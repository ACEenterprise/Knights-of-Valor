#ifndef GUI_H
#define GUI_H
#include<windows.h>
#include<map>
#include<string>
#include<iostream>
#include<algorithm>
class Window
{

private:

	friend class Graphics;

	HWND hwnd;
	WNDCLASSEX wndclass;
	MSG msg;

	int width;
	int height;

	int mod_width;
	int mod_height;

	int client_width;
	int client_height;

	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		  case WM_DESTROY:
			PostQuitMessage(0);
			break;

		}

		return DefWindowProc(hwnd, msg, wParam, lParam);
	}


public:

	struct Keys
	{
		static const int _A = 0;
		static const int _B = 1;
		static const int _C = 2;
		static const int _D = 3;
		static const int _E = 4;
		static const int _F = 5;
		static const int _G = 6;
		static const int _H = 7;
		static const int _I = 8;
		static const int _J = 9;
		static const int _K = 10;
		static const int _L = 11;
		static const int _M = 12;
		static const int _N = 13;
		static const int _O = 14;
		static const int _P = 15;
		static const int _Q = 16;
		static const int _R = 17;
		static const int _S = 18;
		static const int _T = 19;
		static const int _U = 20;
		static const int _V = 21;
		static const int _W = 22;
		static const int _X = 23;
		static const int _Y = 24;
		static const int _Z = 25;
		static const int _a = 26;
		static const int _b = 27;
		static const int _c = 28;
		static const int _d = 29;
		static const int _e = 30;
		static const int _f = 31;
		static const int _g = 32;
		static const int _h = 33;
		static const int _i = 34;
		static const int _j = 35;
		static const int _k = 36;
		static const int _l = 37;
		static const int _m = 38;
		static const int _n = 39;
		static const int _o = 40;
		static const int _p = 41;
		static const int _q = 42;
		static const int _r = 43;
		static const int _s = 44;
		static const int _t = 45;
		static const int _u = 46;
		static const int _v = 47;
		static const int _w = 48;
		static const int _x = 49;
		static const int _y = 50;
		static const int _z = 51;
		static const int _0 = 52;
		static const int _1 = 53;
		static const int _2 = 54;
		static const int _3 = 55;
		static const int _4 = 56;
		static const int _5 = 57;
		static const int _6 = 58;
		static const int _7 = 59;
		static const int _8 = 60;
		static const int _9 = 61;
		static const int arrow_left = 62;
		static const int arrow_right = 63;
		static const int arrow_up = 64;
		static const int arrow_down = 65;
	};

    struct Mouse_event
	{
		static const int left_pressed = 66;
		static const int right_pressed = 67;
		static const int left_released = 68;
		static const int right_released = 69;
	};

	struct Window_event
	{
		static const int close = 70;
	};

	struct Key_event
	{
		static const int key_pressed = 71;
		static const int key_released = 72;
	};




	bool create_window(const char *title, int x, int y, int width, int height)
	{

		wndclass.cbSize = sizeof(wndclass);
		wndclass.cbClsExtra = NULL;
		wndclass.cbWndExtra = NULL;
		wndclass.hInstance = GetModuleHandle(NULL);
		wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndclass.lpszMenuName = NULL;
		wndclass.style = NULL;
		wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
		wndclass.lpszClassName = "window";
		wndclass.lpfnWndProc = WndProc;

		if (!RegisterClassEx(&wndclass))
			return false;

		hwnd = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			"window",
			title,
			WS_OVERLAPPEDWINDOW,
			x, y, width, height,
			NULL, NULL, wndclass.hInstance, NULL);

		RECT rect;

		GetClientRect(hwnd, &rect);

		client_width = rect.right;
		client_height = rect.bottom;

		if (!hwnd)
			return false;


		ShowWindow(hwnd, SW_SHOW);
		UpdateWindow(hwnd);


		this->width = width;
		this->height = height;

		mod_width = width;
		mod_height = height;

		return true;
	}

    std::pair<int,int> pollEvent()
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			int nr = 0;
			switch (msg.message)
			{

			case WM_CLOSE:
				return std::make_pair(Window_event::close, 0);
				break;
			case WM_DESTROY:
				PostQuitMessage(0);
				break;

			case WM_KEYDOWN:
				nr = 0;
				for (int i = 'A'; i <= 'Z'; ++i, nr++)
				{
					if (LOWORD(msg.wParam) == i)
					{
						return std::make_pair(Key_event::key_pressed, nr);
						break;
					}
				}

				for (int i = '0'; i <= '9'; ++i, nr++)
				{
					if (LOWORD(msg.wParam) == i)
					{
						return std::make_pair(Key_event::key_pressed, nr);
						break;
					}
				}
				break;
			case WM_KEYUP:
				nr = 0;
				for (int i = 'A'; i <= 'Z'; ++i, nr++)
				{
					if (LOWORD(msg.wParam) == i)
					{
						return std::make_pair(Key_event::key_released, nr);
						break;
					}
				}

				for (int i = '0'; i <= '9'; ++i, nr++)
				{
					if (LOWORD(msg.wParam) == i)
					{
						return std::make_pair(Key_event::key_released, nr);
						break;
					}
				}
				break;
			}
		}
		return std::make_pair(-1,0);
	}

	void destroy()
	{
		DestroyWindow(hwnd);
	}

	int getWidth()
	{
		return mod_width;
	}

	int getHeight()
	{
		return mod_height;
	}

	int getClientWidth()
	{
		return client_width;
	}

	int getClinetHeight()
	{
		return client_height;
	}

	void setWindowTitle(std::string title)
	{
		SetWindowText(hwnd, title.c_str());
	}

	void make_fullscreen()
	{
		HDC hDC = ::GetWindowDC(NULL);
		::SetWindowPos(hwnd, NULL, 0, 0, ::GetDeviceCaps(hDC, HORZRES), ::GetDeviceCaps(hDC, VERTRES), SWP_FRAMECHANGED);

		mod_width = ::GetDeviceCaps(hDC, HORZRES);
		mod_height = ::GetDeviceCaps(hDC, VERTRES);

		ReleaseDC(NULL, hDC);

		RECT rect;

		GetClientRect(hwnd, &rect);

		client_width = rect.right;
		client_height = rect.bottom;
	}

	void restore()
	{
		HDC hDC = ::GetWindowDC(NULL);
		::SetWindowPos(hwnd, NULL, 0, 0, width, height, SWP_FRAMECHANGED);

		mod_width = width;
		mod_height = height;

		ReleaseDC(NULL, hDC);

		RECT rect;

		GetClientRect(hwnd, &rect);

		client_width = rect.right;
		client_height = rect.bottom;
	}

};

#endif