#include "ast.h"
#include "Logger.h"
#include "LogDefinitions.h"

using namespace std;

AllocaInst *CreateEntryBlockAlloca(Function *TheFunction, string VarName, string type) {
    IRBuilder<> TmpB(&TheFunction->getEntryBlock(), TheFunction->getEntryBlock().begin());
    AllocaInst *alloca_instruction = nullptr;
    if (type == "int") {
        alloca_instruction = TmpB.CreateAlloca(Type::getInt32Ty(Context), 0, VarName);
    } else if (type == "bool") {
        alloca_instruction = TmpB.CreateAlloca(Type::getInt1Ty(Context), 0, VarName);
    } else if (type == "char") {
        alloca_instruction = TmpB.CreateAlloca(Type::getInt8Ty(Context), 0, VarName);
    }

    return alloca_instruction;
}

Logger* logger = new Logger();

Value* ASTProgram::codegen()
{
    
    // cout << fieldList.size();
    logger->writeDebug("\n\nStarting LLVM Phase");
    logger->writeDebug("In Program Node");

    for (auto field : fieldList)
    {
        field->codegen();
    }

    for (auto method : methodList)
    {
        method->codegen();
    }
        
    Value *V;
    cout << "\n\nGenerating LLVM code\n";
    std::string Str;
    raw_string_ostream OS(Str);
    OS << *TheModule;
    OS.flush();
    ofstream out("output.txt");
    out << Str;
    out.close();
    
    system("sh linker.sh");
    return V;
}

Value* ASTField::codegen()
{
    Value *V;
             
    return V;
}

Value* ASTFieldVariable::codegen()
{
    logger->writeDebug("In Field Variable");

    Value *V;
    // cout << "Field Variable\n";
    
    Type *ty = nullptr;

    if (getType() == "int")
        ty = Type::getInt32Ty(Context);
    else if (getType() == "bool")
        ty = Type::getInt1Ty(Context);
    else if (getType() == "char")
        ty = Type::getInt8Ty(Context);

    Value* V_test;
    V_test = TheModule->getNamedGlobal(getId());

    GlobalVariable *gv = new GlobalVariable(*(TheModule), ty, false, GlobalValue::ExternalLinkage, nullptr, getId());
    gv->setInitializer(ConstantAggregateZero::get(ty));

    return V;
}

Value* ASTField1DArray::codegen(){
    logger->writeDebug("In Field 1D Array");
    
    Value* V;

    Type *ty = nullptr;

    if (getType() == "int")
        ty = Type::getInt32Ty(Context);
    else if (getType() == "bool")
        ty = Type::getInt1Ty(Context);
    else if (getType() == "char")
        ty = Type::getInt8Ty(Context);

    Value* V_test;
    V_test = TheModule->getNamedGlobal(getId());

    ArrayType *arrType = ArrayType::get(ty, getSize1D());
    GlobalVariable *gv = new GlobalVariable(*(TheModule), arrType, false, GlobalValue::ExternalLinkage, nullptr, getId());
    gv->setInitializer(ConstantAggregateZero::get(arrType));

    // cout << getType() << "\n";

    return V;
}

Value* ASTField2DArray::codegen(){

    logger->writeDebug("In Field 2D Array");

    Value* V;

    Type *ty = nullptr;

    if (getType() == "int")
        ty = Type::getInt32Ty(Context);
    else if (getType() == "bool")
        ty = Type::getInt1Ty(Context);
    else if (getType() == "char")
        ty = Type::getInt8Ty(Context);

    // cout << getType() << "\n";

    // Don't know how to do using C++ API
    return V;
}


