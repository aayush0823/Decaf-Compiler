#ifndef NODE_CLASS_H
#define NODE_CLASS_H

class ASTnode;

class ASTProgram;

class ASTField;
class ASTFieldVariable;
class ASTField1DArray;
class ASTField2DArray;

class ASTMethod;
class ASTMethodArgument;

class ASTIfCond;
class ASTForLoop;
class ASTWhileLoop;

class ASTBreak;
class ASTContinue;
class ASTReturn;
class ASTPrint;

class ASTCall;
class ASTMethodCall;
class ASTCalloutCall;
class ASTCalloutArg;

class ASTBlock;
class ASTBlockContent;

class ASTVariableDecl;

class ASTStatement;
class ASTAssignStat;
class ASTUnaryStat;
class ASTMethodCallStat;
class ASTIfStat;
class ASTForStat;
class ASTWhileStat;
class ASTReturnStat;
class ASTBreakStat;
class ASTContinueStat;
class ASTPrintStat;
class ASTBlockStat;
class ASTGetIntStat;
class ASTGetCharStat;

class ASTLocation;
class ASTVariableLoc;
class ASTArray1DLoc;
class ASTArray2DLoc;

class ASTExpr;
class ASTLocationExpr;
class ASTMethodCallExpr;
class ASTReadLinesExpr;
class ASTWriteLinesExpr;
class ASTUnaryExpr;
class ASTLiteralExpr;
class ASTStringLiteralExpr;
class ASTBinaryExpr;
class ASTNegativeExpr;
class ASTNegationExpr;
class ASTParenthesisExpr;

class ASTLiteral;
class ASTBoolLiteral;
class ASTIntLiteral;
class ASTCharLiteral;

class ASTBinaryOp;
class ASTArithOp;
class ASTRelOp;
class ASTCondOp;
class ASTEqOp;

// class ASTExprBinary;
// class ASTExprTernary;
// class ASTExprID;
// class ASTExprINT;

#endif