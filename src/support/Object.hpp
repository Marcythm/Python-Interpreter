#ifndef Python_Interpreter_Support_Object
#define Python_Interpreter_Support_Object

#include "ObjectNone.hpp"
#include "ObjectInt.hpp"
#include "ObjectStr.hpp"
#include "ObjectBool.hpp"
#include "ObjectFloat.hpp"

class Object {
public:
static const ObjectNone None;

private:
	ObjectNone *ptr;

public:
	Object();
	~Object();

	template <typename T>
	inline bool is() const { return as<T>() != nullptr; }

	template <typename T>
	inline T as() const { return dynamic_cast<T>(ptr); }

	inline ObjectInt asInt() const { return ptr->asInt(); };
	inline ObjectStr asStr() const { return ptr->asStr(); };
	inline ObjectBool asBool() const { return ptr->asBool(); };
	inline ObjectFloat asFloat() const { return ptr->asFloat(); };
};

#endif
