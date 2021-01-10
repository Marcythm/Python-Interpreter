#include <cstdio>
#include <iostream>
#include "../../src/support/Object.hpp"

struct Output {
	Output& operator () (const Object &rhs) {
		std::cout << rhs.as<str>();
		return *this;
	}
	template <typename T>
	Output& operator () (const innerTypes::Value<T> &rhs) {
		std::cout << rhs.template as<str>();
		return *this;
	}
	Output& operator () (i8 c) {
		std::cout << (i32)(c);
		return *this;
	}
	template <typename T>
	Output& operator () (const T &c) {
		std::cout << c;
		return *this;
	}

	template <typename T>
	Output& err (const T &rhs) {
		(*this)("\033[31m")(rhs)("\033[0m");
		return *this;
	}
	template <typename T>
	Output& correct(const T &rhs) {
		(*this)("\033[32m")(rhs)("\033[0m");
		return *this;
	}
	template <typename T>
	Output& highlight(const T &rhs) {
		(*this)("\033[1m")(rhs)("\033[0m");
		return *this;
	}
} out;

str type[] = {"Int  ", "Str  ", "Bool ", "Float"};
Object var[] = {i99(101), str("qwq"), true, 93.12345678};

inline str tpof(const Object &rhs) {
	if (rhs.as_type<innerTypes::Int>())		return "Int";
	if (rhs.as_type<innerTypes::Str>())		return "Str";
	if (rhs.as_type<innerTypes::Bool>())	return "Bool";
	if (rhs.as_type<innerTypes::Float>())	return "Float";
											return "None";
}

i32 main() {
	out.correct("---------- test: operator not ----------\n");
	for (i32 i = 0; i < 4; ++i)
		try {
			out("not ").highlight(type[i])(": ")
				.highlight("(" + tpof(not var[i]) + ")")(not var[i])('\n');
		} catch (std::invalid_argument e) {
			out.err(e.what())('\n');
		}
	out('\n');

	out.correct("---------- test: operator + ----------\n");
	for (i32 i = 0; i < 4; ++i)
		for (i32 j = 0; j < 4; ++j)
			try {
				out.highlight(type[i])(" + ").highlight(type[j])(": ")
					.highlight("(" + tpof(var[i] + var[j]) + ")")(var[i] + var[j])('\n');
			} catch (std::invalid_argument e) {
				out.err(e.what())('\n');
			}
	out('\n');

	out.correct("---------- test: operator - ----------\n");
	for (i32 i = 0; i < 4; ++i)
		for (i32 j = 0; j < 4; ++j)
			try {
				out.highlight(type[i])(" - ").highlight(type[j])(": ")
					.highlight("(" + tpof(var[i] - var[j]) + ")")(var[i] - var[j])('\n');
			} catch (std::invalid_argument e) {
				out.err(e.what())('\n');
			}
	out('\n');

	out.correct("---------- test: operator * ----------\n");
	for (i32 i = 0; i < 4; ++i)
		for (i32 j = 0; j < 4; ++j)
			try {
				out.highlight(type[i])(" * ").highlight(type[j])(": ")
					.highlight("(" + tpof(var[i] * var[j]) + ")")(var[i] * var[j])('\n');
			} catch (std::invalid_argument e) {
				out.err(e.what())('\n');
			}
	out('\n');

	out.correct("---------- test: operator / ----------\n");
	for (i32 i = 0; i < 4; ++i)
		for (i32 j = 0; j < 4; ++j)
			try {
				out.highlight(type[i])(" // ").highlight(type[j])(": ")
					.highlight("(" + tpof(var[i] / var[j]) + ")")(var[i] / var[j])('\n');
			} catch (std::invalid_argument e) {
				out.err(e.what())('\n');
			}
	out('\n');

	out.correct("---------- test: method div ----------\n");
	for (i32 i = 0; i < 4; ++i)
		for (i32 j = 0; j < 4; ++j)
			try {
				out.highlight(type[i])(" / ").highlight(type[j])(": ")
					.highlight("(" + tpof(var[i].div(var[j])) + ")")(var[i].div(var[j]))('\n');
			} catch (std::invalid_argument e) {
				out.err(e.what())('\n');
			}
	out('\n');

	out.correct("---------- test: operator % ----------\n");
	for (i32 i = 0; i < 4; ++i)
		for (i32 j = 0; j < 4; ++j)
			try {
				out.highlight(type[i])(" % ").highlight(type[j])(": ")
					.highlight("(" + tpof(var[i] % var[j]) + ")")(var[i] % var[j])('\n');
			} catch (std::invalid_argument e) {
				out.err(e.what())('\n');
			}
	out('\n');

	out.correct("---------- test: method compare ----------\n");
	for (i32 i = 0; i < 4; ++i)
		for (i32 j = 0; j < 4; ++j)
			try {
				out("compare").highlight("( " + type[i] + ", " + type[j] + " ): ")
					(var[i].compare(var[j]))('\n');
			} catch (std::invalid_argument e) {
				out.err(e.what())('\n');
			}
	out('\n');

	out.correct("---------- test: method as ----------\n");
	for (i32 i = 0; i < 4; ++i) {
		try {
			out.highlight(type[i])(" as ").highlight(type[0])(": ")
				(var[i].as<innerTypes::Int>())('\n');
		} catch (std::invalid_argument e) {
			out.err(e.what())('\n');
		}
		try {
			out.highlight(type[i])(" as ").highlight(type[1])(": ")
				(var[i].as<innerTypes::Str>())('\n');
		} catch (std::invalid_argument e) {
			out.err(e.what())('\n');
		}
		try {
			out.highlight(type[i])(" as ").highlight(type[2])(": ")
				(var[i].as<innerTypes::Bool>())('\n');
		} catch (std::invalid_argument e) {
			out.err(e.what())('\n');
		}
		try {
			out.highlight(type[i])(" as ").highlight(type[3])(": ")
				(var[i].as<innerTypes::Float>())('\n');
		} catch (std::invalid_argument e) {
			out.err(e.what())('\n');
		}
	}
	out('\n');



	return 0;
}
