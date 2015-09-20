/*
File which definet the methods of the input manager class
*/

#include "InputManager.h"

using namespace df;

InputManger::InputManger(){
	df::Manager::setType("InputManger");
}


//Get the singleton instance of the InputManger.
InputManger &InputManger::getInstance(){
	static InputManger single;
	return single;
}


/*
Start up the input manager, requires the the graphix manager is started
*/
int InputManger::startUp(){
	LogManager &log_manager = LogManager::getInstance();
	GraphicsManager &graphics_manager = GraphicsManager::getInstance();

	if (!graphics_manager.isStarted()){
		log_manager.WriteMessage("Error! InputManager::startup() : graphics manager was not started");
			return -1;
	}

	sf::RenderWindow *render_window = graphics_manager.getWIndow();

	render_window->setKeyRepeatEnabled(false);

	Manager::startUp();
}

/*
shut down the input manager
*/
void InputManger::shutDown(){
	GraphicsManager &graphics_manager = GraphicsManager::getInstance();

	sf::RenderWindow *render_window = graphics_manager.getWIndow();

	render_window->setKeyRepeatEnabled(true);

	Manager::shutDown();
}

/*
Method which gets input from the sfml window
*/
void InputManger::getInput(){

	GraphicsManager &graphics_manager = GraphicsManager::getInstance();

	sf::RenderWindow *render_window = graphics_manager.getWIndow();

	sf::Event event;
	while (render_window ->pollEvent(event)){
		//Key was pressed

	}
}