#ifndef Python_Interpreter_Support_ObjectNone
#define Python_Interpreter_Support_ObjectNone

#include "claim.hpp"

struct ObjectNone {
	ObjectNone();
	virtual ~ObjectNone();

	virtual inline bool isInt() const { return false; };
	virtual inline bool isStr() const { return false; };
	virtual inline bool isBool() const { return false; };
	virtual inline bool isFloat() const { return false; };

	virtual inline ObjectInt asInt() const { return ObjectInt(); }
	virtual inline ObjectStr asStr() const { return ObjectStr("None"); }
	virtual inline ObjectBool asBool() const { return ObjectBool(); }
	virtual inline ObjectFloat asFloat() const { return ObjectFloat(); }
};

#endif
