/*
Class which contsins utility functions
*/

#ifndef UTILITY_H
#define UTILITY_H

//System includes
#include <stdio.h>
#include <time.h>


namespace df{

	class Utility {

	public:
		Utility();
		~Utility();

		//Method which returns a string of the current time
		char *getTimeString();

	};


}

#endif // UTILITY_H