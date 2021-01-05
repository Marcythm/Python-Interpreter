#include "Evalvisitor.h"

using antlrcpp::Any;

FlowController funcFlow, loopFlow;

Any EvalVisitor::visitFile_input(Python3Parser::File_inputContext *ctx) { return visitChildren(ctx); }

// TODO: Funcdef
Any EvalVisitor::visitFuncdef(Python3Parser::FuncdefContext *ctx) {

}

Any EvalVisitor::visitParameters(Python3Parser::ParametersContext *ctx) { return visit(ctx->typedargslist()); }

// XXX: Typedargslist
Any EvalVisitor::visitTypedargslist(Python3Parser::TypedargslistContext *ctx) { }

// Any EvalVisitor::visitTfpdef(Python3Parser::TfpdefContext *ctx) { return ctx->NAME()->getText(); }

Any EvalVisitor::visitStmt(Python3Parser::StmtContext *ctx) { return visitChildren(ctx); }

Any EvalVisitor::visitSimple_stmt(Python3Parser::Simple_stmtContext *ctx) { return visitChildren(ctx); }

Any EvalVisitor::visitSmall_stmt(Python3Parser::Small_stmtContext *ctx) { return visitChildren(ctx); }

// TODO: Expr_stmt
Any EvalVisitor::visitExpr_stmt(Python3Parser::Expr_stmtContext *ctx) {
	// auto &lhs = visit(ctx->testlist(0));
	if (ctx->augassign()) {
	}

}

// Any EvalVisitor::visitAugassign(Python3Parser::AugassignContext *ctx) { return ctx->getText(); }

Any EvalVisitor::visitFlow_stmt(Python3Parser::Flow_stmtContext *ctx) { return visitChildren(ctx); }

Any EvalVisitor::visitBreak_stmt(Python3Parser::Break_stmtContext *ctx) {
	loopFlow.breakout();
	return Object::NONE;
}

Any EvalVisitor::visitContinue_stmt(Python3Parser::Continue_stmtContext *ctx) {
	loopFlow.nextloop();
	return Object::NONE;
}

Any EvalVisitor::visitReturn_stmt(Python3Parser::Return_stmtContext *ctx) {
	funcFlow.exit();
	if (ctx->testlist()) return visit(ctx->testlist());
	return Object::NONE;
}

Any EvalVisitor::visitCompound_stmt(Python3Parser::Compound_stmtContext *ctx) { return visitChildren(ctx); }

Any EvalVisitor::visitIf_stmt(Python3Parser::If_stmtContext *ctx) {
	const auto &&conds = ctx->test();
	const auto &&suites = ctx->suite();
	for (i32 i = 0; i < i32(conds.size()); ++i)
		if (visit(conds[i]).as<Object>().asBool().data())
			return visit(suites[i]);
	if (ctx->ELSE()) return visit(suites.back());
	return Object::NONE;
}

Any EvalVisitor::visitWhile_stmt(Python3Parser::While_stmtContext *ctx) {
	loopFlow.newScope();
	for (; visit(ctx->test()).as<Object>().asBool().data(); ) {
		Object res = std::move(visit(ctx->suite()));

		if (funcFlow.exited()) {
			loopFlow.delScope();
			return res;
		}

		if (loopFlow.exited()) break;
		loopFlow.activate();
	}
	loopFlow.delScope();
	return Object::NONE;
}

Any EvalVisitor::visitSuite(Python3Parser::SuiteContext *ctx) {
	if (ctx->simple_stmt())
		return visit(ctx->simple_stmt());
	for (auto subctx: ctx->stmt()) {
		if (not loopFlow.active()) break;
		const auto &&res = visit(subctx);
		if (funcFlow.exited()) return res;
	}
	return Object::NONE;
}

Any EvalVisitor::visitTest(Python3Parser::TestContext *ctx) { return visit(ctx->or_test()); }

Any EvalVisitor::visitOr_test(Python3Parser::Or_testContext *ctx) {
	for (auto subctx: ctx->and_test())
		if (visit(subctx).as<Object>().asBool().data())
			return Object(true);
	return Object(false);
}

Any EvalVisitor::visitAnd_test(Python3Parser::And_testContext *ctx) {
	for (auto subctx: ctx->not_test())
		if (not visit(subctx).as<Object>().asBool().data())
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

	Object lhs, rhs = visit(ctx->arith_expr(0));
	for (i32 i = 0, sz = ctx->comp_op().size(); i < sz; ++i) {
		lhs = rhs; rhs = visit(ctx->arith_expr(i + 1));
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

// Any EvalVisitor::visitComp_op(Python3Parser::Comp_opContext *ctx) { return ctx->getText(); }

Any EvalVisitor::visitArith_expr(Python3Parser::Arith_exprContext *ctx) {
	Object value = std::move(visit(ctx->term(0)).as<Object>());
	for (i32 i = 0, sz = ctx->addorsub_op().size(); i < sz; ++i)
		if (const auto &&op = ctx->addorsub_op(i)->getText(); op == "+")
			value += visit(ctx->term(i + 1)).as<Object>();
		else
			value -= visit(ctx->term(i + 1)).as<Object>();

	return value;
}

// Any EvalVisitor::visitAddorsub_op(Python3Parser::Addorsub_opContext *ctx) { return ctx->getText(); }

// TODO: Term
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
			value.div_eq(visit(ctx->factor(i + 1)).as<Object>());

	return value;
}

// Any EvalVisitor::visitMuldivmod_op(Python3Parser::Muldivmod_opContext *ctx) { return ctx->getText(); }

Any EvalVisitor::visitFactor(Python3Parser::FactorContext *ctx) {
	if (ctx->factor()) {
		if (ctx->MINUS())
			return -visit(ctx->factor()).as<Object>();
		return visit(ctx->factor()).as<Object>();
	} return visit(ctx->atom_expr());
}

// TODO: Atom_expr
Any EvalVisitor::visitAtom_expr(Python3Parser::Atom_exprContext *ctx) {
	if (ctx->trailer()) {
		// in this case the atom exoression is a function call

	}
	return visit(ctx->atom());
}

// XXX: Trailer
// Any EvalVisitor::visitTrailer(Python3Parser::TrailerContext *ctx) { return visit(ctx->arglist()); }

// TODO: Atom
Any EvalVisitor::visitAtom(Python3Parser::AtomContext *ctx) {
	// if (ctx->NAME())
		// return vars[ctx->NAME()->getText()];
	if (ctx->NUMBER())
		return Object(ctx->NUMBER()->getText());
	return nullptr;
}

Any EvalVisitor::visitTestlist(Python3Parser::TestlistContext *ctx) {
	Vec<Object> res;
	for (auto subctx: ctx->test())
		res.emplace_back(std::move(visit(subctx).as<Object>()));
	if (res.size() == 1) return std::move(res[0]);
	return res;
}

// XXX: Arglist
// Any EvalVisitor::visitArglist(Python3Parser::ArglistContext *ctx) { }

// XXX: Argument
// Any EvalVisitor::visitArgument(Python3Parser::ArgumentContext *ctx) { }

// TODO: EvalVisitor
EvalVisitor::EvalVisitor(): Python3BaseVisitor() {}
