#include "GameObjects.h"
#include "ObjectManager.h" 
#include "Bonus.h"

void ObjectManager::PaddleInteraction(Ball *ball)
{	
	float  mult;

	if (ball->getsprite().getGlobalBounds().intersects(paddle->getsprite().getGlobalBounds()))
	{
		Vector2f v = ball->getspeed();
		Vector2f v1;
		v1.x = 0;
		v1.y = -sqrt(v.x*v.x + v.y*v.y);
		v = v1;

		if (!ball->isOnPaddle())
		{
			if (paddle->isSticky())
			{
				ball->InitBall();
				return;
			}

			mult = ball->getscr_position().x + ball->getSize().x / 2;
			mult = (float)(mult - (paddle->getscr_position().x + paddle->getSize().x / 2)) / paddle->getSize().x;

			//		v = RotateVector(v, ( pi/2 + pi/2 * mult) );
			//printf("%f\n", PI / 2 * mult);
			v = RotateVector(v, (PI / 2 * mult));

			ball->setspeed(v);
			//ball->setscr_position({ ball->getscr_position().x, ball->getscr_position().y - ball->getSize().y });
		}
	}
}


void ObjectManager::BlocksInteraction(Ball *ball)
{
	Vector2i t1 = ball->getscr_position(), t2;

	Vector2f v = ball->getspeed();

	bool changedX, changedY = changedX = false;

	for (int i = 0; i < FieldSize.x; i++)
	{
		for (int j = 0; j < FieldSize.y; j++)
		{
			if (!Blocks[i][j]->isDead())
			{
				t2 = Blocks[i][j]->getscr_position();

				if (ball->getsprite().getGlobalBounds().intersects(Blocks[i][j]->getsprite().getGlobalBounds()))
				{
					float L, R, U, D, minV, minH;

					L = t1.x - (t2.x + Blocks[i][j]->getSize().x);
					R = t1.x + ball->getSize().x - t2.x;
					D = t1.y - (t2.y + Blocks[i][j]->getSize().y);
					U = t1.y + ball->getSize().y - t2.y;

					minV = (fabs(D) > fabs(U)) ? fabs(U) : fabs(D);
					minH = (fabs(R) > fabs(L)) ? fabs(L) : fabs(R);


					if (minV < minH)
					{
						if (!changedY)
						{
							v.y = -v.y;
							changedY = true;
						}
					}
					else
					{
						if (!changedX)
						{
							v.x = -v.x;
							changedX = true;
						}
					}

					switch (Blocks[i][j]->getFeature())
					{
					case Accelerating: {v.x *= 1.05; v.y *= 1.05;	printf("Speed now: %f\n", sqrt(v.x*v.x + v.y*v.y) ); Blocks[i][j]->DecreaseHP(); break; }
					case Unbreakable: {break; }
					case WithBonus: {Blocks[i][j]->DecreaseHP(); break; }
					default: {Blocks[i][j]->DecreaseHP(); }
					}

					Vector2f t = { -ball->getspeed().x, -ball->getspeed().y };
					ball->Move(t);

					ball->setspeed(v);

					Vector2i position_for_bonus = Blocks[i][j]->getscr_position();

					Blocks[i][j]->CheckDeath();

					if (Blocks[i][j]->isDead() && Blocks[i][j]->getFeature() == WithBonus)
					{
						for (int b = rand()%6; b < MaxBonuses; b++)
						{
							if (Bonuses[b]->getspeed().y == 0)
							{
								Bonuses[b]->InitBonus(position_for_bonus);
								printf("+Bonus\n");
								break;
							}
						}
					}
				}
			}
		}
	}
}


void ObjectManager::BallsInteraction(Ball *ball)
{
	Vector2f v1 = ball->getspeed(), v2;

	Vector2i t1 = ball->getscr_position(), t2;

	for (int i = 0; i < MaxBalls; i++)
	{
		if (Balls[i] == ball)
			continue;


		if (ball->getsprite().getGlobalBounds().intersects(Balls[i]->getsprite().getGlobalBounds()))
		{
			t2 = Balls[i]->getscr_position();
			v2 = Balls[i]->getspeed();

			float L, R, U, D, minV, minH;

			L = t1.x - (t2.x + Balls[i]->getSize().x);
			R = t1.x + ball->getSize().x - t2.x;
			D = t1.y - (t2.y + Balls[i]->getSize().y);
			U = t1.y + ball->getSize().y - t2.y;

			minV = (fabs(D) > fabs(U)) ? fabs(U) : fabs(D);
			minH = (fabs(R) > fabs(L)) ? fabs(L) : fabs(R);

			Vector2f t = { -ball->getspeed().x, -ball->getspeed().y };
			ball->Move(t);

			if (minV < minH)
			{
				v1.y = -v1.y;
				v2.y = -v2.y;
			}
			else
			{
				v1.x = -v1.x;
				v2.x = -v2.x;
			}

			ball->setspeed(v1);
			Balls[i]->setspeed(v2);
		}
	}
}
