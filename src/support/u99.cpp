#include "u99.hpp"


/* ---------- private functions ---------- */

auto u99::resize(u32 new_length) -> void { value.resize(new_length); }
auto u99::remove_leading_zero() -> void {
	while (not value.empty() and value.back() == 0) value.pop_back();
}



/* ---------- public functions ----------  */

auto u99::len() const -> u32 { return value.size(); }
auto u99::iszero() const -> bool { return value.size() == 0; }

/* ---------- constructors and assignment operators ---------- */

// template <typename T>
u99::u99(i32 val) {
	// if constexpr (std::is_integral<T>::value) {
		val = std::abs(val);
		do {
			value.emplace_back(val % 10);
			val /= 10;
		} while (val > 0);
	// } else throw "constructing an unsigned integer with an non-integral value";
}
u99::u99(i64 val) {
	// if constexpr (std::is_integral<T>::value) {
		val = std::abs(val);
		do {
			value.emplace_back(val % 10);
			val /= 10;
		} while (val > 0);
	// } else throw "constructing an unsigned integer with an non-integral value";
}

u99::u99(): value() {}

u99::u99(const char *s) {
	value.insert(value.end(), s, s + strlen(s));
	std::reverse(value.begin(), value.end());
	auto pos = value.begin();
	while (pos != value.end() and isdigit(*pos)) *pos++ -= '0';
	value.erase(pos, value.end());
	remove_leading_zero();
}
u99::u99(const str &s) {
	value.insert(value.end(), s.begin(), s.end());
	std::reverse(value.begin(), value.end());
	auto pos = value.begin();
	while (pos != value.end() and isdigit(*pos)) *pos++ -= '0';
	value.erase(pos, value.end());
	remove_leading_zero();
}

u99::u99(const Vec<i32> &rhs): value(rhs) { remove_leading_zero(); }
u99::u99(Vec<i32> &&rhs): value(std::move(rhs)) { remove_leading_zero(); }

u99::u99(const u99 &rhs) = default;
u99::u99(u99 &&rhs) noexcept { value = std::move(rhs.value); }

auto u99::operator = (const u99 &rhs) -> u99& = default;
auto u99::operator = (u99 &&rhs) noexcept -> u99& {
	value = std::move(rhs.value);
	return *this;
}

auto u99::operator [] (const u32 index) -> i32& { return value[index]; }
auto u99::operator [] (const u32 index) const -> const i32& { return value[index]; }


/* ---------- arithmetic operators ---------- */

auto u99::operator + (const u99 &rhs) const -> u99 {
	if (len() > rhs.len()) return rhs + *this;
	/* assume that len() <= rhs.len(); */
	u99 ans(rhs); ans.resize(ans.len() + 1);
	for (u32 i = 0; i < len(); ++i)
		if (ans[i] += value[i]; ans[i] > 9)
			ans[i] -= 10, ++ans[i + 1];
	for (u32 i = len(); i < ans.len() and ans[i] > 9; ++i)
		ans[i] -= 10, ++ans[i + 1];

	ans.remove_leading_zero();
	return ans;
}

auto u99::operator - (const u99 &rhs) const -> u99 {
	assert(*this >= rhs);
	/* assume that the result is non-negative */
	u99 ans(*this);
	for (u32 i = 0; i < rhs.len(); ++i)
		if (ans[i] -= rhs[i]; ans[i] < 0)
			ans[i] += 10, --ans[i + 1];
	for (u32 i = rhs.len(); i + 1 < len() and ans[i] < 0; ++i)
		ans[i] += 10, --ans[i + 1];

	ans.remove_leading_zero();
	return ans;
}

auto u99::operator * (const u99 &rhs) const -> u99 {
	u99 ans; ans.resize(len() + rhs.len() + 1);
	for (u32 i = 0; i < len(); ++i)
		for (u32 j = 0; j < rhs.len(); ++j)
			ans[i + j] += value[i] * rhs[j];
	for (u32 i = 1; i < ans.len(); ++i)
		if (ans[i - 1] > 9)
			ans[i] += ans[i - 1] / 10,
			ans[i - 1] %= 10;

	ans.remove_leading_zero();
	return ans;
}

auto u99::operator / (const u99 &rhs) const -> u99 {
	if (rhs.iszero()) throw std::domain_error("in u99::operator / : Divide By Zero");

	u99 rem; Vec<i32> ans;
	for (auto i = value.rbegin(); i != value.rend(); ++i) {
		rem.value.insert(rem.value.begin(), *i);
		rem.remove_leading_zero();
		i32 cur_rem = 0;
		while (rem >= rhs) {
			rem -= rhs;
			++cur_rem;
		} ans.emplace_back(cur_rem);
	}

	std::reverse(ans.begin(), ans.end());
	return u99(ans);
}

auto u99::operator % (const u99 &rhs) const -> u99 {
	if (rhs.iszero()) throw std::domain_error("in u99::operator % : Modulo By Zero");

	u99 rem;
	for (auto i = value.rbegin(); i != value.rend(); ++i) {
		rem.value.insert(rem.value.begin(), *i);
		rem.remove_leading_zero();
		while (rem >= rhs) rem -= rhs;
	}

	rem.remove_leading_zero();
	return rem;
}


auto u99::operator += (const u99 &rhs) -> u99& { return *this = *this + rhs; }
auto u99::operator -= (const u99 &rhs) -> u99& { return *this = *this - rhs; }
auto u99::operator *= (const u99 &rhs) -> u99& { return *this = *this * rhs; }
auto u99::operator /= (const u99 &rhs) -> u99& { return *this = *this / rhs; }
auto u99::operator %= (const u99 &rhs) -> u99& { return *this = *this % rhs; }


/* ---------- comparison operators ---------- */

/* usage: equal to three-way comparison operator <=> */
auto u99::compare(const u99 &rhs) const -> i8 {
	if (len() > rhs.len()) return 1;
	if (len() < rhs.len()) return -1;
	for (i32 i = len() - 1; i >= 0; --i)
		if (value[i] > rhs[i]) return 1;
		else if (value[i] < rhs[i]) return -1;
	return 0;
}

auto u99::operator == (const u99 &rhs) const -> bool { return compare(rhs) == 0;}
auto u99::operator != (const u99 &rhs) const -> bool { return compare(rhs) != 0; }
auto u99::operator < (const u99 &rhs) const -> bool { return compare(rhs) < 0; }
auto u99::operator > (const u99 &rhs) const -> bool { return compare(rhs) > 0; }
auto u99::operator <= (const u99 &rhs) const -> bool { return compare(rhs) <= 0; }
auto u99::operator >= (const u99 &rhs) const -> bool { return compare(rhs) >= 0; }
