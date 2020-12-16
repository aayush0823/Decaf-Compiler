//#include "ast.h"
#include <iostream>

#include "SuperNodeDeclaration.h"
#include "SymbolTable.h"
#include "Logger.h"

using namespace std;

class PostFixVisitor : public ASTvisitor
{
public:
    SymbolTable* symbolTable = new SymbolTable();
    int errorCount = 0;
    Logger* logger = new Logger();

    int getErrorCount(){
        return this->errorCount;
    }

    virtual void visit(ASTProgram &node)
    {
        logger->writeDebug("PostFixVisit visit function");

        // for (auto field : node.fieldList)
        // {

        //     Datanode* data = field->accept(*this);               
        // }

        // for (auto method : node.methodList)
        // {
        //     Datanode* data = method->accept(*this);
        // }
    };

    virtual void visit(ASTField &node)
    {
        logger->writeDebug("ASTField visit function");

    };

    virtual void visit(ASTFieldVariable &node)
    {
        logger->writeDebug("ASTFieldVariable visit function");

        // cout << node.getType() << " ";
        // cout << node.getId() << endl;
    };

    virtual void visit(ASTField1DArray &node)
    {
        logger->writeDebug("ASTField1DArray visit function");

        // cout << node.getType() << " ";
        // cout << node.getId() << " ";
        // cout << node.getSize1D() << endl;
    };

    virtual void visit(ASTField2DArray &node)
    {
        logger->writeDebug("ASTField2DArray visit function");

        // cout << node.getType() << " ";
        // cout << node.getId() << " ";
        // cout << node.getSize1D() << " ";
        // cout << node.getSize2D() << endl;

    };

    virtual void visit(ASTMethod &node)
    {
        logger->writeDebug("ASTMethod visit function");

        // cout << node.returnType << " ";
        // cout << node.id << endl;

        // for (auto argument : node.methodArgumentList)
        // {
        //     argument->accept(*this);
        // }

        // node.block->accept(*this);
    };

    virtual void visit(ASTBlock &node)
    {
        logger->writeDebug("ASTBlock visit function");

        // for(auto statement : node.statementList){
        //     statement->accept(*this);
        // }

        // for(auto variable : node.variableList){
        //     variable->accept(*this);
        // }
    };

    virtual void visit(ASTMethodArgument &node)
    {
        logger->writeDebug("ASTMethodArgument visit function");

        // cout << node.type << " ";
        // cout << node.id << endl;
    };

    virtual void visit(ASTBlockContent &node)
    {
        logger->writeDebug("ASTBlockContent visit function");

    };

    virtual void visit(ASTVariableDecl &node)
    {

        logger->writeDebug("ASTVariableDecl visit function");

        // cout << node.type << " ";

        // for (auto identifier : node.idList){
        //     cout << identifier << " ";    
        // }

        // cout << endl;
    };

    virtual void visit(ASTIfCond &node)
    {
        logger->writeDebug("ASTIfCond visit function");

    };

    virtual void visit(ASTForLoop &node)
    {
        logger->writeDebug("ASTForLoop visit function");

    };

    virtual void visit(ASTWhileLoop &node)
    {
        logger->writeDebug("ASTWhileLoop visit function");

    };

    virtual void visit(ASTBreak &node)
    {
        logger->writeDebug("ASTBreak visit function");

    };

    virtual void visit(ASTContinue &node)
    {
        logger->writeDebug("ASTContinue visit function");

    };

    virtual void visit(ASTReturn &node)
    {
        logger->writeDebug("ASTReturn visit function");

    };

    virtual void visit(ASTPrint &node)
    {
        logger->writeDebug("ASTPrint visit function");

    };

    virtual void visit(ASTStatement &node)
    {
        logger->writeDebug("ASTStatement visit function");
        
    };

    virtual void visit (ASTCall &node)
    {
        logger->writeDebug("ASTCall visit function");

    };

    virtual void visit (ASTMethodCall &node)
    {
        logger->writeDebug("ASTMethodCall visit function");

    };

    virtual void visit (ASTCalloutCall &node){
        logger->writeDebug("ASTCalloutCall visit function");

    };

    virtual void visit (ASTCalloutArg &node){
        logger->writeDebug("ASTCalloutArg visit function");

    };


    // virtual void visit (ASTMethodParam &node){


    // };  
      
    virtual void visit (ASTUnaryStat &node)
    {   
        logger->writeDebug("ASTUnaryStat visit function");

    };  

    virtual void visit (ASTMethodCallStat &node)
    {
        logger->writeDebug("ASTMethodCallStat visit function");

    };

    virtual void visit (ASTIfStat &node)
    {
        logger->writeDebug("ASTIfStat visit function");

    };

    virtual void visit (ASTForStat &node)
    {
        logger->writeDebug("ASTForStat visit function");

    };

    virtual void visit (ASTWhileStat &node)
    {
        logger->writeDebug("ASTWhileStat visit function");

    };

    virtual void visit (ASTReturnStat &node)
    {
        logger->writeDebug("ASTReturnStat visit function");

    };

    virtual void visit (ASTBreakStat &node)
    {
        logger->writeDebug("ASTBreakStat visit function");

    };

