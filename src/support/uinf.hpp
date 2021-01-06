#pragma once

#ifndef Python_Interpreter_Support_unsigned_integer
#define Python_Interpreter_Support_unsigned_integer

#include "claim.hpp"

class uinf {
	/* lower bit in lower index
	 * e.g. 1234567 = Vec<u32>{7, 6, 5, 4, 3, 2, 1}
	 * */
	Vec<i32> value;

	void resize(u32 new_length);
	void remove_leading_zero();

public:
	u32 len() const;
	bool iszero() const;
	template <typename T> T as() const;

	uinf();
	// template <typename T> uinf(T val);
	uinf(i32);
	uinf(i64);

	explicit uinf(const char *s);
	explicit uinf(const str &s);

	uinf(const Vec<i32> &rhs);
	uinf(Vec<i32> &&rhs);

	uinf(const uinf &rhs);
	uinf(uinf &&rhs) noexcept;

	uinf& operator = (const uinf &rhs);
	uinf& operator = (uinf &&rhs) noexcept;

	i32& operator [] (const u32 index);
	const i32& operator [] (const u32 index) const;

	uinf operator + (const uinf &rhs) const;
	uinf operator - (const uinf &rhs) const;
	uinf operator * (const uinf &rhs) const;
	uinf operator / (const uinf &rhs) const;
	uinf operator % (const uinf &rhs) const;

	uinf& operator += (const uinf &rhs);
	uinf& operator -= (const uinf &rhs);
	uinf& operator *= (const uinf &rhs);
	uinf& operator /= (const uinf &rhs);
	uinf& operator %= (const uinf &rhs);

	i32 compare(const uinf &rhs) const; /* usage: equal to three-way comparison operator <=> */
	bool operator == (const uinf &rhs) const;
	bool operator != (const uinf &rhs) const;
	bool operator < (const uinf &rhs) const;
	bool operator > (const uinf &rhs) const;
	bool operator <= (const uinf &rhs) const;
	bool operator >= (const uinf &rhs) const;

	friend class iinf;
};

#endif
