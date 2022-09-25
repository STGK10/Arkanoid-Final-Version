#include "GameObjects.h"

Ball::Ball()
{
	scr_position = { -100,-100 };

	speed = { 0,0 };

	img.loadFromFile("resourses/ball.png");
	img.createMaskFromColor(img.getPixel(0, 0));
	Tex.loadFromImage(img);
	sprite.setTexture(Tex);
	sprite.setPosition(-1000, -1000);
	
	size = (Vector2i)(Tex.getSize());

}

bool Ball::isOnPaddle()
{
	return OnPaddle;
}

void Ball::SetUnInit()
{
	OnPaddle = 0;
}

void Ball::InitBall()
{
	speed = { 0.0,0.0 };
	OnPaddle = true;
}


void Ball::Move(Vector2f speed)
{
	scr_position.x = scr_position.x + speed.x;
	scr_position.y = scr_position.y + speed.y;
	sprite.setPosition((float)scr_position.x, (float)scr_position.y);		

}

Vector2i Ball::getSize()
{
	return size;
}


void Ball::ResetBall()
{
	Vector2f v = { 0,0 };
	setspeed(v);
	Vector2i p = { -100,-100 };
	setscr_position(p);
}


void Ball::MirrorSpeed(char axis)
{
	if (axis == 'x')
	{
		speed.x = -speed.x;
	}
	else
	{
		speed.y = -speed.y;
	}
}