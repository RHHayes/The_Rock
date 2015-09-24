/*
File which defines the methods og the world manager class
*/


#include "WorldManager.h"
#include "LogManager.h"

using namespace df;

/*
Default Constructor
*/
WorldManager::WorldManager(){

	df::Manager::setType("WorldManager");
	updates = new ObjectList();
	deletions = new ObjectList();

}

/*
Default destructor
*/
WorldManager::~WorldManager(){

}


/*
Meethod which returns the current instance of the WorldManger
*/

WorldManager &WorldManager::getInstance(){
	static df::WorldManager single;
	return single;
}


/*
Method which starts up the world manager
*/
int WorldManager::startUp(){


	return df::Manager::startUp();
	
}

/*
Methoid which shuts down the world manager
*/
void WorldManager::shutDown(){

	//Delete all objects
	ObjectList *p_ol = updates;
	df::ObjectListIterator *li = new df::ObjectListIterator(p_ol);
	for (li->first(); !li->isDone(); li->next()){
		li->currentObject()->~Object();
	}
	updates->clear();
	free(updates);

	//Empty deletions list
	ObjectList *p_dl = deletions;
	df::ObjectListIterator *ld = new df::ObjectListIterator(p_dl);
	for (ld->first(); !ld->isDone(); ld->next()){
		ld->currentObject()->~Object();
	}
	deletions->clear();
	free(deletions);


	Manager::shutDown();

}


/*
Method which inserts an object into the game world
*/
int WorldManager::insertObject(df::Object *p_o){
	return updates->df::ObjectList::insert(p_o);
}

/*
Method which removes an object from the game world
*/
int WorldManager::removeObject(df::Object *p_o){
	return updates->remove(p_o);
}


/*
Method which deletes all object marked for deletion
*/
void WorldManager:: update(){
	//Provide step event to all Objects - move this into update
	EventStep s;
	onEvent(&s);


	//delete the objects in the deletion list
	ObjectList *p_dl = deletions;
	df::ObjectListIterator *ld = new df::ObjectListIterator(p_dl);
	for (ld->first(); !ld->isDone(); ld->next()){
		updates->remove(ld->currentObject());
	}
	deletions->clear();

	//udpade object positions based on their velocities
	int x = -1, y = -1; // poetntial new postition of object
	df::ObjectListIterator *lu = new df::ObjectListIterator(updates);
	while (!lu->isDone()){
		x = lu->currentObject()->getXVelocityStep();
		y = lu->currentObject()->getYVelocityStep();

		if (x || y){
			Position old_position = lu->currentObject()->getPosition();
			Position new_position = Position(old_position.getX() + x,
				old_position.getY() + y);
			lu->currentObject()->setPosition(new_position);
		}
		lu->next();
	}//end while

}

/*
Marks an object for deletion
*/
int WorldManager::markforDelete(df::Object *p_o){
	return deletions->insert(p_o);
}

/*
Returns a pointer to the object list
*/
ObjectList *WorldManager::getAllobjects(void) const{
	return updates;
}

/*
ask all objects to draw themselvs
*/
void WorldManager::draw(){

	ObjectListIterator *li = new ObjectListIterator(updates);
	//for loop that enforeces drawing by alttitude
	for (int alt = 0; alt < MAX_ALTTITUDE; alt++){
		while (!li->isDone()){	
			if (li->currentObject()->getAltitude() == alt){
				li->currentObject()->draw();
			}
			li->next();
		}
		li->first();
	}
}