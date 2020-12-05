#include <fstream>
#include <iostream>
#include <string>
#include "../../src/support/iinf.hpp"

str a, b;

i32 main() {
	std::ifstream input; input.open("/Users/Marcythm/workspace/assignments/Python-Interpreter/test/iinf/input");
	if (not input.is_open()) return 1;
	input >> a >> b;
	// std::cin >> a >> b;
	/*if (op == '+') */ printf("%s\n", (iinf(a) + iinf(b)).to<str>().c_str());
	/*if (op == '-') */ printf("%s\n", (iinf(a) - iinf(b)).to<str>().c_str());
	/*if (op == '*') */ printf("%s\n", (iinf(a) * iinf(b)).to<str>().c_str());
	/*if (op == '/') */ printf("%s\n", (iinf(a) / iinf(b)).to<str>().c_str());
	/*if (op == '%') */ printf("%s\n", (iinf(a) % iinf(b)).to<str>().c_str());

	return 0;
}
