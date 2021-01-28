#pragma once
_Pragma("once")

#include "config.hpp"
#include "u99.hpp"

class i99 {
static constexpr i8 NEG = -1;
static constexpr i8 ZERO = 0;
static constexpr i8 POS = 1;

	i8 sign;
	u99 value;

	auto detect_sign() -> void;

public:
	auto len() const -> u32;
	template <typename T> auto as() const -> T;

	auto isnegative() const -> bool;
	auto iszero() const -> bool;
	auto ispositive() const -> bool;

	i99();
	// template <typename T> i99(T val);
	i99(i32);
	i99(i64);

	explicit i99(const char *s);
	explicit i99(const str &s);

	i99(const u99 &rhs, i8 sgn = POS);
	i99(u99 &&rhs, i8 sgn = POS) noexcept;

	i99(const i99 &rhs);
	i99(i99 &&rhs) noexcept;

	auto operator = (const i99 &rhs) -> i99&;
	auto operator = (i99 &&rhs) noexcept -> i99&;

	auto operator [] (const u32 index) -> i32&;
	auto operator [] (const u32 index) const -> const i32&;

	auto operator + (const i99 &rhs) const -> i99;
	auto operator - (const i99 &rhs) const -> i99;
	auto operator * (const i99 &rhs) const -> i99;
	auto operator / (const i99 &rhs) const -> i99;
	auto operator % (const i99 &rhs) const -> i99;

	auto operator - () const -> i99;

	auto operator += (const i99 &rhs) -> i99&;
	auto operator -= (const i99 &rhs) -> i99&;
	auto operator *= (const i99 &rhs) -> i99&;
	auto operator /= (const i99 &rhs) -> i99&;
	auto operator %= (const i99 &rhs) -> i99&;

	auto compare(const i99 &rhs) const -> i8; /* usage: equal to three-way comparison operator <=> */
	auto operator == (const i99 &rhs) const -> bool;
	auto operator != (const i99 &rhs) const -> bool;
	auto operator < (const i99 &rhs) const -> bool;
	auto operator > (const i99 &rhs) const -> bool;
	auto operator <= (const i99 &rhs) const -> bool;
	auto operator >= (const i99 &rhs) const -> bool;
};
