#include "Bed.h"

Bed::Bed(const std::string filename, sf::Vector2i startingIndex, Map* mapPtr) : Agent(filename, startingIndex, mapPtr)
{
}

Bed::~Bed()
{
}

bool Bed::Interact()
{
	return true;
}

sf::Vector2i Bed::GetIndex()
{
	return positionIndex;
}

void Bed::Move()
{
}
