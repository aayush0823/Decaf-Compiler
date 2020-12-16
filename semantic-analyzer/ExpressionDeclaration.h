#ifndef EXPR_DECLR_H
#define EXPR_DECLR_H

#include <string>
#include <vector>

#include "NodeClassDeclaration.h"
#include "VisitorClassDeclaration.h"
#include "SuperNodeDeclaration.h"

// using namespace std;

class ASTExpr : public ASTnode
{
    public :
        std::string type;
        std::string exprType = "";

        std::string getType(){
            return this->type;
        }

        std::string getExprType(){
            return this->exprType;
        }
        
    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();
};

class ASTLocationExpr : public ASTExpr
{
    public :
        ASTLocation* location;

    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();
};

class ASTMethodCallExpr : public ASTExpr
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

class ASTReadLinesExpr : public ASTExpr
{
    public :
        std::string filename;

    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();
};

class ASTWriteLinesExpr : public ASTExpr
{
    public :
        std::string filename;
        std::string dataLocation;
        std::string filemode;
    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();
};

class ASTUnaryExpr : public ASTExpr
{
    public :
        std::string unaryOp;
        ASTLocation* location;

    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();
};

class ASTLiteralExpr : public ASTExpr
{
    public :
        ASTLiteral* literal;
    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();
};

class ASTStringLiteralExpr : public ASTExpr
{
    public :
        std::string literal;
    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();
};

class ASTBinaryExpr : public ASTExpr
{
    public :
        ASTExpr* expr1;
        ASTExpr* expr2;
        ASTBinaryOp* binaryOp;

    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();
};

class ASTNegativeExpr : public ASTExpr
{
    public :
        ASTExpr* expr;

    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();
};

class ASTNegationExpr : public ASTExpr
{
    public :
        ASTExpr* expr;
    
    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();
};

class ASTParenthesisExpr : public ASTExpr
{
    public :
        ASTExpr* expr;
    
    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();
};

#endif