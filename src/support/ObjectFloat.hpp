#ifndef Python_Interpreter_Support_ObjectFloat
#define Python_Interpreter_Support_ObjectFloat

#include "ObjectNone.hpp"

class ObjectFloat: public ObjectNone {
	f64 value;

public:
	ObjectFloat();

	explicit ObjectFloat(const iinf &val);
	explicit ObjectFloat(const str &s);
	explicit ObjectFloat(const char *&&s);
	explicit ObjectFloat(bool val);
	explicit ObjectFloat(f64 val);

	~ObjectFloat();

	inline bool isFloat() const { return true; };

	inline ObjectInt asInt() const { return ObjectInt(value); }
	inline ObjectStr asStr() const { return ObjectStr(value); }
	inline ObjectBool asBool() const { return ObjectBool(value); }
	inline ObjectFloat asFloat() const { return *this; }

	inline operator f64& () { return value; }
	inline operator const f64& () const { return value; }
};

#endif
