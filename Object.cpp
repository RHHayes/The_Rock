/*
File which defines the methods of the object class
*/

#include "Object.h"

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