Value* ASTMethod::codegen(){
    Value* V;

    logger->writeDebug("In Method");

    vector<string> argIds;
    vector<string> argTypes;

    vector<Type *> arguments;
    vector<ASTMethodArgument *> methodArgumentList = getArguments();

    int numArgs = methodArgumentList.size();

    for(auto &arg : methodArgumentList){
        string arg_type = arg->getType();
        string arg_id = arg->getId();

        if (arg_type == "int") {
            arguments.push_back(Type::getInt32Ty(Context));
        } else if (arg_type == "boolean") {
            arguments.push_back(Type::getInt1Ty(Context));
        } else if (arg_type == "void") {
            arguments.push_back(Type::getVoidTy(Context));
        } 

        argIds.push_back(arg_id);
        argTypes.push_back(arg_type);

    }

    Type *return_type;

    if (returnType == "int") {
        return_type = Type::getInt32Ty(Context);
    } else if (returnType == "boolean") {
        return_type = Type::getInt1Ty(Context);
    } else if (returnType == "char") {
        return_type = Type::getInt8Ty(Context);
    } else if (returnType == "void") {
        return_type = Type::getVoidTy(Context);
    } 

    FunctionType *FT = FunctionType::get(return_type, arguments, false);
    Function *F = Function::Create(FT, Function::ExternalLinkage, getId(), TheModule);

    int Idx = 0;

    for (Function::arg_iterator AI = F->arg_begin(); Idx != numArgs; ++AI, ++Idx) {
        AI->setName(argIds[Idx]);
    }

    BasicBlock *BB = BasicBlock::Create(Context, "entry", F);
    Builder.SetInsertPoint(BB);

    Idx = 0;      

    for (auto &Arg : F->args()) {
        AllocaInst *Alloca = CreateEntryBlockAlloca(F, argIds[Idx], argTypes[Idx]);
        Builder.CreateStore(&Arg, Alloca);
        NamedValues[argIds[Idx]] = Alloca;
        Idx++;
    }

    Value *RetVal = block->codegen();

    if(RetVal==nullptr || RetVal)
    {
        if(returnType == "void")
            Builder.CreateRetVoid();   

        verifyFunction(*F);
        return F;
    }

    F->eraseFromParent();
    return nullptr;
}

Value* ASTMethodArgument::codegen(){
    Value* V;
    return V;
}


Value* ASTIfCond::codegen(){

    logger->writeDebug("In If Cond");

    Value* V;
    Value* cond = expr->codegen();

    Function *TheFunction = Builder.GetInsertBlock()->getParent();
    BasicBlock *ifBlock = BasicBlock::Create(Context, "if", TheFunction);
    BasicBlock *elseBlock = BasicBlock::Create(Context, "else");
    BasicBlock *nextBlock = BasicBlock::Create(Context, "ifcont");
    BasicBlock *otherBlock = elseBlock;

    bool ret_if = block1->hasReturn; 
    bool break_if = block1->hasBreak; 
    bool continue_if = block1->hasContinue; 

    bool ret_else = false, break_else = false, continue_else = false;

    if (block2 == NULL) {
        otherBlock = nextBlock;
    }

    Builder.CreateCondBr(cond, ifBlock, otherBlock);
    Builder.SetInsertPoint(ifBlock);

    Value *if_val = block1->codegen();

    // if (if_val == nullptr) {
    //     return nullptr;
    // }

    // cout << "->->->->->->->->->->->->->->->->->->->->" << !ret_if << !break_if << !continue_if << "\n"; 

    if (!ret_if && !break_if && !continue_if) {
        Builder.CreateBr(nextBlock);
    }

    // if (!ret_if) {
    //     Builder.CreateBr(nextBlock);
    // }

    ifBlock = Builder.GetInsertBlock();

    Value *else_val = nullptr;

    if (block2 != NULL) {

        TheFunction->getBasicBlockList().push_back(elseBlock);
        Builder.SetInsertPoint(elseBlock);
       
        else_val = block2->codegen();

        // if (else_val == nullptr) {
        //     return nullptr;
        // }

        ret_else = block2->hasReturn;
        break_else = block2->hasBreak;
        continue_else = block2->hasContinue;

        // cout << "yeeeeeeeeeeeah " << ret_else << "\n";
        if (!ret_else && !break_else && !continue_else){
            Builder.CreateBr(nextBlock);
        }

        
    }

    TheFunction->getBasicBlockList().push_back(nextBlock);
    Builder.SetInsertPoint(nextBlock);

    if (ret_else && ret_if) {
        Type *retType = Builder.GetInsertBlock()->getParent()->getReturnType();
        if (retType == Type::getVoidTy(Context))
            Builder.CreateRetVoid();
        else {
            Builder.CreateRet(ConstantInt::get(Context, APInt(32, 0)));
        }
    }

    V = ConstantInt::get(Context, APInt(32, 0));
    return V;

}

