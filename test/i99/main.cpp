#include <fstream>
#include <iostream>
#include <string>
#include "../../src/support/i99.hpp"

str a, b;

i32 main() {
	if (i99("-9") < i99("-4")) printf("True");
	// std::ifstream input; input.open("/Users/Marcythm/workspace/tasks/Python-Interpreter/test/i99/input");
	// if (not input.is_open()) return 1;
	// input >> a >> b;
	// // std::cin >> a >> b;
	// /*if (op == '+') */ printf("%s\n", (i99(a) + i99(b)).as<str>().c_str());
	// /*if (op == '-') */ printf("%s\n", (i99(a) - i99(b)).as<str>().c_str());
	// /*if (op == '*') */ printf("%s\n", (i99(a) * i99(b)).as<str>().c_str());
	// /*if (op == '/') */ printf("%s\n", (i99(a) / i99(b)).as<str>().c_str());
	// /*if (op == '%') */ printf("%s\n", (i99(a) % i99(b)).as<str>().c_str());

	return 0;
}
