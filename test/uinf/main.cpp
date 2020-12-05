#include <iostream>
#include <string>
#include "../../src/support/uinf.hpp"

str a, b;

i32 main() {
	std::cin >> a >> b;
	/*if (op == '+') */ printf("%s\n", (uinf(a) + uinf(b)).to<str>().c_str());
	/*if (op == '-') */ printf("%s\n", (uinf(a) - uinf(b)).to<str>().c_str());
	/*if (op == '*') */ printf("%s\n", (uinf(a) * uinf(b)).to<str>().c_str());
	/*if (op == '/') */ printf("%s\n", (uinf(a) / uinf(b)).to<str>().c_str());
	/*if (op == '%') */ printf("%s\n", (uinf(a) % uinf(b)).to<str>().c_str());

	return 0;
}
