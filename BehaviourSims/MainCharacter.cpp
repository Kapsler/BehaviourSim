#include "MainCharacter.h"
#include <iostream>
#include <random>

MainCharacter::HasToPee::HasToPee(MainCharacter* targetChar)
{
	character = targetChar;
}

BehaviourTree::BehaviourStatus MainCharacter::HasToPee::run()
{
	if(character->urinaryUrgency > 50)
	{
		return BehaviourTree::Success;
	} else
	{
		return BehaviourTree::Failure;
	}
}

MainCharacter::IsSleepy::IsSleepy(MainCharacter* targetChar)
{
	character = targetChar;
}

BehaviourTree::BehaviourStatus MainCharacter::IsSleepy::run()
{
	if (character->energy < 200)
	{
		return BehaviourTree::Success;
	}
	else
	{
		return BehaviourTree::Failure;
	}
}

MainCharacter::RelieveUrgency::RelieveUrgency(MainCharacter* targetChar)
{
	character = targetChar;
}

BehaviourTree::BehaviourStatus MainCharacter::RelieveUrgency::run()
{
	character->urinaryUrgency = 0;
	return BehaviourTree::Success;
}

MainCharacter::Sleep::Sleep(MainCharacter* targetChar)
{
	character = targetChar;
}

BehaviourTree::BehaviourStatus MainCharacter::Sleep::run()
{
	if(character->energy > 900)
	{
		character->sleeping = false;
		return BehaviourTree::Success;
	}

	character->sleeping = true;
	character->energy += 90;
	character->energy += (rand() % 20) + 1;
	return BehaviourTree::Running;
}

MainCharacter::MainCharacter(const std::string filename, sf::Vector2i startingIndex, Map* mapPtr) : NPC(filename, startingIndex, mapPtr)
{
	tree = new BehaviourTree();

	//Root
	BehaviourTree::Repeat* live = new BehaviourTree::Repeat();
	tree->root = live;

	//Sleep Need
	live->addChild(generateSleepNode());

	//Toilet Need
	live->addChild(generateToiletNode());
}

BehaviourTree::Node* MainCharacter::generateToiletNode()
{

	BehaviourTree::Sequence* goOnToilet = new BehaviourTree::Sequence();
	BehaviourTree::Selector* openToiletDoor = new BehaviourTree::Selector();
	openToiletDoor->addChild(new Door::IsDoorOpen(GameWorld::getInstance().GetDoor("toiletdoor")));
	BehaviourTree::Sequence* openingTheToiletDoor = new BehaviourTree::Sequence();
	openingTheToiletDoor->addChild(new WalkToDoor(this, GameWorld::getInstance().GetDoor("toiletdoor")));
	openingTheToiletDoor->addChild(new Door::OpenDoorAction(GameWorld::getInstance().GetDoor("toiletdoor")));
	openToiletDoor->addChild(openingTheToiletDoor);
	goOnToilet->addChild(openToiletDoor);
	goOnToilet->addChild(new WalkToObject(this, GameWorld::getInstance().GetToilet("toilet")));
	goOnToilet->addChild(new InteractWithObject(this, GameWorld::getInstance().GetToilet("toilet")));
	goOnToilet->addChild(new RelieveUrgency(this));

	BehaviourTree::Selector* toiletBehaviour = new BehaviourTree::Selector();
	BehaviourTree::Inverter* invert = new BehaviourTree::Inverter();
	invert->setChild(new HasToPee(this));
	toiletBehaviour->addChild(invert);
	toiletBehaviour->addChild(goOnToilet);

	return toiletBehaviour;
}

BehaviourTree::Node* MainCharacter::generateSleepNode()
{
	BehaviourTree::Sequence* goToSleep = new BehaviourTree::Sequence();
	BehaviourTree::Selector* openBedroomDoor = new BehaviourTree::Selector();
	openBedroomDoor->addChild(new Door::IsDoorOpen(GameWorld::getInstance().GetDoor("bedroomdoor")));
	BehaviourTree::Sequence* openingTheBedroomDoor = new BehaviourTree::Sequence();
	openingTheBedroomDoor->addChild(new WalkToDoor(this, GameWorld::getInstance().GetDoor("bedroomdoor")));
	openingTheBedroomDoor->addChild(new Door::OpenDoorAction(GameWorld::getInstance().GetDoor("bedroomdoor")));
	openBedroomDoor->addChild(openingTheBedroomDoor);
	goToSleep->addChild(openBedroomDoor);
	goToSleep->addChild(new WalkToObject(this, GameWorld::getInstance().GetBed("bed")));
	goToSleep->addChild(new InteractWithObject(this, GameWorld::getInstance().GetBed("bed")));
	goToSleep->addChild(new Sleep(this));

	BehaviourTree::Selector* sleepBehaviour = new BehaviourTree::Selector();
	BehaviourTree::Inverter* invert = new BehaviourTree::Inverter();
	invert->setChild(new IsSleepy(this));
	sleepBehaviour->addChild(invert);
	sleepBehaviour->addChild(goToSleep);

	return sleepBehaviour;
}

void MainCharacter::Behave()
{
	std::cout << "Urinary Urgency: " << urinaryUrgency << std::endl;
	std::cout << "Energy: " << energy << std::endl;
	std::cout << std::endl;

	if (tree && tree->root)
	{
		tree->root->run();
	}

	urinaryUrgency += (rand() % 5) + 1;
	if(!sleeping)
	{
		energy -= ((rand() % 10) + 1);
	}

}
