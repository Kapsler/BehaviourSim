#include "BehaviourTree.h"

void BehaviourTree::CompositeNode::addChild(Node* child)
{
	children.push_back(child);
}

void BehaviourTree::CompositeNode::addChildren(std::vector<Node*>& newChrildren)
{
	for(auto nc : newChrildren)
	{
		children.push_back(nc);
	}
}

void BehaviourTree::DecoratorNode::setChild(Node* newChild)
{
	child = newChild;
}

BehaviourTree::BehaviourStatus BehaviourTree::Selector::run()
{
	for (int i = startingIndex; i < children.size(); i++)
	{
		BehaviourStatus result = children[i]->run();

		if (result == Success)
		{
			startingIndex = 0;
			return Success;
		}
		if (result == Running)
		{
			startingIndex = i;
			return Running;
		}
	}

	return Failure;
}

BehaviourTree::BehaviourStatus BehaviourTree::Sequence::run()
{
	for (int i = startingIndex; i < children.size(); i++)
	{
		BehaviourStatus result = children[i]->run();

		if(result == Failure)
		{
			startingIndex = 0;
			return Failure;
		}
		if(result == Running)
		{
			startingIndex = i;
			return Running;
		}
	}

	startingIndex = 0;
	return Success;
}

BehaviourTree::BehaviourStatus BehaviourTree::RepeatUntilFail::run()
{
	for (auto c : children)
	{
		if (c->run() == Failure)
		{
			return Success;
		}
	}

	return Running;
}

BehaviourTree::BehaviourStatus BehaviourTree::Repeat::run()
{
	for (int i = startingIndex; i < children.size(); i++)
	{
		BehaviourStatus result = children[i]->run();

		if (result != Running)
		{
			startingIndex = 0;
		}
		if (result == Running)
		{
			return Running;
		}
	}
}

BehaviourTree::BehaviourStatus BehaviourTree::Inverter::run()
{
	BehaviourStatus result = child->run();

	switch (result)
	{
	case Success:
		return Failure;
	case Failure:
		return Success;
	case Running:
		return Running;
	default:
		return Failure;
	}
}

BehaviourTree::BehaviourStatus BehaviourTree::Successor::run()
{
	child->run();

	return Success;
}
