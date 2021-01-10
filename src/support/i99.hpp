#pragma once

#ifndef PYTHON_INTERPRETER_SUPPORT_IINF
#define PYTHON_INTERPRETER_SUPPORT_IINF

#include "u99.hpp"

class i99 {
static constexpr i8 NEG = -1;
static constexpr i8 ZERO = 0;
static constexpr i8 POS = 1;

	i8 sign;
	u99 value;

	void detect_sign();

public:
	u32 len() const;
	template <typename T> T as() const;

	bool isnegative() const;
	bool iszero() const;
	bool ispositive() const;

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

	i99& operator = (const i99 &rhs);
	i99& operator = (i99 &&rhs) noexcept;

	i32& operator [] (const u32 index);
	const i32& operator [] (const u32 index) const;

	i99 operator + (const i99 &rhs) const;
	i99 operator - (const i99 &rhs) const;
	i99 operator * (const i99 &rhs) const;
	i99 operator / (const i99 &rhs) const;
	i99 operator % (const i99 &rhs) const;

	i99 operator - () const;

	i99& operator += (const i99 &rhs);
	i99& operator -= (const i99 &rhs);
	i99& operator *= (const i99 &rhs);
	i99& operator /= (const i99 &rhs);
	i99& operator %= (const i99 &rhs);

	i8 compare(const i99 &rhs) const; /* usage: equal to three-way comparison operator <=> */
	bool operator == (const i99 &rhs) const;
	bool operator != (const i99 &rhs) const;
	bool operator < (const i99 &rhs) const;
	bool operator > (const i99 &rhs) const;
	bool operator <= (const i99 &rhs) const;
	bool operator >= (const i99 &rhs) const;
};

#endif
