#ifndef STAT_DECLR_H
#define STAT_DECLR_H

#include <string>
#include <vector>

#include "NodeClassDeclaration.h"
#include "VisitorClassDeclaration.h"
#include "SuperNodeDeclaration.h"

using namespace std;

enum class StatementType {
    SIMPLE,
    BREAK,		
    CONTINUE,
    RETURN		
};

class ASTStatement : public ASTBlock
{
    public :
        StatementType sType = StatementType::SIMPLE;

    StatementType getStatementType(){
        return sType;
    }

    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();

};

class ASTAssignStat : public ASTStatement
{
    public :
        ASTLocation* location;
        string assign_op;
        ASTExpr* expr;
    
    string getOp(){
        return assign_op;
    }
    
    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();

};

class ASTUnaryStat : public ASTStatement
{
    public :
        ASTLocation* location;
        string unary_op;

    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();

};

class ASTMethodCallStat : public ASTStatement
{
    public :
        ASTCall* methodCall;

    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();

};

class ASTIfStat : public ASTStatement
{
    public :
        ASTIfCond* ifCond;

    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();

};

class ASTForStat : public ASTStatement
{
    public :
        ASTForLoop* forLoop;

    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();

};

class ASTWhileStat : public ASTStatement
{
    public :
        ASTWhileLoop* whileLoop;

    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();

};

class ASTReturnStat : public ASTStatement
{
    public :
        ASTReturn* returnNode;
    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();

};

class ASTBreakStat : public ASTStatement
{
    public :
        ASTBreak* breakNode;

    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();

};

class ASTContinueStat : public ASTStatement
{
    public :
        ASTContinue* continueNode;

    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();

};

class ASTGetIntStat : public ASTStatement
{
    public :
    
    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();
};

class ASTGetCharStat : public ASTStatement
{
    public :
    
    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();
};

class ASTPrintStat : public ASTStatement
{
    public :
        ASTPrint* printNode;
    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();

};

class ASTBlockStat : public ASTStatement
{
    public :
        ASTBlock* block;
    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();

};

#endif