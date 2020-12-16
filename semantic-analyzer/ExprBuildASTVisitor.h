#include <iostream>
#include <typeinfo>
#include <vector>

#include "ast.h"

#include "ExprVisitor.h"
#include "Logger.h"
#include "LogDefinitions.h"
#include "Record.h"
#include "SymbolTable.h"

using namespace std;

class ExprBuildASTVisitor : public ExprVisitor
{
public:
    /**
   * Visit parse trees produced by ExprParser.
   */
    SymbolTable* symbolTable = new SymbolTable();
    MethodRecord* currMethod = NULL;
    Logger* logger = new Logger();

    bool errorFlag;
    int errorCount;

    bool getErrorFlag(){
        return this->errorFlag;
    }

    void increaseErrorCount(){
        this->errorCount++;
    }

    int getErrorCount(){
        return this->errorCount;
    }

    virtual antlrcpp::Any visitProgram(ExprParser::ProgramContext *context)
    {
        logger->writeDebug("In visitProgram");
        ASTProgram *node = new ASTProgram();

        ASTField *fieldNode;
        ASTMethod *methodNode;

        for (auto field : context->field_declr())
        {
            fieldNode = visit(field);
            if (fieldNode != nullptr)
            {
                node->fieldList.push_back(fieldNode);
            }
        }

        for (auto method : context->method_declr())
        {
            methodNode = visit(method);
            if (methodNode != nullptr)
            {
                node->methodList.push_back(methodNode);
            }
        }

        return (ASTProgram *) node;
    }

    virtual antlrcpp::Any visitFieldVariable(ExprParser::FieldVariableContext *context)
    {
        logger->writeDebug("In visitFieldVariable");
        ASTFieldVariable *node = new ASTFieldVariable();

        node->id = context->id()->getText();
        node->type = context->type()->getText();

        VariableRecord* variable = new VariableRecord(node->id, node->type);
        
        this->symbolTable->addRecord(node->id, variable);
        // cout << this->symbolTable->lookup(node->id)->getId() << "TESTING";

        return (ASTField *) node;
    }
    
    virtual antlrcpp::Any visitField1DArray(ExprParser::Field1DArrayContext *context) 
    {
        logger->writeDebug("In visitField1DArray");
        ASTField1DArray *node = new ASTField1DArray();

        node->id = context->id()->getText();
        node->type = context->type()->getText();
        node->size1D = stoi(context->int_literal()->getText());

        VariableRecord* variable = new VariableRecord(node->id, node->type);
        
        this->symbolTable->addRecord(node->id, variable);
        // cout << this->symbolTable->lookup(node->id)->getId() << "TESTING";
        // cout << node->id << endl;
        // cout << node->type << endl;
        // cout << node->size1D << endl;

        return (ASTField *) node;    
    };

    virtual antlrcpp::Any visitField2DArray(ExprParser::Field2DArrayContext *context) 
    {
        logger->writeDebug("In visitField2DArray");
        ASTField2DArray *node = new ASTField2DArray();

        node->id = context->id()->getText();
        node->type = context->type()->getText();
        node->size1D = stoi(context->int_literal()[0]->getText());
        node->size2D = stoi(context->int_literal()[1]->getText());

        VariableRecord* variable = new VariableRecord(node->id, node->type);
        
        this->symbolTable->addRecord(node->id, variable);
        // this->symbolTable->printTable();

        // cout << node->id << endl;
        // cout << node->type << endl;
        // cout << node->size1D << endl;
        // cout << node->size2D << endl;
        return (ASTField *) node;    
    };

