#pragma once

#ifndef PYTHON_INTERPRETER_SUPPORT_PRECLAIM
#define PYTHON_INTERPRETER_SUPPORT_PRECLAIM

#include <vector>
#include <string>
#include <stack>
#include <map>
#include <unordered_map>

// #include <iostream>
#include <algorithm>

#include <stdexcept>
#include <exception>
#include <type_traits>
// #include <compare>

#include <cassert>
#include <cstring>


using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using f64 = double;
using f128 = long double;

template <typename T> using ptr = T*;

template <typename T> using Vec = std::vector<T>;

using str = std::string;


class uinf;
class iinf;

namespace innerTypes {
	class None;
	template <typename T> class Value;

	using Int = Value<iinf>;
	using Str = Value<str>;
	using Bool = Value<bool>;
	using Float = Value<f64>;
}

class Object;
class RawFunction;
class FunctionCall;

namespace FlowControl {
	class BREAK {};
	class CONTINUE {};
}

#endif
