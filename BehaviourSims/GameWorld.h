#pragma once
#include <string>
#include "Door.h"
#include <unordered_map>
#include "Toilet.h"
#include "Bed.h"
#include "Fridge.h"

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
	void AddFridge(const std::string fridgeName, Fridge* fridge);
	Fridge* GetFridge(const std::string fridgeName);
	void AddObject(const std::string objectname, Object* object);
	Object* GetObject(const std::string objectName);



private:

	std::unordered_map<std::string, Door*> doors;
	std::unordered_map<std::string, Toilet*> toilets;
	std::unordered_map<std::string, Bed*> beds;
	std::unordered_map<std::string, Fridge*> fridges;
	std::unordered_map<std::string, Object*> objects;

	GameWorld();
	~GameWorld();
};
