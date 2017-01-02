#include "Hexagon.h"
#include <SFML/Graphics.hpp>
#include "Moving.h"
#include "Interactive.h"
#include "Renderable.h"
#include "Map.h"
#include "Agent.h"
#include <iostream>
#include "NPC.h"

const float screenWidth = 1050.0f;
const float screenHeight = 1200.0f;
bool movementFlag = true;
sf::RenderWindow *window;
	
std::vector<Renderable*> toRender;
std::vector<Interactive*> toInteract;
std::vector<Moving*> toMove;
std::vector<Behaving*> toBehave;

int main()
{
	window = new sf::RenderWindow(sf::VideoMode(static_cast<unsigned int>(screenWidth), static_cast<unsigned int>(screenHeight)), "Sims");
	window->setVerticalSyncEnabled(true);

	Map* map = new Map(screenWidth, screenHeight, "./Assets/house30.png");
	toRender.push_back(map);
	toInteract.push_back(map);

	NPC* mainCharacter = new NPC("./Assets/Panda.png", sf::Vector2i(15,15), map);
	toRender.push_back(mainCharacter);
	toMove.push_back(mainCharacter);
	toBehave.push_back(mainCharacter);

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

		//Behaving
		for(auto b : toBehave)
		{
			b->Behave();
		}

		//Moving
		if(movementFlag && totalMoveTime > 0.20f)
		{
			float fps = 1.0f / (currentFpsTime);
			window->setTitle("Pathfinding (" + std::to_string(static_cast<int>(fps)) + ")");

			for(auto m : toMove)
			{
				m->Move();
			}
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
