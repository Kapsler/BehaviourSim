#pragma once
#include "NPC.h"

class MainCharacter : public NPC
{
public:

	class HasToPee : public BehaviourTree::Node
	{
	public:
		HasToPee(MainCharacter* targetChar);

		virtual BehaviourTree::BehaviourStatus run() override;

		MainCharacter* character = nullptr;
	};

	class IsSleepy : public BehaviourTree::Node
	{
	public:
		IsSleepy(MainCharacter* targetChar);

		virtual BehaviourTree::BehaviourStatus run() override;

		MainCharacter* character = nullptr;
	};

	class RelieveUrgency : public BehaviourTree::Node
	{
	public:
		RelieveUrgency(MainCharacter* targetChar);

		virtual BehaviourTree::BehaviourStatus run() override;

		MainCharacter* character = nullptr;
	};

	class Sleep : public BehaviourTree::Node
	{
	public:
		Sleep(MainCharacter* targetChar);

		virtual BehaviourTree::BehaviourStatus run() override;

		MainCharacter* character = nullptr;
	};


	MainCharacter(const std::string filename, sf::Vector2i startingIndex, Map* mapPtr);

	BehaviourTree::Node* generateToiletNode();
	BehaviourTree::Node* generateSleepNode();

	void Behave() override;
	float urinaryUrgency = 0;
	float energy = 1000;

	bool sleeping = false;
};