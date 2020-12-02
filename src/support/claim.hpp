#ifndef Python_Interpreter_claim
#define Python_Interpreter_claim

#include <vector>
#include <string>

#include <type_traits>

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

using str = std::string;

template <typename T> using Vec = std::vector<T>;

class uinf;
class iinf;

#endif
