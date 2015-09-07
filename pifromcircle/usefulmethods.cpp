#include "tools.h"
#include <iostream>

namespace tools {
	void waitforkeypress()
	{
		std::cout << "Press <ANY> key to continue\n";
		std::cin.get();
	}
}