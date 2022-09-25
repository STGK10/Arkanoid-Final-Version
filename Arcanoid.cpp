#include "Arcanoid.h"

Arcanoid::Arcanoid()
{
	Init = new Object_Initializer;

	paddle = Init->getpaddleptr();
	Bonuses = Init->getbonusesptr();
	Blocks = Init->getblocksptr();
	Balls = Init->getballsptr();

	Object_Manager = new ObjectManager(Balls, Bonuses, paddle, Blocks, safebottom);
}


Arcanoid::~Arcanoid()
{
	delete Init;
	delete Object_Manager;
}


void Arcanoid::Play()
{
	
	//Window settings
	RenderWindow window;
	window.create(VideoMode(DisplayX, DisplayY), "Arkanoid!");
	window.setFramerateLimit(FPS);

	UserInterface UI(&window);

	Texture backgroundTex;
	backgroundTex.loadFromFile("resourses/background.jpg");
	Sprite background(backgroundTex);
	

	while (window.isOpen())
	{
		Event event;
		window.clear();
		window.draw(background);

		UI.Render(Object_Manager);

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}

		}

		window.display();
	}

}