    virtual antlrcpp::Any visitMethod_declr(ExprParser::Method_declrContext *context)
    {
        logger->writeDebug("In visitMethod_declr");
        ASTMethod *node = new ASTMethod();

        string methodName = context->id()->getText(); 
        string returnType = context->func_type()->getText(); 

        node->id = methodName;
        node->returnType = returnType;
        
        currMethod = new MethodRecord(methodName, returnType);

        // this->symbolTable->printTable();

        // cout << this->symbolTable->lookup(node->id) << endl;

        if (this->symbolTable->lookup(node->id) != NULL)
        {
            this->errorFlag = true;
            logger->writeDuplicate(IdType::TYPE_FUNC, (ParserRuleContext *)context, node->id);
            this->increaseErrorCount();

            // cout << "[DUPLICATE] METHOD NAME: " + node->id + " already defined.\n";
        } 
        else 
        {

            this->symbolTable->addRecord(node->id, currMethod);
            
            this->symbolTable->enterScope();
        
            ASTMethodArgument* methodArgumentNode;

            if (context->arguments() != NULL)
            {
                for(int i=0; i<context->arguments()->type().size(); i++){

                    string argName = context->arguments()->id()[i]->getText();
                    string argType = context->arguments()->type()[i]->getText();

               		VariableRecord* var = new VariableRecord(argName, argType);

                    if (this->symbolTable->lookup(argName) != NULL) {
                        this->errorFlag = true;
                        logger->writeDuplicate(IdType::TYPE_PARAM, (ParserRuleContext *)context, argName, methodName);
                        this->increaseErrorCount();

                    } else {
                        this->symbolTable->addRecord(argName, var);
                        currMethod->addParam(var);
                    }

                    methodArgumentNode = new ASTMethodArgument(argType, argName);
                   
                    // cout << context->arguments()->type()[i]->getText() << " " << context->arguments()->id()[i]->getText() << endl;
                    node->methodArgumentList.push_back(methodArgumentNode);
                }

            }
            
            node->block = visit(context->block());

            this->symbolTable->exitScope();
        }

        return (ASTMethod *) node;
    }

    virtual antlrcpp::Any visitArguments(ExprParser::ArgumentsContext *context) 
    {   

        return 0;
    };

    virtual antlrcpp::Any visitType(ExprParser::TypeContext *context) 
    {
        return 0;
    };

    virtual antlrcpp::Any visitFunc_type(ExprParser::Func_typeContext *context) 
    {
        return 0;    
    };

    virtual antlrcpp::Any visitBlock(ExprParser::BlockContext *context) 
    {
        logger->writeDebug("In visitBlock");
        ASTBlock *block = new ASTBlock();

        ASTBlockContent *contentNode;

        for (auto content : context->block_content())
        {

            contentNode = visit(content);

            if (contentNode != nullptr)
            {
                block->blockContentList.push_back(contentNode);

                if(contentNode->statementNode != NULL){

                    if(contentNode->statementNode->sType == StatementType::RETURN){
                        // cout << "Return Found\n";

                        block->hasReturn = true;
                    }

                    if(contentNode->statementNode->sType == StatementType::CONTINUE){
                        // cout << "Continue Found\n";

                        block->hasContinue = true;
                    }

                    if(contentNode->statementNode->sType == StatementType::BREAK){
                        // cout << "Break Found\n";
                        block->hasBreak = true;
                    }

                    block->statementList.push_back(contentNode->statementNode);
                }

                if(contentNode->variableNode != NULL){
                    block->variableList.push_back(contentNode->variableNode);
                }
            }
        }

        return (ASTBlock *) block;        
    
    };

    virtual antlrcpp::Any visitBlock_content(ExprParser::Block_contentContext *context) 
    {
        logger->writeDebug("In visitBlock_content");

        ASTBlockContent* blockContentNode = new ASTBlockContent();


        if (context->var_declr() != NULL){

            ASTVariableDecl* variableNode = new ASTVariableDecl();
            variableNode = visit(context->var_declr());
            blockContentNode->variableNode = variableNode;
        
        } else if (context->statement() != NULL){
            ASTStatement* statementNode = new ASTStatement();
            statementNode = visit(context->statement());
            blockContentNode->statementNode = statementNode;
        }    

        return (ASTBlockContent *) blockContentNode;

    };

