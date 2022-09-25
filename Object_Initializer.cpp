#include "GameObjects.h"
#include "Bonus.h"
#include "Object_Initializer.h"

Block* Object_Initializer::InitBlock(int i, int j) {
	int Feature_random = rand() % 100;

	if (Feature_random >= 95)
		return new UnbreakableBlock(i, j, 6);
	else if (Feature_random >= 75)
		return new BonusBlock(i, j, rand() % 5 + 1);
	else if (Feature_random >= 60)
		return new AcceleratingBlock(i, j, rand() % 5 + 1);

	return new SimpleBlock(i, j, rand() % 5 + 1);
}

Object_Initializer::Object_Initializer()
{
	safebottom = new int(0);
	//Paddle
	paddle = new Paddle;

	//Blocks
	Blocks = std::vector < std::vector<Block*>> (FieldSize.x, std::vector<Block*>(FieldSize.y));
	Balls = std::vector < Ball*>(MaxBalls);
	Bonuses = std::vector < Bonus*>(MaxBonuses);


	for (int i = 0; i < FieldSize.x; i++)
	{
		for (int j = 0; j < FieldSize.y; j++)
		{
			Blocks[i][j] = InitBlock(i, j);
		}
	}

	//Balls	

	for (int i = 1; i < MaxBalls; i++)
	{
		Balls[i] = new Ball;
	}
	Balls[0] = new Ball;//createball();
	Balls[0]->InitBall();

	//Bonuses 

	Bonus *p = nullptr;
	for (int i = 0; i < MaxBonuses; i++)
	{
		switch (i % 6)
		{
		case 0: { p = new BChangeBallSpeed(Balls, paddle, Blocks, safebottom, i);  break; }
		case 1: { p = new BChangePaddleScale(Balls, paddle, Blocks, safebottom, i); break; }
		case 2: { p = new BCreateBall(Balls, paddle, Blocks, safebottom, i); break; }
		case 3: { p = new BCreateMovingBlock(Balls, paddle, Blocks, safebottom, i); break; }
		case 4: { p = new BSafeBottom(Balls, paddle, Blocks, safebottom, i); break; }
		case 5: { p = new BStickyPaddle(Balls, paddle, Blocks, safebottom, i); break; }
		}

		Bonuses[i] = p;
	}

}


std::vector<std::vector<Block*>> Object_Initializer::getblocksptr()
{
	return Blocks;
}

std::vector <Ball*> Object_Initializer::getballsptr()
{
	return Balls;
}

std::vector <Bonus*> Object_Initializer::getbonusesptr()
{
	return Bonuses;
}

Paddle* Object_Initializer::getpaddleptr()
{
	return paddle;
}


Object_Initializer::~Object_Initializer()
{
	for (int i = 0; i < FieldSize.x; i++)//right
	{
		for (int j = 0; j < FieldSize.y; j++)//right
		{
			delete Blocks[i][j];
		}
	}

	for (int j = 0; j < MaxBalls; j++)//right
	{
		delete Balls[j];
	}

	for (int j = 0; j < MaxBonuses; j++)//right
	{
		delete Bonuses[j];
	}
}