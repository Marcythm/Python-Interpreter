#ifndef Python_Interpreter_Support_ObjectInt
#define Python_Interpreter_Support_ObjectInt

#include "ObjectNone.hpp"
#include "iinf.hpp"

class ObjectInt: public ObjectNone {
	iinf value;

public:
	ObjectInt();
	explicit ObjectInt(iinf &&val);

	explicit ObjectInt(const iinf &val);
	explicit ObjectInt(const str &s);
	explicit ObjectInt(const char *&&s);
	explicit ObjectInt(bool val);
	explicit ObjectInt(f64 val);

	~ObjectInt();

	inline bool isInt() const { return true; };

	inline ObjectInt asInt() const { return *this; }
	inline ObjectStr asStr() const { return ObjectStr(value); }
	inline ObjectBool asBool() const { return ObjectBool(value); }
	inline ObjectFloat asFloat() const { return ObjectFloat(value); }

	inline operator iinf& () { return value; }
	inline operator const iinf& () const { return value; }
};

#endif
