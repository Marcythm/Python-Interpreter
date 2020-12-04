#ifndef Python_Interpreter_Support_Object
#define Python_Interpreter_Support_Object


#include "ObjectNone.hpp"
#include "ObjectInt.hpp"
#include "ObjectStr.hpp"
#include "ObjectBool.hpp"
#include "ObjectFloat.hpp"

class Object {
	ObjectNone *ptr;

public:
	Object();
	~Object();

};

#endif
