#ifndef GRAPHICS_H
#define GRAPHICS_H
#include<Windows.h>
#include<fstream>
#include<iostream>
#include"Gui.h"
using namespace std;

class Bitmap
{

private:
	friend class Graphics;

	BITMAPFILEHEADER bmH;
	BITMAPINFOHEADER bmiH;
	HBITMAP bm;
	BITMAPINFO *bmi;
	unsigned char *pixels;
	unsigned char *color_table;

private:
	void create(HWND hwnd)
	{
		if (bm == NULL)
		{
			bmi = (BITMAPINFO*)malloc(sizeof(BITMAPINFO) + bmH.bfOffBits - 54);

			ZeroMemory(bmi, sizeof(BITMAPINFO) + bmH.bfOffBits - 54);

			bmi->bmiHeader = bmiH;

			memcpy(bmi->bmiColors, color_table, bmH.bfOffBits - 54);

			HDC dc = GetDC(hwnd);
			
			bm = CreateDIBitmap(dc, &bmiH, CBM_INIT, pixels, bmi, DIB_RGB_COLORS);
		
			ReleaseDC(hwnd, dc);
		}
	}

	void create_mask(HWND hwnd, bool reverse)
	{
		if (bm == NULL)
		{
			bmi = (BITMAPINFO*)malloc(sizeof(BITMAPINFO) + bmH.bfOffBits - 54);

			ZeroMemory(bmi, sizeof(BITMAPINFO) + bmH.bfOffBits - 54);

			bmi->bmiHeader = bmiH;

			memcpy(bmi->bmiColors, color_table, bmH.bfOffBits - 54);

			HDC dc = GetDC(hwnd);

			if (reverse)
			{
				for (int i = 0; i < bmH.bfSize - bmH.bfOffBits; ++i)
					pixels[i] ^= 0xFF;
			}

			bm = CreateDIBitmap(NULL, &bmiH, CBM_INIT, pixels, bmi, DIB_RGB_COLORS);

			ReleaseDC(hwnd, dc);
		}
	}

public:

	int width;
	int height;

	Bitmap()
	{
		width = height = 0;
		pixels = NULL;
		color_table = NULL;
		bmi = NULL;
		bm = NULL;
	}


	bool Load(const char *file_name)
	{
		ifstream in(file_name, fstream::binary);


		in.read((char*)&bmH.bfType, 2);

		if (bmH.bfType != 19778)
			return false;

		in.read((char*)&bmH.bfSize, 4);

		in.read((char*)&bmH.bfReserved1, 2);

		in.read((char*)&bmH.bfReserved2, 2);

		in.read((char*)&bmH.bfOffBits, 4);

		in.read((char*)&bmiH.biSize, 4);

		in.read((char*)&bmiH.biWidth, 4);

		width = bmiH.biWidth;

		in.read((char*)&bmiH.biHeight, 4);

		height = bmiH.biHeight;

		in.read((char*)&bmiH.biPlanes, 2);

		in.read((char*)&bmiH.biBitCount, 2);

		in.read((char*)&bmiH.biCompression, 4);

		in.read((char*)&bmiH.biSizeImage, 4);

		in.read((char*)&bmiH.biXPelsPerMeter, 4);

		in.read((char*)&bmiH.biYPelsPerMeter, 4);

		in.read((char*)&bmiH.biClrUsed, 4);

		in.read((char*)&bmiH.biClrImportant, 4);

		if (bmH.bfOffBits - 54 != 0)
		{
			color_table = new unsigned char[bmH.bfOffBits - 54];
			in.read((char*)color_table, bmH.bfOffBits - 54);
		}

		pixels = new unsigned char[bmH.bfSize - bmH.bfOffBits];
		in.read((char*)pixels, bmH.bfSize - bmH.bfOffBits);

		return true;
	}

	int getWidth()
	{
		return width;
	}

	int getHeight()
	{
		return height;
	}

	~Bitmap()
	{
		delete[] pixels;

		if (color_table)
			delete[] color_table;

		if (bmi)
			delete bmi;

		DeleteObject(&bmiH);
	}
};

class Sprite
{
private:
	friend class Graphics;
	Bitmap bm;

	int x, y;
	int number_of_frames;
	int frames_per_width;
	int frames_per_height;

	int current_frame;
	int width_of_frame;
	int height_of_frame;

public:
	Sprite()
	{
		x = 0;
		y = 0;
		width_of_frame = 0;
		height_of_frame = 0;

		current_frame = 0;
		number_of_frames = 0;
	}

