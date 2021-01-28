#include "Evalvisitor.h"

using antlrcpp::Any;

auto EvalVisitor::visitParameters(Python3Parser::ParametersContext *ctx)		-> Any { return visitChildren(ctx); }
auto EvalVisitor::visitTypedargslist(Python3Parser::TypedargslistContext *ctx)	-> Any { return visitChildren(ctx); }
auto EvalVisitor::visitTfpdef(Python3Parser::TfpdefContext *ctx)				-> Any { return visitChildren(ctx); }
auto EvalVisitor::visitAugassign(Python3Parser::AugassignContext *ctx)			-> Any { return visitChildren(ctx); }
auto EvalVisitor::visitComp_op(Python3Parser::Comp_opContext *ctx)				-> Any { return visitChildren(ctx); }
auto EvalVisitor::visitAddorsub_op(Python3Parser::Addorsub_opContext *ctx)		-> Any { return visitChildren(ctx); }
auto EvalVisitor::visitMuldivmod_op(Python3Parser::Muldivmod_opContext *ctx)	-> Any { return visitChildren(ctx); }
auto EvalVisitor::visitTrailer(Python3Parser::TrailerContext *ctx)				-> Any { return visitChildren(ctx); }
auto EvalVisitor::visitArglist(Python3Parser::ArglistContext *ctx)				-> Any { return visitChildren(ctx); }
auto EvalVisitor::visitArgument(Python3Parser::ArgumentContext *ctx)			-> Any { return visitChildren(ctx); }

auto EvalVisitor::visitFile_input(Python3Parser::File_inputContext *ctx)		-> Any { return visitChildren(ctx); }
auto EvalVisitor::visitStmt(Python3Parser::StmtContext *ctx)					-> Any { return visitChildren(ctx); }
auto EvalVisitor::visitSimple_stmt(Python3Parser::Simple_stmtContext *ctx)		-> Any { return visitChildren(ctx); }
auto EvalVisitor::visitSmall_stmt(Python3Parser::Small_stmtContext *ctx)		-> Any { return visitChildren(ctx); }
auto EvalVisitor::visitFlow_stmt(Python3Parser::Flow_stmtContext *ctx)			-> Any { return visitChildren(ctx); }
auto EvalVisitor::visitCompound_stmt(Python3Parser::Compound_stmtContext *ctx)	-> Any { return visitChildren(ctx); }


extern FunctionCall* current;
extern FunctionCall* global;

auto EvalVisitor::visitFuncdef(Python3Parser::FuncdefContext *ctx) -> Any {
	FunctionCall::newFunction(ctx);
	return Object();
}

auto EvalVisitor::visitExpr_stmt(Python3Parser::Expr_stmtContext *ctx) -> Any {
	if (ctx->augassign()) {
		const auto lhs = ctx->testlist(0)->test(); auto lit = lhs.begin();
		const auto rhs = ctx->testlist(1)->test(); auto rit = rhs.begin();
		if (auto aug = ctx->augassign()->getText();
				aug == "+=")	for (; lit != lhs.end(); ++lit, ++rit) current->varRef((*lit)->getText()) += visitTest(*rit).as<Object>();
		else if (aug == "-=")	for (; lit != lhs.end(); ++lit, ++rit) current->varRef((*lit)->getText()) -= visitTest(*rit).as<Object>();
		else if (aug == "*=")	for (; lit != lhs.end(); ++lit, ++rit) current->varRef((*lit)->getText()) *= visitTest(*rit).as<Object>();
		else if (aug == "/=")	for (; lit != lhs.end(); ++lit, ++rit) current->varRef((*lit)->getText()) /= visitTest(*rit).as<Object>();
		else if (aug == "//=")	for (; lit != lhs.end(); ++lit, ++rit) current->varRef((*lit)->getText()).diveq(visitTest(*rit).as<Object>());
		else if (aug == "%=")	for (; lit != lhs.end(); ++lit, ++rit) current->varRef((*lit)->getText()) %= visitTest(*rit).as<Object>();
		return Object();
	}

	auto testlists = ctx->testlist();
	auto listit = testlists.rbegin();
	const auto value = visitTestlist(*listit).as<Vec<Object>>();
	for (; ++listit != testlists.rend(); ) {
		for (i32 i = 0; i < value.size(); ++i)
			current->varRef((*listit)->test(i)->getText()) = value[i];
	}

	return Object();
}

