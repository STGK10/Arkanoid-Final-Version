#ifndef BONUS_H
#define BONUS_H

#include "GameObjects.h"



class Bonus : public Object
{
private:
	Vector2i size;
	
public:

	std::vector < std::vector<Block*>> Blocks;
	std::vector < Ball*> Balls;
	Paddle *paddle;
	int* safebottom;
	Vector2i FieldSize = { 12,8 };

	Bonus( std::vector < Ball*> Balls, Paddle *paddle,  std::vector<std::vector<Block*>> Blocks, int *safebottom, int i);

	void InitBonus(Vector2i t);
	virtual void MakeAction() {};
	void ResetBonus();

	virtual Vector2i getSize();
	
};



class BChangePaddleScale : public Bonus
{
	
public:
	BChangePaddleScale( std::vector < Ball*> Balls, Paddle *paddle,  std::vector<std::vector<Block*>> Blocks, int *safebottom, int i) :Bonus(Balls, paddle, Blocks, safebottom, i) {};
	void MakeAction()
	{
		printf(" Bonus Action: Paddle");
		paddle->setRNDScale();
		printf("BONUS: Paddle size changed\n");
	}

};

class BChangeBallSpeed :public Bonus
{

public:
	BChangeBallSpeed( std::vector < Ball*> Balls, Paddle *paddle,  std::vector<std::vector<Block*>> Blocks, int *safebottom, int i) :Bonus(Balls, paddle, Blocks, safebottom, i) {};
	void MakeAction()
	{
		
		Vector2f speed, zeros = { 0,0 };
		float rnd = (float)(rand() % 100) / 100.0 + 0.5;

		for (int i = 0; i < MaxBalls; i++)
		{
			if (Balls[i]->getspeed() != zeros)
			{
				speed = Balls[i]->getspeed();
				speed.x *= rnd;
				speed.y *= rnd;
				Balls[i]->setspeed(speed);
			}
		}
		printf("BONUS: Ball speed changed\n");
	}

};


class BStickyPaddle : public Bonus
{

public:
	BStickyPaddle( std::vector < Ball*> Balls, Paddle *paddle,  std::vector<std::vector<Block*>> Blocks, int *safebottom, int i) :Bonus(Balls, paddle, Blocks, safebottom, i) {};
	void MakeAction()
	{
		paddle->setSticky();
		printf("BONUS: Sticky paddle.\n");
	}

};


class BSafeBottom : public Bonus
{

public:
	BSafeBottom( std::vector < Ball*> Balls, Paddle *paddle,  std::vector<std::vector<Block*>> Blocks, int *safebottom, int i) :Bonus(Balls, paddle, Blocks, safebottom, i) {};
	void MakeAction()
	{
		*safebottom = 1;
		printf("BONUS: Safe Bottom\n");
	}

};


class BCreateMovingBlock : public Bonus
{

public:
	BCreateMovingBlock( std::vector < Ball*> Balls, Paddle *paddle,  std::vector<std::vector<Block*>> Blocks, int *safebottom, int i) :Bonus(Balls, paddle, Blocks, safebottom, i) {};
	void MakeAction()
	{
		for (int i = FieldSize.y - 1; i >= 0; i--)
		{
			for (int j = FieldSize.y - 1; j >= 0; j--)
			{
				if (!Blocks[i][j]->isDead())
				{
					Vector2f v = { 3.0, 0 };
					Blocks[i][j]->setspeed(v);
					printf("BONUS: Moving block\n");
					return;
				}
			}
		}
	}

};


class BCreateBall : public Bonus
{

public:
	BCreateBall( std::vector < Ball*> Balls, Paddle *paddle,  std::vector<std::vector<Block*>> Blocks, int *safebottom, int i) :Bonus(Balls, paddle, Blocks, safebottom, i) {};
	void MakeAction()
	{
		Vector2f speed = Balls[0]->getspeed(), zeros = { 0,0 }, v1, v2;
		float alpha = PI / 8;

		int free = -1, busy = -1;

		for (int i = 0; i < MaxBalls; i++)
		{
			if (Balls[i]->getspeed() == zeros)
			{
				free = i;
			}
			else
			{
				busy = i;
			}
		}

		if (free != -1)
		{
			v1 = Balls[busy]->getspeed();

			v2 = RotateVector(v1, alpha);
			v1 = RotateVector(v1, -alpha);

			Vector2i delta = Balls[busy]->getSize();

			Balls[free]->setscr_position(Balls[busy]->getscr_position() + delta);
			Balls[free]->setspeed(v2);
			Balls[busy]->setspeed(v1);

			printf("BONUS: Ball create\n");
		}
	}

};


#endif BONUS_H