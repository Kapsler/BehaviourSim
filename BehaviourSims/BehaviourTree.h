#pragma once
#include <vector>

class BehaviourTree {
public: 
	
	enum BehaviourStatus
	{
		Success,
		Failure,
		Running
	};

	class Node {
		public:
		virtual BehaviourStatus run() = 0;
	};

	class CompositeNode : public Node
	{
	public:
		void addChild(Node* child);
		void addChildren(std::vector<Node*>& newChrildren);

		std::vector<Node*> children;

		int startingIndex = 0;
	};

	class DecoratorNode : public Node
	{
	public:
		void setChild(Node* newChild);

		Node* child = nullptr;;
	};

	class Selector : public CompositeNode
	{
	public:
		virtual BehaviourStatus run() override;
	};

	class Sequence : public CompositeNode
	{
		virtual BehaviourStatus run() override;
	};

	class RepeatUntilFail : public CompositeNode
	{
		virtual BehaviourStatus run() override;
	};

	class Repeat : public CompositeNode
	{
		virtual BehaviourStatus run() override;
	};

	class Inverter : public DecoratorNode
	{
		virtual BehaviourStatus run() override;
	};

	class Successor : public DecoratorNode
	{
		virtual BehaviourStatus run() override;
	};

	Node* root = nullptr;
};
