#include "GameObjects.h"



//SET

void Object::setspeed(Vector2f speed)
{
	this->speed = speed;
}

void Object::setscr_position(Vector2i pos)
{
	scr_position = pos;
}

void Object::setsprite(Sprite s)
{
	sprite = s;
}



//GET

Sprite Object::getsprite()
{
	return sprite;
}

Vector2i Object::getscr_position()
{
	return scr_position;
}

Vector2f Object::getspeed()
{
	return speed;
}



//Manipulate

Vector2f RotateVector(Vector2f vec, float alpha)
{
	Vector2f New = vec;

	New.x = vec.x*cos(alpha) - vec.y*sin(alpha);
	New.y = vec.x*sin(alpha) + vec.y*cos(alpha);

	return New;
}

void Object::Move()
{
	if (this != nullptr)
	{
		scr_position.x = scr_position.x + speed.x;
		scr_position.y = scr_position.y + speed.y;
		sprite.setPosition((float)scr_position.x, (float)scr_position.y);
	}
}

void Object::Draw(RenderWindow *window)
{
	sprite.setPosition((float)scr_position.x, (float)scr_position.y);
	window->draw(sprite);
}