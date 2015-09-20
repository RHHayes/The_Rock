/*
header file which defines the game object class
*/

#ifndef OBJECT
#define OBJECT

//System includes
#include <string>

//Engine includes
#include "Position.h"
#include "Event.h"

namespace df{

	class Object{

	private:
		int id; //unique id of oject
		std::string type; //string type representation
		Position pos; //Object position in game world
		int altitude; //0 to max

	public:
		//Construct Object and add to the game world
		Object();

		//Destruct object and remove from game world
		virtual ~Object();

		//Generic Event Handler
		virtual int eventHandler(const df::Event *p_e);

		//Objects should be able to draw themselvs
		virtual void draw();

		//getter and setters

		//Set Object id
		void setID(int new_id);

		//get object id
		int getId() const;

		//set type
		void setType(std::string new_type);

		//get object ype
		std::string getType();

		//Set position object
		void setPosition(Position new_pos);

		//Get position of object
		Position getPosition() const;

		//altitude controll
		int setAltitude(int new_altitude);

		//Return object altitude
		int getAltitude() const;

	};






}// end df


#endif //end OBJECT