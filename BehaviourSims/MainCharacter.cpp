#include "MainCharacter.h"
#include <iostream>
#include <random>
#include "Bathtub.h"
#include "Desk.h"

MainCharacter::IsDead::IsDead(MainCharacter* targetChar)
{
	character = targetChar;
}

BehaviourTree::BehaviourStatus MainCharacter::IsDead::run()
{
	if(character->energy < 0)
	{
		std::cout << "Died of energy" << std::endl;
		character->dead = true;
		return BehaviourTree::Running;
	}
	if(character->hygene < 0)
	{
		std::cout << "Died of hygene" << std::endl;
		character->dead = true;
		return BehaviourTree::Running;
	}
	if(character->hunger > 1000)
	{
		std::cout << "Died of hunger" << std::endl;
		character->dead = true;
		return BehaviourTree::Running;
	}
	if(character->urinaryUrgency > 500)
	{
		std::cout << "Died of urin" << std::endl;
		character->dead = true;
		return BehaviourTree::Running;
	}
	if(character->work > 2000)
	{
		std::cout << "Died of work" << std::endl;
		character->dead = true;
		return BehaviourTree::Running;
	}

	return BehaviourTree::Success;
}

MainCharacter::HasToPee::HasToPee(MainCharacter* targetChar)
{
	character = targetChar;
}

BehaviourTree::BehaviourStatus MainCharacter::HasToPee::run()
{
	if(character->urinaryUrgency > 100)
	{
		std::cout << "HasToPee: Success" << std::endl;
		return BehaviourTree::Success;
	} else
	{
		std::cout << "HasToPee: Failure" << std::endl;
		return BehaviourTree::Failure;
	}
}

MainCharacter::IsSleepy::IsSleepy(MainCharacter* targetChar)
{
	character = targetChar;
}

BehaviourTree::BehaviourStatus MainCharacter::IsSleepy::run()
{
	if (character->energy < 400)
	{
		std::cout << "IsSleepy: Success" << std::endl;
		return BehaviourTree::Success;
	}

	std::cout << "IsSleepy: Failure" << std::endl;
	return BehaviourTree::Failure;
}

MainCharacter::IsDirty::IsDirty(MainCharacter* targetChar)
{
	character = targetChar;
}

BehaviourTree::BehaviourStatus MainCharacter::IsDirty::run()
{
	if (character->hygene < 350)
	{
		std::cout << "IsDirty: Success" << std::endl;
		return BehaviourTree::Success;
	}

	std::cout << "isDirty: Failure" << std::endl;
	return BehaviourTree::Failure;
}

MainCharacter::IsHungry::IsHungry(MainCharacter* targetChar)
{
	character = targetChar;
}

BehaviourTree::BehaviourStatus MainCharacter::IsHungry::run()
{
	if (character->hunger > 400)
	{
		std::cout << "IsHungry: Success" << std::endl;
		return BehaviourTree::Success;
	}

	std::cout << "IsHungry: Failure" << std::endl;
	return BehaviourTree::Failure;
}

MainCharacter::IsOverworked::IsOverworked(MainCharacter* targetChar)
{
	character = targetChar;
}

BehaviourTree::BehaviourStatus MainCharacter::IsOverworked::run()
{
	if(character->work > 1000)
	{
		return BehaviourTree::Success;
	}

	return BehaviourTree::Failure;
}

MainCharacter::RelieveUrgency::RelieveUrgency(MainCharacter* targetChar)
{
	character = targetChar;
}

BehaviourTree::BehaviourStatus MainCharacter::RelieveUrgency::run()
{
	character->urinaryUrgency = 0;
	character->hunger += 50;
	character->hygene -= 200;
	std::cout << "Relieve: Success" << std::endl;
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
		std::cout << "Sleep: Success" << std::endl;
		return BehaviourTree::Success;
	}

	character->sleeping = true;
	character->energy += 90;
	character->energy += (rand() % 20) + 1;
	std::cout << "Sleep: Running" << std::endl;
	return BehaviourTree::Running;
}

MainCharacter::Eat::Eat(MainCharacter* targetChar)
{
	character = targetChar;
}

BehaviourTree::BehaviourStatus MainCharacter::Eat::run()
{
	if(character->inventory.at("food") > 0)
	{
		character->inventory.insert_or_assign("food", character->inventory.at("food") - 1);
		character->hunger -= 600 + (rand()%200);
		return BehaviourTree::Success;
	}

	return BehaviourTree::Failure;
}

MainCharacter::HasInInventory::HasInInventory(MainCharacter* targetChar, const std::string targetItem)
{
	character = targetChar;
	itemName = targetItem;
}

BehaviourTree::BehaviourStatus MainCharacter::HasInInventory::run()
{
	if (character->inventory.find(itemName) != character->inventory.end())
	{
		if(character->inventory.at(itemName) > 0)
		{
			return BehaviourTree::Success;
		}
	}

	return BehaviourTree::Failure;
}

MainCharacter::MainCharacter(const std::string filename, sf::Vector2i startingIndex, Map* mapPtr) : NPC(filename, startingIndex, mapPtr)
{
	inventory.insert_or_assign("food", 0);

	tree = new BehaviourTree();

	//Root
	BehaviourTree::Repeat* live = new BehaviourTree::Repeat();
	tree->root = live;

	//Eating Need
	live->addChild(new IsDead(this));

	//Eating Need
	live->addChild(generateEatingNode());

	//Sleep Need
	live->addChild(generateSleepNode());

	//Toilet Need
	live->addChild(generateToiletNode());

	//Hygene Need
	live->addChild(generateHygeneNode());

	//Work
	live->addChild(generateWorkNode());

}

