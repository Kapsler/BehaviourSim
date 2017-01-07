#include "GameWorld.h"

GameWorld& GameWorld::getInstance()
{
	static GameWorld instance;
	return instance;
}

void GameWorld::AddDoor(const std::string doorName, Door* door)
{
	doors.insert_or_assign(doorName, door);
	AddObject(doorName, door);
}

Door* GameWorld::GetDoor(const std::string doorName)
{
	return doors.find(doorName)->second;
}

void GameWorld::AddToilet(const std::string toiletName, Toilet* toilet)
{
	toilets.insert_or_assign(toiletName, toilet);
	AddObject(toiletName, toilet);
}

Toilet* GameWorld::GetToilet(const std::string toiletName)
{
	return toilets.find(toiletName)->second;
}

void GameWorld::AddBed(const std::string bedName, Bed* bed)
{
	beds.insert_or_assign(bedName, bed);
	AddObject(bedName, bed);
}

Bed* GameWorld::GetBed(const std::string bedName)
{
	return beds.find(bedName)->second;
}

void GameWorld::AddFridge(const std::string fridgeName, Fridge* fridge)
{
	fridges.insert_or_assign(fridgeName, fridge);
	AddObject(fridgeName, fridge);
}

Fridge* GameWorld::GetFridge(const std::string fridgeName)
{
	return fridges.find(fridgeName)->second;
}

void GameWorld::AddObject(const std::string objectname, Object* object)
{
	objects.insert_or_assign(objectname, object);
}

Object* GameWorld::GetObject(const std::string objectName)
{
	return objects.at(objectName);
}

GameWorld::GameWorld()
{
}

GameWorld::~GameWorld()
{
}
