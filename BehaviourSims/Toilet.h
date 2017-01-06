#pragma once
#include "Object.h"
#include "Agent.h"

class Toilet : public Object, public Agent
{
public:

	Toilet(const std::string filename, sf::Vector2i startingIndex, Map* mapPtr);
	~Toilet();

	bool Interact() override;
	sf::Vector2i GetIndex() override;
	void Move() override;
};