    virtual antlrcpp::Any visitVar_declr(ExprParser::Var_declrContext *context) 
    {
        logger->writeDebug("In visitVar_declr");

        ASTVariableDecl* variableNode = new ASTVariableDecl();

        string varType = context->type()->getText();
        variableNode->type = varType;
        
        for(auto identifier : context->id()){

            string varName = identifier->getText();

            // if (this->symbolTable->lookup(varName) != NULL){
            //     this->errorFlag = true;
            //     logger->writeDuplicate(IdType::TYPE_VAR, (ParserRuleContext *)context, varName);            
            //     this->increaseErrorCount();
            // }

            variableNode->idList.push_back(varName);

            VariableRecord* variable = new VariableRecord(varName, varType);
            this->symbolTable->addRecord(varName, variable);

        }

        return (ASTVariableDecl *) variableNode;    
    
    };

    virtual antlrcpp::Any visitStatement(ExprParser::StatementContext *context) 
    {
        logger->writeDebug("In visitStatement");
        ASTStatement* statementNode = new ASTStatement();

        return (ASTStatement *) statementNode;    
    };

    virtual antlrcpp::Any visitAssignStat(ExprParser::AssignStatContext *context)
    {
        logger->writeDebug("In visitAssignStat");
        ASTAssignStat* node = new ASTAssignStat();

        node->location = visit(context->location());
        node->assign_op = context->assign_op()->getText();
        node->expr = visit(context->expr());

        if(node->location->getType() != node->expr->getType())
        {
            logger->writeInvalidAssignment(context, node->location->getType(), node->expr->getType());
            this->increaseErrorCount();

        } 
        else if (node->assign_op != "=" and node->location->getType() != "int")
        {
            logger->writeInvalidAssignmentInt(node->assign_op, context, node->location->getType(), node->expr->getType());
            this->increaseErrorCount();

        }

        return (ASTStatement *) node;
    };

    virtual antlrcpp::Any visitUnaryStat(ExprParser::UnaryStatContext *context)
    {
        logger->writeDebug("In visitUnaryStat");

        ASTUnaryStat* node = new ASTUnaryStat();
        node->location = visit(context->location());
        node->unary_op = context->unary_op()->getText();

        return (ASTStatement *) node;
    };

    virtual antlrcpp::Any visitMethodCallStat(ExprParser::MethodCallStatContext *context)
    {
        logger->writeDebug("In visitMethodCallStat");

        ASTMethodCallStat* node = new ASTMethodCallStat();

        node->methodCall = visit(context->method_call());
        return (ASTStatement *) node;
    };

    virtual antlrcpp::Any visitIfStat(ExprParser::IfStatContext *context)
    {
        logger->writeDebug("In visitIfStat");

        ASTIfStat* node = new ASTIfStat();

        node->ifCond = visit(context->if_statement());
        return (ASTStatement *) node;
    };

    virtual antlrcpp::Any visitForStat(ExprParser::ForStatContext *context)
    {
        logger->writeDebug("In visitForStat");

        ASTForStat* node = new ASTForStat();
        node->forLoop = visit(context->for_statement());

        return (ASTStatement *) node;
    };

    virtual antlrcpp::Any visitWhileStat(ExprParser::WhileStatContext *context)
    {
        logger->writeDebug("In visitWhileStat");

        ASTWhileStat* node = new ASTWhileStat();
        node->whileLoop = visit(context->while_statement());

        return (ASTStatement *) node;
    };

    virtual antlrcpp::Any visitReturnStat(ExprParser::ReturnStatContext *context)
    {
        logger->writeDebug("In visitReturnStat");

        ASTReturnStat* node = new ASTReturnStat();
        node->returnNode = visit(context->ret_rule());
        node->sType = StatementType::RETURN;
        
        return (ASTStatement *) node;
    };

    virtual antlrcpp::Any visitBreakStat(ExprParser::BreakStatContext *context)
    {
        logger->writeDebug("In visitBreakStat");

        ASTBreakStat* node = new ASTBreakStat();
        node->breakNode = new ASTBreak();
        node->sType = StatementType::BREAK;
        
        return (ASTStatement *) node;
    };

