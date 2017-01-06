#include "Toilet.h"

Toilet::Toilet(const std::string filename, sf::Vector2i startingIndex, Map* mapPtr) : Agent(filename, startingIndex, mapPtr)
{
}

Toilet::~Toilet()
{
}

bool Toilet::Interact()
{
	return true;
}

sf::Vector2i Toilet::GetIndex()
{
	return positionIndex;
}

void Toilet::Move()
{
}
