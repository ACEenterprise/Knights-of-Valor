#include"Camera.h"

Camera::Camera(Map* map)
{
	this->map = map;
}

void Camera::centrate(Knight* knight)
{
	this->knight = knight;
	
	
}

void Camera::action(Graphics &g)
{
	map->setX((1920 / 2 / 64) * 64-knight->getX());
	map->setY((1080 / 2 / 64) * 64 -knight->getY());

	knight->draw(g, (1920 / 2 / 64) * 64, (1080 / 2 / 64) * 64);
}

int Camera::getX()
{
	return map->getX();
}

int Camera::getY()
{
	return map->getY();
}