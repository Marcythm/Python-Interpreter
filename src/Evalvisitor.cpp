#include "Evalvisitor.h"
#include "support/iinf.hpp"

using antlrcpp::Any;

Any EvalVisitor::visitFile_input(Python3Parser::File_inputContext *ctx) { return visitChildren(ctx); }

#pragma ToBeComplete
Any EvalVisitor::visitFuncdef(Python3Parser::FuncdefContext *ctx) {

}

#pragma ToBeComplete
Any EvalVisitor::visitParameters(Python3Parser::ParametersContext *ctx) {

}

#pragma ToBeComplete
Any EvalVisitor::visitTypedargslist(Python3Parser::TypedargslistContext *ctx) {

}

Any EvalVisitor::visitTfpdef(Python3Parser::TfpdefContext *ctx) { return ctx->NAME()->getText(); }

Any EvalVisitor::visitStmt(Python3Parser::StmtContext *ctx) { return visitChildren(ctx); }

Any EvalVisitor::visitSimple_stmt(Python3Parser::Simple_stmtContext *ctx) { return visitChildren(ctx); }

Any EvalVisitor::visitSmall_stmt(Python3Parser::Small_stmtContext *ctx) { return visitChildren(ctx); }

#pragma ToBeComplete
Any EvalVisitor::visitExpr_stmt(Python3Parser::Expr_stmtContext *ctx) {

}

Any EvalVisitor::visitAugassign(Python3Parser::AugassignContext *ctx) { return ctx->getText(); }

Any EvalVisitor::visitFlow_stmt(Python3Parser::Flow_stmtContext *ctx) { return visitChildren(ctx); }

#pragma ToBeComplete
Any EvalVisitor::visitBreak_stmt(Python3Parser::Break_stmtContext *ctx) {

}

#pragma ToBeComplete
Any EvalVisitor::visitContinue_stmt(Python3Parser::Continue_stmtContext *ctx) {

}

#pragma ToBeComplete
Any EvalVisitor::visitReturn_stmt(Python3Parser::Return_stmtContext *ctx) {

}

Any EvalVisitor::visitCompound_stmt(Python3Parser::Compound_stmtContext *ctx) { return visitChildren(ctx); }

#pragma ToBeComplete
Any EvalVisitor::visitIf_stmt(Python3Parser::If_stmtContext *ctx) {

}

#pragma ToBeComplete
Any EvalVisitor::visitWhile_stmt(Python3Parser::While_stmtContext *ctx) {

}

#pragma ToBeComplete
Any EvalVisitor::visitSuite(Python3Parser::SuiteContext *ctx) {

}

Any EvalVisitor::visitTest(Python3Parser::TestContext *ctx) { return visitOr_test(ctx->or_test()); }

Any EvalVisitor::visitOr_test(Python3Parser::Or_testContext *ctx) {
	for (auto subctx: ctx->and_test())
		if (visitAnd_test(subctx))
			return Obj(true);
	return Obj(false);
}

Any EvalVisitor::visitAnd_test(Python3Parser::And_testContext *ctx) {
	for (auto subctx: ctx->not_test())
		if (not visitNot_test(subctx))
			return Obj(false);
	return Obj(true);
}

Any EvalVisitor::visitNot_test(Python3Parser::Not_testContext *ctx) {
	if (ctx->NOT())
		return not visitNot_test(ctx->not_test());
	return visitComparison(ctx->comparison());
}

Any EvalVisitor::visitComparison(Python3Parser::ComparisonContext *ctx) {
	if (ctx->comp_op().size() == 0)
		return visitArith_expr(ctx->arith_expr(0));

	Obj lhs, rhs = visitArith_expr(ctx->arith_expr(0));
	for (i32 i = 0, sz = ctx->comp_op().size(); i < sz; ++i) {
		lhs = rhs; rhs = visitArith_expr(ctx->arith_expr(i + 1));
		if (const auto &&op = ctx->comp_op(i)->getText();
			(op == "==" and lhs != rhs)
		or	(op == "!=" and lhs == rhs)
		or	(op == "<"  and lhs >= rhs)
		or	(op == ">"  and lhs <= rhs)
		or	(op == "<=" and lhs >  rhs)
		or	(op == ">=" and lhs <  rhs)
		) return Obj(false);
	}

	return Obj(true);
}

// Any EvalVisitor::visitComp_op(Python3Parser::Comp_opContext *ctx) { return ctx->getText(); }

Any EvalVisitor::visitArith_expr(Python3Parser::Arith_exprContext *ctx) {
	Obj value = visitTerm(ctx->term(0));
	for (i32 i = 0, sz = ctx->addorsub_op().size(); i < sz; ++i)
		if (const auto &&op = ctx->addorsub_op(i)->getText(); op == "+")
			value += visitTerm(ctx->term(i + 1));
		else
			value -= visitTerm(ctx->term(i + 1));

	return value;
}

// Any EvalVisitor::visitAddorsub_op(Python3Parser::Addorsub_opContext *ctx) { return ctx->getText(); }

Any EvalVisitor::visitTerm(Python3Parser::TermContext *ctx) {
	Obj value = visitFactor(ctx->factor(0));
	for (i32 i = 0, sz = ctx->muldivmod_op().size(); i < sz; ++i)
		if (const auto &&op = ctx->muldivmod_op(i)->getText(); op == "*")
			value *= visitFactor(ctx->factor(i + 1));
		else if (op == "%")
			value %= visitFactor(ctx->factor(i + 1));
		else
			value /= visitFactor(ctx->factor(i + 1));

	return value;
}

// Any EvalVisitor::visitMuldivmod_op(Python3Parser::Muldivmod_opContext *ctx) { return ctx->getText(); }

Any EvalVisitor::visitFactor(Python3Parser::FactorContext *ctx) {
	if (ctx->factor())
		return ctx->MINUS() ? -visitFactor(ctx->factor()).as<Obj>() : visitFactor(ctx->factor()).as<Obj>();
	return visitAtom_expr(ctx->atom_expr());
}

#pragma ToBeComplete
Any EvalVisitor::visitAtom_expr(Python3Parser::Atom_exprContext *ctx) {
	if (ctx->trailer()) {
		// in this case the atom exoression is a function call
	}
	return visitAtom(ctx->atom());
}

#pragma ToBeComplete
Any EvalVisitor::visitTrailer(Python3Parser::TrailerContext *ctx) {

}

#pragma ToBeComplete
Any EvalVisitor::visitAtom(Python3Parser::AtomContext *ctx) {
	if (ctx->NAME())
		return vars[ctx->NAME()->getText()];
	if (ctx->NUMBER())
		return Obj(ctx->NUMBER()->getText());
	return visitChildren(ctx);
}

#pragma ToBeComplete
Any EvalVisitor::visitTestlist(Python3Parser::TestlistContext *ctx) {
	return visitChildren(ctx);
}

#pragma ToBeComplete
Any EvalVisitor::visitArglist(Python3Parser::ArglistContext *ctx) {
	return visitChildren(ctx);
}

#pragma ToBeComplete
Any EvalVisitor::visitArgument(Python3Parser::ArgumentContext *ctx) {
	return visitChildren(ctx);
}

#pragma ToBeComplete
EvalVisitor::EvalVisitor(): Python3BaseVisitor() {}
