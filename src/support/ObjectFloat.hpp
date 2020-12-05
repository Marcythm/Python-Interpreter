#ifndef Python_Interpreter_Support_ObjectFloat
#define Python_Interpreter_Support_ObjectFloat

#include "ObjectNone.hpp"

class ObjectFloat: public ObjectNone {
	f64 value;

public:
	/* constructors */
	ObjectFloat();

	explicit ObjectFloat(const iinf &);
	explicit ObjectFloat(const str &);
	explicit ObjectFloat(const char *&&);
	explicit ObjectFloat(bool);
	explicit ObjectFloat(f64);

	/* destructor */
	~ObjectFloat();

	// inline bool isFloat() const { return true; };

	ObjectInt asInt() const;
	ObjectStr asStr() const;
	ObjectBool asBool() const;
	ObjectFloat asFloat() const;

	inline operator f64& () { return value; };
	inline operator const f64& () const { return value; };

	/* comparison operators */
	template <typename T> i32 cmp(const T &) const;
	template <typename T> inline bool operator == (const T &rhs) const { return cmp(rhs) == 0; };
	template <typename T> inline bool operator != (const T &rhs) const { return cmp(rhs) != 0; };
	template <typename T> inline bool operator < (const T &rhs) const { return cmp(rhs) < 0; };
	template <typename T> inline bool operator > (const T &rhs) const { return cmp(rhs) > 0; };
	template <typename T> inline bool operator <= (const T &rhs) const { return cmp(rhs) <= 0; };
	template <typename T> inline bool operator >= (const T &rhs) const { return cmp(rhs) >= 0; };

};

#endif
