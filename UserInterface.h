#ifndef HEADER_H
#define HEADER_H

#include "GameObjects.h"
#include "ObjectManager.h"
#include "Bonus.h"


class UserInterface
{
public:
	RenderWindow *window;
	Texture backgroundTex;
	Sprite background;
	Vector2i FieldSize = { 12,8 };

	UserInterface(RenderWindow *window) : window(window) {}

	void Render(ObjectManager *Manager);
	void DrawObjects(ObjectManager *Manager);

};





#endif HEADER_H