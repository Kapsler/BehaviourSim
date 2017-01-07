#include "Bathtub.h"
#include "MainCharacter.h"
#include <iostream>

Bathtub::TakeShower::TakeShower(MainCharacter* targetChar)
{
	character = targetChar;
}

BehaviourTree::BehaviourStatus Bathtub::TakeShower::run()
{
	if(character->hygene > 800)
	{
		std::cout << "TakeShower: Success" << std::endl;
		return BehaviourTree::Success;
	}

	character->hygene += 100 + (rand() % 100);

	std::cout << "TakeShower: Running" << std::endl;
	return BehaviourTree::Running;
}

Bathtub::Bathtub(const std::string filename, sf::Vector2i startingIndex, Map* mapPtr) : Agent(filename, startingIndex, mapPtr)
{
}

Bathtub::~Bathtub()
{
}

bool Bathtub::Interact()
{
	return true;
}

sf::Vector2i Bathtub::GetIndex()
{
	return positionIndex;
}

void Bathtub::Move()
{
}