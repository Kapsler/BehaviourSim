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
	if (targetIndex == npc->positionIndex)
	{
		return BehaviourTree::Success;
	}

	bool result;
	HexData* nextHex = npc->GetNextField(targetIndex, result);

	if (result == false)
	{
		return BehaviourTree::Failure;
	}

	npc->RotateStencil(nextHex);
	npc->positionIndex = nextHex->index;
	npc->position = nextHex->hex->getPosition();
	npc->sprite.setPosition(npc->position);

	return BehaviourTree::Running;
}

NPC::WalkToObject::WalkToObject(NPC* targetNpc, Object* object)
{
	npc = targetNpc;
	targetIndex = object->GetIndex();
}

BehaviourTree::BehaviourStatus NPC::WalkToObject::run()
{
	if (targetIndex == npc->positionIndex)
	{
		return BehaviourTree::Success;
	}

	bool result;
	HexData* nextHex = npc->GetNextField(targetIndex, result);

	if (result == false)
	{
		return BehaviourTree::Failure;
	}

	npc->RotateStencil(nextHex);
	npc->positionIndex = nextHex->index;
	npc->position = nextHex->hex->getPosition();
	npc->sprite.setPosition(npc->position);

	return BehaviourTree::Running;
}

NPC::WalkToDoor::WalkToDoor(NPC* targetNpc, Object* object)
{
	npc = targetNpc;
	targetIndex = object->GetIndex();
}

BehaviourTree::BehaviourStatus NPC::WalkToDoor::run()
{
	bool result;
	HexData* nextHex = npc->GetNextField(targetIndex, result);

	if (result == false)
	{
		return BehaviourTree::Failure;
	}

	if (targetIndex == nextHex->index)
	{
		return BehaviourTree::Success;
	}

	npc->RotateStencil(nextHex);
	npc->positionIndex = nextHex->index;
	npc->position = nextHex->hex->getPosition();
	npc->sprite.setPosition(npc->position);

	return BehaviourTree::Running;
}

NPC::InteractWithObject::InteractWithObject(NPC* targetNpc, Object* object)
{
	targetObject = object;
	npc = targetNpc;
}

BehaviourTree::BehaviourStatus NPC::InteractWithObject::run()
{
	if(targetObject->Interact())
	{
		return BehaviourTree::Success;
	} else
	{
		return BehaviourTree::Failure;
	}
}

NPC::NPC(const std::string filename, sf::Vector2i startingIndex, Map* mapPtr) : Agent(filename, startingIndex, mapPtr)
{

}

void NPC::Behave()
{
	
	if (tree && tree->root)
	{
		tree->root->run();
	}
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
