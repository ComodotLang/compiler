grammar Comodot;

statementList
  : statement+ ;

statement
  : ifStatement
  | whileStatement
  | functionCall
  | functionDeclaration
  | returnStatement
  | variableDeclaration
  | assignment ;

expression
  : expression ('+' | '-' | '*' | '/' | '%') expression
  | expression ('&&' | '||') expression
  | expression ('<' | '>' | '<=' | '>=' | '==' | '!=') expression
  | '-' expression
  | '(' expression ')'
  | functionCall
  | variable
  | literal ;

ifStatement
  : 'if'  expression  '{' statementList '}' ('else' '{' statementList '}')? ;

whileStatement
  : 'while'  expression '{' statementList '}' ;

functionCall
  : Identifier '(' argumentList ')' ;

argumentList
  : fnArg?
  | fnArg (',' fnArg)* ;

fnArg
    :expression ':' type;

literal
  : IntegerLiteral | StringLiteral | 'true' | 'false' | 'null' ;

functionDeclaration
  : accessModifier 'fn' Identifier functionArguments '->' type '{' statementList '}' ;

functionArguments
  : '(' (arg? | arg (',' arg)*) ')' ;

arg
  : Identifier ':' type;

returnStatement
  : 'ret' expression ;

assignment
  : Identifier ('=' | '+=' | '-=' | '*=' | '/=' | '%=') expression ;

variableDeclaration
  : type Identifier '=' expression ;

accessModifier
  : 'pub' | 'priv';

variable
  : Identifier ;

type
  : 'Int'
  | 'Float'
  | 'Bool'
  | 'Char'
  | 'auto' ;

IntegerLiteral
  : [0-9]+ ;

Identifier
  : IdentifierStart IdentifierPart* ;

fragment
IdentifierStart
  : [a-zA-Z$_] ;

fragment
IdentifierPart
  : [a-zA-Z0-9$_] ;

StringLiteral
  : '"' DoubleQuotedStringCharacter* '"' ;

fragment
DoubleQuotedStringCharacter
  : ~["\r\n\\] | ('\\' .) ;

Whitespace
  : [ \t\r\n\u000C]+ -> skip ;

Comment
  : '//' ~[\r\n]* -> channel(HIDDEN) ;