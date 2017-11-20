
#include "Game.h"
#include <sstream>
#include <iostream>
int main(int argc, char** argv)
{
	std::stringstream strValue;
	strValue << argv[1];

	unsigned int intValue;
	strValue >> intValue;
	Game myGame= Game(intValue);
	if (myGame.Initialize())
	{
		myGame.RunLoop();
	}
	myGame.Shutdown();
	std::cout << myGame.cont;
	return 0;
}
