#ifndef Python_Interpreter_Support_Object
#define Python_Interpreter_Support_Object

#include "None.hpp"
#include "Int.hpp"
#include "Str.hpp"
#include "Bool.hpp"
#include "Float.hpp"

using innerTypes::None;
using innerTypes::Int;
using innerTypes::Str;
using innerTypes::Bool;
using innerTypes::Float;

class Object {
public:
static const None NONE;

private:
	None *ptr;

public:
	Object();
	Object(const Object &);
	Object(Object &&);

	Object(const iinf &);
	Object(const str &);
	Object(const char *);
	Object(bool);
	Object(f64);

	~Object();

	template <typename T>
	inline bool is_type() const { return as_type<T>() != nullptr; }

	template <typename T>
	inline T* as_type() const { return dynamic_cast<T*>(ptr); }

	inline Int asInt() const { return ptr->asInt(); };
	inline Str asStr() const { return ptr->asStr(); };
	inline Bool asBool() const { return ptr->asBool(); };
	inline Float asFloat() const { return ptr->asFloat(); };


	/* comparison operators */
	i8 compare(const Object &) const;
	inline bool operator == (const Object &rhs) const { return compare(rhs) == 0; };
	inline bool operator != (const Object &rhs) const { return compare(rhs) != 0; };
	inline bool operator < (const Object &rhs) const { return compare(rhs) < 0; };
	inline bool operator > (const Object &rhs) const { return compare(rhs) > 0; };
	inline bool operator <= (const Object &rhs) const { return compare(rhs) <= 0; };
	inline bool operator >= (const Object &rhs) const { return compare(rhs) >= 0; };

	/* assignment operators */
	Object& operator = (const Object &);
	Object& operator = (Object &&);

	inline bool operator not () const { return not ptr->asBool().data(); }
	Object operator - () const;

	Object operator + (const Object &) const;
	Object operator - (const Object &) const;
	Object operator * (const Object &) const;
	Object operator / (const Object &) const;
	Object div(const Object &) const;
	Object operator % (const Object &) const;

	inline Object operator += (const Object &rhs) {return *this = *this + rhs; };
	inline Object operator -= (const Object &rhs) {return *this = *this - rhs; };
	inline Object operator *= (const Object &rhs) {return *this = *this * rhs; };
	inline Object operator /= (const Object &rhs) {return *this = *this / rhs; };
	inline Object& div_eq(const Object &rhs) { return *this = this->div(rhs);};
	inline Object operator %= (const Object &rhs) {return *this = *this % rhs; };
};

#endif
