/*
File which defines the methods of the object class
*/

#include "Object.h"
#include "WorldManager.h"

using namespace df;

Object::Object(){
	static int id_counter = 0;
	id = id_counter;
	id_counter++;

	//object is inittially has no type
	type = "Undifined Object";

	//object position is inititaill the top left corner of the screen
	pos = Position();

}


//virtual destructor, should not be used
Object::~Object(){


}



/*
Geters and setters
*/

//Set Object id
void Object::setID(int new_id){
	id = new_id;
}

//get object id
int Object::getId() const{
	return id;
}

//set type
void Object::setType(std::string new_type){
	type = new_type;
}

//get object ype
std::string Object::getType(){
	return type;
}

//Set position object
void Object::setPosition(Position new_pos){
	pos = new_pos;
}

//Get position of object
Position Object::getPosition() const{
	return pos;
}

//Generic Event Handler
int Object::eventHandler(const df::Event *p_e){
	return -1;
}

//To be overided by each object, objects should be able to draw themselvs
void Object::draw(){
	
}

//set altitude, any value greater than MAX_Altitude is regected
int Object::setAltitude(int new_altitude){
	if (new_altitude < MAX_ALTTITUDE){
		altitude = new_altitude;
		return 0;
	}
	else{
		return -1;
	}
}

//Return object altitude
int Object::getAltitude() const{
	return altitude;
}