Value* ASTForLoop::codegen(){

    logger->writeDebug("In For Loop");

    Value* init = expr1->codegen();

    if(expr1->getExprType() == "location"){
        init = Builder.CreateLoad(init);
    }

    Function *TheFunction = Builder.GetInsertBlock()->getParent();
    llvm::AllocaInst *Alloca = CreateEntryBlockAlloca(TheFunction, iterator, string("int"));
    Builder.CreateStore(init, Alloca);

    Value *step_val = ConstantInt::get(Context, APInt(32, 1));
    BasicBlock *pre_header_basic_block = Builder.GetInsertBlock();
    BasicBlock *loop_body = BasicBlock::Create(Context, "loop", TheFunction);
    BasicBlock *afterBB = BasicBlock::Create(Context, "afterloop", TheFunction);
    Builder.CreateBr(loop_body);
    Builder.SetInsertPoint(loop_body);

    PHINode *Variable = Builder.CreatePHI(Type::getInt32Ty(Context), 2, iterator);
    Variable->addIncoming(init, pre_header_basic_block);
    Value *end = expr2->codegen();

    if (expr2->getExprType() == "location") {
        end = Builder.CreateLoad(end);
    }

    loops->push(new loopInfo(afterBB, loop_body, end, iterator, Variable));
    llvm::AllocaInst *OldVal = NamedValues[iterator];
    NamedValues[iterator] = Alloca;

    block->codegen();

    Value *cur = Builder.CreateLoad(Alloca, iterator);
    Value *next_val = Builder.CreateAdd(cur, step_val, "NextVal");
    Builder.CreateStore(next_val, Alloca);
    end = Builder.CreateICmpSLT(next_val, end, "loopcondition");
    BasicBlock *loopEndBlock = Builder.GetInsertBlock();
    Builder.CreateCondBr(end, loop_body, afterBB);
    Builder.SetInsertPoint(afterBB);
    Variable->addIncoming(next_val, loopEndBlock);

    if (OldVal) {
        NamedValues[iterator] = OldVal;
    } else {
        NamedValues.erase(iterator);
    }
    llvm::Value *V = ConstantInt::get(Context, APInt(32, 1));
    return V;

    return V;
}

Value* ASTWhileLoop::codegen(){
    Value* V;
    return V;
}


Value* ASTBreak::codegen(){
    logger->writeDebug("In Break");

    Value* V = ConstantInt::get(Context, APInt(32, 1));
    loopInfo *currentLoop = loops->top();
    Builder.CreateBr(currentLoop->getAfterBlock());

    return V;
}

Value* ASTContinue::codegen(){
    logger->writeDebug("In Continue");

    Value* V = ConstantInt::get(Context, llvm::APInt(32, 1));
    loopInfo *currentLoop = loops->top();

    string var = currentLoop->getLoopVariable();
    AllocaInst *Alloca = NamedValues[var];

    Value *step_val = ConstantInt::get(Context, APInt(32, 1));
    Value *cur = Builder.CreateLoad(Alloca, var);
    Value *next_val = Builder.CreateAdd(cur, step_val, "NextVal");
    Builder.CreateStore(next_val, Alloca);

    Value *cond = Builder.CreateICmpULE(next_val, currentLoop->getCondition(),"loopcondition");
    BasicBlock *loopEndBlock = Builder.GetInsertBlock();
    Builder.CreateCondBr(cond, currentLoop->getCheckBlock(), currentLoop->getAfterBlock());
    return V;
}

Value* ASTReturn::codegen(){
    logger->writeDebug("In Return");

    Value *V = nullptr;

    if (expr != nullptr) {
        V = expr->codegen();
        if (expr->getExprType() == "location") {
            V = Builder.CreateLoad(V);
        }
        Builder.CreateRet(V);
        return V;
    }
    // cout << "here generated void return \n";
    Builder.CreateRetVoid();
    return V;
}

Value* ASTPrint::codegen(){
    Value* V;
    return V;
}

Value* ASTCall::codegen(){
    Value* V;
    return V;
}

