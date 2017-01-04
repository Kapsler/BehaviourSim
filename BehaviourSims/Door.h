#pragma once
#include "Object.h"
#include "Renderable.h"
#include "Agent.h"

class Door : public Object, public Agent
{
public:
	class OpenDoorAction : public BehaviourTree::Node
	{
	public:
		OpenDoorAction(Door* targetDoor);

		BehaviourTree::BehaviourStatus run() override;

		Door* door;
	};

	class CloseDoorAction : public BehaviourTree::Node
	{
	public:
		CloseDoorAction(Door* targetDoor);

		BehaviourTree::BehaviourStatus run() override;

		Door* door;
	};

	Door(const std::string filename, sf::Vector2i startingIndex, Map* mapPtr);
	~Door();

	void closeDoor();
	void openDoor();
	virtual void Interact() override;

	void Move() override;
	HexData* GetNextField() override;

	bool open = false;
};
