#ifndef AST_DEFS_H
#define AST_DEFS_H

#include <string>
#include <vector>
#include "BinaryOperatorDeclaration.h"
#include "LocationDeclaration.h"
#include "LiteralDeclaration.h"
#include "ExpressionDeclaration.h"
#include "StatementDeclaration.h"
#include "NodeClassDeclaration.h"
#include "VisitorClassDeclaration.h"
#include "SuperNodeDeclaration.h"
#include "LLVMlibraries.h"


using namespace std;
using namespace llvm;

class loopInfo {
    BasicBlock *afterBB, *checkBB;
    llvm::Value *condition;
    std::string loopVariable;
    PHINode *phiVariable;
public:
    loopInfo(BasicBlock *afterBlock, BasicBlock *checkBlock, Value *cond, std::string var, PHINode *phiVar) {
        afterBB = afterBlock;
        checkBB = checkBlock;
        condition = cond;
        loopVariable = var;
        phiVariable = phiVar;
    }

    BasicBlock *getAfterBlock() { return afterBB; }

    BasicBlock *getCheckBlock() { return checkBB; }

    llvm::Value *getCondition() { return condition; }

    PHINode *getPHINode() { return phiVariable; }

    std::string getLoopVariable() { return loopVariable; }
};


static LLVMContext Context;
static Module *TheModule = new Module("Mini C Compiler", Context); // Contains all functions and variables
static IRBuilder<> Builder(Context); // helps to generate LLVM IR with helper functions
static map <string, AllocaInst*>NamedValues; // keeps track of all the values defined in the current scope like a symbol table
static stack<loopInfo *> *loops = new stack<loopInfo*>();


AllocaInst *CreateEntryBlockAlloca(Function *TheFunction, string VarName, string type);
Value *reportError(string error_str);
string replace_newline(string str);

// class ASTnode
// {
// public:
//     virtual ~ASTnode()
//     {
//     }

//     //  virtual antlrcpp::Any printPostFix() const = 0;

//     virtual antlrcpp::Any accept(ASTvisitor &V) = 0;
// };

// class ASTStat : public ASTnode
// {
// public:
//     virtual ~ASTStat()
//     {
//     }

//     //  virtual antlrcpp::Any printPostFix() const = 0;

//     virtual antlrcpp::Any accept(ASTvisitor &V) = 0;
// };

class ASTProgram : public ASTnode
{
public:
    std::vector<ASTField *> fieldList;
    std::vector<ASTMethod *> methodList;

    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();
};

class ASTField : public ASTnode
{
public:

    //  virtual antlrcpp::Any printPostFix() const = 0;
    string id;
    string type;

    virtual antlrcpp::Any accept(ASTvisitor &v)
    {

        v.visit(*this);

        return this->type;
        // Datanode* node = new Datanode();
        // node->type = type;

        // return (Datanode*) node;
    }

    std::string getId(){
        return id;
    }

    std::string getType(){
        return type;
    }

    virtual llvm::Value *codegen();
    
};

class ASTFieldVariable : public ASTField
{
public:
    //  virtual antlrcpp::Any printPostFix() const = 0;

    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        
        return 0;
        // Datanode* node = new Datanode(this->id, this->type);
        // return (Datanode*) node;
    }

    virtual llvm::Value *codegen();
    
};

class ASTField1DArray : public ASTField
{
public:
    int size1D;
    //  virtual antlrcpp::Any printPostFix() const = 0;

    virtual antlrcpp::Any accept(ASTvisitor &v)
    {

        v.visit(*this);

        return 0;

        // Datanode* node = new Datanode(this->id, this->type);
        // return (Datanode*) node;
    }

    int getSize1D(){
        return size1D;
    }

    virtual llvm::Value *codegen();
    
};

class ASTField2DArray : public ASTField
{
public:
    int size1D;
    int size2D;

