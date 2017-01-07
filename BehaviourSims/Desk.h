#pragma once
#include "Object.h"
#include "Agent.h"

class MainCharacter;

class Desk : public Object, public Agent
{
public:
	class Work : public BehaviourTree::Node
	{
	public:
		Work(MainCharacter* targetChar);

		BehaviourTree::BehaviourStatus run() override;

		MainCharacter* character;
	};

	Desk(const std::string filename, sf::Vector2i startingIndex, Map* mapPtr);
	~Desk();

	bool Interact() override;
	sf::Vector2i GetIndex() override;
	void Move() override;
};
