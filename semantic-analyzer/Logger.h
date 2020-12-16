#ifndef LOGGER_CLASS_H
#define LOGGER_CLASS_H

#include <iostream>
#include <string>

#include "antlr4-runtime.h"
#include "LogDefinitions.h"

class Logger {
    
	public:
		void writeDebug(string message){
			if (DEBUG){
				cout << message << endl; 
			}
		}

		void writeDuplicate(IdType idType, ParserRuleContext* ctx, string id, string id2 = ""){
			
			if(idType == IdType::TYPE_VAR){
				int lineNum = ctx->getStart()->getLine();
				cout << "Line Number: " + to_string(lineNum) + " [DUPLICATE] VARIABLE: " + id + " already declared in this scope\n";
			}

			if(idType == IdType::TYPE_FUNC){
				int lineNum = ctx->getStart()->getLine();
				cout << "Line Number: " + to_string(lineNum) + " [DUPLICATE] METHOD: " + id + " already defined.\n";
			}
			
			if(idType == IdType::TYPE_PARAM){
				int lineNum = ctx->getStart()->getLine();
				cout << "Line Number: " + to_string(lineNum) + " [DUPLICATE] PARAMETER: " +  id + " already defined in method " + id2 + "\n";
			}

		}

		void writeNotDeclr(IdType idType, ParserRuleContext* ctx, string id){
			if(idType == IdType::TYPE_VAR){
				int lineNum = ctx->getStart()->getLine();
				cout << "Line Number: " + to_string(lineNum) + " [NOT DECLARED] VARIABLE: " + id + " not declared in this scope\n";
			}

			if(idType == IdType::TYPE_ARRAY){
				int lineNum = ctx->getStart()->getLine();
				cout << "Line Number: " + to_string(lineNum) + " [NOT DECLARED] ARRAY: " + id + " not declared in this scope\n";
			}

			if(idType == IdType::TYPE_FUNC){
				int lineNum = ctx->getStart()->getLine();
				cout << "Line Number: " + to_string(lineNum) + " [NOT DECLARED] METHOD: " + id + " not declared in this scope\n";
			}
		}

		void writeInvalidOp(OpType opType, ParserRuleContext* ctx, string op, string type1, string type2){
			if(opType == OpType::TYPE_ARITH){
				int lineNum = ctx->getStart()->getLine();
				cout << "Line Number: " + to_string(lineNum) + " [INVALID OPERATION] Undefined arithmetic operation: " + op + " between operators of type " + type1 + " and " + type2 + " in the expression " + ctx->getText() + "\n";
			}

			if(opType == OpType::TYPE_REL){
				int lineNum = ctx->getStart()->getLine();
				cout << "Line Number: " + to_string(lineNum) + " [INVALID OPERATION] Undefined relational operation: " + op + " between operators of type " + type1 + " and " + type2 + " in the expression " + ctx->getText() + "\n";
			}

			if(opType == OpType::TYPE_COND){
				int lineNum = ctx->getStart()->getLine();
				cout << "Line Number: " + to_string(lineNum) + " [INVALID OPERATION] Undefined conditional operation: " + op + " between operators of type " + type1 + " and " + type2 + " in the expression " + ctx->getText() + "\n";
			}

			if(opType == OpType::TYPE_EQ){
				int lineNum = ctx->getStart()->getLine();
				cout << "Line Number: " + to_string(lineNum) + " [INVALID OPERATION] Undefined equality operation: " + op + " between operators of type " + type1 + " and " + type2 + " in the expression " + ctx->getText() + "\n";
			}
		}

		void writeInvalidAssignment(ParserRuleContext* ctx, string type1, string type2){
			int lineNum = ctx->getStart()->getLine();
			cout << "Line Number: " + to_string(lineNum) + " [INVALID ASSIGNMENT] Invalid assignment between variables of type: " + type1 + " and " + type2 + "\n";
		}

		void writeInvalidAssignmentInt(string op, ParserRuleContext* ctx, string type1, string type2){
			int lineNum = ctx->getStart()->getLine();
			cout << "Line Number: " + to_string(lineNum) + " [INVALID ASSIGNMENT] Invalid assignment operation "+ op +" between variables of type: " + type1 + " and " + type2 + "\n";
		}

		void writeInvalidIfCond(string type, ParserRuleContext* ctx){
			int lineNum = ctx->getStart()->getLine();
			cout << "Line Number: " + to_string(lineNum) + " [INVALID EXPRESSION] Invalid type " + type + " in If condition, expecting expression of type bool" + "\n";
		}

};

#endif