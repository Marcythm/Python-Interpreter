#include "Evalvisitor.h"

using antlrcpp::Any;

Any EvalVisitor::visitParameters(Python3Parser::ParametersContext *ctx)			{ return visitChildren(ctx); }
Any EvalVisitor::visitTypedargslist(Python3Parser::TypedargslistContext *ctx)	{ return visitChildren(ctx); }
Any EvalVisitor::visitTfpdef(Python3Parser::TfpdefContext *ctx)					{ return visitChildren(ctx); }
Any EvalVisitor::visitAugassign(Python3Parser::AugassignContext *ctx)			{ return visitChildren(ctx); }
Any EvalVisitor::visitComp_op(Python3Parser::Comp_opContext *ctx)				{ return visitChildren(ctx); }
Any EvalVisitor::visitAddorsub_op(Python3Parser::Addorsub_opContext *ctx)		{ return visitChildren(ctx); }
Any EvalVisitor::visitMuldivmod_op(Python3Parser::Muldivmod_opContext *ctx)		{ return visitChildren(ctx); }
Any EvalVisitor::visitTrailer(Python3Parser::TrailerContext *ctx)				{ return visitChildren(ctx); }
Any EvalVisitor::visitArglist(Python3Parser::ArglistContext *ctx)				{ return visitChildren(ctx); }
Any EvalVisitor::visitArgument(Python3Parser::ArgumentContext *ctx)				{ return visitChildren(ctx); }

Any EvalVisitor::visitFile_input(Python3Parser::File_inputContext *ctx)			{ return visitChildren(ctx); }
Any EvalVisitor::visitStmt(Python3Parser::StmtContext *ctx)						{ return visitChildren(ctx); }
Any EvalVisitor::visitSimple_stmt(Python3Parser::Simple_stmtContext *ctx)		{ return visitChildren(ctx); }
Any EvalVisitor::visitSmall_stmt(Python3Parser::Small_stmtContext *ctx)			{ return visitChildren(ctx); }
Any EvalVisitor::visitFlow_stmt(Python3Parser::Flow_stmtContext *ctx)			{ return visitChildren(ctx); }
Any EvalVisitor::visitCompound_stmt(Python3Parser::Compound_stmtContext *ctx)	{ return visitChildren(ctx); }


extern FunctionCall* current;

Any EvalVisitor::visitFuncdef(Python3Parser::FuncdefContext *ctx) {
	current->newFunction(ctx);
	return Object::NONE;
}

Any EvalVisitor::visitExpr_stmt(Python3Parser::Expr_stmtContext *ctx) {
	if (ctx->augassign()) {
		const auto lhs = ctx->testlist(0)->test(); auto lit = lhs.begin();
		const auto rhs = ctx->testlist(1)->test(); auto rit = rhs.begin();
		if (auto aug = ctx->augassign()->getText();
				aug == "+=")	for (; lit != lhs.end(); ++lit, ++rit) current->varRef((*lit)->getText()) += visit(*rit).as<Object>();
		else if (aug == "-=")	for (; lit != lhs.end(); ++lit, ++rit) current->varRef((*lit)->getText()) -= visit(*rit).as<Object>();
		else if (aug == "*=")	for (; lit != lhs.end(); ++lit, ++rit) current->varRef((*lit)->getText()) *= visit(*rit).as<Object>();
		else if (aug == "/=")	for (; lit != lhs.end(); ++lit, ++rit) current->varRef((*lit)->getText()) /= visit(*rit).as<Object>();
		else if (aug == "//=")	for (; lit != lhs.end(); ++lit, ++rit) current->varRef((*lit)->getText()).diveq(visit(*rit).as<Object>());
		else if (aug == "%=")	for (; lit != lhs.end(); ++lit, ++rit) current->varRef((*lit)->getText()) %= visit(*rit).as<Object>();
		return Object::NONE;
	}

	auto testlists = ctx->testlist();
	auto listit = testlists.rbegin();
	const auto value = visit(*listit).as<Vec<Object>>();
	for (; ++listit != testlists.rend(); ) {
		for (i32 i = 0; i < value.size(); ++i)
			current->varRef((*listit)->test(i)->getText()) = value[i];
	}

	return Object::NONE;
}

Any EvalVisitor::visitBreak_stmt(Python3Parser::Break_stmtContext *ctx) {
	throw FlowControl::BREAK();
	return Object::NONE;
}

Any EvalVisitor::visitContinue_stmt(Python3Parser::Continue_stmtContext *ctx) {
	throw FlowControl::CONTINUE();
	return Object::NONE;
}

Any EvalVisitor::visitReturn_stmt(Python3Parser::Return_stmtContext *ctx) {
	if (ctx->testlist())
		throw visit(ctx->testlist()).as<Vec<Object>>();
	throw Vec<Object>(1, Object::NONE);
	return Object::NONE;
}

Any EvalVisitor::visitIf_stmt(Python3Parser::If_stmtContext *ctx) {
	const auto &&conds = ctx->test();
	const auto &&suites = ctx->suite();
	for (i32 i = 0; i < i32(conds.size()); ++i)
		if (visit(conds[i]).as<Object>().as<bool>())
			return visit(suites[i]);
	if (ctx->ELSE()) return visit(suites.back());
	return Object::NONE;
}

Any EvalVisitor::visitWhile_stmt(Python3Parser::While_stmtContext *ctx) {
	for (; visit(ctx->test()).as<Object>().as<bool>(); )
		try {
			visit(ctx->suite());
		} catch (FlowControl::BREAK) { break; }
		catch (FlowControl::CONTINUE) { continue; }
	return Object::NONE;
}

