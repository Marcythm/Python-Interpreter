file_input: (NEWLINE | stmt)* EOF;

suite: simple_stmt | NEWLINE INDENT stmt+ DEDENT;
stmt: simple_stmt | compound_stmt;

	compound_stmt: if_stmt | while_stmt | funcdef ;
		if_stmt: 'if' test ':' suite ('elif' test ':' suite)* ('else' ':' suite)?;
		while_stmt: 'while' test ':' suite;
		funcdef: 'def' NAME parameters ':' suite;
			parameters: '(' typedargslist? ')';
			typedargslist: (tfpdef ('=' test)? (',' tfpdef ('=' test)?)*);
			tfpdef: NAME ;

	simple_stmt: small_stmt  NEWLINE;
	small_stmt: expr_stmt | flow_stmt;

		flow_stmt: break_stmt | continue_stmt | return_stmt;
		break_stmt: 'break';
		continue_stmt: 'continue';
		return_stmt: 'return' (testlist)?;

		expr_stmt: testlist ( (augassign testlist) | ('=' testlist)*);
		augassign: ('+=' | '-=' | '*=' | '/=' | '//=' | '%=' );

		testlist: test (',' test)* (',')?;
		test: or_test ; // boolean expression: bool or Object
		or_test: and_test ('or' and_test)*;
		and_test: not_test ('and' not_test)*;
		not_test: 'not' not_test | comparison;
			comparison: arith_expr (comp_op arith_expr)*; // compare expression: bool or Object
			comp_op: '<' | '>' | '==' | '>=' | '<=' | '!=';
				arith_expr: term (addorsub_op term)*; // arithmetic expression: Object
				addorsub_op: '+' | '-';
					term: factor (muldivmod_op factor)*; // arithmetic expression (mul/div/mod ops included only): Object
					muldivmod_op: '*' | '/' | '//' | '%';
						factor: ('+' | '-') factor | atom_expr; // atom expression (with sign): Object
						atom_expr: atom trailer?; // a term or a function call (in case trailer matched): Object
							atom: (NAME | NUMBER | STRING+ | 'None' | 'True' | 'False' | ('(' test ')'));
							trailer: '(' (arglist)? ')' ;

		arglist: argument (',' argument)*  (',')?; // argument list
		argument: ( test | test '=' test ); // argument of a function
