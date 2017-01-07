#pragma once
#include "Object.h"
#include "Agent.h"

class Chair : public Object, public Agent
{
public:
	Chair(const std::string filename, sf::Vector2i startingIndex, Map* mapPtr);
	~Chair();

	bool Interact() override;
	sf::Vector2i GetIndex() override;
	void Move() override;
};