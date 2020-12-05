#ifndef Python_Interpreter_Support_ObjectBool
#define Python_Interpreter_Support_ObjectBool

#include "ObjectNone.hpp"

class ObjectBool: public ObjectNone {
	bool value;

public:
	/* constructors */
	ObjectBool();

	explicit ObjectBool(const iinf &);
	explicit ObjectBool(const str &);
	explicit ObjectBool(const char *&&);
	explicit ObjectBool(bool);
	explicit ObjectBool(f64);

	/* destructor */
	~ObjectBool();

	// inline bool isBool() const { return true; };

	ObjectInt asInt() const;
	ObjectStr asStr() const;
	ObjectBool asBool() const;
	ObjectFloat asFloat() const;

	inline operator bool& () { return value; };
	inline operator const bool& () const { return value; };

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
