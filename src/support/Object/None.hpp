#ifndef Python_Interpreter_Support_None
#define Python_Interpreter_Support_None

#include "../claim.hpp"

namespace innerTypes {

struct None {
	None();
	virtual ~None();

	template <typename T> T as() const;
};

}

#endif