    //  virtual antlrcpp::Any printPostFix() const = 0;

    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);

        return 0;

        // Datanode* node = new Datanode(this->id, this->type);
        // return (Datanode*) node;
    }

    int getSize1D(){
        return size1D;
    }

    int getSize2D(){
        return size2D;
    }

    virtual llvm::Value *codegen();
    
};

class ASTMethod : public ASTnode
{
public:

    string id;
    string returnType;
    ASTBlock* block;
    std::vector<ASTMethodArgument *> methodArgumentList;

    //  virtual antlrcpp::Any printPostFix() const = 0;

    std::string getId(){
        return id;
    }

    std::string getReturnType(){
        return returnType;
    }

    std::vector<ASTMethodArgument *> getArguments(){
        return methodArgumentList;
    }

    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);

        return 0;
        // Datanode* node = new Datanode(this->id, this->returnType);
        // return (Datanode*) node;
    }

    virtual llvm::Value *codegen();
    
};

class ASTMethodArgument : public ASTnode
{
    public :
    string type;
    string id;

    ASTMethodArgument(string x, string y) { 
      this->type = x;
      this->id = y;
    }
    
    std::string getId(){
        return id;
    }

    std::string getType(){
        return type;
    }

    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        
        return 0;

        // Datanode* node = new Datanode(this->id, this->type);
        // return (Datanode*) node;
    }

    virtual llvm::Value *codegen();
    
};



class ASTBlockContent : public ASTnode
{

    public :
        ASTStatement* statementNode;
        ASTVariableDecl* variableNode;

    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();
    
};

class ASTVariableDecl : public ASTnode
{
    public :
        string type;
        vector<string> idList; 
    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }


    virtual llvm::Value* codegen()
    {
        return nullptr;
    }    

    llvm::Value *codegen(map<string, AllocaInst *> &initial_vals);
    
};

class ASTCall : public ASTnode
{
public:
    string methodName;
    string type;

    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    std::string getId(){
        return methodName;
    }

    std::string getType(){
        return type;
    }
    
    virtual llvm::Value *codegen();
    
};


class ASTMethodCall : public ASTCall
{
public:

    
    std::vector<ASTExpr *> paramExprList;

    //  virtual antlrcpp::Any printPostFix() const = 0;

    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();
    
};

class ASTCalloutCall : public ASTCall
{
public:

    std::vector<ASTCalloutArg *> paramList;

    //  virtual antlrcpp::Any printPostFix() const = 0;

    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();
    
};

class ASTCalloutArg : public ASTnode
{
public:

    ASTExpr* expr;
    string argument;

    //  virtual antlrcpp::Any printPostFix() const = 0;

    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();
    
};

// class ASTMethodParam : public ASTnode
// {
// public:

//     ASTExpr *expr;

//     //  virtual antlrcpp::Any printPostFix() const = 0;

//     virtual antlrcpp::Any accept(ASTvisitor &v)
//     {
//         v.visit(*this);
//     }
// };

class ASTIfCond : public ASTnode
{
public:

    ASTExpr* expr;
    ASTBlock* block1;
    ASTBlock* block2;

    //  virtual antlrcpp::Any printPostFix() const = 0;

    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();
    
};

class ASTForLoop : public ASTnode
{
public:

    string iterator;
    ASTExpr* expr1;
    ASTExpr* expr2;
    ASTExpr* expr3;
    ASTBlock* block;

    //  virtual antlrcpp::Any printPostFix() const = 0;

    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();
    
};

class ASTWhileLoop : public ASTnode
{
public:

    ASTExpr* expr;
    ASTBlock* block;

    //  virtual antlrcpp::Any printPostFix() const = 0;

    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();
    
};

class ASTBreak : public ASTnode
{
public:


    //  virtual antlrcpp::Any printPostFix() const = 0;

    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();
    
};

class ASTContinue : public ASTnode
{
public:


    //  virtual antlrcpp::Any printPostFix() const = 0;

    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();
    
};

class ASTReturn : public ASTnode
{
public:

    ASTExpr* expr;
    //  virtual antlrcpp::Any printPostFix() const = 0;

    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();
    
};

class ASTPrint : public ASTnode
{
public:

