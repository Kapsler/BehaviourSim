#include "NPC.h"
#include <iostream>
#include "Door.h"
#include "GameWorld.h"

NPC::WalkToIndex::WalkToIndex(NPC* targetNpc, sf::Vector2i& target)
{
	targetIndex = target;
	npc = targetNpc;
}

BehaviourTree::BehaviourStatus NPC::WalkToIndex::run()
{
	return npc->GoToIndex(targetIndex);
}

NPC::NPC(const std::string filename, sf::Vector2i startingIndex, Map* mapPtr) : Agent(filename, startingIndex, mapPtr)
{
	tree = new BehaviourTree();

	BehaviourTree::Sequence* walkAroundSequence = new BehaviourTree::Sequence();
	BehaviourTree::Node* gotonode1 = new WalkToIndex(this, sf::Vector2i(18, 18));
	Door::OpenDoorAction* openDoorNode = new Door::OpenDoorAction(GameWorld::getInstance().GetDoor("door1"));
	BehaviourTree::Node* gotonode2 = new WalkToIndex(this, sf::Vector2i(15, 15));
	Door::CloseDoorAction* closeDoorNode = new Door::CloseDoorAction(GameWorld::getInstance().GetDoor("door1"));
	
	walkAroundSequence->addChild(gotonode1);
	walkAroundSequence->addChild(openDoorNode);
	walkAroundSequence->addChild(gotonode2);
	walkAroundSequence->addChild(closeDoorNode);

	tree->root = walkAroundSequence;
}

void NPC::Behave()
{
	
	if (tree && tree->root)
	{
		tree->root->run();
	}
}

BehaviourTree::BehaviourStatus NPC::GoToIndex(sf::Vector2i target)
{
	if(target == positionIndex)
	{
		return BehaviourTree::Success;
	}

	bool result;
	HexData* nextHex = GetNextField(target, result);

	if(result == false)
	{
		return BehaviourTree::Failure;
	}

	RotateStencil(nextHex);
	positionIndex = nextHex->index;
	position = nextHex->hex->getPosition();
	sprite.setPosition(position);


	return BehaviourTree::Running;
}

HexData* NPC::GetNextField(sf::Vector2i indexOfTarget, bool& result)
{
	HexData* target = map->GetHexDatByIndex(indexOfTarget.x, indexOfTarget.y);

	pathToFollow.clear();

	pathToFollow = map->AStarPath((*map->GetMapPtr())[positionIndex.x][positionIndex.y], target, *map->GetMapPtr(), this);

	if (pathToFollow.size() > 1)
	{
		HexData* nextField = pathToFollow[1];

		result = true;
		return nextField;
	}
	
	result = false;
	return map->GetHexDatByIndex(positionIndex.x, positionIndex.y);
}
