#ifndef CAMERA_H
#define CAMERA_H

#include"Map.h"
#include"Knight.h"

class Camera
{
private:
	Map *map;
	Knight *knight;
public:

	Camera(Map* map);

	void centrate(Knight* knight);

	void action(Graphics &g); 

	int getX();

	int getY();
};

#endif