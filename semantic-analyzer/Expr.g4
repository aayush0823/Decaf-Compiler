grammar Expr;
program: 'class Program' '{' field_declr* method_declr* '}';

// Variable and Array declaration
field_declr: type id ';'                                 #fieldVariable
	| type id'['int_literal']' ';'						 #field1DArray	
	| type id'['int_literal']['int_literal']' ';'		 #field2DArray
	;
	
// Method declaration and arguments
method_declr: (func_type) id ('()' | '('arguments?')') block;

arguments: (type id) (  COMMA  type id )*;

// Function return value type
func_type: type
	|'void';

// Code block definition
block: '{'block_content*'}';
block_content: var_declr 								
	| statement											
	;

// Different statement types
statement: location assign_op expr ';'													#assignStat
	| location unary_op ';'																#unaryStat
	| method_call ';'																	#methodCallStat
	| if_statement																		#ifStat
	| for_statement																		#forStat
	| while_statement 																	#whileStat
	| ret_rule																			#returnStat
	| 'break' ';'																		#breakStat
	| 'continue' ';'																	#continueStat
	| 'scanInt' '(' location ')'														#getIntStat
	| 'scanChar' '(' location ')'														#getCharStat
	| print																				#printStat
	| block																				#blockStat
	;

// While statement
while_statement : 'while' '(' expr ')' block ;

// For statement
for_statement : 'for' '(' id '=' expr  SEMICOLON  expr SEMICOLON (expr)? ')' block ;

// If statement
if_statement : 'if' '(' expr ')' block ('else' block)?;

// Print function
print : 'myprint' '(' ((expr) (  COMMA  expr )*)? ')' ';' 
	| 'myprint' '()' ';';

// Return statement
ret_rule : Return ';' 																	
	| Return expr ';'																	
	;

// Variable declaration
var_declr: type id ( COMMA  id )* ';'  				
	;

// Variable location
location : id 							#variableLoc
	| id '['expr']' 					#array1DLoc
	| id '['expr']['expr']' 			#array2DLoc
	;

// Different expression types
expr : location																	#locationExpr
	| method_call																#methodCallExpr	
	| 'readLines' '(' id'[]' ')'												#readLinesExpr
	| 'writeLines''(' id'[]' COMMA id'[]' COMMA '"' ALPHA '"' ')'				#writeLinesExpr
	| location unary_op															#unaryExpr
	| literal																	#literalExpr
	| string_literal															#stringLiteralExpr
	| expr bin_op expr															#binaryExpr
	| '-'expr																	#negativeExpr
	| '!'expr																	#negationExpr
	| '('expr')'																#parenthesisExpr
	;

// Method call expression
method_call : method_name ('()'|'('((expr) (  COMMA  expr )*)?')')				#methodCall
	| 'callout' '(' string_literal (COMMA callout_arg)* ')'						#calloutCall
	;

method_name : id;

callout_arg : expr;

// Return keyword
Return: 'return';

// Data types
type: 'int'
	| 'bool' 
	| 'char';

// Assignment operator
assign_op : '='
		| '+='
		| '-='
		| '*='
		| '/='
		| '%=';

// Unary operator
unary_op: '++' 
	| '--';

// Binary operator
bin_op : arith_op 																#arithOp
	| rel_op 																	#relOp
	| eq_op 																	#eqOp
	| cond_op																	#condOp
	;

// Arithmetic operator
arith_op : '+'
	|'-'
	|'*'
	|'/'
	|'%';

// Relational operator
rel_op : '<'
	|'>'
	|'<='
	|'>=';

// Equality operator
eq_op : '=='
	|'!=';

// Conditional operator
cond_op : '&&' 
	| '||';

// Different literal types
literal : bool_literal 														#boolLiteral
	| int_literal 															#intLiteral
	| '\'' char_literal '\'' 												#charLiteral
	;

// Different boolean literals
bool_literal : 'true' 
	| 'false';

// Different character literals
char_literal : ALPHA 
	| DIGIT 
	| '>' 
	| '*' 
	| '&' 
	| '^' 
	| '$' 
	| '#' 
	| '@' 
	|'!' 
	|';'
	|':'
	|'|'
	|'<'
	| COMMA 
	| '.' 
	| '\\0'
	| '\\n'
	| '%'
	;

// Comma symbol
COMMA: ',';

// Semicolon symbol
SEMICOLON: ';';

// String literal
string_literal: '"' char_literal* '"';

// Integer literal
int_literal: DIGIT+;

// Identifier
id : ALPHA alpha_num*;

// Alpha Numeric characters
alpha_num : ALPHA 
	| DIGIT;

// Alphabets
ALPHA : [a-zA-Z];

// Digits
DIGIT : [0-9];

// Comments
COMMENT: '//' ~[\r\n]*->skip;

// Whitespace characters
NS : [ \t\n\r]+ -> skip; 