#pragma once
#include "Object.h"
#include "Renderable.h"

class Door : public Object, public Renderable
{
public:
	Door();
	~Door();

	virtual void Interact() override;

	virtual void Render(sf::RenderWindow* window) override;
	virtual void DebugRender(sf::RenderWindow* window) override;
};
