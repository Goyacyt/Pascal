%option yylineno
yylineno=1;

letter [_a-zA-z]
digit [0-9]
INT 0|[1-9]{digit}*|00|0[1-7][0-7]*|0x0|0x[1-9A-Fa-f][0-9A-Fa-f]*
EXPPART [Ee][+-]?{INT}
FLOAT ({digit}*\.{digit}+|{digit}+\.{digit}*){EXPPART}{0,1}
ID {letter}[_a-zA-z0-9]*
SEMI ";"
COMMA ","
ASSIGNOP "="
RELOP "<"|">"|"<="|">="|"=="|"!="
PLUS "+"
MINUS "-"
STAR "*"
DIV "/"
AND "&&"
OR "||"
DOT "."
NOT "!"
TYPE "int"|"float"
LP "("
RP ")"
LB "["
RB "]"
LC "{"
RC "}"
STRUCT "struct"
RETURN "return"
IF "if" 
ELSE "else"
WHILE "while"

%%

{SEMI} {printf("%s\n SEMI",yytext);}
{COMMA} {printf("%s\n COMMA",yytext);}
{ASSIGNOP} {printf("%s\n ASSIGNOP",yytext);}
{RELOP} {printf("%s\n RELOP",yytext);}
{PLUS} {printf("%s\n PLUS",yytext);}
{MINUS} {printf("%s\n MINUS",yytext);}
{STAR} {printf("%s\n STAR",yytext);}
{DIV} {printf("%s\n DIV",yytext);}
{AND} {printf("%s\n AND",yytext);}
{OR} {printf("%s\n OR",yytext);}
{DOT} {printf("%s\n DOT",yytext);}
{NOT} {printf("%s\n NOT",yytext);}
{TYPE} {printf("%s\n TYPE",yytext);}
{LP} {printf("%s\n LP",yytext);}
{RP} {printf("%s\n RP",yytext);}
{LB} {printf("%s\n LB",yytext);}
{RB} {printf("%s\n RB",yytext);}
{LC} {printf("%s\n LC",yytext);}
{RC} {printf("%s\n RC",yytext);}
{STRUCT} {printf("%s\n STRUCT",yytext);}
{RETURN} {printf("%s\n RETURN",yytext);}
{IF} {printf("%s\n IF",yytext);}
{ELSE} {printf("%s\n ELSE",yytext);}
{WHILE} {printf("%s\n WHILE",yytext);}

{INT} {printf("%s\n INT",yytext);}
{FLOAT} {printf("%s\n FLOAT",yytext);}
{ID} {printf("%s\n ID",yytext);}
.  {printf("ERROR TYPE A at line %d: Mysterious characters \'%s\'\n",yylineno,yytext);}

%%
