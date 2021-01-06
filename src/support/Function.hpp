#pragma once

#ifndef PYTHON_INTERPRETER_SUPPORT_FUNCTION
#define PYTHON_INTERPRETER_SUPPORT_FUNCTION

#include "Object.hpp"
#include "../../generated/Python3BaseVisitor.h"


struct RawFunction {
using entry_t = Python3Parser::FuncdefContext;

	entry_t *entry;
	Vec<str> parameters;
	std::map<str, Object> default_args;

	RawFunction() = default;
	RawFunction(RawFunction &&);
	RawFunction(entry_t *);
};


struct FunctionCall {
	std::map<str, Object> vars;
	std::map<str, RawFunction> funcs;
	RawFunction* entry_info;
	Vec<Object> result;

	FunctionCall() = default;
	FunctionCall(Python3Parser::Atom_exprContext *);
	~FunctionCall() = default;

	Object& varRef(const str &);
	void newFunction(Python3Parser::FuncdefContext *);
	RawFunction& funcRef(const str &);
};


#endif
