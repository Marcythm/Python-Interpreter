#ifndef PYTHON_INTERPRETER_EVALVISITOR_H
#define PYTHON_INTERPRETER_EVALVISITOR_H


#include "../generated/Python3BaseVisitor.h"
#include "support/config.hpp"
#include "support/Object.hpp"
#include "support/Function.hpp"


class EvalVisitor: public Python3BaseVisitor {
//todo:override all methods of Python3BaseVisitor
public:

	virtual auto visitFile_input(Python3Parser::File_inputContext *ctx) 		-> antlrcpp::Any;

	virtual auto visitFuncdef(Python3Parser::FuncdefContext *ctx) 				-> antlrcpp::Any;
	virtual auto visitParameters(Python3Parser::ParametersContext *ctx) 		-> antlrcpp::Any;
	virtual auto visitTypedargslist(Python3Parser::TypedargslistContext *ctx)	-> antlrcpp::Any;
	virtual auto visitTfpdef(Python3Parser::TfpdefContext *ctx) 				-> antlrcpp::Any;

	virtual auto visitStmt(Python3Parser::StmtContext *ctx) 					-> antlrcpp::Any;
	virtual auto visitSimple_stmt(Python3Parser::Simple_stmtContext *ctx) 		-> antlrcpp::Any;
	virtual auto visitSmall_stmt(Python3Parser::Small_stmtContext *ctx) 		-> antlrcpp::Any;
	virtual auto visitExpr_stmt(Python3Parser::Expr_stmtContext *ctx) 			-> antlrcpp::Any;
	virtual auto visitAugassign(Python3Parser::AugassignContext *ctx) 			-> antlrcpp::Any;

	virtual auto visitFlow_stmt(Python3Parser::Flow_stmtContext *ctx) 			-> antlrcpp::Any;
	virtual auto visitBreak_stmt(Python3Parser::Break_stmtContext *ctx) 		-> antlrcpp::Any;
	virtual auto visitContinue_stmt(Python3Parser::Continue_stmtContext *ctx)	-> antlrcpp::Any;
	virtual auto visitReturn_stmt(Python3Parser::Return_stmtContext *ctx) 		-> antlrcpp::Any;
	virtual auto visitCompound_stmt(Python3Parser::Compound_stmtContext *ctx)	-> antlrcpp::Any;
	virtual auto visitIf_stmt(Python3Parser::If_stmtContext *ctx) 				-> antlrcpp::Any;
	virtual auto visitWhile_stmt(Python3Parser::While_stmtContext *ctx) 		-> antlrcpp::Any;

	virtual auto visitSuite(Python3Parser::SuiteContext *ctx) 					-> antlrcpp::Any;

	virtual auto visitTest(Python3Parser::TestContext *ctx) 					-> antlrcpp::Any;
	virtual auto visitOr_test(Python3Parser::Or_testContext *ctx) 				-> antlrcpp::Any;
	virtual auto visitAnd_test(Python3Parser::And_testContext *ctx) 			-> antlrcpp::Any;
	virtual auto visitNot_test(Python3Parser::Not_testContext *ctx) 			-> antlrcpp::Any;
	virtual auto visitComparison(Python3Parser::ComparisonContext *ctx) 		-> antlrcpp::Any;
	virtual auto visitComp_op(Python3Parser::Comp_opContext *ctx) 				-> antlrcpp::Any;
	virtual auto visitArith_expr(Python3Parser::Arith_exprContext *ctx) 		-> antlrcpp::Any;
	virtual auto visitAddorsub_op(Python3Parser::Addorsub_opContext *ctx) 		-> antlrcpp::Any;
	virtual auto visitTerm(Python3Parser::TermContext *ctx) 					-> antlrcpp::Any;
	virtual auto visitMuldivmod_op(Python3Parser::Muldivmod_opContext *ctx) 	-> antlrcpp::Any;
	virtual auto visitFactor(Python3Parser::FactorContext *ctx) 				-> antlrcpp::Any;
	virtual auto visitAtom_expr(Python3Parser::Atom_exprContext *ctx) 			-> antlrcpp::Any;
	virtual auto visitTrailer(Python3Parser::TrailerContext *ctx) 				-> antlrcpp::Any;
	virtual auto visitAtom(Python3Parser::AtomContext *ctx) 					-> antlrcpp::Any;

	virtual auto visitTestlist(Python3Parser::TestlistContext *ctx) 			-> antlrcpp::Any;
	virtual auto visitArglist(Python3Parser::ArglistContext *ctx) 				-> antlrcpp::Any;
	virtual auto visitArgument(Python3Parser::ArgumentContext *ctx) 			-> antlrcpp::Any;

	EvalVisitor();
	~EvalVisitor();
};


#endif //PYTHON_INTERPRETER_EVALVISITOR_H
