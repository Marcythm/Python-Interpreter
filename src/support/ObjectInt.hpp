#ifndef Python_Interpreter_Support_ObjectInt
#define Python_Interpreter_Support_ObjectInt

#include "ObjectNone.hpp"
#include "iinf.hpp"

class ObjectInt: public ObjectNone {
	iinf value;

public:
	/* constructors */
	ObjectInt();
	explicit ObjectInt(iinf &&);

	explicit ObjectInt(const iinf &);
	explicit ObjectInt(const str &);
	explicit ObjectInt(const char *&&);
	explicit ObjectInt(bool);
	explicit ObjectInt(f64);

	/* destructor */
	~ObjectInt();

	// inline bool isInt() const { return true; };

	ObjectInt asInt() const;
	ObjectStr asStr() const;
	ObjectBool asBool() const;
	ObjectFloat asFloat() const;

	inline operator iinf& () { return value; };
	inline operator const iinf& () const { return value; };

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

// operator + - * / % <=> = and or not
