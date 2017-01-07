#include "DinnerTable.h"
#include "Door.h"

DinnerTable::DinnerTable(const std::string filename, sf::Vector2i startingIndex, Map* mapPtr) : Agent(filename, startingIndex, mapPtr)
{
	SetThreatStencil(new DoorStencil());
}

DinnerTable::~DinnerTable()
{
}

bool DinnerTable::Interact()
{
	return true;
}

sf::Vector2i DinnerTable::GetIndex()
{
	return positionIndex;
}

void DinnerTable::Move()
{
}
