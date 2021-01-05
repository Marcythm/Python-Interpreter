#pragma once
#ifndef Python_Interpreter_Support_Object
#define Python_Interpreter_Support_Object

#include "Value.hpp"

using innerTypes::None;
using innerTypes::Int;
using innerTypes::Str;
using innerTypes::Bool;
using innerTypes::Float;

class Object {
public:
static const None NONE;
static None *const noneptr;

private:
	None *ptr;

public:
	Object();
	Object(Object &&);
	Object(const Object &);

	template <typename T> Object(T &&);
	template <typename T> Object(const T &);

	~Object();

	// template <typename T>
	// inline bool is_type() const { return as_type<T>() != nullptr; }

	template <typename T>
	inline T* as_type() const { return dynamic_cast<T*>(ptr); }

	template <typename T> T as() const;

	/* comparison operators */
	i8 compare(const Object &) const;
	inline bool operator == (const Object &rhs) const { return compare(rhs) == 0; };
	inline bool operator != (const Object &rhs) const { return compare(rhs) != 0; };
	inline bool operator <  (const Object &rhs) const { return compare(rhs) <  0; };
	inline bool operator >  (const Object &rhs) const { return compare(rhs) >  0; };
	inline bool operator <= (const Object &rhs) const { return compare(rhs) <= 0; };
	inline bool operator >= (const Object &rhs) const { return compare(rhs) >= 0; };

	/* assignment operators */
	Object& operator = (const Object &);
	Object& operator = (Object &&);

	inline bool operator not () const { return not ptr->as<Bool>().data(); }
	Object operator - () const;

	Object operator +	(const Object &) const;
	Object operator -	(const Object &) const;
	Object operator *	(const Object &) const;
	Object operator /	(const Object &) const;
	Object div			(const Object &) const;
	Object operator %	(const Object &) const;

	inline Object& operator +=	(const Object &rhs) { return *this = *this + rhs; };
	inline Object& operator -=	(const Object &rhs) { return *this = *this - rhs; };
	inline Object& operator *=	(const Object &rhs) { return *this = *this * rhs; };
	inline Object& operator /=	(const Object &rhs) { return *this = *this / rhs; };
	inline Object& diveq		(const Object &rhs) { return *this = this->div(rhs); };
	inline Object& operator %=	(const Object &rhs) { return *this = *this % rhs; };
};

#endif
