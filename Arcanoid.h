#ifndef ARCANOID_H
#define ARCANOID_H

#include "GameObjects.h"
#include "Object_Initializer.h"
#include "ObjectManager.h"
#include "UserInterface.h"


class Arcanoid
{

public:

	Arcanoid();
	~Arcanoid();

	void Play();

	Object_Initializer *Init;
	ObjectManager *Object_Manager;
	   
	std::vector < std::vector<Block*>> Blocks;
	std::vector < Bonus*> Bonuses;
	std::vector < Ball*> Balls;
	Paddle *paddle;

	int *safebottom;


};






#endif ARCANOID_H
