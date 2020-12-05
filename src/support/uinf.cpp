#include "uinf.hpp"


/* ---------- private functions ---------- */

void uinf::resize(u32 new_length) { value.resize(new_length); }
void uinf::remove_leading_zero() {
	while (not value.empty() and value.back() == 0) value.pop_back();
}



/* ---------- public functions ----------  */

u32 uinf::len() const { return value.size(); }
bool uinf::iszero() const { return value.size() == 0; }

str uinf::tostr() const {
	if (iszero()) return str("0");
	str s; s.reserve(len());
	for (auto i = value.rbegin(); i != value.rend(); ++i)
		s.push_back('0' + *i);
	return s;
}

/* ---------- constructors and assignment operators ---------- */

// template <typename T>
uinf::uinf(i32 val) {
	// if constexpr (std::is_integral<T>::value) {
		val = std::abs(val);
		do {
			value.emplace_back(val % 10);
			val /= 10;
		} while (val > 0);
	// } else throw "constructing an unsigned integer with an non-integral value";
}
uinf::uinf(i64 val) {
	// if constexpr (std::is_integral<T>::value) {
		val = std::abs(val);
		do {
			value.emplace_back(val % 10);
			val /= 10;
		} while (val > 0);
	// } else throw "constructing an unsigned integer with an non-integral value";
}

uinf::uinf(): value() {}

uinf::uinf(const char *s) {
	value.insert(value.end(), s, s + strlen(s));
	std::reverse(value.begin(), value.end());
	auto pos = value.begin();
	while (pos != value.end() and isdigit(*pos)) *pos++ -= '0';
	value.erase(pos, value.end());
	remove_leading_zero();
}
uinf::uinf(const str &s) {
	value.insert(value.end(), s.begin(), s.end());
	std::reverse(value.begin(), value.end());
	auto pos = value.begin();
	while (pos != value.end() and isdigit(*pos)) *pos++ -= '0';
	value.erase(pos, value.end());
	remove_leading_zero();
}

uinf::uinf(const Vec<i32> &rhs): value(rhs) { remove_leading_zero(); }
uinf::uinf(Vec<i32> &&rhs): value(std::move(rhs)) { remove_leading_zero(); }

uinf::uinf(const uinf &rhs) = default;
uinf::uinf(uinf &&rhs) noexcept { value = std::move(rhs.value); }

uinf& uinf::operator = (const uinf &rhs) = default;
uinf& uinf::operator = (uinf &&rhs) noexcept {
	value = std::move(rhs.value);
	return *this;
}

i32& uinf::operator [] (const u32 index) { return value[index]; }
const i32& uinf::operator [] (const u32 index) const { return value[index]; }


/* ---------- arithmetic operators ---------- */

uinf uinf::operator + (const uinf &rhs) const {
	if (len() > rhs.len()) return rhs + *this;
	/* assume that len() <= rhs.len(); */
	uinf ans(rhs); ans.resize(ans.len() + 1);
	for (u32 i = 0; i < len(); ++i)
		if (ans[i] += value[i]; ans[i] > 9)
			ans[i] -= 10, ++ans[i + 1];
	for (u32 i = len(); i < ans.len() and ans[i] > 9; ++i)
		ans[i] -= 10, ++ans[i + 1];

	ans.remove_leading_zero();
	return ans;
}

uinf uinf::operator - (const uinf &rhs) const {
	assert(*this >= rhs);
	/* assume that the result is non-negative */
	uinf ans(*this);
	for (u32 i = 0; i < rhs.len(); ++i)
		if (ans[i] -= rhs[i]; ans[i] < 0)
			ans[i] += 10, --ans[i + 1];
	for (u32 i = rhs.len(); i < len() and ans[i] < 0; ++i)
		ans[i] += 10, --ans[i + 1];

	ans.remove_leading_zero();
	return ans;
}

uinf uinf::operator * (const uinf &rhs) const {
	uinf ans; ans.resize(len() + rhs.len() + 1);
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

uinf uinf::operator / (const uinf &rhs) const {
	if (rhs.iszero()) throw std::domain_error("in uinf::operator / : Divide By Zero");

	uinf rem; Vec<i32> ans_vec;
	for (auto i = value.rbegin(); i != value.rend(); ++i) {
		rem.value.insert(rem.value.begin(), *i);
		i32 cur_rem = 0;
		while (rem >= rhs) {
			rem -= rhs;
			++cur_rem;
		} ans_vec.emplace_back(cur_rem);
	}

	std::reverse(ans_vec.begin(), ans_vec.end());
	uinf ans(ans_vec); ans.remove_leading_zero();
	return ans;
}

uinf uinf::operator % (const uinf &rhs) const {
	if (rhs.iszero()) throw std::domain_error("in uinf::operator % : Modulo By Zero");

	uinf rem;
	for (auto i = value.rbegin(); i != value.rend(); ++i) {
		rem.value.insert(rem.value.begin(), *i);
		while (rem >= rhs) rem -= rhs;
	}

	rem.remove_leading_zero();
	return rem;
}


uinf& uinf::operator += (const uinf &rhs) { return *this = *this + rhs; }
uinf& uinf::operator -= (const uinf &rhs) { return *this = *this - rhs; }
uinf& uinf::operator *= (const uinf &rhs) { return *this = *this * rhs; }
uinf& uinf::operator /= (const uinf &rhs) { return *this = *this / rhs; }
uinf& uinf::operator %= (const uinf &rhs) { return *this = *this % rhs; }


/* ---------- comparison operators ---------- */

/* usage: equal to three-way comparison operator <=> */
i32 uinf::cmp(const uinf &rhs) const {
	if (len() > rhs.len()) return 1;
	if (len() < rhs.len()) return -1;
	for (i32 i = len() - 1; i >= 0; --i)
		if (value[i] > rhs[i]) return 1;
		else if (value[i] < rhs[i]) return -1;
	return 0;
}

bool uinf::operator == (const uinf &rhs) const { return cmp(rhs) == 0;}
bool uinf::operator != (const uinf &rhs) const { return cmp(rhs) != 0; }
bool uinf::operator < (const uinf &rhs) const { return cmp(rhs) < 0; }
bool uinf::operator > (const uinf &rhs) const { return cmp(rhs) > 0; }
bool uinf::operator <= (const uinf &rhs) const { return cmp(rhs) <= 0; }
bool uinf::operator >= (const uinf &rhs) const { return cmp(rhs) >= 0; }