Value* ASTMethodCall::codegen(){
    
    logger->writeDebug("In Method Call -> "  + getId());

    Function* F = TheModule->getFunction(getId());

    vector<ASTExpr *> paramList = paramExprList;
    FunctionType *FTy = F->getFunctionType();

    for(int i=0; i<paramExprList.size(); i++)
    {
        Value *argVal = paramExprList[i]->codegen();

        argVal = Builder.CreateLoad(argVal);
        
    }

    vector<Value *> argumentsVal;

    for (auto &arg : paramExprList) {

        Value *argVal = arg->codegen();
        argVal = Builder.CreateLoad(argVal);
        
        argumentsVal.push_back(argVal);
    }

    Value *V = Builder.CreateCall(F, argumentsVal);

    return V;
}

Value* ASTCalloutCall::codegen(){
    logger->writeDebug("In Callout Call");

    vector<Type *> argTypes;
    vector<Value *> Args;
    vector<ASTCalloutArg *> arguments = paramList;

    // cout << "1" << "\n";
    for (auto &arg : arguments) {
        Value *temp = arg->codegen();
        
        Args.push_back(temp);

        // cout << temp->getType() << "\n";
        argTypes.push_back(temp->getType());
    }

    // cout << "2" << "\n";

    ArrayRef<Type *> argsRef(argTypes);
    ArrayRef<Value *> funcargs(Args);
    FunctionType *FType = FunctionType::get(Type::getInt32Ty(Context), argsRef, false);
    auto func = TheModule->getOrInsertFunction(getId(), FType);

    // cout << "3" << "\n";

    Value* V = Builder.CreateCall(func, funcargs);

    return V;
}

Value* ASTCalloutArg::codegen(){

    logger->writeDebug("In CalloutArg");

    Value *V = expr->codegen();
    V = Builder.CreateLoad(V);

    return V;
}

Value* ASTBlock::codegen(){
    logger->writeDebug("In Block");

    Value* V;
    map<string, AllocaInst *> initial_vals;

    for(auto &variable: getVariableList()){
        V = variable->codegen(initial_vals);
    }

    for(auto &statement: getStatementList()){
        V = statement->codegen();
    }

    for (auto it = initial_vals.begin(); it != initial_vals.end(); it++) {
        NamedValues[it->first] = initial_vals[it->first];
    }

    return V;
}

Value* ASTBlockContent::codegen(){
    Value* V;
    return V;
}


Value* ASTVariableDecl::codegen(map<string, AllocaInst *> &initial_vals){
    logger->writeDebug("In VariableDecl");

    Value* V_test;
    llvm::Function *TheFunction = Builder.GetInsertBlock()->getParent();

    for (auto &varId : idList) {

        llvm::Value *initval = nullptr;
        llvm::AllocaInst *Alloca = nullptr;

        if (type == "int") {

            V_test = NamedValues[varId];

            initval = ConstantInt::get(Context, APInt(32, 0));
            Alloca = CreateEntryBlockAlloca(TheFunction, varId, "int");

        } else if (type == "char") {

            V_test = NamedValues[varId];

            initval = ConstantInt::get(Context, APInt(8, 0));
            Alloca = CreateEntryBlockAlloca(TheFunction, varId, "char");
        } else if (type == "bool") {

            V_test = NamedValues[varId];

            initval = ConstantInt::get(Context, APInt(1, 0));
            Alloca = CreateEntryBlockAlloca(TheFunction, varId, "bool");
        }
        Builder.CreateStore(initval, Alloca);

        initial_vals[varId] = NamedValues[varId];
        NamedValues[varId] = Alloca;
    }

    Value *V = ConstantInt::get(Context, APInt(32, 1));
    return V;
}


Value* ASTStatement::codegen(){
    Value* V;
    return V;
}

Value* ASTAssignStat::codegen(){
    logger->writeDebug("In AssignStat");

    Value* value = NULL;

    Value *cur = NamedValues[location->getId()];

    if (cur == nullptr) {
        cur = TheModule->getGlobalVariable(location->getId());
    }

    // cout << "1\n";
    value = expr->codegen();
    // cout << "2\n";

    // cout << *value << "\n";
    if(expr->getExprType() == "location"){
        value = Builder.CreateLoad(value);
    }

    // cout << "Function loaded" << "\n";
    // cout << "3\n";
    Value *lhs = location->codegen();
    // cout << "4\n";
    
    cur = Builder.CreateLoad(lhs);

    string op = getOp();

    if (op == "+=") {
        value = Builder.CreateAdd(cur, value, "addEqualTo");
    } else if (op == "-=") {
        value = Builder.CreateSub(cur, value, "subEqualTo");
    } else if (op == "*=") {
        value = Builder.CreateMul(cur, value, "mulEqualTo");
    } else if (op == "/=") {
        value = Builder.CreateSDiv(cur, value, "divEqualTo");
    } else if (op == "%=") {
        value = Builder.CreateSRem(cur, value, "modEqualTo");
    }

    return Builder.CreateStore(value, lhs);

    // return V;
}

