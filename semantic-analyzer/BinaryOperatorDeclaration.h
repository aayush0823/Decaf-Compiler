#ifndef BINARY_OP_CLASS_H
#define BINARY_OP_CLASS_H

#include "NodeClassDeclaration.h"
#include "VisitorClassDeclaration.h"
#include "SuperNodeDeclaration.h"

class ASTBinaryOp : public ASTnode
{
    public :
        std::string type;
        std::string op;

        std::string getType(){
            return this->type;
        }

        std::string getOp(){
            return this->op;
        }

    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();
};

class ASTArithOp : public ASTBinaryOp
{
    public :

    ASTArithOp()
    {
        this->type = "arith";
    }

    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();
};

class ASTRelOp : public ASTBinaryOp
{
    public :

    ASTRelOp()
    {
        this->type = "rel";
    }

    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();
};

class ASTCondOp : public ASTBinaryOp
{
    public :

    ASTCondOp()
    {
        this->type = "cond";
    }

    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();
};

class ASTEqOp : public ASTBinaryOp
{
    public :

    ASTEqOp()
    {
        this->type = "eq";
    }

    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();
};
#endif