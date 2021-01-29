#include <iostream>
#include "antlr4-runtime.h"
#include "Python3Lexer.h"
#include "Python3Parser.h"
#include "Evalvisitor.h"
using namespace antlr4;
//todo: regenerating files in directory named "generated" is dangerous.
//       if you really need to regenerate,please ask TA for help.
EvalVisitor visitor;
auto main(int argc, const char* argv[]) -> i32 {
    //todo:please don't modify the code below the construction of ifs if you want to use visitor mode
    ANTLRInputStream input(std::cin);
    Python3Lexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    tokens.fill();
    Python3Parser parser(&tokens);
    tree::ParseTree* tree=parser.file_input();
    try {
        visitor.visit(tree);
    } catch (const std::invalid_argument &e) {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