    virtual void visit (ASTContinueStat &node)
    {
        logger->writeDebug("ASTContinueStat visit function");

    };

    virtual void visit (ASTPrintStat &node)
    {
        logger->writeDebug("ASTPrintStat visit function");

    };

    virtual void visit (ASTGetIntStat &node)
    {
        logger->writeDebug("ASTGetIntStat visit function");

    };

    virtual void visit (ASTGetCharStat &node)
    {
        logger->writeDebug("ASTGetCharStat visit function");

    };

    virtual void visit (ASTBlockStat &node)
    {
        logger->writeDebug("ASTBlockStat visit function");

    };
    
    virtual void visit (ASTExpr &node)
    {
        logger->writeDebug("ASTExpr visit function");

    };

    virtual void visit (ASTLocationExpr &node)
    {
        logger->writeDebug("ASTLocationExpr visit function");

    };

    virtual void visit (ASTMethodCallExpr &node)
    {
        logger->writeDebug("ASTMethodCallExpr visit function");

    };

    virtual void visit (ASTReadLinesExpr &node)
    {
        logger->writeDebug("ASTReadLinesExpr visit function");

    };

    virtual void visit (ASTWriteLinesExpr &node)
    {
        logger->writeDebug("ASTWriteLinesExpr visit function");

    };

    virtual void visit (ASTUnaryExpr &node)
    {
        logger->writeDebug("ASTUnaryExpr visit function");

    };

    virtual void visit (ASTLiteralExpr &node)
    {
        logger->writeDebug("ASTLiteralExpr visit function");

    };

    virtual void visit (ASTStringLiteralExpr &node)
    {
        logger->writeDebug("ASTStringLiteralExpr visit function");

    };

    virtual void visit (ASTBinaryExpr &node)
    {
        logger->writeDebug("ASTBinaryExpr visit function");

    };

    virtual void visit (ASTNegativeExpr &node)
    {
        logger->writeDebug("ASTNegativeExpr visit function");

    };

    virtual void visit (ASTNegationExpr &node)
    {
        logger->writeDebug("ASTNegationExpr visit function");

    };

    virtual void visit (ASTParenthesisExpr &node)
    {
        logger->writeDebug("ASTParenthesisExpr visit function");

    };

    virtual void visit (ASTLocation &node)
    {
        logger->writeDebug("ASTLocation visit function");

    };

    virtual void visit (ASTVariableLoc &node)
    {
        logger->writeDebug("ASTVariableLoc visit function");

    };

    virtual void visit (ASTArray1DLoc &node)
    {
        logger->writeDebug("ASTArray1DLoc visit function");

    };

    virtual void visit (ASTArray2DLoc &node)
    {
        logger->writeDebug("ASTArray2DLoc visit function");

    };

    virtual void visit (ASTLiteral &node)
    {
        logger->writeDebug("ASTLiteral visit function");

    };
    
    virtual void visit (ASTBoolLiteral &node)
    {
        logger->writeDebug("ASTBoolLiteral visit function");

    };
    
    virtual void visit (ASTIntLiteral &node)
    {
        logger->writeDebug("ASTIntLiteral visit function");

    };
    
    virtual void visit (ASTCharLiteral &node)
    {
        logger->writeDebug("ASTCharLiteral visit function");

    };

    virtual void visit (ASTBinaryOp &node)
    {
        logger->writeDebug("ASTBinaryOp visit function");

    };

    virtual void visit (ASTArithOp &node)
    {
        logger->writeDebug("ASTArithOp visit function");

    };

    virtual void visit (ASTRelOp &node)
    {
        logger->writeDebug("ASTRelOp visit function");

    };

    virtual void visit (ASTCondOp &node)
    {
        logger->writeDebug("ASTCondOp visit function");

    };

    virtual void visit (ASTEqOp &node)
    {
        logger->writeDebug("ASTEqOp visit function");

    };

    



    // virtual void visit(ASTStatExpr &node)
    // {
    //     node.expr->accept(*this);
    // }

    // virtual void visit(ASTStatAssignExpr &node)
    // {
    //     cout << node.id;
    //     node.expr->accept(*this);
    //     cout << " =";
    // }

    // virtual void visit(ASTExpr &node)
    // {
    //     cout << "ASTExpr visit function" << endl;
    // }

    // virtual void visit(ASTExprBinary &node)
    // {
    //     ASTExpr *left = node.getLeft();
    //     ASTExpr *right = node.getRight();

    //     left->accept(*this);
    //     right->accept(*this);
    //     cout << " " + node.getBin_operator();
    // }

    // virtual void visit(ASTExprTernary &node)
    // {
    //     ASTExpr *first = node.getFirst();
    //     ASTExpr *second = node.getSecond();
    //     ASTExpr *third = node.getThird();

    //     first->accept(*this);
    //     second->accept(*this);
    //     third->accept(*this);

    //     // visit(node.getFirst());
    //     // visit(node.getSecond());
    //     // visit(node.getThird());
    //     cout << " ?:";
    // }

    // virtual void visit(ASTExprID &node)
    // {
    //     cout << " " << node.getID();
    // }

    // virtual void visit(ASTExprINT &node)
    // {
    //     cout << " " << node.getIntLit();
    // }
};