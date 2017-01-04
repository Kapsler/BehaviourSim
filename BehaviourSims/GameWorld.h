#pragma once
#include <string>
#include "Door.h"
#include <unordered_map>

class GameWorld
{
public:
	static GameWorld& getInstance();

	void AddDoor(const std::string doorName, Door* door);
	Door* GetDoor(const std::string doorName);
private:

	std::unordered_map<std::string, Door*> doors;

	GameWorld();
	~GameWorld();
};