    virtual antlrcpp::Any visitContinueStat(ExprParser::ContinueStatContext *context)
    {
        logger->writeDebug("In visitContinueStat");

        ASTContinueStat* node = new ASTContinueStat();
        node->continueNode = new ASTContinue();
        node->sType = StatementType::CONTINUE;

        return (ASTStatement *) node;
    };

    virtual antlrcpp::Any visitPrintStat(ExprParser::PrintStatContext *context)
    {
        logger->writeDebug("In visitPrintStat");

        ASTPrintStat* node = new ASTPrintStat();
        node->printNode = visit(context->print());

        return (ASTStatement *) node;
    };

    virtual antlrcpp::Any visitBlockStat(ExprParser::BlockStatContext *context)
    {
        logger->writeDebug("In visitBlockStat");

        ASTBlockStat* node = new ASTBlockStat();
        node->block = visit(context->block());
        
        return (ASTStatement *) node;
    };

    virtual antlrcpp::Any visitIf_statement(ExprParser::If_statementContext *context) 
    {
        logger->writeDebug("In visitIf_statement");

        ASTIfCond *node = new ASTIfCond();

        this->symbolTable->enterScope();

        node->expr = visit(context->expr());

        if (node->expr->getType() != "bool")
        {
            logger->writeInvalidIfCond(node->expr->getType(), context);
            this->increaseErrorCount();

        }

        if(context->block().size() == 1){
            node->block1 = visit(context->block()[0]);
            node->block2 = NULL;
        } else {
            node->block1 = visit(context->block()[0]);
            node->block2 = visit(context->block()[1]);
        }

        this->symbolTable->exitScope();

        return (ASTIfCond *) node;    
    };

    virtual antlrcpp::Any visitFor_statement(ExprParser::For_statementContext *context){
        logger->writeDebug("In visitFor_statement");

        ASTForLoop *node = new ASTForLoop();

        // this->symbolTable->printTable();
        this->symbolTable->enterScope();

        node->iterator = context->id()->getText();

        // cout << node->iterator << "\n";

        node->block = visit(context->block());

        if(context->expr().size() == 3){
            node->expr1 = visit(context->expr()[0]);
            node->expr2 = visit(context->expr()[1]);
            node->expr3 = visit(context->expr()[2]);
        } else {
            node->expr1 = visit(context->expr()[0]);
            node->expr2 = visit(context->expr()[1]);
        }

        this->symbolTable->exitScope();

        return (ASTForLoop *) node;
    };

    virtual antlrcpp::Any visitWhile_statement(ExprParser::While_statementContext *context){
        logger->writeDebug("In visitWhile_statement");

        ASTWhileLoop *node = new ASTWhileLoop();

        this->symbolTable->enterScope();

        node->expr = visit(context->expr());
        node->block = visit(context->block());

        this->symbolTable->exitScope();

        return (ASTWhileLoop *) node;
    };

    virtual antlrcpp::Any visitPrint(ExprParser::PrintContext *context) 
    {
        logger->writeDebug("In visitPrint");

        ASTPrint *node = new ASTPrint();

        ASTExpr *exprNode;

        for (auto expr : context->expr())
        {
            exprNode = visit(expr);
            if (exprNode != nullptr)
            {
                node->exprList.push_back(exprNode);
            }
        }
        return (ASTPrint *) node;    
    };

    virtual antlrcpp::Any visitGetIntStat(ExprParser::GetIntStatContext *context) 
    {
        logger->writeDebug("In visitGetIntStat");
        ASTGetIntStat *node = new ASTGetIntStat();

        return (ASTGetIntStat *) node;    
    };

    virtual antlrcpp::Any visitGetCharStat(ExprParser::GetCharStatContext *context) 
    {
        logger->writeDebug("In visitGetCharStat");
        ASTGetCharStat *node = new ASTGetCharStat();

        return (ASTGetCharStat *) node;    
    };

    virtual antlrcpp::Any visitRet_rule(ExprParser::Ret_ruleContext *context) 
    {
        logger->writeDebug("In visitRet_rule");

        ASTReturn *node = new ASTReturn();

        if(context->expr()){
            node->expr = visit(context->expr());
        } else {
            node->expr = NULL;
        }

        return (ASTReturn *) node;    
    };

