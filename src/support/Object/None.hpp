#ifndef Python_Interpreter_Support_None
#define Python_Interpreter_Support_None

#include "../claim.hpp"

namespace innerTypes {

struct None {
	None();
	virtual ~None();

	// virtual inline bool isInt() const { return false; };
	// virtual inline bool isStr() const { return false; };
	// virtual inline bool isBool() const { return false; };
	// virtual inline bool isFloat() const { return false; };

	virtual Int asInt() const;
	virtual Str asStr() const;
	virtual Bool asBool() const;
	virtual Float asFloat() const;
};

}

#endif
