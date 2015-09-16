/*
File which define methods of the Manger abstract class
*/

#include "Manager.h"
using namespace df;
//Set type identifier of Manger.
void df::Manager::setType(std::string type){
	type = type;
}

// Get type identifier of Manager.
std::string df::Manager::getType() const{
	return type;
}

//Check to see if a manager has started
bool df::Manager::isStarted() const{
	return is_started;
}


//Startup Manager.
//Return 0 if ok, else negative number.
int df::Manager::startUp(){
	is_started = true;
	return 0;
}

//Shutdown Manager.
void df::Manager::shutDown(){
	is_started = false;

}