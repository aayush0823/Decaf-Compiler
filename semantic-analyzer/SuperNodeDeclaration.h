#ifndef SUPER_NODE_CLASS_H
#define SUPER_NODE_CLASS_H

#include "LLVMlibraries.h"

class ASTnode
{
public:
    virtual ~ASTnode()
    {
    }

    //  virtual void printPostFix() const = 0;

    virtual llvm::Value *codegen() = 0;

    virtual antlrcpp::Any accept(ASTvisitor &V) = 0;
};

class Datanode
{
    public:
        std::string id;
        std::string type;

        Datanode(std::string id, std::string type){
            this->id = id;
            this->type = type;
        }

        std::string getId(){
            return this->id;
        }

        std::string getType(){
            return this->type;
        }
};

class ASTBlock : public ASTnode
{
    public :
        std::vector<ASTnode *> blockContentList;
        std::vector<ASTStatement *> statementList;
        std::vector<ASTVariableDecl *> variableList;

        bool hasReturn;
        bool hasContinue;
        bool hasBreak;

    std::vector<ASTStatement *> getStatementList(){
        return statementList;
    }

    std::vector<ASTVariableDecl *> getVariableList(){
        return variableList;
    }

    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();

};

#endif