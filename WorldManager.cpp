/*
File which defines the methods og the world manager class
*/


#include "WorldManager.h"

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
	ObjectList *p_dl = deletions;
	df::ObjectListIterator *ld = new df::ObjectListIterator(p_dl);
	for (ld->first(); !ld->isDone(); ld->next()){
		updates->remove(ld->currentObject());
	}
	deletions->clear();
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