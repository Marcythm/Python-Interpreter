#include "Function.hpp"
#include "../Evalvisitor.h"

extern EvalVisitor visitor;


RawFunction::RawFunction(RawFunction &&rhs): entry(rhs.entry), parameters(std::move(rhs.parameters)), default_args(std::move(rhs.default_args)) {}

RawFunction::RawFunction(RawFunction::entry_t *ctx): entry(ctx) {
	auto paralist = ctx->parameters()->typedargslist();
	auto namelist = paralist->tfpdef();
	auto testlist = paralist->test();

	for (auto subctx: namelist)
		parameters.emplace_back(subctx->getText());
	auto nameit = namelist.rbegin();
	auto testit = testlist.rbegin();
	for (; testit != testlist.rend(); ++nameit, ++testit)
		default_args[(*nameit)->getText()] = visitor.visit(*testit).as<Object>();
}

FunctionCall* current;

FunctionCall::FunctionCall(Python3Parser::Atom_exprContext *ctx): entry_info(&(current->funcRef(ctx->atom()->getText()))) {
	/* initialize */
	vars = entry_info->default_args;
	auto args = ctx->trailer()->arglist()->argument();

	auto argit = args.rbegin();
	auto nameit = entry_info->parameters.rbegin();
	for (; argit != args.rend() and (*argit)->ASSIGN(); ++argit, ++nameit)
		vars[(*argit)->test(0)->getText()] = visitor.visit((*argit)->test(1)).as<Object>();
	for (; argit != args.rend(); ++argit, ++nameit)
		vars[*nameit] = visitor.visit((*argit)->test(0)).as<Object>();

	/* run function suite */
	auto tmp = current;
	try {
		current = this;
		visitor.visit(entry_info->entry);
		result = Vec<Object>(1, Object::NONE);
	} catch (Vec<Object> res) {
		result = std::move(res);
	}
	current = tmp;
};


Object& FunctionCall::varRef(const str &name) {
	return vars[name];
}

void FunctionCall::newFunction(Python3Parser::FuncdefContext *ctx) {
	funcs.emplace(std::make_pair(ctx->NAME()->getText(), RawFunction(ctx)));
}

RawFunction& FunctionCall::funcRef(const str &name) {
	return funcs[name];
}
