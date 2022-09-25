#ifndef OBJECT_H
#define OBJECT_H

#include <Math.h>
#include <iostream>
#include <string> 
#include "Settings.h"


class Object
{
protected:
	Vector2i scr_position; //x,y hor, vert
	Vector2i tab_position;
	Vector2f speed;

	Image img;
	Texture Tex;
	Sprite sprite;

public:
	virtual void Move();
	virtual Vector2i getSize() = 0;

	void setspeed(Vector2f speed);
	void setscr_position(Vector2i pos);
	void setsprite(Sprite sprite);

	Vector2f getspeed();
	Vector2i getscr_position();
	Sprite getsprite();

	void Draw(RenderWindow *window);
};


#endif OBJECT_H