Value* ASTUnaryStat::codegen(){
    Value* V;
    return V;
}

Value* ASTMethodCallStat::codegen(){
    Value* V = methodCall->codegen();
    return V;
}

Value* ASTIfStat::codegen(){
    Value* V = ifCond->codegen();
    return V;
}

Value* ASTForStat::codegen(){
    Value* V = forLoop->codegen();
    return V;
}

Value* ASTWhileStat::codegen(){
    Value* V;
    return V;
}

Value* ASTReturnStat::codegen(){
    Value* V = returnNode->codegen();
    return V;
}

Value* ASTBreakStat::codegen(){
    Value* V = breakNode->codegen();
    return V;
}

Value* ASTContinueStat::codegen(){
    Value* V = continueNode->codegen();
    return V;
}

Value* ASTPrintStat::codegen(){
    Value* V;
    return V;
}

Value* ASTGetIntStat::codegen(){
    logger->writeDebug("In Int Statement");


    Value* V = nullptr;

    llvm::FunctionType *readFnType = llvm::FunctionType::get(Builder.getInt32Ty(), true); 
    llvm::Function* readfn = llvm::Function::Create(readFnType, llvm::GlobalValue::ExternalLinkage, "getInt", TheModule);

    
    return V;
}

Value* ASTGetCharStat::codegen(){
    logger->writeDebug("In Char Statement");


    Value* V;
    return V;
}

Value* ASTBlockStat::codegen(){
    Value* V;
    return V;
}


Value* ASTLocation::codegen(){
    Value* V;
    return V;
}

Value* ASTVariableLoc::codegen(){

    logger->writeDebug("In Variable Location");

    string varId = getId();
    Value* V = NamedValues[varId];

    if (V == nullptr) {
        V = TheModule->getNamedGlobal(varId);
    };

    return V;
}

Value* ASTArray1DLoc::codegen(){
    logger->writeDebug("Array 1D Location Expr");

    Value* V;

    V = NamedValues[getId()];

    if (V == nullptr) {
        V = TheModule->getNamedGlobal(getId());
    }

    if (expr1 == nullptr) {
        cout<<"ERROR: Invalid array index"<<endl;
    }

    Value *index = expr1->codegen();

    // cout << index;

    // if (expr1->getExprType() == "location"){
    index = Builder.CreateLoad(index);
    // }

    vector<Value *> array_index;
    array_index.push_back(Builder.getInt32(0));
    array_index.push_back(index);
    V = Builder.CreateGEP(V, array_index, getId() + "_Index");

    return V;
}

Value* ASTArray2DLoc::codegen(){
    logger->writeDebug("Array 2D Location Expr");

    Value* V;
    return V;
}


Value* ASTExpr::codegen(){
    Value* V;
    return V;
}

Value* ASTLocationExpr::codegen(){

    logger->writeDebug("In Location Expr");

    Value* V;

    V = location->codegen();

    return V;
}

Value* ASTMethodCallExpr::codegen(){
    logger->writeDebug("In Method Call Expr");

    Value* V = methodCall->codegen();
    return V;
}

Value* ASTReadLinesExpr::codegen(){
    logger->writeDebug("In ReadLines Expr");

    Value* V;
    return V;
}

Value* ASTWriteLinesExpr::codegen(){
    logger->writeDebug("In WriteLines Expr");


    Value* V;
    return V;
}

Value* ASTUnaryExpr::codegen(){
    logger->writeDebug("In Unary Expr");

    Value* V;
    return V;
}

Value* ASTLiteralExpr::codegen(){
    logger->writeDebug("In Literal Expr");

    // cout << "before literal codegen\n";
    Value* V = literal->codegen();
    // cout << "after literal codegen\n";

    return V;
}

