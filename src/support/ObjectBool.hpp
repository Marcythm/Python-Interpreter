#ifndef Python_Interpreter_Support_ObjectBool
#define Python_Interpreter_Support_ObjectBool

#include "ObjectNone.hpp"

class ObjectBool: public ObjectNone {
	bool value;

public:
	ObjectBool();

	explicit ObjectBool(const iinf &val);
	explicit ObjectBool(const str &s);
	explicit ObjectBool(const char *&&s);
	explicit ObjectBool(bool val);
	explicit ObjectBool(f64 val);

	~ObjectBool();

	inline bool isBool() const { return true; };

	inline ObjectInt asInt() const { return ObjectInt(value); }
	inline ObjectStr asStr() const { return ObjectStr(value); }
	inline ObjectBool asBool() const { return *this; }
	inline ObjectFloat asFloat() const { return ObjectFloat(value); }

	inline operator bool& () { return value; }
	inline operator const bool& () const { return value; }
};

#endif
