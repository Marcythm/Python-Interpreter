#include "iinf.hpp"


/* ---------- private functions ---------- */

void iinf::detect_sign() { if (value.iszero()) sign = ZERO; }

/* ---------- public functions ----------  */

u32 iinf::len() const { return value.len(); }
bool iinf::isnegative() const { return sign == NEG; }
bool iinf::iszero() const { return sign == ZERO; }
bool iinf::ispositive() const { return sign == POS; }

template <>
bool iinf::as<bool>() const { return sign != 0; }

template <>
str iinf::as<str>() const { return (isnegative() ? "-" : "") + value.as<str>(); }

template <>
i32 iinf::as<i32>() const { return sign * static_cast<i32>(value.as<u32>()); }

template <>
i64 iinf::as<i64>() const { return sign * static_cast<i64>(value.as<u64>()); }

template <>
f64 iinf::as<f64>() const { return sign * value.as<f64>(); }

/* ---------- constructors and assignment operators ---------- */

// template <typename T>
iinf::iinf(i32 val): sign((val < 0) ? -1 : (val == 0 ? 0 : 1)), value(std::abs(val)) {}
iinf::iinf(i64 val): sign((val < 0) ? -1 : (val == 0 ? 0 : 1)), value(std::abs(val)) {}

iinf::iinf(): sign(0), value() {}

iinf::iinf(const char *s): sign(s[0] == '-' ? NEG : POS), value(s + (isdigit(s[0]) ? 0 : 1)) { detect_sign(); }
iinf::iinf(const str &s): sign(s[0] == '-' ? NEG : POS), value(str(s[0] == '-' ? ++s.begin() : s.begin(), s.end())) { detect_sign(); }

iinf::iinf(const uinf &rhs, i8 sgn): sign(sgn), value(rhs) { detect_sign(); }
iinf::iinf(uinf &&rhs, i8 sgn) noexcept: sign(sgn), value(std::move(rhs)) { detect_sign(); }

iinf::iinf(const iinf &rhs) = default;
iinf::iinf(iinf &&rhs) noexcept: sign(rhs.sign) { value = std::move(rhs.value); }

iinf& iinf::operator = (const iinf &rhs) = default;
iinf& iinf::operator = (iinf &&rhs) noexcept {
	sign = rhs.sign;
	value = std::move(rhs.value);
	return *this;
}

i32& iinf::operator [] (const u32 index) { return value[index]; }
const i32& iinf::operator [] (const u32 index) const { return value[index]; }


/* ---------- arithmetic operators ---------- */

iinf iinf::operator + (const iinf &rhs) const {
	if (sign == rhs.sign) return iinf(value + rhs.value, sign);
	if (iszero()) return rhs; if (rhs.iszero()) return *this;
	if (ispositive())
		return (value >= rhs.value) ? iinf(value - rhs.value, POS) : iinf(rhs.value - value, NEG);
	return (rhs.value >= value) ? iinf(rhs.value - value, POS) : iinf(value - rhs.value, NEG);
}

iinf iinf::operator - (const iinf &rhs) const {
	if (sign * rhs.sign < 0) return iinf(value + rhs.value, sign);
	if (iszero()) return -rhs; if (rhs.iszero()) return *this;
	if (ispositive())
		return (value >= rhs.value) ? iinf(value - rhs.value, POS) : iinf(rhs.value - value, NEG);
	return (rhs.value >= value) ? iinf(rhs.value - value, POS) : iinf(value - rhs.value, NEG);
}

iinf iinf::operator * (const iinf &rhs) const { return iinf(value * rhs.value, sign * rhs.sign); }

iinf iinf::operator / (const iinf &rhs) const {
	if (rhs.iszero()) throw std::domain_error("in iinf::operator / : Divide By Zero");
	if (iszero()) return iinf();
	if (sign == rhs.sign) return iinf(value / rhs.value, POS);
	if ((value % rhs.value).iszero()) return iinf(value / rhs.value, NEG);
	return iinf(value / rhs.value + uinf(1), NEG);
}

/* a lazy implementation */
iinf iinf::operator % (const iinf &rhs) const { return *this - rhs * (*this / rhs); }

iinf iinf::operator - () const { return iinf(value, -sign); }


iinf& iinf::operator += (const iinf &rhs) { return *this = *this + rhs; }
iinf& iinf::operator -= (const iinf &rhs) { return *this = *this - rhs; }
iinf& iinf::operator *= (const iinf &rhs) { return *this = *this * rhs; }
iinf& iinf::operator /= (const iinf &rhs) { return *this = *this / rhs; }
iinf& iinf::operator %= (const iinf &rhs) { return *this = *this % rhs; }


/* ---------- comparison operators ---------- */

/* usage: equal to three-way comparison operator <=> */
i32 iinf::compare(const iinf &rhs) const {
	if (sign != rhs.sign) return sign < rhs.sign ? -1 : 1;
	return isnegative() xor (value.compare(rhs.value));
}

bool iinf::operator == (const iinf &rhs) const { return compare(rhs) == 0;}
bool iinf::operator != (const iinf &rhs) const { return compare(rhs) != 0; }
bool iinf::operator < (const iinf &rhs) const { return compare(rhs) < 0; }
bool iinf::operator > (const iinf &rhs) const { return compare(rhs) > 0; }
bool iinf::operator <= (const iinf &rhs) const { return compare(rhs) <= 0; }
bool iinf::operator >= (const iinf &rhs) const { return compare(rhs) >= 0; }
