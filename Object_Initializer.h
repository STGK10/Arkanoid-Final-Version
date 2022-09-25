#ifndef OBJECT_INITIALIZER_H
#define OBJECT_INITIALIZER_H

#include "GameObjects.h"
#include "Bonus.h"
#include <vector>


class Object_Initializer
{
public:
	
	Object_Initializer();
	~Object_Initializer();
	Block* InitBlock(int i, int j);
	std::vector<std::vector<Block*>> getblocksptr();
	std::vector < Ball*>  getballsptr();
	std::vector < Bonus*>  getbonusesptr();
	Paddle* getpaddleptr();
	
	
private:
	

	Vector2i FieldSize = { 12,8 };

	std::vector < std::vector<Block*>> Blocks;	
	std::vector < Bonus*> Bonuses;
	std::vector < Ball*> Balls;
	Paddle *paddle;
	int* safebottom;
};


#endif OBJECT_INITIALIZER_H