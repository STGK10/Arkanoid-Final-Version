#include "UserInterface.h"


void UserInterface::DrawObjects(ObjectManager *Manager)
{
	//Paddle
	Manager->getPaddle()->Draw(window);

	//Balls
	for (int i = 0; i < Manager->getMaxBalls(); i++)
	{
		Manager->getBall(i)->Draw(window);
	}

	//Blocks
	for (int i = 0; i < Manager->getFieldSize().x; i++)
	{
		for (int j = 0; j < Manager->getFieldSize().y; j++)
		{
			Manager->getBlock(i, j)->Draw(window);
		}
	}	   	 

	//Bonuses
	for (int i = 0; i < Manager->getMaxBonuses(); i++)
	{
		Manager->getBonus(i)->Draw(window);
	}
	   
}

void UserInterface::Render(ObjectManager *Manager)
{
	DrawObjects(Manager);
	Manager->MakeFrame();
//	Manager->IntersectionCheck();

}
