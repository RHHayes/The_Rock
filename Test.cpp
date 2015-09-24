/*
File which tests the dragonfly egg development checkpoint
*/

//System includes
#include <Windows.h>

//Engine includes
#include "Test.h"
#include "GameManager.h"
#include "Object.h"
#include "ObjectList.h"
#include "ObjectListIterator.h" 
#include "Utility.h"
#include "Clock.h"
#include "GraphicsManager.h"
#include "Position.h"

/*
Method which runs various tests
*/
int test(){
	//Set up testing environment
	int testResult;
	df::GameManager &game_manager = df::GameManager::getInstance();
	game_manager.startUp();


	df::LogManager &log_manager = df::LogManager::getInstance();
	log_manager.setFlush(true);
	
	



	
	
	//Tests
	testResult = testObjectListIterator();
	if(!testResult) testResult = testLogManager();
	if (!testResult) testResult = testWorldManager();
	if (!testResult) testResult = testClock();
	if (!testResult) testResult = testObjectVelocity();
	if (!testResult) testResult  = testGraphicsManager();
	if (!testResult) testResult = testGameManager();
	
	
	

	//print result of testing
	if (!!testResult){
		log_manager.WriteMessage("Tests failed!");
	}
	else{
		log_manager.WriteMessage("Tests compleated!");
	}

	

	//Shut down testing environment
	game_manager.shutDown();



	return 0;

}



/*
Method to test the graphics manager
*/
int testGraphicsManager(){
	df::GraphicsManager &graphics_manager = df::GraphicsManager::getInstance();

	
	df::Position *pos = new df::Position(15, 15);

	/*
	graphics_manager.drawCh(*pos, 'X', df::GREEN);
	graphics_manager.swapBuffers();
	*/
	graphics_manager.drawString(*pos, "Press Space to end Test", df::CENTER_JUSTIFIED, df::YELLOW);
	graphics_manager.swapBuffers();



	return 0;
}


/*
Method which tests the ObjectListIterator class, and consequently the object list and object classes
*/
int testObjectListIterator(){
	int testResult = -1;
	df::ObjectList *aList = new df::ObjectList();


	
	
	//add dummy objects to the list. They should be consturcted with ids 0,1 , and 2
	aList->insert(new df::Object());
	aList->insert(new df::Object());
	aList->insert(new df::Object());

	//create a list iterator from the list
	df::ObjectListIterator *iterator = new df::ObjectListIterator(aList);

	//check if objects added to the list have the appropriate ids
	int ids = 0;
	iterator->first();
	while (!iterator->isDone()){
		df::Object *item = iterator->currentObject();
		if (item->getId() == ids){
			testResult = 0;
		}
		else
			testResult = -1;


		iterator->next();
		//iterate to next id that should be present
		ids++;
	}

	return testResult;

}

/*
Method which tests the Log manager class
*/
int testLogManager(){

	
	df::LogManager &log_manager = df::LogManager::getInstance();
	log_manager.WriteMessage("This is a test of the Log manager");

	log_manager.WriteMessage("This is a test of the Log manager multiple args. int: %d", 64);

	return 0;
}


/*
Method which tests the world manager
*/
int testWorldManager(){
	int testResult = -1;
	df::WorldManager &world_manager = df::WorldManager::getInstance();

	//save this sad object for later, id 3
	df::Object *sad_object = new df::Object();

	//add dummy opbjects to world manage, the two new objects have id 4 and 5
	world_manager.insertObject(sad_object);
	world_manager.insertObject(new df::Object());
	world_manager.insertObject(new df::Object());


	
	df::ObjectListIterator *iterator = new df::ObjectListIterator(world_manager.getAllobjects());


	//Check if objects are contined in the world manager
	int ids = 3;
	iterator->first();
	while (!iterator->isDone()){
		df::Object *item = iterator->currentObject();
		if (item->getId() == ids){
			testResult = 0;
		}
		else
			testResult = -1;
		

		iterator->next();
		//iterate to next id that should be present
		ids++;
	}

	//test mark for delete functionality

	//mark the sad object for delet
	world_manager.markforDelete(sad_object);

	//update game manager
	world_manager.update();

	//construct iterator from updated world managers current objects
	iterator = new df::ObjectListIterator(world_manager.getAllobjects());

	//test to eunsure only objects 4 and 5 remain in the world manager
	ids = 4;
	iterator->first();
	while (!iterator->isDone()){
		df::Object *item = iterator->currentObject();
		if (item->getId() == ids){
			testResult = 0;
		}
		else
			testResult = -1;


		iterator->next();
		ids++;
	}


	return testResult;


}


/*
Method which tests the clock utility
*/
int testClock(){
	int testResult = -1;
	df::Clock *clk = new df::Clock();

	//time change we are looking for in milliseconds
	long diff = 33;

	long before;
	long after;
	before = clk->delta();
	Sleep(33);
	after = clk->delta();

	if (diff = (after - before)){
		testResult = 0;
	}
	else{
		testResult = -1;
	}

	return testResult;

}

/*
Method which test game manager functionality
*/
int testGameManager(){
	int testResult = -1;
	df::LogManager &log_manager = df::LogManager::getInstance();
	df::GameManager &game_manager = df::GameManager::getInstance();

	log_manager.WriteMessage("Entering Game Loop");
	//test the game manger run functionality
	game_manager.run();
	log_manager.WriteMessage("Exiting Game Loop");
	testResult = 0;
	return testResult;

}

//method which checks object velocity math for x and y;
int testObjectVelocity(){
	int testResult = -1;
	df::Object *object = new df::Object();
	object->setXVelocity(.25);
	object->setYVelocity(.25);

	for (int i = 0; i < 3; i++){
		object->getYVelocityStep();
		object->getXVelocityStep();
	}
	if (object->getYVelocityStep() == 1 && object->getXVelocityStep() == 1){
		testResult = 0;
	}
	else{
		return testResult = -1;
	}
	
	//test different velocity
	df::Object *object_b = new df::Object();
	object->setXVelocity(1.5);
	object->setYVelocity(1.5);

	//spaces value should flip flop from 1 to 2
	if (object->getYVelocityStep() == 1 && object->getXVelocityStep() == 1){
		testResult = 0;
	}
	else{
		return testResult = -1;
	}

	if (object->getYVelocityStep() == 2 && object->getXVelocityStep() == 2){
		testResult = 0;
	}
	else{
		return testResult = -1;
	}

	if (object->getYVelocityStep() == 1 && object->getXVelocityStep() == 1){
		testResult = 0;
	}
	else{
		return testResult = -1;
	}
	
	return testResult;
}