grammar Expr;		
prog:	(expr SEMI)+ EOF;

expr:	expr ('*'|'/'|'%') expr
   	|	expr ('+'|'-') expr
    |	INT
    |   FLOAT
    |   CHAR
    |   expr ('>'|'>='|'<='|'<'|'='|'=='|'!=') expr
    |	'(' expr ')'
    ;

SEMI : ';' ; 

NEWLINE : [\r\n]+->skip;

INT     : [0-9]+ ;

FLOAT     : [0-9]+ '.' [0-9]+;

CHAR: [a-zA-Z0-9]+;

/*Tokens*/

COMMENT : '//' ~[\r\n]*->skip; 
NS : [ \t\n]+ -> skip; 