#include "Fridge.h"
#include "MainCharacter.h"

Fridge::TakeFood::TakeFood(MainCharacter* targetChar)
{
	character = targetChar;
}

BehaviourTree::BehaviourStatus Fridge::TakeFood::run()
{
	character->lastNode = "TakeFood";

	character->inventory.insert_or_assign("food", character->inventory.at("food") + 1);
	return BehaviourTree::Success;
}

Fridge::Fridge(const std::string filename, sf::Vector2i startingIndex, Map* mapPtr) : Agent(filename, startingIndex, mapPtr)
{
}

Fridge::~Fridge()
{
}

bool Fridge::Interact()
{
	return true;
}

sf::Vector2i Fridge::GetIndex()
{
	return positionIndex;
}

void Fridge::Move()
{
}
