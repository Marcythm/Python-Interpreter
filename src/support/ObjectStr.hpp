#ifndef Python_Interpreter_Support_ObjectStr
#define Python_Interpreter_Support_ObjectStr

#include "ObjectNone.hpp"

class ObjectStr: public ObjectNone {
	str value;

public:
	ObjectStr();
	explicit ObjectStr(str &&s);

	explicit ObjectStr(const iinf &val);
	explicit ObjectStr(const str &s);
	explicit ObjectStr(const char *&&s);
	explicit ObjectStr(bool val);
	explicit ObjectStr(f64 val);

	~ObjectStr();

	inline bool isStr() const { return true; };

	inline ObjectInt asInt() const { return ObjectInt(value); }
	inline ObjectStr asStr() const { return *this; }
	inline ObjectBool asBool() const { return ObjectBool(value); }
	inline ObjectFloat asFloat() const { return ObjectFloat(value); }

	inline operator str& () { return value; }
	inline operator const str& () const { return value; }
};

#endif
