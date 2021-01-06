#pragma once

#ifndef PYTHON_INTERPRETER_SUPPORT_PRECLAIM
#define PYTHON_INTERPRETER_SUPPORT_PRECLAIM

#include <vector>
#include <string>
#include <stack>
#include <map>

#include <stdexcept>
#include <exception>
#include <type_traits>
#include <compare>

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


	template <typename T> struct in_typeset;
	template <typename T> constexpr bool in_typeset_v = in_typeset<T>::value;
	template <typename T> struct is_storage;
	template <typename T> constexpr bool is_storage_v = is_storage<T>::value;
													//= std::is_base_of_v<None, T>;
	template <typename T> struct is_integral_type;
	template <typename T> constexpr bool is_integral_type_v = is_integral_type<T>::value;
	template <typename T> struct is_integral_storage;
	template <typename T> constexpr bool is_integral_storage_v = is_integral_storage<T>::value;
	template <typename T> struct is_arithmetic_type;
	template <typename T> constexpr bool is_arithmetic_type_v = is_arithmetic_type<T>::value;
	template <typename T> struct is_arithmetic_storage;
	template <typename T> constexpr bool is_arithmetic_storage_v = is_arithmetic_storage<T>::value;
}

class Object;
class RawFunction;
class FunctionCall;

namespace FlowControl {
	class BREAK {};
	class CONTINUE {};
}

#endif