	bool Load(const char* filename, int frames_per_width, int frames_per_height)
	{
		if (bm.Load(filename) == true)
		{
			this->frames_per_width = frames_per_width;
			this->frames_per_height = frames_per_height;
			this->number_of_frames = frames_per_width * frames_per_height;


			width_of_frame = bm.getWidth() / frames_per_width;
			height_of_frame = bm.getHeight() / frames_per_height;

			return true;
		}
		else
			return false;
	}

	void set_starting_frame(int x)
	{
		if (x >= 0 && x <= number_of_frames)
			current_frame = x;
	}

	void next_frame()
	{
		current_frame = (current_frame + 1) % number_of_frames;
	}

	int get_current_frame()
	{
		return current_frame;
	}

	int get_number_of_frames()
	{
		return number_of_frames;
	}

	int getWidth()
	{
		return width_of_frame;
	}

	int getHeight()
	{
		return height_of_frame;
	}

};


class Graphics
{
private:

	HWND hwnd;
	HDC mHdc;
	HBITMAP backbuffer, oldBackBuffer;
	HBRUSH oldBrush;
	int width, height;
	int scale_width, scale_height;

	int x, y;

public:
	Graphics()
	{
		scale_width = scale_height = width = height = 0;
		x = y = 0;
	}

	Graphics(Window &window, int width, int height)
	{
		x = y = 0;
		this->hwnd = window.hwnd;
		HDC hdc = GetDC(hwnd);

		scale_width = this->width = width;
		scale_height = this->height = height;

		mHdc = CreateCompatibleDC(hdc);

		backbuffer = CreateCompatibleBitmap(hdc, width, height);

		ReleaseDC(hwnd, hdc);

		HBITMAP oldBackBuffer = (HBITMAP)SelectObject(mHdc, backbuffer);

		HBRUSH oldBrush = (HBRUSH)SelectObject(mHdc, (HBRUSH)GetStockObject(WHITE_BRUSH));

		Rectangle(mHdc, 0, 0, width, height);

		SelectObject(mHdc, oldBrush);
	}
	void create(Window &window, int width, int height)
	{
		x = y = 0;
		this->hwnd = window.hwnd;
		HDC hdc = GetDC(hwnd);

		scale_width = this->width = width;
		scale_height = this->height = height;

		mHdc = CreateCompatibleDC(hdc);

		backbuffer = CreateCompatibleBitmap(hdc, width, height);

		ReleaseDC(hwnd, hdc);

		HBITMAP oldBackBuffer = (HBITMAP)SelectObject(mHdc, backbuffer);

		oldBrush = (HBRUSH)SelectObject(mHdc, (HBRUSH)GetStockObject(BLACK_BRUSH));

		Rectangle(mHdc, 0, 0, width, height);

	}
	void invalidate()
	{
		HDC hdc = GetDC(hwnd);
		StretchBlt(hdc, x, y, scale_width, scale_height, mHdc, 0, 0, width, height, SRCCOPY);
		ReleaseDC(hwnd, hdc);
	}


	void draw(Bitmap *bitmap, int x, int y, int width, int height)
	{
		if (bitmap)
		{
			bitmap->create(hwnd);

			HDC hdc = GetDC(hwnd);

			HDC mem = CreateCompatibleDC(hdc);

			HBITMAP old = (HBITMAP)SelectObject(mem, bitmap->bm);


			StretchBlt(mHdc, x, y, width, height, mem, 0, 0, bitmap->width, bitmap->height, SRCCOPY);

			SelectObject(mem, old);

			DeleteDC(mem);
			ReleaseDC(hwnd, hdc);
		}



	}

	void draw(Bitmap *bitmap, int x, int y, int width, int height,int chop_x,int chop_y,int chop_width,int chop_height)
	{
		if (bitmap)
		{
			bitmap->create(hwnd);

			HDC hdc = GetDC(hwnd);

			HDC mem = CreateCompatibleDC(hdc);

			HBITMAP old = (HBITMAP)SelectObject(mem, bitmap->bm);


			StretchBlt(mHdc, x, y, width, height, mem, chop_x, chop_y, chop_width, chop_height, SRCCOPY);

			SelectObject(mem, old);

			DeleteDC(mem);
			ReleaseDC(hwnd, hdc);
		}



	}


