#ifndef Python_Interpreter_Support_ObjectStr
#define Python_Interpreter_Support_ObjectStr

#include "ObjectNone.hpp"

class ObjectStr: public ObjectNone {
	str value;

public:
	/* constructors */
	ObjectStr();
	explicit ObjectStr(str &&);

	explicit ObjectStr(const iinf &);
	explicit ObjectStr(const str &);
	explicit ObjectStr(const char *&&);
	explicit ObjectStr(bool);
	explicit ObjectStr(f64);

	/* destructor */
	~ObjectStr();

	// inline bool isStr() const { return true; };

	ObjectInt asInt() const;
	ObjectStr asStr() const;
	ObjectBool asBool() const;
	ObjectFloat asFloat() const;

	inline operator str& () { return value; };
	inline operator const str& () const { return value; };

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