    virtual antlrcpp::Any visitLocation(ExprParser::LocationContext *context) 
    {
        logger->writeDebug("In visitLocation");
        ASTLocation *node = new ASTLocation();
        return (ASTLocation *) node;    
    };

    virtual antlrcpp::Any visitExpr(ExprParser::ExprContext *context) 
    {
        logger->writeDebug("In visitExpr");
        ASTExpr *node = new ASTExpr();

        return (ASTExpr *) node;    
    };

    virtual antlrcpp::Any visitLocationExpr(ExprParser::LocationExprContext *context) 
    {
        logger->writeDebug("In visitLocationExpr");
        ASTLocationExpr *node = new ASTLocationExpr();

        node->location = visit(context->location());
        node->type = node->location->type;
        node->exprType = "location";


        return (ASTExpr *) node;    
    };

    virtual antlrcpp::Any visitMethodCallExpr(ExprParser::MethodCallExprContext *context) 
    {
        logger->writeDebug("In visitMethodCallExpr");
        ASTMethodCallExpr *node = new ASTMethodCallExpr();

        node->methodCall = visit(context->method_call());
        node->type = node->methodCall->type;

        return (ASTExpr *) node;    
    };

    virtual antlrcpp::Any visitReadLinesExpr(ExprParser::ReadLinesExprContext *context) 
    {
        logger->writeDebug("In visitReadLinesExpr");
        ASTReadLinesExpr *node = new ASTReadLinesExpr();

        node->filename = context->id()->getText();
        node->type = "char";

        // cout << node->filename;

        return (ASTExpr *) node;    
    };

    virtual antlrcpp::Any visitWriteLinesExpr(ExprParser::WriteLinesExprContext *context) 
    {
        logger->writeDebug("In visitWriteLinesExpr");
        ASTWriteLinesExpr *node = new ASTWriteLinesExpr();

        node->filename = context->id()[0]->getText();
        node->dataLocation = context->id()[1]->getText();
        node->filemode = context->ALPHA()->getText();

        node->type = "int";
        // cout << node->filemode << endl;

        return (ASTExpr *) node;    
    };

    virtual antlrcpp::Any visitUnaryExpr(ExprParser::UnaryExprContext *context) 
    {
        logger->writeDebug("In visitUnaryExpr");
        ASTUnaryExpr *node = new ASTUnaryExpr();

        node->unaryOp = context->unary_op()->getText();
        node->location = visit(context->location());
        node->type = node->location->type;
        return (ASTExpr *) node;    
    };

    virtual antlrcpp::Any visitLiteralExpr(ExprParser::LiteralExprContext *context) 
    {
        logger->writeDebug("In visitLiteralExpr");
        ASTLiteralExpr *node = new ASTLiteralExpr();

        node->literal = visit(context->literal());
        node->type = node->literal->type;

        return (ASTExpr *) node;    
    };

    virtual antlrcpp::Any visitStringLiteralExpr(ExprParser::StringLiteralExprContext *context) 
    {
        logger->writeDebug("In visitStringLiteralExpr");
        ASTStringLiteralExpr *node = new ASTStringLiteralExpr();

        for(auto character : context->string_literal()->char_literal()){
            node->literal += character->getText();
        }

        node->type = "char";

        return (ASTExpr *) node;    
    };

