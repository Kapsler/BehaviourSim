#include "Door.h"
#include <iostream>
#include "EmptyThreatStencil.h"

Door::OpenDoorAction::OpenDoorAction(Door* targetDoor)
{
	door = targetDoor;
}

BehaviourTree::BehaviourStatus Door::OpenDoorAction::run()
{
	if(door->open)
	{
		//std::cout << "OpenDoor: Success" << std::endl;
		return BehaviourTree::Success;
	} 

	door->openDoor();
	
	if(door->open)
	{
		//std::cout << "OpenDoor: Running" << std::endl;
		return  BehaviourTree::Running;
	} 

	//std::cout << "OpenDoor: Failure" << std::endl;
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
		//std::cout << "CloseDoor: Success" << std::endl;
		return BehaviourTree::Success;
	}

	door->closeDoor();

	if (!door->open)
	{
		//std::cout << "CloseDoor: Running" << std::endl;
		return  BehaviourTree::Running;
	}

	//std::cout << "CloseDoor: Failure" << std::endl;
	return BehaviourTree::Failure;
}

Door::IsDoorOpen::IsDoorOpen(Door* targetDoor)
{
	door = targetDoor;
}

BehaviourTree::BehaviourStatus Door::IsDoorOpen::run()
{
	if(door->open)
	{
		//std::cout << "IsDoorOpen: Success" << std::endl;
		return BehaviourTree::Success;
	} else
	{
		//std::cout << "IsDoorOpen: Failure" << std::endl;
		return BehaviourTree::Failure;
	}
}

Door::Door(const std::string filename, sf::Vector2i startingIndex, Map* mapPtr): Agent(filename, startingIndex, mapPtr)
{
	closedThreatStencil = new DoorStencil();
	openThreatStencil = new EmptyThreatStencil();;

	closeDoor();
}

Door::~Door()
{
}

void Door::closeDoor()
{
	open = false;
	sprite.setRotation(0);

	SetThreatStencil(closedThreatStencil);
}

void Door::openDoor()
{
	open = true;
	sprite.rotate(90.0f);

	SetThreatStencil(openThreatStencil);
}

bool Door::Interact()
{
	return true;
}

void Door::Move()
{
}

HexData* Door::GetNextField()
{
	return new HexData();
}

sf::Vector2i Door::GetIndex()
{
	return positionIndex;
}
