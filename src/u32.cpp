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


// ---------- arithmetic operators ----------

u u::operator + (const u &rhs) const {
	if (len() > rhs.len()) return rhs + *this;
	// assume that len() <= rhs.len();
	u ans(rhs);
	u32 up = 0; const u32 l = ans.len();
	for (u32 i = 0; i < l; ++i) {
		ans[i] += value[i] + up;
		if (ans[i] > 9) ans[i] -= 10, up = 1;
		else up = 0;
	} if (up != 0) ans.value.emplace_back(up);
	return ans;
}

u u::operator - (const u &rhs) const {
	assert(operator>(rhs));
	u ans(*this);
	u32 up = 0; const u32 l = len();
	for (u32 i = 0; i < l; ++i) {
		ans[i] -= rhs[i] + up;
		if (ans[i] < 0) ans[i] += 10, up = 1;
		else up = 0;
	} ans.remove_leading_zero();
	return ans;
}

u u::operator * (const u &rhs) const {
	u ans; ans.resize(len() + rhs.len());
	const u32 l1 = len(), l2 = rhs.len();
	for (u32 i = 0; i < l1; ++i)
		for (u32 j = 0; j < l2; ++j)
			ans[i + j] += value[i] * rhs[j];
	for (u32 i = 0; i < l1 + l2; ++i)
		if (ans[i] > 9)
			ans[i + 1] += ans[i] / 10,
			ans[i] %= 10;
	ans.remove_leading_zero();
	return ans;
}


// ---------- comparison operators ----------

// usage: equal to three-way comparison operator <=>
i32 u::cmp(const u &rhs) const {
	if (len() > rhs.len()) return 1;
	if (len() < rhs.len()) return -1;
	const u32 l = len();
	for (u32 i = 0; i < l; ++i)
		if (value[i] > rhs[i]) return -1;
		else if (value[i] < rhs[i]) return 1;
	return 0;
}

bool u::operator == (const u &rhs) const { return cmp(rhs) == 0;}
bool u::operator != (const u &rhs) const { return cmp(rhs) != 0; }
bool u::operator < (const u &rhs) const { return cmp(rhs) < 0; }
bool u::operator > (const u &rhs) const { return cmp(rhs) > 0; }
bool u::operator <= (const u &rhs) const { return cmp(rhs) <= 0; }
bool u::operator >= (const u &rhs) const { return cmp(rhs) >= 0; }
