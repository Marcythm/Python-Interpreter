#pragma once

#ifndef PYTHON_INTERPRETER_SUPPORT_IINF
#define PYTHON_INTERPRETER_SUPPORT_IINF

#include "uinf.hpp"

class iinf {
static constexpr i8 NEG = -1;
static constexpr i8 ZERO = 0;
static constexpr i8 POS = 1;

	i8 sign;
	uinf value;

	void detect_sign();

public:
	u32 len() const;
	template <typename T> T as() const;

	bool isnegative() const;
	bool iszero() const;
	bool ispositive() const;

	iinf();
	// template <typename T> iinf(T val);
	iinf(i32);
	iinf(i64);

	explicit iinf(const char *s);
	explicit iinf(const str &s);

	iinf(const uinf &rhs, i8 sgn = POS);
	iinf(uinf &&rhs, i8 sgn = POS) noexcept;

	iinf(const iinf &rhs);
	iinf(iinf &&rhs) noexcept;

	iinf& operator = (const iinf &rhs);
	iinf& operator = (iinf &&rhs) noexcept;

	i32& operator [] (const u32 index);
	const i32& operator [] (const u32 index) const;

	iinf operator + (const iinf &rhs) const;
	iinf operator - (const iinf &rhs) const;
	iinf operator * (const iinf &rhs) const;
	iinf operator / (const iinf &rhs) const;
	iinf operator % (const iinf &rhs) const;

	iinf operator - () const;

	iinf& operator += (const iinf &rhs);
	iinf& operator -= (const iinf &rhs);
	iinf& operator *= (const iinf &rhs);
	iinf& operator /= (const iinf &rhs);
	iinf& operator %= (const iinf &rhs);

	i8 compare(const iinf &rhs) const; /* usage: equal to three-way comparison operator <=> */
	bool operator == (const iinf &rhs) const;
	bool operator != (const iinf &rhs) const;
	bool operator < (const iinf &rhs) const;
	bool operator > (const iinf &rhs) const;
	bool operator <= (const iinf &rhs) const;
	bool operator >= (const iinf &rhs) const;
};

#endif