    vector<ASTExpr*> exprList;
    //  virtual antlrcpp::Any printPostFix() const = 0;

    virtual antlrcpp::Any accept(ASTvisitor &v)
    {
        v.visit(*this);
        return 0;
    }

    virtual llvm::Value *codegen();
    
};

#endif


// class ASTExpr : public ASTnode
// {
// public:
//     virtual antlrcpp::Any accept(ASTvisitor &v)
//     {
//         v.visit(*this);
//     }
// };

// class ASTStatExpr : public ASTStat
// {
// public:
//     ASTExpr *expr;
//     virtual antlrcpp::Any accept(ASTvisitor &v)
//     {
//         v.visit(*this);
//     }
// };

// class ASTStatAssignExpr : public ASTStat
// {
// public:
//     string id;
//     ASTExpr *expr;
//     virtual antlrcpp::Any accept(ASTvisitor &v)
//     {
//         v.visit(*this);
//     }
// };

// class ASTExprBinary : public ASTExpr
// {
//     std::string bin_operator;

//     // lhs and rhs can be of any type.
//     // So we need to use BaseAST
//     ASTExpr *left;
//     ASTExpr *right;

// public:
//     // Constructor to initialize binary operator,
//     // lhs and rhs of the binary expression.
//     ASTExprBinary(std::string op, ASTExpr *_left, ASTExpr *_right) : bin_operator(op), left(_left), right(_right) {}

//     /*  virtual antlrcpp::Any printPostFix() const 
//      {
//      	lhs->printPostFix();
//      	rhs->printPostFix();
//      	std::cout << bin_operator << " "; 
//      } */

//     ASTExpr *getLeft()
//     {
//         return left;
//     }

//     ASTExpr *getRight()
//     {
//         return right;
//     }

//     std::string getBin_operator()
//     {
//         return bin_operator;
//     }
//     virtual antlrcpp::Any accept(ASTvisitor &v)
//     {
//         v.visit(*this);
//     }
// };

// class ASTExprTernary : public ASTExpr
// {

//     ASTExpr *first;
//     ASTExpr *second;
//     ASTExpr *third;

// public:
//     ASTExprTernary(ASTExpr *first, ASTExpr *second, ASTExpr *third) : first(first), second(second), third(third) {}

//     /*   virtual antlrcpp::Any printPostFix() const
//      {
//      	first->printPostFix();
//      	second->printPostFix();
//      	third->printPostFix();
//      	std::cout << "? " << std::endl; 
//      }  */

//     ASTExpr *getFirst()
//     {
//         return first;
//     }

//     ASTExpr *getSecond()
//     {
//         return second;
//     }

//     ASTExpr *getThird()
//     {
//         return third;
//     }

//     virtual antlrcpp::Any accept(ASTvisitor &v)
//     {
//         v.visit(*this);
//     }
// };

// class ASTExprINT : public ASTExpr
// {

//     int intlit;

// public:
//     ASTExprINT(int intlit) : intlit(intlit) {}

//     int getIntLit()
//     {
//         return intlit;
//     }

//     virtual antlrcpp::Any accept(ASTvisitor &v)
//     {
//         v.visit(*this);
//     }

//     /* virtual antlrcpp::Any printPostFix() const
// 	{
// 		std::cout << intlit << " " ;
// 	} */
// };

// class ASTExprID : public ASTExpr
// {

//     string id;

// public:
//     ASTExprID(string id) : id(id) {}

//     string getID()
//     {
//         return id;
//     }

//     virtual antlrcpp::Any accept(ASTvisitor &v)
//     {
//         v.visit(*this);
//     }

//     /* virtual antlrcpp::Any printPostFix() const
// 	{
// 		std::cout << intlit << " " ;
// 	} */
// };

// class ASTContext
// {
// public:
//     ASTnode *root;

//     ~ASTContext()
//     {
//         clearAST();
//     }

//     /// free all saved expression trees
//     void clearAST()
//     {
//         delete root;
//     }
// };

