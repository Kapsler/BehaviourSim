#pragma once
#include "Object.h"
#include "Agent.h"

class Bed : public Object, public Agent
{
public:

	Bed(const std::string filename, sf::Vector2i startingIndex, Map* mapPtr);
	~Bed();

	bool Interact() override;
	sf::Vector2i GetIndex() override;
	void Move() override;
};
