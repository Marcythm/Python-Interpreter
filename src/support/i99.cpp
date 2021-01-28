#include "i99.hpp"


/* ---------- private functions ---------- */

auto i99::detect_sign() -> void { if (value.iszero()) sign = ZERO; }

/* ---------- public functions ----------  */

auto i99::len()			const -> u32  { return value.len(); }
auto i99::isnegative()	const -> bool { return sign == NEG; }
auto i99::iszero()		const -> bool { return sign == ZERO; }
auto i99::ispositive()	const -> bool { return sign == POS; }

template <>
auto i99::as<bool>() const -> bool { return sign != 0; }

template <>
auto i99::as<str>() const -> str { return (isnegative() ? "-" : "") + value.as<str>(); }

template <>
auto i99::as<i32>() const -> i32 { return sign * static_cast<i32>(value.as<u32>()); }

template <>
auto i99::as<i64>() const -> i64 { return sign * static_cast<i64>(value.as<u64>()); }

template <>
auto i99::as<f64>() const -> f64 { return sign * value.as<f64>(); }

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

auto i99::operator [] (const u32 index) -> i32& { return value[index]; }
auto i99::operator [] (const u32 index) const -> const i32& { return value[index]; }


/* ---------- arithmetic operators ---------- */

auto i99::operator + (const i99 &rhs) const -> i99 {
	if (sign == rhs.sign) return i99(value + rhs.value, sign);
	if (iszero()) return rhs; if (rhs.iszero()) return *this;
	if (ispositive())
		return (value >= rhs.value) ? i99(value - rhs.value, POS) : i99(rhs.value - value, NEG);
	return (rhs.value >= value) ? i99(rhs.value - value, POS) : i99(value - rhs.value, NEG);
}

auto i99::operator - (const i99 &rhs) const -> i99 {
	if (sign * rhs.sign < 0) return i99(value + rhs.value, sign);
	if (iszero()) return -rhs; if (rhs.iszero()) return *this;
	if (ispositive())
		return (value >= rhs.value) ? i99(value - rhs.value, POS) : i99(rhs.value - value, NEG);
	return (rhs.value >= value) ? i99(rhs.value - value, POS) : i99(value - rhs.value, NEG);
}

auto i99::operator * (const i99 &rhs) const -> i99 { return i99(value * rhs.value, sign * rhs.sign); }

auto i99::operator / (const i99 &rhs) const -> i99 {
	if (rhs.iszero()) throw std::domain_error("in i99::operator / : Divide By Zero");
	if (iszero()) return i99();
	if (sign == rhs.sign) return i99(value / rhs.value, POS);
	if ((value % rhs.value).iszero()) return i99(value / rhs.value, NEG);
	return i99(value / rhs.value + u99(1), NEG);
}

/* a lazy implementation */
auto i99::operator % (const i99 &rhs) const -> i99 { return *this - rhs * (*this / rhs); }

auto i99::operator - () const -> i99 { return i99(value, -sign); }


auto i99::operator += (const i99 &rhs) -> i99& { return *this = *this + rhs; }
auto i99::operator -= (const i99 &rhs) -> i99& { return *this = *this - rhs; }
auto i99::operator *= (const i99 &rhs) -> i99& { return *this = *this * rhs; }
auto i99::operator /= (const i99 &rhs) -> i99& { return *this = *this / rhs; }
auto i99::operator %= (const i99 &rhs) -> i99& { return *this = *this % rhs; }


/* ---------- comparison operators ---------- */

/* usage: equal to three-way comparison operator <=> */
auto i99::compare(const i99 &rhs) const -> i8 {
	if (sign != rhs.sign) return sign < rhs.sign ? -1 : 1;
	return (isnegative() ? -1 : 1) * value.compare(rhs.value);
}

auto i99::operator == (const i99 &rhs) const -> bool { return compare(rhs) == 0;}
auto i99::operator != (const i99 &rhs) const -> bool { return compare(rhs) != 0; }
auto i99::operator < (const i99 &rhs) const -> bool { return compare(rhs) < 0; }
auto i99::operator > (const i99 &rhs) const -> bool { return compare(rhs) > 0; }
auto i99::operator <= (const i99 &rhs) const -> bool { return compare(rhs) <= 0; }
auto i99::operator >= (const i99 &rhs) const -> bool { return compare(rhs) >= 0; }
