#include "GameObjects.h"
#include "ObjectManager.h"
#include "Bonus.h"




Vector2i ObjectManager::getSize() //plug
{
	return { -1,-1 };
}

void ObjectManager::ScreenCheck(Ball *ball)
{
	if (ball->getscr_position().x <= 0 || ball->getscr_position().x >= DisplayX - ball->getSize().x)
	{
		ball->MirrorSpeed('x');
	}

	if (ball->getscr_position().y <= 0)
	{
		ball->MirrorSpeed('y');
	}

	if (ball->getscr_position().y >= DisplayY - ball->getSize().y)
	{
		if (!isSafeBottom())
		{
			printf("One Ball Lost\n");
			ball->ResetBall();
			GameOverCheck();
			if (GameStatus == -1)												//доп. Шарик
				Balls[0]->InitBall();
		}
	}

}

void ObjectManager::GameOverCheck()
{
	int i;
	Vector2f zeros = { 0.0, 0.0 };
	for (i = 0; i < MaxBalls; i++)
	{
		if (Balls[i]->getspeed() != zeros || Balls[i]->isOnPaddle())
			break;
	}
	if (i == MaxBalls)
		GameStatus = -1;
}

void ObjectManager::VictoryCheck()
{
	for (int i = 0; i < FieldSize.x; i++)
	{
		for (int j = 0; j < FieldSize.y; j++)
		{
			if (!Blocks[i][j]->isDead())
				return;
		}
	}
	GameStatus = 1;
	printf("You Win!\n");
}

void ObjectManager::BallMakeStep(Ball *ball)
{

	ball->Move(ball->getspeed());

	PaddleInteraction(ball);
	BlocksInteraction(ball);
	BallsInteraction(ball);

	//For init ball
	if (ball->isOnPaddle())
	{
		Vector2i pos = paddle->getscr_position();
		Vector2i size = paddle->getSize();
		pos.x += size.x / 2 - ball->getSize().x;
		pos.y -= (ball->getSize().y + 2);
   		ball->setscr_position(pos);

		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			ball->SetUnInit();
			//Vector2f v = { (float)(rand() % 16 / 2.0) - 8, -(float)(rand() % 8 / 2.0 + 2) };
			Vector2f v = { 0.0, -5.0 };
			float alpha = (float) (rand() % 100) / 100.0 * -PI + PI/4;
			v = RotateVector(v, alpha );
			ball->setspeed(v);
		}
	}
	   	 	   	
	ScreenCheck(ball);	
}


void ObjectManager::BlockMakeStep(Block *block)
{

	if (block->getspeed().x == 0.0)
	{
		return;
	}

	block->Move();
	
	Vector2f v1 = block->getspeed(), v2;

	for (int i = 0; i < FieldSize.x; i++)
	{
		for (int j = 0; j < FieldSize.y; j++)
		{
			if (Blocks[i][j] == block)
				continue;


			if (block->getsprite().getGlobalBounds().intersects(Blocks[i][j]->getsprite().getGlobalBounds()))
			{
				v1.x = -v1.x;
				block->setspeed(v1);
			}
		}
		
	}
	block->ScreenCheck();
}

void ObjectManager::BonusMakeStep(Bonus *bonus)
{

	bonus->Move();

	if (bonus->getsprite().getGlobalBounds().intersects(paddle->getsprite().getGlobalBounds()))
	{
		bonus->MakeAction();
		
		bonus->ResetBonus();
	}
}

void ObjectManager::MakeFrame()
{

	//Paddle
	paddle->Move();

	//Balls
	for (int i = 0; i < MaxBalls; i++)
	{
		BallMakeStep(Balls[i]);
	}


	//Blocks
	for (int i = 0; i < FieldSize.x; i++)
	{
		for (int j = 0; j < FieldSize.y; j++)
		{
			BlockMakeStep(Blocks[i][j]);
		}
	}
	

	//Bonuses
	for (int i = 0; i < MaxBonuses; i++)
	{
		BonusMakeStep(Bonuses[i]);
	}

	VictoryCheck();

}

bool ObjectManager::isSafeBottom()
{
	return safebottom;
}

Vector2i ObjectManager::getFieldSize()
{
	return FieldSize;
}

int ObjectManager::getMaxBalls()
{
	return MaxBalls;
}

int ObjectManager::getMaxBonuses()
{
	return MaxBonuses;
}

Block* ObjectManager::getBlock(int i, int j)
{
	return Blocks[i][j];
}

Ball* ObjectManager::getBall(int i)
{
	return Balls[i];
}

Bonus* ObjectManager::getBonus(int i)
{
	return Bonuses[i];
}

Paddle* ObjectManager::getPaddle()
{
	return paddle;
}






