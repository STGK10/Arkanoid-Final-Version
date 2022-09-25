#include "GameObjects.h"
#include "ObjectManager.h"
#include "Bonus.h"
#include <string>



Bonus::Bonus(std::vector < Ball*> Balls, Paddle *paddle,  std::vector<std::vector<Block*>> Blocks, int *safebottom, int i) : Balls(Balls), paddle(paddle), Blocks(Blocks), safebottom(safebottom)
{
	static String Names[6] = { "bonus_paddlescale","bonus_ballspeed","bonus_stickypaddle","bonus_safebottom","bonus_makeball","bonus_movingblock" };
	speed = { 0, 0 };
	scr_position = { -100,-100 };
	img.loadFromFile("resourses/" + Names[i % 6] + ".png");
	img.createMaskFromColor(img.getPixel(0, 0));
	Tex.loadFromImage(img);
	sprite.setTexture(Tex);
	size = (Vector2i)(Tex.getSize());
}

void Bonus::InitBonus(Vector2i t)
{
	scr_position = t;
	speed = { 0, 2 };
}

void Bonus::ResetBonus()
{
	Vector2f v = { 0,0 };
	setspeed(v);
	Vector2i p = { -100,-100 };
	setscr_position(p);
}


Vector2i Bonus::getSize()
{
	return size;
}


