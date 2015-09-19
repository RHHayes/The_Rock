/*
File containing definitions of game manager methods
*/

//System includes


//Project includes
#include "GameManager.h"

using namespace df;

/*
Constructor for Game manager
*/
GameManager::GameManager(){
	df::Manager::setType("GameManager");
	frame_time = FRAME_TIME_DEFAULT;
}

/*
Destructor 
*/
GameManager::~GameManager(){
	shutDown();
}

//Get the singleton instance of the GameManager.
GameManager &GameManager::getInstance(){
	static GameManager single;
	return single;
}

		
/*
Start up all the managers required to run the game
*/
void GameManager::startUp(){
	timeBeginPeriod(1);//Set granuality of time system call

	//Start up log manager
	df::LogManager &log_manager = df::LogManager::getInstance();
	log_manager.startUp();

	//Start up world manager
	df::WorldManager &world_manager = df::WorldManager::getInstance();
	world_manager.startUp();

	game_over = false;

	Manager::startUp();

}

		//Shut GameManager services
void GameManager::shutDown(){
	
	//Tell game world objects that the game is over
	setGameOver(true);
	
	//Shut down log manager
	df::LogManager &log_manager = df::LogManager::getInstance();
	log_manager.shutDown();
	
	Manager::shutDown();

	timeEndPeriod(1); //Restore default time granularity
}

/*
Method which runs the game loop
*/
void GameManager::run(){
	df::LogManager &log_manager = df::LogManager::getInstance();
	df::Clock* clock = new df::Clock;
	long int loop_time;
	int runs = 0;
	while(!game_over) {
		clock->delta();




		//dummy game over for testing
		if (runs == 30){
			game_over = true;
		}

		//Provide step event to all Objects
		EventStep s;
		onEvent(&s);


		//draw current scene to back buffer
		//swap back buffer to current buffer
		loop_time = clock->split();
		Sleep(frame_time - loop_time);
		runs++;
	
		
	}
	
}

//Set game over status to indicated value
//If true (default), will stop game loop.
void GameManager::setGameOver(bool newValue) {
	
	game_over = newValue;
}

//Get game over status
bool GameManager::getGameOver() const {
	return game_over;
}

//Return farme time
//Frame time is target time for game loop, in milliseconds.
int GameManager::getFrameTime() const {
	return frame_time;

}