#pragma once
#include "Agent.h"

class NPC : public Agent, public Behaving
{
	class WalkToIndex : public BehaviourTree::Node
	{
		WalkToIndex(sf::Vector2i& target);

		virtual BehaviourTree::BehaviourStatus run() override;

		sf::Vector2i targetIndex;
		NPC* npc = nullptr;
	};

public:
	NPC(const std::string filename, sf::Vector2i startingIndex, Map* mapPtr);

	virtual void Behave() override;

	virtual bool GoToIndex(sf::Vector2i target);

	virtual HexData* GetNextField(sf::Vector2i target, bool& result);
};