    virtual antlrcpp::Any visitBinaryExpr(ExprParser::BinaryExprContext *context) 
    {
        logger->writeDebug("In visitBinaryExpr");
        ASTBinaryExpr *node = new ASTBinaryExpr();
        node->type = "undefined";

        node->expr1 = visit(context->expr()[0]);
        node->expr2 = visit(context->expr()[1]);

        node->binaryOp = visit(context->bin_op());

        // symbolTable->printTable();

        // cout << context->getText() << "\n";
        // cout << context->expr()[0]->getText() << " " << context->expr()[1]->getText() << "\n";
        // cout << node->expr1->getType() << " " << node->expr2->getType() << "\n";

        if (node->binaryOp->getType() == "arith")
        {
            if (node->expr1->getType() == "int" && node->expr2->getType() == "int")
            {
                node->type = "int";
            }
            else if (node->expr1->getType() == "char" && node->expr2->getType() == "char")
            {
                node->type = "char";
            }
            else 
            {
                logger->writeInvalidOp(OpType::TYPE_ARITH, context, node->binaryOp->getOp(), node->expr1->getType(), node->expr2->getType());
                this->increaseErrorCount();

            }
        }

        if (node->binaryOp->getType() == "rel")
        {
            if (node->expr1->getType() == "int" && node->expr2->getType() == "int")
            {
                node->type = "bool";
            }
            else 
            {
                logger->writeInvalidOp(OpType::TYPE_REL, context, node->binaryOp->getOp(), node->expr1->getType(), node->expr2->getType());
                this->increaseErrorCount();
            }
        }

        if (node->binaryOp->getType() == "cond")
        {
            if (node->expr1->getType() == "bool" && node->expr2->getType() == "bool")
            {
                node->type = "bool";
            }
            else 
            {
                logger->writeInvalidOp(OpType::TYPE_COND, context, node->binaryOp->getOp(), node->expr1->getType(), node->expr2->getType());
                this->increaseErrorCount();

            }
        }

        if (node->binaryOp->getType() == "eq")
        {
            if (node->expr1->getType() == node->expr2->getType())
            {
                node->type = "bool";
            }
            else 
            {
                logger->writeInvalidOp(OpType::TYPE_EQ, context, node->binaryOp->getOp(), node->expr1->getType(), node->expr2->getType());
                this->increaseErrorCount();
    
            }
        }


        // cout << node->binaryOp << endl;

        return (ASTExpr *) node;    
    };

    virtual antlrcpp::Any visitNegativeExpr(ExprParser::NegativeExprContext *context) 
    {
        logger->writeDebug("In visitNegativeExpr");
        ASTNegativeExpr *node = new ASTNegativeExpr();

        node->expr = visit(context->expr());
        node->type = node->expr->type;
        return (ASTExpr *) node;    
    };

    virtual antlrcpp::Any visitNegationExpr(ExprParser::NegationExprContext *context) 
    {
        logger->writeDebug("In visitNegationExpr");
        ASTNegationExpr *node = new ASTNegationExpr();
        
        node->expr = visit(context->expr());
        node->type = node->expr->type;
        
        return (ASTExpr *) node;    
    };

    virtual antlrcpp::Any visitParenthesisExpr(ExprParser::ParenthesisExprContext *context) 
    {
        logger->writeDebug("In visitParenthesisExpr");
        ASTParenthesisExpr *node = new ASTParenthesisExpr();

        node->expr = visit(context->expr());
        node->type = node->expr->type;

        return (ASTExpr *) node;    
    };

    virtual antlrcpp::Any visitVariableLoc(ExprParser::VariableLocContext *context){
        logger->writeDebug("In visitVariableLoc");
        ASTVariableLoc *node = new ASTVariableLoc();
        
        string varName = context->id()->getText(); 
        node->id = varName;

        if (this->symbolTable->lookup(varName) == NULL){
            this->errorFlag = true;
            logger->writeNotDeclr(IdType::TYPE_VAR, (ParserRuleContext *)context, varName);            
            this->increaseErrorCount();

        } else {
            node->type= this->symbolTable->lookup(varName)->getType();
        }

        return (ASTLocation *) node;   
    };

    virtual antlrcpp::Any visitArray1DLoc(ExprParser::Array1DLocContext *context){
        logger->writeDebug("In visitArray1DLoc");

        ASTArray1DLoc *node = new ASTArray1DLoc();
        
        string varName = context->id()->getText(); 
        node->id = varName;

        if (this->symbolTable->lookup(varName) == NULL){
            this->errorFlag = true;
            logger->writeNotDeclr(IdType::TYPE_ARRAY, (ParserRuleContext *)context, varName);            
            this->increaseErrorCount();

        } else {
            node->type= this->symbolTable->lookup(varName)->getType();
        }

        node->expr1 = visit(context->expr());

        return (ASTLocation *) node;
    };

