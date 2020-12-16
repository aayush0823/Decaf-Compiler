grammar Parser;
program: 'class Program' '{' field_declr* method_declr* '}';

// Variable and Array declaration
field_declr: type id ';'| type id'['int_literal']' ';'| type id'['int_literal']['int_literal']' ';';

// Method declaration and arguments
method_declr: (func_type) id ('()'|'('arguments?')') block;
arguments: (type id) (  COMMA  type id )*;

// Data types
type: 'int'| 'bool' | 'char';

// Function return value type
func_type: type|'void';

// Code block definition
block: '{'block_content*'}';
block_content: var_declr | statement;

// Different statement types
statement: location assign_op expr ';'
	| location unary_op ';'
	| method_call ';'
	| if_statement
	| 'for' '(' id '=' expr  SEMICOLON  expr SEMICOLON (expr)?')' block
	| 'while' '(' expr ')' block 
	| ret_rule
	| 'break' ';'
	| 'continue' ';'
	| print
	| block
	;

// If statement
if_statement : 'if' '(' expr ')' block ('else' block)?;

// Print function
print : 'print' '(' ((expr) (  COMMA  expr )*)? ')' ';' | 'print' '()' ';';

// Return statement
ret_rule : Return ';' | Return expr ';';

// Variable declaration
var_declr: type id ( COMMA  id )* ';' ;

// Variable location
location : id | id '['expr']' | id '['expr']['expr']' | id '[]';

// Different expression types
expr : location
	| method_call
	| 'getInt()'
	| 'getChar()'
	| 'readLines''('expr')'
	| 'writeLines''('expr COMMA expr COMMA ALPHA')'
	| location unary_op
	| literal
	| string_literal
	| expr bin_op expr
	| '-'expr
	| '!'expr
	| '('expr')'
	;

// Method call expression
method_call : method_name ('()'|'('((expr) (  COMMA  expr )*)?')');
method_name : id;

// Return keyword
Return: 'return';

// Assignment operator
assign_op : '='
		| '+='
		| '-='
		| '*='
		| '/='
		| '%=';

// Unary operator
unary_op: '++' | '--';

// Binary operator
bin_op : arith_op | rel_op | eq_op | cond_op;

// Arithmetic operator
arith_op : '+'|'-'|'*'|'/'|'%';

// Relational operator
rel_op : '<'|'>'|'<='|'>=';

// Equality operator
eq_op : '=='|'!=';

// Conditional operator
cond_op : '&&' | '||';

// Different literal types
literal : bool_literal | int_literal | '\'' char_literal '\'' ;

// Different boolean literals
bool_literal : 'true' | 'false';

// Different character literals
char_literal : ALPHA | DIGIT | '>' | '*' | '&' | '^' | '$' | '#' | '@' |'!' |';'|':'|'|'|'<'| COMMA | '.' | '\\0';

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
alpha_num : ALPHA | DIGIT;

// Alphabets
ALPHA : [a-zA-Z];

// Digits
DIGIT : [0-9];

// Comments
COMMENT: '//' ~[\r\n]*->skip;

// Whitespace characters
NS : [ \t\n\r]+ -> skip; 