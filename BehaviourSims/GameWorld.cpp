#include "GameWorld.h"

GameWorld& GameWorld::getInstance()
{
	static GameWorld instance;
	return instance;
}

void GameWorld::AddDoor(const std::string doorName, Door* door)
{
	doors.insert_or_assign(doorName, door);
}

Door* GameWorld::GetDoor(const std::string doorName)
{
	return doors.find(doorName)->second;
}

GameWorld::GameWorld()
{
}

GameWorld::~GameWorld()
{
}
