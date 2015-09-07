#include <iostream>
#include <string>
#include "tools.h"
#include "bmp.h"

namespace ver
{
	const std::string version = ".1";
}

int main()
{
	std::cout << "Pi from circle v" << ver::version << std::endl;
	std::cout << "Loading circle...\n";

	const auto fn = u8"res/circle3.bmp";
	auto bitmap = bmp::bmp_header(fn);

	bitmap.print_headerinfo();
	std::cout << "Black pixles: " << bitmap.nof_blackpixles() << std::endl;
	std::cout << "Black pixles: (accumulate) " << bitmap.nof_blackpixles_accumulate() << std::endl;
	tools::waitforkeypress();
	return 0;
}
