#include "Chair.h"

Chair::Chair(const std::string filename, sf::Vector2i startingIndex, Map* mapPtr) : Agent(filename, startingIndex, mapPtr)
{
}

Chair::~Chair()
{
}

bool Chair::Interact()
{
	return true;
}

sf::Vector2i Chair::GetIndex()
{
	return positionIndex;
}

void Chair::Move()
{
}
