#pragma once
#include "Object.h"
#include "Agent.h"

class MainCharacter;

class Fridge : public Object, public Agent
{
public:
	class TakeFood : public BehaviourTree::Node
	{
	public:
		TakeFood(MainCharacter* targetChar);

		BehaviourTree::BehaviourStatus run() override;

		MainCharacter* character;
	};

	Fridge(const std::string filename, sf::Vector2i startingIndex, Map* mapPtr);
	~Fridge();

	bool Interact() override;
	sf::Vector2i GetIndex() override;
	void Move() override;
};
