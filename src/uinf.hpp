#ifndef Python_Interpreter_unsigned_integer
#define Python_Interpreter_unsigned_integer

#include "claim.hpp"

class uinf {
	// lower bit in lower index
	// e.g. 1234567 = Vec<u32>{7, 6, 5, 4, 3, 2, 1}
	Vec<i32> value;

	void resize(u32 new_length) { resize(new_length); }
	void remove_leading_zero() {
		while (not value.empty() and value.back() == 0) value.pop_back();
		if (value.size() == 0) value.emplace_back(0);
	}
	i32 cmp(const uinf &rhs) const; // usage: equal to three-way comparison operator <=>

public:
	const u32 len() const { return value.size(); }

	uinf(): value(1, 0) { }
	template <typename T> explicit uinf(T val);
	explicit uinf(const char *s);
	explicit uinf(const str &s);
	uinf(const uinf &rhs) { operator=(rhs); }
	uinf(uinf &&rhs) noexcept;

	uinf& operator = (const uinf &rhs) = default;
	uinf& operator = (uinf &&rhs) noexcept;

	i32& operator [] (const u32 &index);
	const i32& operator [] (const u32 &index) const;

	uinf operator + (const uinf &rhs) const;
	uinf operator - (const uinf &rhs) const;
	uinf operator * (const uinf &rhs) const;
	uinf operator / (const uinf &rhs) const;
	uinf operator % (const uinf &rhs) const;

	uinf& operator += (const uinf &rhs) { return operator=(operator+(rhs)); };
	uinf& operator -= (const uinf &rhs) { return operator=(operator-(rhs)); };
	uinf& operator *= (const uinf &rhs) { return operator=(operator*(rhs)); };
	uinf& operator /= (const uinf &rhs) { return operator=(operator/(rhs)); };
	uinf& operator %= (const uinf &rhs) { return operator=(operator%(rhs)); };

	bool operator == (const uinf &rhs) const;
	bool operator != (const uinf &rhs) const;
	bool operator < (const uinf &rhs) const;
	bool operator > (const uinf &rhs) const;
	bool operator <= (const uinf &rhs) const;
	bool operator >= (const uinf &rhs) const;
};

#endif