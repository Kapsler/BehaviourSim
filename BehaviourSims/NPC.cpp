#include "NPC.h"

NPC::WalkToIndex::WalkToIndex(sf::Vector2i& target)
{
	targetIndex = target;
}

BehaviourTree::BehaviourStatus NPC::WalkToIndex::run()
{
	bool result = npc->GoToIndex(targetIndex);
	//Fix Results!

	if(result)
	{
		return BehaviourTree::Success;
	} else
	{
		return BehaviourTree::Failure;
	}
}

NPC::NPC(const std::string filename, sf::Vector2i startingIndex, Map* mapPtr) : Agent(filename, startingIndex, mapPtr)
{
	tree = new BehaviourTree();

	
	
	//Add Nodes


}

void NPC::Behave()
{
	if (tree)
	{
		tree->root->run();
	}
}

bool NPC::GoToIndex(sf::Vector2i target)
{
	bool result = false;
	HexData* nextHex = GetNextField(target, result);

	RotateStencil(nextHex);
	positionIndex = nextHex->index;
	position = nextHex->hex->getPosition();
	sprite.setPosition(position);

	return result;
}

HexData* NPC::GetNextField(sf::Vector2i indexOfTarget, bool& result)
{
	HexData* target = map->GetHexDatByIndex(indexOfTarget.x, indexOfTarget.y);

	pathToFollow.clear();


	pathToFollow = map->AStarPath((*map->GetMapPtr())[positionIndex.x][positionIndex.y], target, *map->GetMapPtr(), this, result);

	if (pathToFollow.size() > 1)
	{
		HexData* nextField = pathToFollow[1];

		return nextField;
	}
	
	return map->GetHexDatByIndex(positionIndex.x, positionIndex.y);
}
