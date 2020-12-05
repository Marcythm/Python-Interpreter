#ifndef Python_Interpreter_Support_ObjectNone
#define Python_Interpreter_Support_ObjectNone

#include "claim.hpp"

struct ObjectNone {
	ObjectNone();
	virtual ~ObjectNone();

	// virtual inline bool isInt() const { return false; };
	// virtual inline bool isStr() const { return false; };
	// virtual inline bool isBool() const { return false; };
	// virtual inline bool isFloat() const { return false; };

	virtual ObjectInt asInt() const;
	virtual ObjectStr asStr() const;
	virtual ObjectBool asBool() const;
	virtual ObjectFloat asFloat() const;
};

#endif
