#include "i99.hpp"


/* ---------- private functions ---------- */

void i99::detect_sign() { if (value.iszero()) sign = ZERO; }

/* ---------- public functions ----------  */

u32 i99::len() const { return value.len(); }
bool i99::isnegative() const { return sign == NEG; }
bool i99::iszero() const { return sign == ZERO; }
bool i99::ispositive() const { return sign == POS; }

template <>
bool i99::as<bool>() const { return sign != 0; }

template <>
str i99::as<str>() const { return (isnegative() ? "-" : "") + value.as<str>(); }

template <>
i32 i99::as<i32>() const { return sign * static_cast<i32>(value.as<u32>()); }

template <>
i64 i99::as<i64>() const { return sign * static_cast<i64>(value.as<u64>()); }

template <>
f64 i99::as<f64>() const { return sign * value.as<f64>(); }

/* ---------- constructors and assignment operators ---------- */

// template <typename T>
i99::i99(i32 val): sign((val < 0) ? -1 : (val == 0 ? 0 : 1)), value(std::abs(val)) {}
i99::i99(i64 val): sign((val < 0) ? -1 : (val == 0 ? 0 : 1)), value(std::abs(val)) {}

i99::i99(): sign(0), value() {}

i99::i99(const char *s): sign(s[0] == '-' ? NEG : POS), value(s + (isdigit(s[0]) ? 0 : 1)) { detect_sign(); }
i99::i99(const str &s): sign(s[0] == '-' ? NEG : POS), value(str(s[0] == '-' ? ++s.begin() : s.begin(), s.end())) { detect_sign(); }

i99::i99(const u99 &rhs, i8 sgn): sign(sgn), value(rhs) { detect_sign(); }
i99::i99(u99 &&rhs, i8 sgn) noexcept: sign(sgn), value(std::move(rhs)) { detect_sign(); }

i99::i99(const i99 &rhs) = default;
i99::i99(i99 &&rhs) noexcept: sign(rhs.sign) { value = std::move(rhs.value); }

i99& i99::operator = (const i99 &rhs) = default;
i99& i99::operator = (i99 &&rhs) noexcept {
	sign = rhs.sign;
	value = std::move(rhs.value);
	return *this;
}

i32& i99::operator [] (const u32 index) { return value[index]; }
const i32& i99::operator [] (const u32 index) const { return value[index]; }


/* ---------- arithmetic operators ---------- */

i99 i99::operator + (const i99 &rhs) const {
	if (sign == rhs.sign) return i99(value + rhs.value, sign);
	if (iszero()) return rhs; if (rhs.iszero()) return *this;
	if (ispositive())
		return (value >= rhs.value) ? i99(value - rhs.value, POS) : i99(rhs.value - value, NEG);
	return (rhs.value >= value) ? i99(rhs.value - value, POS) : i99(value - rhs.value, NEG);
}

i99 i99::operator - (const i99 &rhs) const {
	if (sign * rhs.sign < 0) return i99(value + rhs.value, sign);
	if (iszero()) return -rhs; if (rhs.iszero()) return *this;
	if (ispositive())
		return (value >= rhs.value) ? i99(value - rhs.value, POS) : i99(rhs.value - value, NEG);
	return (rhs.value >= value) ? i99(rhs.value - value, POS) : i99(value - rhs.value, NEG);
}

i99 i99::operator * (const i99 &rhs) const { return i99(value * rhs.value, sign * rhs.sign); }

i99 i99::operator / (const i99 &rhs) const {
	if (rhs.iszero()) throw std::domain_error("in i99::operator / : Divide By Zero");
	if (iszero()) return i99();
	if (sign == rhs.sign) return i99(value / rhs.value, POS);
	if ((value % rhs.value).iszero()) return i99(value / rhs.value, NEG);
	return i99(value / rhs.value + u99(1), NEG);
}

/* a lazy implementation */
i99 i99::operator % (const i99 &rhs) const { return *this - rhs * (*this / rhs); }

i99 i99::operator - () const { return i99(value, -sign); }


i99& i99::operator += (const i99 &rhs) { return *this = *this + rhs; }
i99& i99::operator -= (const i99 &rhs) { return *this = *this - rhs; }
i99& i99::operator *= (const i99 &rhs) { return *this = *this * rhs; }
i99& i99::operator /= (const i99 &rhs) { return *this = *this / rhs; }
i99& i99::operator %= (const i99 &rhs) { return *this = *this % rhs; }


/* ---------- comparison operators ---------- */

/* usage: equal to three-way comparison operator <=> */
i8 i99::compare(const i99 &rhs) const {
	if (sign != rhs.sign) return sign < rhs.sign ? -1 : 1;
	return (isnegative() ? -1 : 1) * value.compare(rhs.value);
}

bool i99::operator == (const i99 &rhs) const { return compare(rhs) == 0;}
bool i99::operator != (const i99 &rhs) const { return compare(rhs) != 0; }
bool i99::operator < (const i99 &rhs) const { return compare(rhs) < 0; }
bool i99::operator > (const i99 &rhs) const { return compare(rhs) > 0; }
bool i99::operator <= (const i99 &rhs) const { return compare(rhs) <= 0; }
bool i99::operator >= (const i99 &rhs) const { return compare(rhs) >= 0; }
