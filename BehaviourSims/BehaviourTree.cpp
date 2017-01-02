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
	for (auto c : children)
	{
		if (c->run() == Success)
		{
			return Success;
		}
	}

	return Failure;
}

BehaviourTree::BehaviourStatus BehaviourTree::Sequence::run()
{
	for (auto c : children)
	{
		if (c->run() == Failure)
		{
			return Failure;
		}
	}

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
	for (auto c : children)
	{
		c->run();
	}

	return Running;
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
