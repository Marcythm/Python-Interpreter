#pragma once
_Pragma("once")

#include "config.hpp"

class u99 {
	/* lower bit in lower index
	 * e.g. 1234567 = Vec<u32>{7, 6, 5, 4, 3, 2, 1}
	 * */
	Vec<i32> value;

	auto resize(u32 new_length) -> void;
	auto remove_leading_zero() -> void;

public:
	auto len() const -> u32;
	auto iszero() const -> bool;
	template <typename T> auto as() const -> T;

	u99();
	// template <typename T> u99(T val);
	u99(i32);
	u99(i64);

	explicit u99(const char *s);
	explicit u99(const str &s);

	u99(const Vec<i32> &rhs);
	u99(Vec<i32> &&rhs);

	u99(const u99 &rhs);
	u99(u99 &&rhs) noexcept;

	auto operator = (const u99 &rhs) -> u99&;
	auto operator = (u99 &&rhs) noexcept -> u99&;

	auto operator [] (const u32 index) -> i32& ;
	auto operator [] (const u32 index) const -> const i32& ;

	auto operator + (const u99 &rhs) const -> u99;
	auto operator - (const u99 &rhs) const -> u99;
	auto operator * (const u99 &rhs) const -> u99;
	auto operator / (const u99 &rhs) const -> u99;
	auto operator % (const u99 &rhs) const -> u99;

	auto operator += (const u99 &rhs) -> u99&;
	auto operator -= (const u99 &rhs) -> u99&;
	auto operator *= (const u99 &rhs) -> u99&;
	auto operator /= (const u99 &rhs) -> u99&;
	auto operator %= (const u99 &rhs) -> u99&;

	auto compare(const u99 &rhs) const -> i8; /* usage: equal to three-way comparison operator <=> */
	auto operator == (const u99 &rhs) const -> bool;
	auto operator != (const u99 &rhs) const -> bool;
	auto operator < (const u99 &rhs) const -> bool;
	auto operator > (const u99 &rhs) const -> bool;
	auto operator <= (const u99 &rhs) const -> bool;
	auto operator >= (const u99 &rhs) const -> bool;

	friend class i99;
};

template <typename T> auto u99::as() const -> T {
	if constexpr (std::is_same_v<T, bool>)
		return value.size() == 0;
	if constexpr (std::is_same_v<T, str>) {
		if (iszero()) return str("0");
		str s; s.reserve(len());
		for (auto i = value.rbegin(); i != value.rend(); ++i)
			s.push_back('0' + *i);
		return s;
	}
	if constexpr (std::is_integral_v<T>) {
		T val = 0;
		for (auto i = value.rbegin(); i != value.rend(); ++i)
			val = val * T(10) + T(*i);
		return val;
	}
	if constexpr (std::is_same_v<T, f64>)
		return std::stod(as<str>());
	throw std::bad_cast();
	return T();
}
