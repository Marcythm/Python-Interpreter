#pragma once

#ifndef PYTHON_INTERPRETER_SUPPORT_FUNCTION
#define PYTHON_INTERPRETER_SUPPORT_FUNCTION

#include "Object.hpp"
#include "../../generated/Python3BaseVisitor.h"


struct RawFunction {
	Python3Parser::FuncdefContext *entry;
	Vec<str> parameters;
	std::map<str, Object> default_args;

	RawFunction() = default;
	RawFunction(RawFunction &&);
	RawFunction(Python3Parser::FuncdefContext *);
};


class FunctionCall {
	std::map<str, Object> vars;
	std::map<str, RawFunction*> funcs;
	Vec<RawFunction*> newFuncs;
	RawFunction* entry_info;

public:
	Vec<Object> result;

	FunctionCall() = default;
	FunctionCall(Python3Parser::Atom_exprContext *);
	~FunctionCall();

	Object& varRef(const str &);
	const Object& varVal(const str &) const;
	void newFunction(Python3Parser::FuncdefContext *);
	RawFunction& funcRef(const str &);
};


#endif