auto EvalVisitor::visitBreak_stmt(Python3Parser::Break_stmtContext *ctx) -> Any {
	throw FlowControl::BREAK();
	return Object();
}

auto EvalVisitor::visitContinue_stmt(Python3Parser::Continue_stmtContext *ctx) -> Any {
	throw FlowControl::CONTINUE();
	return Object();
}

auto EvalVisitor::visitReturn_stmt(Python3Parser::Return_stmtContext *ctx) -> Any {
	if (ctx->testlist())
		throw visitTestlist(ctx->testlist()).as<Vec<Object>>();
	throw Vec<Object>(1, Object());
	return Object();
}

auto EvalVisitor::visitIf_stmt(Python3Parser::If_stmtContext *ctx) -> Any {
	const auto conds = ctx->test();
	const auto suites = ctx->suite();
	for (i32 i = 0; i < i32(conds.size()); ++i)
		if (visitTest(conds[i]).as<Object>().as<bool>())
			return visitSuite(suites[i]);
	if (ctx->ELSE()) return visitSuite(suites.back());
	return Object();
}

auto EvalVisitor::visitWhile_stmt(Python3Parser::While_stmtContext *ctx) -> Any {
	for (; visitTest(ctx->test()).as<Object>().as<bool>(); )
		try {
			visitSuite(ctx->suite());
		} catch (FlowControl::BREAK) { break; }
		catch (FlowControl::CONTINUE) { continue; }
	return Object();
}

auto EvalVisitor::visitSuite(Python3Parser::SuiteContext *ctx) -> Any { return visitChildren(ctx); }

auto EvalVisitor::visitTest(Python3Parser::TestContext *ctx) -> Any { return visitOr_test(ctx->or_test()); }

auto EvalVisitor::visitOr_test(Python3Parser::Or_testContext *ctx) -> Any {
	if (ctx->OR().empty())
		return visitAnd_test(ctx->and_test(0));
	for (auto subctx: ctx->and_test())
		if (visitAnd_test(subctx).as<Object>().as<bool>())
			return Object(true);
	return Object(false);
}

auto EvalVisitor::visitAnd_test(Python3Parser::And_testContext *ctx) -> Any {
	if (ctx->AND().empty())
		return visitNot_test(ctx->not_test(0));
	for (auto subctx: ctx->not_test())
		if (not visitNot_test(subctx).as<Object>().as<bool>())
			return Object(false);
	return Object(true);
}

auto EvalVisitor::visitNot_test(Python3Parser::Not_testContext *ctx) -> Any {
	if (ctx->NOT())
		return not visitNot_test(ctx->not_test()).as<Object>();
	return visitComparison(ctx->comparison());
}

auto EvalVisitor::visitComparison(Python3Parser::ComparisonContext *ctx) -> Any {
	if (ctx->comp_op().empty())
		return visitArith_expr(ctx->arith_expr(0));

	Object lhs, rhs = std::move(visitArith_expr(ctx->arith_expr(0)).as<Object>());
	for (i32 i = 0, sz = ctx->comp_op().size(); i < sz; ++i) {
		lhs = std::move(rhs);
		rhs = std::move(visitArith_expr(ctx->arith_expr(i + 1)).as<Object>());
		if (const auto op = ctx->comp_op(i)->getText();
			(op == "==" and lhs != rhs)
		or	(op == "!=" and lhs == rhs)
		or	(op == "<"  and lhs >= rhs)
		or	(op == ">"  and lhs <= rhs)
		or	(op == "<=" and lhs >  rhs)
		or	(op == ">=" and lhs <  rhs)
		) return Object(false);
	}

	return Object(true);
}

auto EvalVisitor::visitArith_expr(Python3Parser::Arith_exprContext *ctx) -> Any {
	if (ctx->addorsub_op().empty())
		return visitTerm(ctx->term(0));
	Object value = std::move(visitTerm(ctx->term(0)).as<Object>());
	for (i32 i = 0, sz = ctx->addorsub_op().size(); i < sz; ++i)
		if (const auto op = ctx->addorsub_op(i)->getText(); op == "+")
			value += visitTerm(ctx->term(i + 1)).as<Object>();
		else
			value -= visitTerm(ctx->term(i + 1)).as<Object>();

	return value;
}

