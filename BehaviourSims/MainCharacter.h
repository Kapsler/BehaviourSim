#pragma once
#include "NPC.h"

class MainCharacter : public NPC
{
public:
	class IsDead : public BehaviourTree::Node
	{
	public:
		IsDead(MainCharacter* targetChar);

		virtual BehaviourTree::BehaviourStatus run() override;

		MainCharacter* character = nullptr;
	};
	
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

	class IsDirty : public BehaviourTree::Node
	{
	public:
		IsDirty(MainCharacter* targetChar);

		virtual BehaviourTree::BehaviourStatus run() override;

		MainCharacter* character = nullptr;
	};

	class IsHungry : public BehaviourTree::Node
	{
	public:
		IsHungry(MainCharacter* targetChar);

		virtual BehaviourTree::BehaviourStatus run() override;

		MainCharacter* character = nullptr;
	};

	class IsOverworked : public BehaviourTree::Node
	{
	public:
		IsOverworked(MainCharacter* targetChar);

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

	class Eat : public BehaviourTree::Node
	{
	public:
		Eat(MainCharacter* targetChar);

		virtual BehaviourTree::BehaviourStatus run() override;

		MainCharacter* character = nullptr;
	};

	class HasInInventory : public BehaviourTree::Node
	{
	public:
		HasInInventory(MainCharacter* targetChar, const std::string targetItem);

		virtual BehaviourTree::BehaviourStatus run() override;

		MainCharacter* character;
		std::string itemName;
	};

	MainCharacter(const std::string filename, sf::Vector2i startingIndex, Map* mapPtr);

	BehaviourTree::Node* generateToiletNode();
	BehaviourTree::Node* generateSleepNode();
	BehaviourTree::Node* generateEatingNode();
	BehaviourTree::Node* generateHygeneNode();
	BehaviourTree::Node* generateWorkNode();
	BehaviourTree::Node* generatePathNode(const std::string doorName, const std::string objectName);

	void Behave() override;
	void Render(sf::RenderWindow* window) override;
	float urinaryUrgency = 0;
	float energy = 1000;
	float hunger = 0;
	float hygene = 1000;
	float work = 500;

	bool sleeping = false;
	bool eating = false;

	bool dead = false;

	std::unordered_map<std::string, int> inventory;

	sf::Font debugFont;
	sf::Text debugText;
};