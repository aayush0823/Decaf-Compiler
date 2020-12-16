#ifndef LOCATION_DECLR_H
#define LOCATION_DECLR_H

#include <string>
#include <vector>

#include "NodeClassDeclaration.h"
#include "VisitorClassDeclaration.h"
#include "SuperNodeDeclaration.h"

// using namespace std;

class ASTLocation : public ASTnode
{
    public :
        std::string id;
        std::string type = "undefined";

        std::string getId(){
            return this->id;
        }

        std::string getType(){
            return this->type;
        }

    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();
};

class ASTVariableLoc : public ASTLocation
{
    public :

    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();
};

class ASTArray1DLoc : public ASTLocation
{
    public :
        ASTExpr* expr1;

    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();
};

class ASTArray2DLoc : public ASTLocation
{
    public :
        ASTExpr* expr1;
        ASTExpr* expr2;

    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();
};

#endif