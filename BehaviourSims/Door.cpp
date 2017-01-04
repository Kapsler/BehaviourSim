#include "Door.h"

Door::OpenDoorAction::OpenDoorAction(Door* targetDoor)
{
	door = targetDoor;
}

BehaviourTree::BehaviourStatus Door::OpenDoorAction::run()
{
	if(door->open)
	{
		return BehaviourTree::Success;
	} 

	door->Interact();
	
	if(door->open)
	{
		return  BehaviourTree::Success;
	} 

	return BehaviourTree::Failure;
	
}

Door::CloseDoorAction::CloseDoorAction(Door* targetDoor)
{
	door = targetDoor;
}

BehaviourTree::BehaviourStatus Door::CloseDoorAction::run()
{
	if (!door->open)
	{
		return BehaviourTree::Success;
	}

	door->Interact();

	if (!door->open)
	{
		return  BehaviourTree::Success;
	}

	return BehaviourTree::Failure;
}

Door::Door(const std::string filename, sf::Vector2i startingIndex, Map* mapPtr): Agent(filename, startingIndex, mapPtr)
{
}

Door::~Door()
{
}

void Door::closeDoor()
{
	open = false;
	sprite.rotate(-90.0f);
}

void Door::openDoor()
{
	open = true;
	sprite.rotate(90.0f);
}

void Door::Interact()
{
	if(open)
	{
		closeDoor();
	} else
	{
		openDoor();
	}
}

void Door::Move()
{
}

HexData* Door::GetNextField()
{
	return new HexData();
}
