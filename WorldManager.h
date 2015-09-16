/*
Header file which defines the world manager, a singleton class
*/

#ifndef WORLD_MANAGER
#define WORLD_MANAGER

//Engine includes
#include "Manager.h"
#include "ObjectList.h"

namespace df{

	class WorldManager : public Manager {

	private:
		//Singleton behaivior
		WorldManager();
		WorldManager(WorldManager const&);
		void operator=(WorldManager const&);

		//All objects in world to update
		ObjectList *updates;
		//All objects in the world to delete
		ObjectList *deletions;

	public:
		//Get the instance of the world manager
		static WorldManager &getInstance();


		//Destructor
		~WorldManager();

		//Startup game world(initialize everything to empty).
		//Return 0.
		int startUp();

		//Shutdown game world(delete all game owrl objects)
		void shutDown();

		//Add an object to world
		int insertObject(Object *p_o);

		//Remove an object from the world
		int removeObject(Object *p_o);

		//Return a list of objects in world
		ObjectList *getAllobjects(void) const;

		//update world
		//delete all objects marked for deletion
		void update();

		//Indicate Object is to be deleted at the end of current game loop
		int markforDelete(Object *p_o);
	};

}//edn df

#endif // end WORLD_MANAGER