BehaviourTree::Node* MainCharacter::generateToiletNode()
{

	BehaviourTree::Sequence* goOnToilet = new BehaviourTree::Sequence();
	goOnToilet->addChild(generatePathNode("toiletdoor","toilet"));
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
	goToSleep->addChild(generatePathNode("bedroomdoor", "bed"));
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

BehaviourTree::Node* MainCharacter::generateEatingNode()
{
	BehaviourTree::Sequence* goEat = new BehaviourTree::Sequence();
	BehaviourTree::Selector* foodSelector = new BehaviourTree::Selector();
	foodSelector->addChild(new HasInInventory(this, "food"));
	BehaviourTree::Sequence* getFoodSequence = new BehaviourTree::Sequence();
	getFoodSequence->addChild(generatePathNode("kitchendoor", "fridge"));
	getFoodSequence->addChild(new WalkToDoor(this, GameWorld::getInstance().GetObject("fridge")));
	getFoodSequence->addChild(new Fridge::TakeFood(this));
	foodSelector->addChild(getFoodSequence);
	goEat->addChild(foodSelector);
	goEat->addChild(generatePathNode("kitchendoor", "dinnerchair"));
	goEat->addChild(new WalkToObject(this, GameWorld::getInstance().GetObject("dinnerchair")));
	goEat->addChild(new Eat(this));

	BehaviourTree::Selector* eatBehaviour = new BehaviourTree::Selector();
	BehaviourTree::Inverter* invert = new BehaviourTree::Inverter();
	invert->setChild(new IsHungry(this));
	eatBehaviour->addChild(invert);
	eatBehaviour->addChild(goEat);

	return eatBehaviour;
}

BehaviourTree::Node* MainCharacter::generateHygeneNode()
{
	BehaviourTree::Sequence* goShower = new BehaviourTree::Sequence();
	goShower->addChild(generatePathNode("bathroomdoor", "bathtub"));
	goShower->addChild(new WalkToObject(this, GameWorld::getInstance().GetObject("bathtub")));
	goShower->addChild(new InteractWithObject(this, GameWorld::getInstance().GetObject("bathtub")));
	goShower->addChild(new Bathtub::TakeShower(this));

	BehaviourTree::Selector* hygeneBehaviour = new BehaviourTree::Selector();
	BehaviourTree::Inverter* invert = new BehaviourTree::Inverter();
	invert->setChild(new IsDirty(this));
	hygeneBehaviour->addChild(invert);
	hygeneBehaviour->addChild(goShower);

	return hygeneBehaviour;
}

BehaviourTree::Node* MainCharacter::generateWorkNode()
{
	BehaviourTree::Sequence* goWork = new BehaviourTree::Sequence();
	goWork->addChild(generatePathNode("officedoor", "officechair"));
	goWork->addChild(new WalkToObject(this, GameWorld::getInstance().GetObject("officechair")));
	goWork->addChild(new InteractWithObject(this, GameWorld::getInstance().GetObject("officechair")));
	goWork->addChild(new Desk::Work(this));

	BehaviourTree::Selector* workbehaviour = new BehaviourTree::Selector();
	workbehaviour->addChild(new IsOverworked(this));
	workbehaviour->addChild(goWork);

	return workbehaviour;
}

BehaviourTree::Node* MainCharacter::generatePathNode(const std::string doorName, const std::string objectName)
{
	BehaviourTree::Selector* openDoorSelector = new BehaviourTree::Selector();
	openDoorSelector->addChild(new IsPathPossible(this, GameWorld::getInstance().GetObject(objectName)));
	openDoorSelector->addChild(new Door::IsDoorOpen(GameWorld::getInstance().GetDoor(doorName)));
	BehaviourTree::Sequence* openingDoorSequence = new BehaviourTree::Sequence();
	openingDoorSequence->addChild(new WalkToDoor(this, GameWorld::getInstance().GetDoor(doorName)));
	openingDoorSequence->addChild(new InteractWithObject(this, GameWorld::getInstance().GetDoor(doorName)));
	openingDoorSequence->addChild(new Door::OpenDoorAction(GameWorld::getInstance().GetDoor(doorName)));
	openDoorSelector->addChild(openingDoorSequence);

	return openDoorSelector;
}

void MainCharacter::Behave()
{
	if(!dead)
	{
		std::cout << std::endl;
		std::cout << "Urinary Urgency: " << urinaryUrgency << std::endl;
		std::cout << "Energy: " << energy << std::endl;
		std::cout << "Hunger: " << hunger << std::endl;
		std::cout << "Hygene: " << hygene << std::endl;
		std::cout << "Work: " << work << std::endl;

		if (tree && tree->root)
		{
			tree->root->run();
		}

		if (!sleeping)
		{
			energy -= ((rand() % 5) + 1);
			hunger += (rand() % 3) + 1;
			urinaryUrgency += (rand() % 2);
			hygene -= (rand() % 2);
			work -= rand() % 10;
		} else
		{
			hunger += (rand() % 1) + 1;
			urinaryUrgency += (rand() % 1);
			hygene -= (rand() % 1);
		}
	}
}
