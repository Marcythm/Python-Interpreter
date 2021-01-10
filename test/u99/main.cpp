#include <iostream>
#include <string>
#include "../../src/support/u99.hpp"

str a, b;

i32 main() {
	std::cin >> a >> b;
	/*if (op == '+') */ printf("%s\n", (u99(a) + u99(b)).as<str>().c_str());
	/*if (op == '-') */ printf("%s\n", (u99(a) - u99(b)).as<str>().c_str());
	/*if (op == '*') */ printf("%s\n", (u99(a) * u99(b)).as<str>().c_str());
	/*if (op == '/') */ printf("%s\n", (u99(a) / u99(b)).as<str>().c_str());
	/*if (op == '%') */ printf("%s\n", (u99(a) % u99(b)).as<str>().c_str());

	return 0;
}
