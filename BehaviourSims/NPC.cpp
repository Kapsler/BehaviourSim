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
	npc->lastNode = "WalkToIndex";

	if (targetIndex == npc->positionIndex)
	{
		//std::cout << "WalkToIndex: Success" << std::endl;
		return BehaviourTree::Success;
	}

	bool result;
	HexData* nextHex = npc->GetNextField(targetIndex, result);

	if (result == false)
	{
		//std::cout << "WalkToIndex: Failure" << std::endl;
		return BehaviourTree::Failure;
	}

	npc->RotateStencil(nextHex);
	npc->positionIndex = nextHex->index;
	npc->position = nextHex->hex->getPosition();
	npc->sprite.setPosition(npc->position);

	//std::cout << "WalkToIndex: Running" << std::endl;
	return BehaviourTree::Running;
}

NPC::IsPathPossible::IsPathPossible(NPC* targetNpc, sf::Vector2i& target)
{
	npc = targetNpc;
	targetIndex = target;
}

NPC::IsPathPossible::IsPathPossible(NPC* targetNpc, Object* object)
{
	npc = targetNpc;
	targetIndex = object->GetIndex();
}

BehaviourTree::BehaviourStatus NPC::IsPathPossible::run()
{
	bool result;

	npc->lastNode = "IsPathPossible";

	if (targetIndex == npc->GetPositionIndex())
	{
		//std::cout << "IsPathPossible: Succcess" << std::endl;
		return BehaviourTree::Success;
	}

	npc->GetNextField(targetIndex, result);

	if (result == false)
	{
		//std::cout << "IsPathPossible: Failure" << std::endl;
		return BehaviourTree::Failure;
	} 

	//std::cout << "IsPathPossible: Succcess" << std::endl;
	return BehaviourTree::Success;
}

NPC::WalkToObject::WalkToObject(NPC* targetNpc, Object* object)
{
	npc = targetNpc;
	targetIndex = object->GetIndex();
}

BehaviourTree::BehaviourStatus NPC::WalkToObject::run()
{
	npc->lastNode = "WalkToObject";

	if (targetIndex == npc->positionIndex)
	{
		//std::cout << "WalkToObject: Success" << std::endl;
		return BehaviourTree::Success;
	}

	bool result;
	HexData* nextHex = npc->GetNextField(targetIndex, result);

	if (result == false)
	{
		//std::cout << "WalkToObject: Failure" << std::endl;
		return BehaviourTree::Failure;
	}

	npc->RotateStencil(nextHex);
	npc->positionIndex = nextHex->index;
	npc->position = nextHex->hex->getPosition();
	npc->sprite.setPosition(npc->position);

	//std::cout << "WalkToObject: Running" << std::endl;
	return BehaviourTree::Running;
}

NPC::WalkToDoor::WalkToDoor(NPC* targetNpc, Object* object)
{
	npc = targetNpc;
	targetIndex = object->GetIndex();
}

BehaviourTree::BehaviourStatus NPC::WalkToDoor::run()
{
	npc->lastNode = "WalkToDoor";

	bool result;
	HexData* nextHex = npc->GetNextField(targetIndex, result);

	if (targetIndex == nextHex->index)
	{
		//std::cout << "WalkToDoor: Success" << std::endl;
		return BehaviourTree::Success;
	}

	if (result == false)
	{
		//std::cout << "WalkToDoor: Failure" << std::endl;
		return BehaviourTree::Failure;
	}


	npc->RotateStencil(nextHex);
	npc->positionIndex = nextHex->index;
	npc->position = nextHex->hex->getPosition();
	npc->sprite.setPosition(npc->position);

	//std::cout << "WalkToDoor: Running" << std::endl;
	return BehaviourTree::Running;
}

NPC::InteractWithObject::InteractWithObject(NPC* targetNpc, Object* object)
{
	targetObject = object;
	npc = targetNpc;
}

BehaviourTree::BehaviourStatus NPC::InteractWithObject::run()
{
	npc->lastNode = "InteractWithObject";

	if(targetObject->Interact())
	{
		//std::cout << "InteractWithObject: Success" << std::endl;
		return BehaviourTree::Success;
	} 

	//std::cout << "InteractWithObject: Failure" << std::endl;
	return BehaviourTree::Failure;
	
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
