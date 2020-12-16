#ifndef LITERAL_DECLR_H
#define LITERAL_DECLR_H

#include <string>
#include <vector>

#include "NodeClassDeclaration.h"
#include "VisitorClassDeclaration.h"
#include "SuperNodeDeclaration.h"

using namespace std;

class ASTLiteral : public ASTnode
{

    public :
        string type;

    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();
};

class ASTBoolLiteral : public ASTLiteral
{

    public :
        bool literal;

        ASTBoolLiteral()
        {
            this->type = "bool";
        }

    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();
};

class ASTIntLiteral : public ASTLiteral
{

    public :
        int literal;
        ASTIntLiteral()
        {
            this->type = "int";
        }

    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();
};

class ASTCharLiteral : public ASTLiteral
{

    public :
        string literal;
        ASTCharLiteral()
        {
            this->type = "char";
        }
    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();
};

#endif