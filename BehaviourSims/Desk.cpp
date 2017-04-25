#include "Desk.h"
#include "DoorStencil.h"
#include "MainCharacter.h"
#include <iostream>

Desk::Work::Work(MainCharacter* targetChar)
{
	character = targetChar;
}

BehaviourTree::BehaviourStatus Desk::Work::run()
{
	character->lastNode = "Work";

	character->work += 10 + (rand() % 10);

	//std::cout << "Work: Success" << std::endl;
	return BehaviourTree::Success;
}

Desk::Desk(const std::string filename, sf::Vector2i startingIndex, Map* mapPtr) : Agent(filename, startingIndex, mapPtr)
{
	SetThreatStencil(new DoorStencil());
}

Desk::~Desk()
{
}

bool Desk::Interact()
{
	return true;
}

sf::Vector2i Desk::GetIndex()
{
	return positionIndex;
}

void Desk::Move()
{
}
