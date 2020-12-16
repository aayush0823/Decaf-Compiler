#ifndef VISITOR_CLASS_H
#define VISITOR_CLASS_H

#include "NodeClassDeclaration.h"

class ASTvisitor
{
public:
    virtual void visit(ASTProgram &node) = 0;

    virtual void visit(ASTField &node) = 0;
    virtual void visit(ASTFieldVariable &node) = 0;
    virtual void visit(ASTField1DArray &node) = 0;
    virtual void visit(ASTField2DArray &node) = 0;

    virtual void visit(ASTMethod &node) = 0;
    virtual void visit(ASTMethodArgument &node) = 0;

    virtual void visit(ASTBlock &node) = 0;
    virtual void visit(ASTBlockContent &node) = 0;

    virtual void visit(ASTVariableDecl &node) = 0;

    virtual void visit(ASTIfCond &node) = 0;
    virtual void visit(ASTForLoop &node) = 0;
    virtual void visit(ASTWhileLoop &node) = 0;

    virtual void visit(ASTBreak &node) = 0;
    virtual void visit(ASTContinue &node) = 0;
    virtual void visit(ASTReturn &node) = 0;
    virtual void visit(ASTPrint &node) = 0;

    virtual void visit (ASTCall &node) = 0;
    virtual void visit (ASTMethodCall &node) = 0;
    virtual void visit (ASTCalloutCall &node) = 0;
    virtual void visit (ASTCalloutArg &node) = 0;
    // virtual void visit (ASTMethodParam &node) = 0;

    virtual void visit(ASTStatement &node) = 0;

    virtual void visit (ASTUnaryStat &node) = 0;
    virtual void visit (ASTMethodCallStat &node) = 0;
    virtual void visit (ASTIfStat &node) = 0;
    virtual void visit (ASTForStat &node) = 0;
    virtual void visit (ASTWhileStat &node) = 0;
    virtual void visit (ASTReturnStat &node) = 0;
    virtual void visit (ASTBreakStat &node) = 0;
    virtual void visit (ASTContinueStat &node) = 0;
    virtual void visit (ASTPrintStat &node) = 0;
    virtual void visit (ASTGetIntStat &node) = 0;
    virtual void visit (ASTGetCharStat &node) = 0;
    virtual void visit (ASTBlockStat &node) = 0;

    virtual void visit (ASTLocation &node) = 0;

    virtual void visit (ASTVariableLoc &node) = 0;
    virtual void visit (ASTArray1DLoc &node) = 0;
    virtual void visit (ASTArray2DLoc &node) = 0;

    virtual void visit (ASTExpr &node) = 0;

    virtual void visit (ASTLocationExpr &node) = 0;
    virtual void visit (ASTMethodCallExpr &node) = 0;
    virtual void visit (ASTReadLinesExpr &node) = 0;
    virtual void visit (ASTWriteLinesExpr &node) = 0;
    virtual void visit (ASTUnaryExpr &node) = 0;
    virtual void visit (ASTLiteralExpr &node) = 0;
    virtual void visit (ASTStringLiteralExpr &node) = 0;
    virtual void visit (ASTBinaryExpr &node) = 0;
    virtual void visit (ASTNegativeExpr &node) = 0;
    virtual void visit (ASTNegationExpr &node) = 0;
    virtual void visit (ASTParenthesisExpr &node) = 0;

    virtual void visit (ASTLiteral &node) = 0;
    virtual void visit (ASTBoolLiteral &node) = 0;
    virtual void visit (ASTIntLiteral &node) = 0;
    virtual void visit (ASTCharLiteral &node) = 0;

    virtual void visit (ASTBinaryOp &node) = 0;
    virtual void visit (ASTArithOp &node) = 0;
    virtual void visit (ASTRelOp &node) = 0;
    virtual void visit (ASTCondOp &node) = 0;
    virtual void visit (ASTEqOp &node) = 0;

    // virtual void visit(ASTStatExpr &node) = 0;
    // virtual void visit(ASTStatAssignExpr &node) = 0;

    // virtual void visit(ASTExprBinary &node) = 0;
    // virtual void visit(ASTExprTernary &node) = 0;
    // virtual void visit(ASTExprID &node) = 0;
    // virtual void visit(ASTExprINT &node) = 0;
    // virtual void visit(ASTExpr &node) = 0;
};

#endif