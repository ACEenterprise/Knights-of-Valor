#ifndef ANIMATION_H
#define ANIMATION_H

#include"Graphics.h"

class Animation
{
private:
	Sprite *sprite;
	int duration;
	long long last_time;
	long long current_time;
	double mili_per_frame;
	bool repeat;
	int frame;

public:

	Animation()
	{
		repeat = true;
		last_time = 0;
		current_time = 0;
		mili_per_frame = 0;
		frame = 0;
		sprite = NULL;
	}

	void setSprite(Sprite *sprite)
	{
		this->sprite = sprite;
	}

	void setDuration(int duration)
	{
		if (sprite)
		{
			this->duration = duration;

			mili_per_frame = (double)duration / sprite->get_number_of_frames();
		}
	}

	void restart()
	{
		frame = 0;
		last_time = 0;
	}

	void setRepeat(bool state)
	{
		repeat = state;
	}

	int getFrame()
	{
		return  frame;
	}

	void runAnimation()
	{
		if (sprite)
		{

			current_time = GetTickCount();

			if (last_time == 0)
				last_time = current_time;

			if (repeat ==true || (repeat == false && frame != sprite->get_number_of_frames()-1))
			{
				long long x = current_time - last_time;
				if (repeat == false  && frame + (int)x/mili_per_frame < sprite->get_number_of_frames())
				{
					frame = frame + (int)(x / mili_per_frame);

					if ((int)(x / mili_per_frame) != 0)
					{
						last_time = current_time;

					}
				}
				else if (repeat == true)
				{
					frame = (frame + (int)(x / mili_per_frame)) % sprite->get_number_of_frames();

					if ((int)(x / mili_per_frame) !=0)
					{
						last_time = current_time;

					}

				}
			}
		}
	}

	Sprite* getSprite()
	{
		return sprite;
	}
};

#endif;