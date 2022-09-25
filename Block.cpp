#include "GameObjects.h"

Block::Block(int i, int j, int h)
{
	health = h;
	Tex.loadFromFile("resourses/block_texture1.png");

	size = (Vector2i)(Tex.getSize());
	size.x /= 6;

	sprite.setTexture(Tex);
	setTexture(health);


	tab_position.x = i;
	tab_position.y = j;

	scr_position.x = 5 + (size.x + 5) * i;
	scr_position.y = 3 + (size.y + 3) * j;

	speed = { 0,0 };
}


void Block::ScreenCheck()
{
	if (this != nullptr)
	{
		if (scr_position.x <= 0 || scr_position.x >= DisplayX - size.x)
		{
			speed.x *= -1;
		}
	}
}

void Block::setTexture(int health)
{
	sprite.setTextureRect(IntRect((health-1)*(size.x), 0, (size.x), size.y));
}

void Block::DecreaseHP()
{
	health--;
	setTexture(health);
}

Vector2i Block::getSize()
{
	return size;
}

FeatureType Block::getFeature()
{
	return feature;
}

void Block::CheckDeath()
{
	if (health <= 0)
	{
		Vector2i t = { -100, -100 };
		setscr_position(t);
		Vector2f v = { 0,0 };
		setspeed(v);
		Dead = true;
		
	}
}

bool Block::isDead()
{
	return Dead;
}