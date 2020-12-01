#include <iostream>
#include <string>
#include "../../src/uinf.hpp"

str a, b;

i32 main() {
	std::cin >> a >> b;
	/*if (op == '+') */ printf("%s\n", (uinf(a) + uinf(b)).tostr().c_str());
	/*if (op == '-') */ printf("%s\n", (uinf(a) - uinf(b)).tostr().c_str());
	/*if (op == '*') */ printf("%s\n", (uinf(a) * uinf(b)).tostr().c_str());
	/*if (op == '/') */ printf("%s\n", (uinf(a) / uinf(b)).tostr().c_str());
	/*if (op == '%') */ printf("%s\n", (uinf(a) % uinf(b)).tostr().c_str());

	return 0;
}
