#include "Function.hpp"
#include "../Evalvisitor.h"

extern EvalVisitor visitor;

RawFunction::RawFunction(RawFunction &&rhs): entry(rhs.entry), parameters(std::move(rhs.parameters)), default_args(std::move(rhs.default_args)) {}

RawFunction::RawFunction(Python3Parser::FuncdefContext *ctx): entry(ctx) {
	if (auto paralist = ctx->parameters()->typedargslist()) {
		auto namelist = paralist->tfpdef();
		auto testlist = paralist->test();

		for (auto subctx: namelist)
			parameters.emplace_back(subctx->getText());
		auto nameit = namelist.rbegin();
		auto testit = testlist.rbegin();
		for (; testit != testlist.rend(); ++nameit, ++testit)
			default_args[(*nameit)->getText()] = visitor.visitTest(*testit).as<Object>();
	}
}

FunctionCall* current;

std::map<str, RawFunction> FunctionCall::funcs;

FunctionCall::FunctionCall(Python3Parser::Atom_exprContext *ctx): entry_info(&(FunctionCall::funcRef(ctx->atom()->getText()))) {
	/* initialize */
	if (entry_info) vars = entry_info->default_args;
	if (auto arglis = ctx->trailer()->arglist()) {
		auto args = arglis->argument();
		auto argit = args.begin();
		auto nameit = entry_info->parameters.begin();

		for (; argit != args.end() and (*argit)->ASSIGN() == nullptr; ++argit, ++nameit)
			vars[*nameit] = visitor.visitTest((*argit)->test(0)).as<Object>();
		for (; argit != args.end(); ++argit)
			vars[(*argit)->test(0)->getText()] = visitor.visit((*argit)->test(1)).as<Object>();
	}

	/* run function suite */
	auto origin = current;
	try {
		current = this;
		visitor.visitSuite(entry_info->entry->suite());
		result = Vec<Object>(1, Object());
	} catch (Vec<Object> res) {
		result = std::move(res);
	}
	current = origin;
};


Object& FunctionCall::varRef(const str &name) {
	return vars[name];
}

const Object& FunctionCall::varVal(const str &name) const {
	return vars.find(name)->second;
}

void FunctionCall::newFunction(Python3Parser::FuncdefContext *ctx) {
	funcs.emplace(ctx->NAME()->getText(), RawFunction(ctx));
}

RawFunction& FunctionCall::funcRef(const str &name) {
	return funcs[name];
}