    virtual antlrcpp::Any visitArray2DLoc(ExprParser::Array2DLocContext *context){
        logger->writeDebug("In visitArray2DLoc");
        ASTArray2DLoc *node = new ASTArray2DLoc();
        
        string varName = context->id()->getText(); 
        node->id = varName;

        if (this->symbolTable->lookup(varName) == NULL){
            this->errorFlag = true;
            logger->writeNotDeclr(IdType::TYPE_ARRAY, (ParserRuleContext *)context, varName);    
            this->increaseErrorCount();

        } else {
            node-> type= this->symbolTable->lookup(varName)->getType();
        }

        node->expr1 = visit(context->expr()[0]);
        node->expr2 = visit(context->expr()[1]);

        return (ASTLocation *) node;
    };

    virtual antlrcpp::Any visitMethodCall(ExprParser::MethodCallContext *context) 
    {
        logger->writeDebug("In visitMethodCall");

        ASTMethodCall *node = new ASTMethodCall();

        string methodName = context->method_name()->getText();
        node->methodName = methodName;

        if (this->symbolTable->lookup(methodName) == NULL){
            this->errorFlag = true;
            logger->writeNotDeclr(IdType::TYPE_FUNC, (ParserRuleContext *)context, methodName);  
            this->increaseErrorCount();

        } else {
            node->type = this->symbolTable->lookup(methodName)->getType();
        }

        ASTExpr *exprNode;

        for (auto param : context->expr())
        {
            exprNode = visit(param);
            if (exprNode != nullptr)
            {
                node->paramExprList.push_back(exprNode);
            }
        }

        return (ASTCall *) node;    
    };

    virtual antlrcpp::Any visitCalloutCall(ExprParser::CalloutCallContext *context){

        logger->writeDebug("In visitCalloutCall");

        ASTCalloutCall *node = new ASTCalloutCall();

        // cout << "before" << "\n";
        string methodName = "";
        for(auto character : context->string_literal()->char_literal()){
            methodName += character->getText();
        }
        // string methodName = context->string_literal()->getText();
        // cout << "after" << "\n";

        // cout << methodName << "\n";

        node->methodName = methodName;
        node->type = "int";

        ASTCalloutArg *argNode;

        for (auto param : context->callout_arg())
        {
            argNode = visit(param);
            if (argNode != nullptr)
            {
                node->paramList.push_back(argNode);
            }
        }
        
        // cout << "here" << "\n";
        return (ASTCall *) node;
    };

    virtual antlrcpp::Any visitCallout_arg(ExprParser::Callout_argContext *context){
        logger->writeDebug("In visitCalloutArg");

        ASTCalloutArg *node = new ASTCalloutArg();

        node->expr = visit(context->expr());
        
        // if (context->string_literal() != NULL){
        //     node->argument = context->string_literal()->getText();
        // } else {
        //     node->argument = "";
        // }

        return (ASTCalloutArg *) node;
    };


        virtual antlrcpp::Any visitLiteral(ExprParser::LiteralContext *context) 
    {
        ASTLiteral *node = new ASTLiteral();
        return (ASTLiteral *) node;    
    };

    virtual antlrcpp::Any visitBoolLiteral(ExprParser::BoolLiteralContext *context) 
    {
        logger->writeDebug("In visitBoolLiteral");

        ASTBoolLiteral *node = new ASTBoolLiteral();

        if(context->bool_literal()->getText() == "true"){
            node->literal = true;
        } else {
            node->literal = false;
        }

        return (ASTLiteral *) node;    
    };

    virtual antlrcpp::Any visitIntLiteral(ExprParser::IntLiteralContext *context) 
    {
        logger->writeDebug("In visitIntLiteral");

        ASTIntLiteral *node = new ASTIntLiteral();

        node->literal = stoi(context->int_literal()->getText());
        return (ASTLiteral *) node;    
    };

