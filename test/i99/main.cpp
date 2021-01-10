#include <fstream>
#include <iostream>
#include <string>
#include "../../src/support/i99.hpp"

str a, b;

i32 main() {
	std::cin >> a >> b;
	printf("%s\n", (i99(a) + i99(b)).as<str>().c_str());
	printf("%s\n", (i99(a) - i99(b)).as<str>().c_str());
	printf("%s\n", (i99(a) * i99(b)).as<str>().c_str());
	printf("%s\n", (i99(a) / i99(b)).as<str>().c_str());
	printf("%s\n", (i99(a) % i99(b)).as<str>().c_str());
	printf("%d\n", i99(a).compare(i99(b)));

	return 0;
}
