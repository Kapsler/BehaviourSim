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

void GameWorld::AddToilet(const std::string toiletName, Toilet* toilet)
{
	toilets.insert_or_assign(toiletName, toilet);
}

Toilet* GameWorld::GetToilet(const std::string toiletName)
{
	return toilets.find(toiletName)->second;
}

void GameWorld::AddBed(const std::string bedName, Bed* bed)
{
	beds.insert_or_assign(bedName, bed);
}

Bed* GameWorld::GetBed(const std::string bedName)
{
	return beds.find(bedName)->second;
}

GameWorld::GameWorld()
{
}

GameWorld::~GameWorld()
{
}
