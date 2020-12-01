#ifndef Python_Interpreter_claim
#define Python_Interpreter_claim

#include <vector>
#include <string>

#include <type_traits>

#include <cassert>
#include <cstring>

using i16 = short;
using i32 = int;
using i64 = long long;

using u16 = unsigned short;
using u32 = unsigned int;
using u64 = unsigned long long;

using f64 = double;
using f128 = long double;

using str = std::string;

template <typename T> using Vec = std::vector<T>;

#endif