Any EvalVisitor::visitSuite(Python3Parser::SuiteContext *ctx) { return visitChildren(ctx); }

Any EvalVisitor::visitTest(Python3Parser::TestContext *ctx) { return visit(ctx->or_test()); }

Any EvalVisitor::visitOr_test(Python3Parser::Or_testContext *ctx) {
	for (auto subctx: ctx->and_test())
		if (visit(subctx).as<Object>().as<bool>())
			return Object(true);
	return Object(false);
}

Any EvalVisitor::visitAnd_test(Python3Parser::And_testContext *ctx) {
	for (auto subctx: ctx->not_test())
		if (not visit(subctx).as<Object>().as<bool>())
			return Object(false);
	return Object(true);
}

Any EvalVisitor::visitNot_test(Python3Parser::Not_testContext *ctx) {
	if (ctx->NOT())
		return not visit(ctx->not_test()).as<Object>();
	return visit(ctx->comparison());
}

Any EvalVisitor::visitComparison(Python3Parser::ComparisonContext *ctx) {
	if (ctx->comp_op().size() == 0)
		return visit(ctx->arith_expr(0));

	Object lhs, rhs = visit(ctx->arith_expr(0)).as<Object>();
	for (i32 i = 0, sz = ctx->comp_op().size(); i < sz; ++i) {
		lhs = rhs; rhs = visit(ctx->arith_expr(i + 1)).as<Object>();
		if (const auto &&op = ctx->comp_op(i)->getText();
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

Any EvalVisitor::visitArith_expr(Python3Parser::Arith_exprContext *ctx) {
	Object value = std::move(visit(ctx->term(0)).as<Object>());
	for (i32 i = 0, sz = ctx->addorsub_op().size(); i < sz; ++i)
		if (const auto &&op = ctx->addorsub_op(i)->getText(); op == "+")
			value += visit(ctx->term(i + 1)).as<Object>();
		else
			value -= visit(ctx->term(i + 1)).as<Object>();

	return value;
}

Any EvalVisitor::visitTerm(Python3Parser::TermContext *ctx) {
	Object value = std::move(visit(ctx->factor(0)).as<Object>());
	for (i32 i = 0, sz = ctx->muldivmod_op().size(); i < sz; ++i)
		if (const auto &&op = ctx->muldivmod_op(i)->getText(); op == "*")
			value *= visit(ctx->factor(i + 1)).as<Object>();
		else if (op == "%")
			value %= visit(ctx->factor(i + 1)).as<Object>();
		else if (op == "//")
			value /= visit(ctx->factor(i + 1)).as<Object>();
		else
			value.diveq(visit(ctx->factor(i + 1)).as<Object>());

	return value;
}

Any EvalVisitor::visitFactor(Python3Parser::FactorContext *ctx) {
	if (ctx->factor()) {
		if (ctx->MINUS())
			return -visit(ctx->factor()).as<Object>();
		return visit(ctx->factor()).as<Object>();
	} return visit(ctx->atom_expr());
}

Any EvalVisitor::visitAtom_expr(Python3Parser::Atom_exprContext *ctx) {
	if (ctx->trailer()) {
		const auto name = ctx->atom()->getText();
		if (name == "print") {
			auto args = ctx->trailer()->arglist()->argument();
			auto it = args.begin();

			printf("%s", visit((*it)->test(0)).as<Object>().as<str>().c_str());
			for (; it != args.end(); ++it)
				printf(" %s", visit((*it)->test(0)).as<Object>().as<str>().c_str());
			puts("");
		}
		else if (name == "int")		return visit(ctx->trailer()->arglist()->argument(0)->test(0)).as<Object>().as<innerTypes::Int>();
		else if (name == "str")		return visit(ctx->trailer()->arglist()->argument(0)->test(0)).as<Object>().as<innerTypes::Str>();
		else if (name == "bool")	return visit(ctx->trailer()->arglist()->argument(0)->test(0)).as<Object>().as<innerTypes::Bool>();
		else if (name == "float")	return visit(ctx->trailer()->arglist()->argument(0)->test(0)).as<Object>().as<innerTypes::Float>();
		// in this case the atom expression is a function call
		auto result = FunctionCall(ctx).result;
		if (result.size() == 1) return result[0];
		return result;
	}
	return visit(ctx->atom());
}

Any EvalVisitor::visitAtom(Python3Parser::AtomContext *ctx) {
	auto raw = ctx->getText();
	if (ctx->NAME())		return current->varRef(raw);
	if (ctx->NUMBER())		return Object(iinf(raw));
	if (not (ctx->STRING().empty())) {
		str res;
		for (auto subctx: ctx->STRING()) {
			auto substr = subctx->getText();
			res.insert(res.end(), substr.begin(), substr.end());
		}
		return Object(res);
	}
	if (raw == "None")		return Object::NONE;
	if (raw == "True")		return Object(true);
	if (raw == "False")		return Object(false);
	return visit(ctx->test());
}

Any EvalVisitor::visitTestlist(Python3Parser::TestlistContext *ctx) {
	Vec<Object> res;
	for (auto subctx: ctx->test())
		res.emplace_back(std::move(visit(subctx).as<Object>()));
	return res;
}


EvalVisitor::EvalVisitor(): Python3BaseVisitor() {
	current = new FunctionCall();
}
EvalVisitor::~EvalVisitor() {
	delete current;
}
