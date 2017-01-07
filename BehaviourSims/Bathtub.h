#pragma once
#include "Object.h"
#include "Agent.h"

class MainCharacter;

class Bathtub : public Object, public Agent
{
public:
	class TakeShower : public BehaviourTree::Node
	{
	public:
		TakeShower(MainCharacter* targetChar);

		BehaviourTree::BehaviourStatus run() override;

		MainCharacter* character;
	};

	Bathtub(const std::string filename, sf::Vector2i startingIndex, Map* mapPtr);
	~Bathtub();

	bool Interact() override;
	sf::Vector2i GetIndex() override;
	void Move() override;
};
