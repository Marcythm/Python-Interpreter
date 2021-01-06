#pragma once

#ifndef PYTHON_INTERPRETER_SUPPORT_FUNCTION
#define PYTHON_INTERPRETER_SUPPORT_FUNCTION

#include "Object.hpp"
#include "../../generated/Python3BaseVisitor.h"


struct RawFunction {
	Python3Parser::FuncdefContext *entry;
	Vec<str> parameters;
	std::unordered_map<str, Object> default_args;

	RawFunction() = default;
	RawFunction(RawFunction &&);
	RawFunction(Python3Parser::FuncdefContext *);
};


class FunctionCall {
	static std::unordered_map<str, RawFunction> funcs;
	std::unordered_map<str, Object> vars;
	RawFunction* entry_info;

public:
	Vec<Object> result;

	FunctionCall() = default;
	FunctionCall(Python3Parser::Atom_exprContext *);
	~FunctionCall() = default;

	Object& varRef(const str &);
	const Object& varVal(const str &) const;
	static void newFunction(Python3Parser::FuncdefContext *);
	static RawFunction& funcRef(const str &);
};


#endif
