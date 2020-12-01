#include "u32.hpp"

// ---------- constructors and assignment operators ----------

template <typename T>
u::u(T val) {
	if constexpr (std::is_integral<T>::value) {
		val = std::abs(val);
		do {
			value.emplace_back(val % 10);
			val /= 10;
		} while (val > 0);
	} else throw "constructing an unsigned integer with an non-integral value";
}
u::u(const char *s) {
	value.insert(value.end(), s, s + strlen(s));
	auto pos = value.begin();
	while (pos != value.end() and isdigit(*pos)) *pos++ -= '0';
	value.erase(pos, value.end());
}
u::u(const str &s) {
	value.insert(value.end(), s.begin(), s.end());
	auto pos = value.begin();
	while (pos != value.end() and isdigit(*pos)) *pos++ -= '0';
	value.erase(pos, value.end());
}
u::u(u &&rhs) noexcept { value = std::move(rhs.value); }

u& u::operator = (u &&rhs) noexcept {
	value = std::move(rhs.value);
	return *this;
}

i32& u::operator [] (const u32 &index) { return value[index]; }
const i32& u::operator [] (const u32 &index) const { return value[index]; }
