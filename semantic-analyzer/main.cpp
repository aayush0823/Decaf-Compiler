#include <iostream>

#include "antlr4-runtime.h"
#include "ExprLexer.cpp"
#include "ExprParser.cpp"

#include "ExprBuildASTVisitor.h"
#include "CodeGenerator.h"

#include "PostfixVisitor.h"

#include "Record.h"
#include "Scope.h"
#include "SymbolTable.h"
//#include "ast.h"

using namespace std;
using namespace antlr4;

int main(int argc, const char* argv[]) {
    std::ifstream stream;

    cout << "Processing input file " << argv[1] << endl;
    stream.open(argv[1]);
    
    ANTLRInputStream input(stream);

    ExprLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    ExprParser parser(&tokens);    

    ExprParser::ProgramContext *ctx = parser.program();


    ExprBuildASTVisitor *ASTree = new ExprBuildASTVisitor();
    ExprVisitor *visitor = (ExprVisitor *) ASTree;
    
    ASTProgram *program_root = ASTree->visitProgram(ctx);
    
    int errorCount = ASTree->getErrorCount();

    if(errorCount == 0)
    {
        cout << "Compiled Successfully\n";
        program_root->codegen();
    } 
    else
    {
        cout << to_string(errorCount) + " Errors Found\n";
    }


    // PostFixVisitor *pv = new PostFixVisitor();
    // pv->visit(*program_root);
    

    // Record* record = new Record("var1", "char");
    // VariableRecord* varRec = new VariableRecord("hello", "int");
    // vector<VariableRecord*> varVec;

    // varVec.push_back(varRec);
    // // varVec.push_back(varRec);
    // MethodRecord* methodRec = new MethodRecord("func", "int");
    // methodRec->setParamList(varVec);
    // methodRec->setVariableList(varVec);

    // Scope* scope = new Scope(NULL);
    // scope->addRecord("var1", record);

    return 0;
}
