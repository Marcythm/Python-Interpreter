#pragma once
_Pragma("once")

#include "config.hpp"
#include "Object.hpp"
#include "../Evalvisitor.h"


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

public:
	Vec<Object> result;

	FunctionCall() = default;
	FunctionCall(Python3Parser::Atom_exprContext *);
	~FunctionCall() = default;

	Object& varRef(const str &);
	const Object& varVal(const str &);

	static void newFunction(Python3Parser::FuncdefContext *);
	static RawFunction* funcinfo(const str &);
};
