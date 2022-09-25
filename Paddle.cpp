#include "GameObjects.h"

Paddle::Paddle()
{
	speed = { 6,0 };

	img.loadFromFile("resourses/paddle.png");
	img.createMaskFromColor(img.getPixel(0, 0));
	Tex.loadFromImage(img);
	sprite.setTexture(Tex);
	sprite.setPosition((float)scr_position.x, (float)scr_position.y);

	size = (Vector2i)(Tex.getSize());

	scr_position.x = DisplayX / 2;
	scr_position.y = DisplayY - size.y;	
}


Vector2i Paddle::getSize()
{
	return size;
}

void Paddle::setSticky()
{
	sticky_duration = 3;
}

bool Paddle::isSticky()
{
	if (sticky_duration > 0)
	{
		sticky_duration--;
		return true;
	}
	return false;
}

void Paddle::Move()
{
	if ( (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D) ) && scr_position.x+size.x < DisplayX)
	{
		scr_position.x = scr_position.x + speed.x;
		sprite.setPosition((float)scr_position.x, (float)scr_position.y);
	}

	if ( (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) && scr_position.x > 0)
	{
		scr_position.x = scr_position.x - speed.x;
		sprite.setPosition((float)scr_position.x, (float)scr_position.y);
	}

}

void Paddle::setRNDScale()
{
	Vector2f scale = sprite.getScale();
	float rnd = (float)(rand() % 100 + 50) / 100.0;
	sprite.setScale(scale.x*rnd, scale.y);
	size.x *= rnd;
	size.y *= rnd;
}