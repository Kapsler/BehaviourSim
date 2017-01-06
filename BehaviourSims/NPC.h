#pragma once
#include "Agent.h"
#include "Door.h"
#include "GameWorld.h"

class Object;

class NPC : public Agent, public Behaving
{
public:

	class WalkToIndex : public BehaviourTree::Node
	{
	public:
		WalkToIndex(NPC* targetNpc, sf::Vector2i& target);

		virtual BehaviourTree::BehaviourStatus run() override;

		sf::Vector2i targetIndex;
		NPC* npc = nullptr;
	};

	class WalkToObject : public BehaviourTree::Node
	{
	public:
		WalkToObject(NPC* targetNpc, Object* object);

		virtual BehaviourTree::BehaviourStatus run() override;

		sf::Vector2i targetIndex;
		NPC* npc = nullptr;
	};

	class WalkToDoor : public BehaviourTree::Node
	{
	public:
		WalkToDoor(NPC* targetNpc, Object* object);

		virtual BehaviourTree::BehaviourStatus run() override;

		sf::Vector2i targetIndex;
		NPC* npc = nullptr;
	};

	class InteractWithObject : public BehaviourTree::Node
	{
	public:
		InteractWithObject(NPC* targetNpc, Object* object);

		virtual BehaviourTree::BehaviourStatus run() override;

		Object* targetObject;
		NPC* npc = nullptr;
	};

	NPC(const std::string filename, sf::Vector2i startingIndex, Map* mapPtr);

	virtual void Behave() override;

	virtual HexData* GetNextField(sf::Vector2i target, bool& result);
};