	void draw(Bitmap *bitmap, int x, int y, int width, int height, int chop_x, int chop_y, int chop_width, int chop_height, Bitmap *mask,int reverse,double rotation)
	{
		if (bitmap)
		{
			bitmap->create(hwnd);

			if (mask)
				mask->create_mask(hwnd, reverse);



			HDC hdc = GetDC(hwnd);

			HDC mem = CreateCompatibleDC(hdc);

			HBITMAP old = (HBITMAP)SelectObject(mem, bitmap->bm);

			POINT mid_rotated_top_left = { -width / 2.0 * cos(rotation) - (-height / 2.0 * sin(rotation))
										  , -width / 2.0 * sin(rotation) + (-height / 2.0 * cos(rotation)) };
			POINT mid_rotated_top_right = { width / 2.0 * cos(rotation) - (-height / 2.0 * sin(rotation))
										  , width / 2.0 * sin(rotation) + (-height / 2.0 * cos(rotation)) };
			POINT mid_rotated_bottom_left = { -width / 2.0 * cos(rotation) - (height / 2.0 * sin(rotation))
										  , -width / 2.0 * sin(rotation) + (height / 2.0 * cos(rotation)) };

			POINT p[3] = { {x + width / 2 + mid_rotated_top_left.x,y + height / 2 + mid_rotated_top_left.y},
						  { x + width / 2 + mid_rotated_top_right.x,y + height / 2 + mid_rotated_top_right.y },
						  { x + width / 2 + mid_rotated_bottom_left.x,y + height / 2 + mid_rotated_bottom_left.y } };

			PlgBlt(mHdc, p, mem, chop_x, chop_y, chop_width, chop_height, mask->bm, chop_x, chop_y);

			SelectObject(mem, old);

			DeleteDC(mem);
			ReleaseDC(hwnd, hdc);
		}



	}

	void draw(Sprite *sprite, int x, int y, int width, int height)
	{
		if (sprite)
		{
			int position_x = (sprite->current_frame%sprite->frames_per_width)*sprite->width_of_frame;
			int position_y = (sprite->current_frame / sprite->frames_per_width)*sprite->height_of_frame;

			draw(&sprite->bm, x, y, width, height, position_x, position_y, sprite->width_of_frame, sprite->height_of_frame);
		}

	}

	void draw(Sprite *sprite,int frame, int x, int y, int width, int height)
	{
		if (sprite)
		{
			frame %= sprite->number_of_frames;
			int position_x = (frame%sprite->frames_per_width)*sprite->width_of_frame;
			int position_y = (frame / sprite->frames_per_width)*sprite->height_of_frame;

			draw(&sprite->bm, x, y, width, height, position_x, position_y, sprite->width_of_frame, sprite->height_of_frame);
		}

	}



	void draw(Sprite *sprite, int x, int y, int width, int height, Bitmap *mask,bool reverse, double rotation)
	{
		if (sprite)
		{
			int position_x = (sprite->current_frame%sprite->frames_per_width)*sprite->width_of_frame;
			int position_y = (sprite->current_frame / sprite->frames_per_width)*sprite->height_of_frame;

			draw(&sprite->bm, x, y, width, height, position_x, position_y, sprite->width_of_frame, sprite->height_of_frame, mask, true, rotation);
		}

	}

	void draw(Sprite *sprite,int frame, int x, int y, int width, int height, Bitmap *mask, bool reverse, double rotation)
	{
		if (sprite)
		{
			frame %= sprite->number_of_frames;
			int position_x = (frame%sprite->frames_per_width)*sprite->width_of_frame;
			int position_y = (frame/ sprite->frames_per_width)*sprite->height_of_frame;

			draw(&sprite->bm, x, y, width, height, position_x, position_y, sprite->width_of_frame, sprite->height_of_frame, mask, true, rotation);
		}

	}

	void draw(int left, int top, int right, int bottom)
	{
		Rectangle(mHdc, left, top, right, bottom);
	}

	void translate(int x, int y)
	{
		RECT rect;
		rect.left = 0;
		rect.right = scale_width;
		rect.bottom = scale_height;
		rect.top = 0;
		InvalidateRect(hwnd, &rect, true);


		this->x = x;
		this->y = y;
	}



	void resize(int width, int height)
	{
		scale_width = width;
		scale_height = height;
	}

	~Graphics()
	{
		SelectObject(mHdc, oldBrush);
		SelectObject(mHdc, oldBackBuffer);

		DeleteObject(backbuffer);
		DeleteDC(mHdc);
	}

};

#endif