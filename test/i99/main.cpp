#include <fstream>
#include <iostream>
#include <string>
#include "../../src/support/i99.hpp"

str a, b;

i32 main() {
	std::ifstream input; input.open("/Users/Marcythm/workspace/tasks/Python-Interpreter/test/i99/input");
	if (not input.is_open()) return 1;
	input >> a >> b;
	// std::cin >> a >> b;
	printf("%s\n", (i99(a) + i99(b)).as<str>().c_str());
	printf("%s\n", (i99(a) - i99(b)).as<str>().c_str());
	printf("%s\n", (i99(a) * i99(b)).as<str>().c_str());
	printf("%s\n", (i99(a) / i99(b)).as<str>().c_str());
	printf("%s\n", (i99(a) % i99(b)).as<str>().c_str());
	printf("%d\n", i99(a).compare(i99(b)));

	return 0;
}
