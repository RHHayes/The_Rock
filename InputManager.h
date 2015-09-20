/*
Header file which define the input manager class
*/

#ifndef INPUT_MANAGER
#define INPUT_MANAGER

#include "Manager.h"
#include "GraphicsManager.h"

namespace df{

	class InputManger : public Manager{

	private:
		//Singleton behaivior
		InputManger();
		InputManger(InputManger const&);
		void operator=(InputManger const&);

	public:
		//Get the instanc of the game manager
		static InputManger &getInstance();

		//Get terminal ready to capture input
		int startUp();

		//revert to normal terminl mode
		void shutDown();

		//Getinput from the keyboard and mouse
		//pass event along to all objects
		void getInput();

	};

}// !df

#endif // !INPUT_MANAGER
