#include "Hexagon.h"
#include <SFML/Graphics.hpp>
#include "Moving.h"
#include "Interactive.h"
#include "Renderable.h"
#include "Map.h"
#include "Agent.h"
#include <iostream>
#include "NPC.h"
#include "Door.h"
#include "GameWorld.h"
#include "MainCharacter.h"
#include <chrono>

const float screenWidth = 1050.0f;
const float screenHeight = 1200.0f;
bool movementFlag = true;
sf::RenderWindow *window;
	
std::vector<Renderable*> toRender;
std::vector<Interactive*> toInteract;
std::vector<Moving*> toMove;
std::vector<Behaving*> toBehave;

void GenerateWorld()
{
	Map* map = new Map(screenWidth, screenHeight, "./Assets/house30.png");
	toRender.push_back(map);
	toInteract.push_back(map);

	Door* door = new Door("./Assets/door.png", sf::Vector2i(9, 14), map);
	toRender.push_back(door);
	GameWorld::getInstance().AddDoor("toiletdoor", door);

	Toilet* toilet = new Toilet("./Assets/toilet.png", sf::Vector2i(4, 14), map);
	toRender.push_back(toilet);
	GameWorld::getInstance().AddToilet("toilet", toilet);

	door = new Door("./Assets/door.png", sf::Vector2i(9, 7), map);
	toRender.push_back(door);
	GameWorld::getInstance().AddDoor("bedroomdoor", door);

	Bed* bed = new Bed("./Assets/bed.png", sf::Vector2i(4, 10), map);
	toRender.push_back(bed);
	GameWorld::getInstance().AddBed("bed", bed);

	MainCharacter* mainCharacter = new MainCharacter("./Assets/panda.png", sf::Vector2i(15, 15), map);
	toRender.push_back(mainCharacter);
	toMove.push_back(mainCharacter);
	toBehave.push_back(mainCharacter);

}

int main()
{
	srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());

	window = new sf::RenderWindow(sf::VideoMode(static_cast<unsigned int>(screenWidth), static_cast<unsigned int>(screenHeight)), "Sims");
	window->setVerticalSyncEnabled(true);

	GenerateWorld();

	sf::Clock fpsClock, moveClock;
	float totalMoveTime = 0;

	while (window->isOpen())
	{
		float currentFpsTime = fpsClock.restart().asSeconds();

		sf::Event event;

		//Interacting
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window->close();
			}

			if(event.type == sf::Event::KeyPressed)
			{
				if(event.key.code == sf::Keyboard::Escape)
				{
					window->close();
				}
				if(event.key.code == sf::Keyboard::M)
				{
					movementFlag = !movementFlag;
				}

				for (const auto i : toInteract)
				{
					i->HandleKeyboard(event.key.code);
				}
			}

			if(event.type == sf::Event::MouseMoved)
			{
				sf::Vector2f mpos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

				for (const auto i : toInteract)
				{
					i->HandleMouse(mpos);
				}
			}
			
			if(event.type == sf::Event::MouseButtonPressed)
			{
				for (const auto i : toInteract)
				{
					i->HandleMouse(event.mouseButton.button);
				}
			}

		}

		totalMoveTime += moveClock.restart().asSeconds();

		//Moving
		if(movementFlag && totalMoveTime > 1.0f)
		{
			float fps = 1.0f / (currentFpsTime);
			window->setTitle("Sims (" + std::to_string(static_cast<int>(fps)) + ")");

			for(auto m : toMove)
			{
				m->Move();
			}

			//Behaving
			for (auto b : toBehave)
			{
				b->Behave();
			}
			//Behaving End

			totalMoveTime = 0.0f;
		}

		window->clear();

		//Rendering
		for(const auto r : toRender)
		{
			r->Render(window);
			r->DebugRender(window);
		}

		window->display();
	}

	return 0;
}
