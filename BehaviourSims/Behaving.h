#pragma once

class Behaving
{
public:
	virtual void Behave() = 0;

	BehaviourTree* tree = nullptr;
};