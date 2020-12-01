#include "uinf.hpp"


/* ---------- private functions ---------- */

void uinf::resize(u32 new_length) { value.resize(new_length); }
void uinf::remove_leading_zero() {
	while (not value.empty() and value.back() == 0) value.pop_back();
	if (value.size() == 0) value.emplace_back(0);
}



/* ---------- public functions ----------  */

const u32 uinf::len() const { return value.size(); }
const bool uinf::iszero() const { return value.size() == 1 and value[0] == 0; }

str uinf::tostr() const {
	str s; s.reserve(len());
	for (auto i = value.rbegin(); i != value.rend(); ++i)
		s.push_back('0' + *i);
	return s;
}

/* ---------- constructors and assignment operators ---------- */

template <typename T>
uinf::uinf(T val) {
	if constexpr (std::is_integral<T>::value) {
		val = std::abs(val);
		do {
			value.emplace_back(val % 10);
			val /= 10;
		} while (val > 0);
	} else throw "constructing an unsigned integer with an non-integral value";
}

uinf::uinf(const char *s) {
	value.insert(value.end(), s, s + strlen(s));
	std::reverse(value.begin(), value.end());
	auto pos = value.begin();
	while (pos != value.end() and isdigit(*pos)) *pos++ -= '0';
	value.erase(pos, value.end());
}
uinf::uinf(const str &s) {
	value.insert(value.end(), s.begin(), s.end());
	std::reverse(value.begin(), value.end());
	auto pos = value.begin();
	while (pos != value.end() and isdigit(*pos)) *pos++ -= '0';
	value.erase(pos, value.end());
}

uinf::uinf(const Vec<i32> &rhs): value(rhs) { }
uinf::uinf(Vec<i32> &&rhs): value(std::move(rhs)) { }

uinf::uinf(const uinf &rhs) { *this = rhs; }
uinf::uinf(uinf &&rhs) noexcept { value = std::move(rhs.value); }

uinf& uinf::operator = (const uinf &rhs) = default;
uinf& uinf::operator = (uinf &&rhs) noexcept {
	value = std::move(rhs.value);
	return *this;
}

i32& uinf::operator [] (const u32 &index) { return value[index]; }
const i32& uinf::operator [] (const u32 &index) const { return value[index]; }


/* ---------- arithmetic operators ---------- */

uinf uinf::operator + (const uinf &rhs) const {
	if (len() > rhs.len()) return rhs + *this;
	/* assume that len() <= rhs.len(); */
	uinf ans(rhs);
	u32 up = 0; const u32 l = ans.len();
	for (u32 i = 0; i < l; ++i) {
		ans[i] += value[i] + up;
		if (ans[i] > 9) ans[i] -= 10, up = 1;
		else up = 0;
	} if (up != 0) ans.value.emplace_back(up);
	return ans;
}

uinf uinf::operator - (const uinf &rhs) const {
	assert(*this >= rhs);
	uinf ans(*this);
	u32 up = 0; const u32 l = len();
	for (u32 i = 0; i < l; ++i) {
		ans[i] -= rhs[i] + up;
		if (ans[i] < 0) ans[i] += 10, up = 1;
		else up = 0;
	} ans.remove_leading_zero();
	return ans;
}

uinf uinf::operator * (const uinf &rhs) const {
	uinf ans;
	ans.resize(len() + rhs.len() + 1);
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

uinf uinf::operator / (const uinf &rhs) const {
	if (rhs.iszero()) throw std::overflow_error("in uinf::operator / : Divide By Zero");
	uinf rem; Vec<i32> ans;

	for (auto i = value.rbegin(); i != value.rend(); ++i) {
		rem.value.insert(rem.value.begin(), *i);
		i32 cur_rem = 0;
		while (rem >= rhs) {
			rem -= rhs;
			++cur_rem;
			printf("cur_rem = %d, rem = %s\n", cur_rem, rem.tostr().c_str());
		} ans.emplace_back(cur_rem);
	}

	std::reverse(ans.begin(), ans.end());
	return uinf(ans);
}

uinf uinf::operator % (const uinf &rhs) const {
	if (rhs.iszero()) throw std::overflow_error("in uinf::operator % : Modulo By Zero");
	uinf rem;
	for (auto i = value.rbegin(); i != value.rend(); ++i) {
		rem.value.insert(rem.value.begin(), *i);
		while (rem >= rhs) rem -= rhs;
	}
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