    virtual antlrcpp::Any visitCharLiteral(ExprParser::CharLiteralContext *context) 
    {
        logger->writeDebug("In visitCharLiteral");

        ASTCharLiteral *node = new ASTCharLiteral();

        node->literal = context->char_literal()->getText();
        return (ASTLiteral *) node;    
    };

    virtual antlrcpp::Any visitArithOp(ExprParser::ArithOpContext *context)
    {
        ASTArithOp *node = new ASTArithOp();

        node->op = context->getText();
        return (ASTBinaryOp *) node;

    };

    virtual antlrcpp::Any visitRelOp(ExprParser::RelOpContext *context)
    {
        ASTRelOp *node = new ASTRelOp();

        node->op = context->getText();

        // cout << node ->op;
        return (ASTBinaryOp *) node;
    };

    virtual antlrcpp::Any visitEqOp(ExprParser::EqOpContext *context)
    {
        ASTEqOp *node = new ASTEqOp();

        node->op = context->getText();
        return (ASTBinaryOp *) node;
    };

    virtual antlrcpp::Any visitCondOp(ExprParser::CondOpContext *context)
    {
        ASTCondOp *node = new ASTCondOp();

        node->op = context->getText();
        return (ASTBinaryOp *) node;
    };

    virtual antlrcpp::Any visitMethod_name(ExprParser::Method_nameContext *context) 
    {
        ASTnode *node = new ASTProgram();
        return (ASTProgram *) node;    
    };

    virtual antlrcpp::Any visitAssign_op(ExprParser::Assign_opContext *context) 
    {
        ASTnode *node = new ASTProgram();
        return (ASTProgram *) node;    
    };

    virtual antlrcpp::Any visitUnary_op(ExprParser::Unary_opContext *context) 
    {
        ASTnode *node = new ASTProgram();
        return (ASTProgram *) node;    
    };

    virtual antlrcpp::Any visitBin_op(ExprParser::Bin_opContext *context) 
    {
        ASTnode *node = new ASTProgram();
        return (ASTProgram *) node;    
    };

    virtual antlrcpp::Any visitArith_op(ExprParser::Arith_opContext *context) 
    {
        ASTnode *node = new ASTProgram();
        return (ASTProgram *) node;    
    };

    virtual antlrcpp::Any visitRel_op(ExprParser::Rel_opContext *context) 
    {
        ASTnode *node = new ASTProgram();
        return (ASTProgram *) node;    
    };

    virtual antlrcpp::Any visitEq_op(ExprParser::Eq_opContext *context) 
    {
        ASTnode *node = new ASTProgram();
        return (ASTProgram *) node;    
    };

    virtual antlrcpp::Any visitCond_op(ExprParser::Cond_opContext *context) 
    {
        ASTnode *node = new ASTProgram();
        return (ASTProgram *) node;    
    };

    virtual antlrcpp::Any visitBool_literal(ExprParser::Bool_literalContext *context) 
    {
        ASTnode *node = new ASTProgram();
        return (ASTProgram *) node;    
    };

    virtual antlrcpp::Any visitChar_literal(ExprParser::Char_literalContext *context) 
    {
        ASTnode *node = new ASTProgram();
        return (ASTProgram *) node;    
    };

    virtual antlrcpp::Any visitString_literal(ExprParser::String_literalContext *context) 
    {
        ASTnode *node = new ASTProgram();
        return (ASTProgram *) node;    
    };

    virtual antlrcpp::Any visitInt_literal(ExprParser::Int_literalContext *context) 
    {
        ASTnode *node = new ASTProgram();
        return (ASTProgram *) node;    
    };

    virtual antlrcpp::Any visitId(ExprParser::IdContext *context) 
    {
        ASTnode *node = new ASTProgram();
        return (ASTProgram *) node;    
    };

    virtual antlrcpp::Any visitAlpha_num(ExprParser::Alpha_numContext *context) 
    {
        ASTnode *node = new ASTProgram();
        return (ASTProgram *) node;    
    };

};