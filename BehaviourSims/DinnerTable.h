#pragma once
#include "Object.h"
#include "Agent.h"

class DinnerTable : public Object, public Agent
{
public:
	DinnerTable(const std::string filename, sf::Vector2i startingIndex, Map* mapPtr);
	~DinnerTable();

	bool Interact() override;
	sf::Vector2i GetIndex() override;
	void Move() override;
};
