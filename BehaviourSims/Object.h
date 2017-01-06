#pragma once
#include "ThreatStencil.h"

class Object
{
public:

	virtual bool Interact() = 0;
	virtual sf::Vector2i GetIndex() = 0;
};