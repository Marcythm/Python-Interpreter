#include "Function.hpp"

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
FunctionCall* global;

std::unordered_map<str, RawFunction> FunctionCall::funcs;

FunctionCall::FunctionCall(Python3Parser::Atom_exprContext *ctx) {
	auto entry_info = funcinfo(ctx->atom()->getText());
	/* initialize parameters */
	if (entry_info)
		for (const auto &p: entry_info->default_args)
			vars[p.first] = p.second;
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
	current = this;
	try {
		visitor.visitSuite(entry_info->entry->suite());
		result = Vec<Object>(1, Object());
	} catch (Vec<Object> res) {
		result = std::move(res);
	}
	current = origin;
}


auto FunctionCall::varRef(const str &name) -> Object& {
	if (auto p = vars.find(name); p != vars.end())
		return p->second;
	if (auto p = global->vars.find(name); p != global->vars.end())
		return p->second;
	return vars[name];
}

auto FunctionCall::varVal(const str &name) -> const Object& {
	return varRef(name);
}

auto FunctionCall::newFunction(Python3Parser::FuncdefContext *ctx) -> void {
	funcs.emplace(ctx->NAME()->getText(), ctx);
}

auto FunctionCall::funcinfo(const str &name) -> RawFunction* {
	if (auto p = funcs.find(name); p != funcs.end())
		return &(p->second);
	return nullptr;
}