Value* ASTStringLiteralExpr::codegen(){
    logger->writeDebug("String Literal Expr");

    // Value* V = literal->codegen();
    // return V;
    return Builder.CreateGlobalStringPtr(literal);
}

Value* ASTBinaryExpr::codegen(){
    logger->writeDebug("In Binary Expr");

    Value *left = NULL;
    Value *right = NULL;

    left = expr1->codegen();

    right = expr2->codegen();

    if (expr1->getExprType() == "location") {
        left = Builder.CreateLoad(left);
    }
    if (expr2->getExprType() == "location") {
        right = Builder.CreateLoad(right);
    }

    string op = binaryOp->op;

    Value *V = nullptr;
    if (op == "+") {
        V = Builder.CreateAdd(left, right, "addition");
    } else if (op == "-") {
        V = Builder.CreateSub(left, right, "subtraction");
    } else if (op == "*") {
        V = Builder.CreateMul(left, right, "multiplication");
    } else if (op == "/") {
        V = Builder.CreateSDiv(left, right, "division");
    } else if (op == "%") {
        V = Builder.CreateSRem(left, right, "modulus");
    } else if (op == "<") {
        V = Builder.CreateICmpSLT(left, right, "ltcompare");
    } else if (op == ">") {
        V = Builder.CreateICmpSGT(left, right, "gtcompare");
    } else if (op == "<=") {
        V = Builder.CreateICmpSLE(left, right, "lecompare");
    } else if (op == ">=") {
        V = Builder.CreateICmpSGE(left, right, "gecompare");
    } else if (op == "==") {
        V = Builder.CreateICmpEQ(left, right, "equalcompare");
    } else if (op == "!=") {
        V = Builder.CreateICmpNE(left, right, "notequalcompare");
    } else if (op == "||") {
        return Builder.Insert(BinaryOperator::Create(Instruction::Or, left, right, "doubleor"));
    } else if (op == "&&") {
        return Builder.Insert(BinaryOperator::Create(Instruction::And, left, right, "doubleand"));
    }     
    
    return V;
}

Value* ASTNegativeExpr::codegen(){
    logger->writeDebug("In Negative Expr");

    Value* V;
    return V;
}

Value* ASTNegationExpr::codegen(){
    logger->writeDebug("Negation Expr");

    Value* V;
    return V;
}

Value* ASTParenthesisExpr::codegen(){
    logger->writeDebug("In Parenthesis Expr");

    Value* V = expr->codegen();
    return V;
}


Value* ASTLiteral::codegen(){
    Value* V;
    return V;
}

Value* ASTBoolLiteral::codegen(){

    logger->writeDebug("In Bool Literal");
    
    Value* V;
    // llvm::Function *TheFunction = Builder.GetInsertBlock()->getParent();
    // llvm::AllocaInst *Alloca = nullptr;

    V = ConstantInt::get(Context, APInt(1, literal));
    // Alloca = CreateEntryBlockAlloca(TheFunction, "const", "int");

    return V;
}

Value* ASTIntLiteral::codegen(){
    logger->writeDebug("In Int Literal");

    Value* V;
    // llvm::Function *TheFunction = Builder.GetInsertBlock()->getParent();
    // llvm::AllocaInst *Alloca = nullptr;

    V = ConstantInt::get(Context, APInt(32, static_cast<uint64_t>(literal)));
    // Alloca = CreateEntryBlockAlloca(TheFunction, "const", "int");

    return V;
}

Value* ASTCharLiteral::codegen(){
    logger->writeDebug("In Char Literal");

    Value* V;
    // llvm::Function *TheFunction = Builder.GetInsertBlock()->getParent();
    // llvm::AllocaInst *Alloca = nullptr;

    V = ConstantInt::get(Context, APInt(8, static_cast<uint64_t>(char(literal[0]))));
    // V = CreateEntryBlockAlloca(TheFunction, "const", "int");

    return V;
}


Value* ASTBinaryOp::codegen(){
    Value* V;
    return V;
}

Value* ASTArithOp::codegen(){
    Value* V;
    return V;
}

Value* ASTRelOp::codegen(){
    Value* V;
    return V;
}

Value* ASTCondOp::codegen(){
    Value* V;
    return V;
}

Value* ASTEqOp::codegen(){
    Value* V;
    return V;
}
