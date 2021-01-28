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

	auto varRef(const str &) -> Object&;
	auto varVal(const str &) -> const Object&;

	static auto newFunction(Python3Parser::FuncdefContext *) -> void;
	static auto funcinfo(const str &) -> RawFunction*;
};
