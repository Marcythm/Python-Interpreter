#include <iostream>
#include <string>
#include "../../src/support/u99.hpp"

str a, b;

i32 main() {
	std::cin >> a >> b;
	printf("%s\n", (u99(a) + u99(b)).as<str>().c_str());
	printf("%s\n", (u99(a) - u99(b)).as<str>().c_str());
	printf("%s\n", (u99(a) * u99(b)).as<str>().c_str());
	printf("%s\n", (u99(a) / u99(b)).as<str>().c_str());
	printf("%s\n", (u99(a) % u99(b)).as<str>().c_str());
	printf("%d\n", u99(a).compare(u99(b)));


	return 0;
}
