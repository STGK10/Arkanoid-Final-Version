#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "Object.h"
#include "GameObjects.h"
#include "Bonus.h"




class ObjectManager : public Object
{

public:
	ObjectManager(std::vector < Ball*> Balls,  std::vector < Bonus*> Bonuses, Paddle *paddle, std::vector<std::vector<Block*>> Blocks, int *safebottom) : Balls(Balls), paddle(paddle), Bonuses(Bonuses), Blocks(Blocks), safebottom(safebottom) {};
	
	void MakeFrame();

	void BallMakeStep(Ball* ball);
	void ScreenCheck(Ball *ball);
	void BlockMakeStep(Block *block);

	Vector2i getFieldSize();
	int getMaxBalls();
	int getMaxBonuses();


	Block* getBlock(int i, int j);
	Ball* getBall(int i);
	Bonus* getBonus(int i);
	Paddle* getPaddle();

	virtual Vector2i getSize();

	bool isSafeBottom();
	void GameOverCheck();
	void VictoryCheck();

	void PaddleInteraction(Ball *ball);
	void BlocksInteraction(Ball *ball);
	void BallsInteraction(Ball *ball);
	
	//Bonus
	void BonusMakeStep(Bonus *bonus);


private:

	std::vector < std::vector<Block*>> Blocks;
	std::vector < Bonus*> Bonuses;
	std::vector < Ball*> Balls;
	Paddle *paddle;
	Vector2i FieldSize = { 12,8 };

	int *safebottom;
	int GameStatus = 0;
};



#endif OBJECTMANAGER_H