auto EvalVisitor::visitTerm(Python3Parser::TermContext *ctx) -> Any {
	if (ctx->muldivmod_op().empty())
		return visitFactor(ctx->factor(0));
	Object value = std::move(visitFactor(ctx->factor(0)).as<Object>());
	for (i32 i = 0, sz = ctx->muldivmod_op().size(); i < sz; ++i)
		if (const auto op = ctx->muldivmod_op(i)->getText(); op == "*")
			value *= visitFactor(ctx->factor(i + 1)).as<Object>();
		else if (op == "/")
			value /= visitFactor(ctx->factor(i + 1)).as<Object>();
		else if (op == "//")
			value.diveq(visitFactor(ctx->factor(i + 1)).as<Object>());
		else
			value %= visitFactor(ctx->factor(i + 1)).as<Object>();

	return value;
}

auto EvalVisitor::visitFactor(Python3Parser::FactorContext *ctx) -> Any {
	if (ctx->factor()) {
		if (ctx->MINUS())
			return -visitFactor(ctx->factor()).as<Object>();
		return visitFactor(ctx->factor()).as<Object>();
	} return visitAtom_expr(ctx->atom_expr());
}

auto EvalVisitor::visitAtom_expr(Python3Parser::Atom_exprContext *ctx) -> Any {
	if (ctx->trailer()) {
		const auto name = ctx->atom()->getText();
		if (name == "print") {
			if (auto arglis = ctx->trailer()->arglist()) {
				auto args = arglis->argument();
				auto it = args.begin();
				printf("%s", visitTest((*it)->test(0)).as<Object>().as<str>().c_str());
				for (; ++it != args.end(); )
					printf(" %s", visitTest((*it)->test(0)).as<Object>().as<str>().c_str());
			} puts("");
			return Object();
		}
		else if (name == "int")		return Object(visitTest(ctx->trailer()->arglist()->argument(0)->test(0)).as<Object>().as<innerTypes::Int>());
		else if (name == "str")		return Object(visitTest(ctx->trailer()->arglist()->argument(0)->test(0)).as<Object>().as<innerTypes::Str>());
		else if (name == "bool")	return Object(visitTest(ctx->trailer()->arglist()->argument(0)->test(0)).as<Object>().as<innerTypes::Bool>());
		else if (name == "float")	return Object(visitTest(ctx->trailer()->arglist()->argument(0)->test(0)).as<Object>().as<innerTypes::Float>());
		// in this case the atom expression is a function call
		auto result = FunctionCall(ctx).result;
		if (result.size() == 1) return result[0];
		return result;
	}
	return visitAtom(ctx->atom());
}

auto EvalVisitor::visitAtom(Python3Parser::AtomContext *ctx) -> Any {
	auto raw = ctx->getText();
	if (ctx->NAME())		return current->varVal(raw);
	if (ctx->NUMBER())		return (raw.find('.') == str::npos) ? Object(i99(raw)) : Object(std::stod(raw));
	if (not (ctx->STRING().empty())) {
		str res;
		for (auto subctx: ctx->STRING()) {
			auto substr = subctx->getText();
			res.insert(res.end(), ++substr.begin(), --substr.end());
		}
		return Object(res);
	}
	if (raw == "None")		return Object();
	if (raw == "True")		return Object(true);
	if (raw == "False")		return Object(false);
	return visitTest(ctx->test());
}

auto EvalVisitor::visitTestlist(Python3Parser::TestlistContext *ctx) -> Any {
	const auto tests = ctx->test();
	Vec<Object> res;
	for (auto subctx: tests) {
		auto tmp = std::move(visitTest(subctx));
		if (tmp.is<Vec<Object>>()) return tmp.as<Vec<Object>>();
		res.emplace_back(std::move(tmp.as<Object>()));
	}
	return res;
}


EvalVisitor::EvalVisitor(): Python3BaseVisitor() {
	global = current = new FunctionCall();
}
EvalVisitor::~EvalVisitor() {
	delete current;
}
