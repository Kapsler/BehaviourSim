#pragma once
#include <string>
#include "Door.h"
#include <unordered_map>
#include "Toilet.h"
#include "Bed.h"

class GameWorld
{
public:
	static GameWorld& getInstance();

	void AddDoor(const std::string doorName, Door* door);
	Door* GetDoor(const std::string doorName);
	void AddToilet(const std::string toiletName, Toilet* toilet);
	Toilet* GetToilet(const std::string toiletName);
	void AddBed(const std::string bedName, Bed* bed);
	Bed* GetBed(const std::string bedName);

private:

	std::unordered_map<std::string, Door*> doors;
	std::unordered_map<std::string, Toilet*> toilets;
	std::unordered_map<std::string, Bed*> beds;

	GameWorld();
	~GameWorld();
};
