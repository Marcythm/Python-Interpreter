#ifndef Python_Interpreter_unsigned_integer
#define Python_Interpreter_unsigned_integer

#include "claim.hpp"

class u {
	// lower bit in lower index
	// e.g. 1234567 = Vec<u32>{7, 6, 5, 4, 3, 2, 1}
	Vec<i32> value;

	void resize(u32 new_length) { resize(new_length); }
	void remove_leading_zero() { while (not value.empty() and value.back() == 0) value.pop_back(); }
	i32 cmp(const u &rhs) const; // usage: equal to three-way comparison operator <=>

public:
	const u32 len() const { return value.size(); }

	u() { }
	template <typename T> explicit u(T val);
	explicit u(const char *s);
	explicit u(const str &s);
	u(const u &rhs) { operator=(rhs); }
	u(u &&rhs) noexcept;

	u& operator = (const u &rhs) = default;
	u& operator = (u &&rhs) noexcept;

	i32& operator [] (const u32 &index);
	const i32& operator [] (const u32 &index) const;

	u operator + (const u &rhs) const;
	u operator - (const u &rhs) const;
	u operator * (const u &rhs) const;
	u operator / (const u &rhs) const;
	u operator % (const u &rhs) const;

	u& operator += (const u &rhs) { return operator=(operator+(rhs)); };
	u& operator -= (const u &rhs) { return operator=(operator-(rhs)); };
	u& operator *= (const u &rhs) { return operator=(operator*(rhs)); };
	u& operator /= (const u &rhs) { return operator=(operator/(rhs)); };
	u& operator %= (const u &rhs) { return operator=(operator%(rhs)); };

	bool operator == (const u &rhs) const;
	bool operator != (const u &rhs) const;
	bool operator < (const u &rhs) const;
	bool operator > (const u &rhs) const;
	bool operator <= (const u &rhs) const;
	bool operator >= (const u &rhs) const;
};

#endif
