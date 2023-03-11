%{
    #include "syntax.tab.h"
    int yycolumn =1;
    #define YY_USER_ACTION  \
        yylloc.first_line=yylloc.last_line=yylineno;    \
        yylloc.first_column=yycolumn;   \
        yylloc.last_column=yycolumn+yyleng-1;   \
        yycolumn+=yyleng;

%}

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

{SEMI} {printf("\'%s\'->SEMI\n",yytext);return SEMI;}
{COMMA} {printf("\'%s\'->COMMA\n",yytext);return COMMA;}
{ASSIGNOP} {printf("\'%s\'->ASSIGNOP\n",yytext);return ASSIGNOP;}
{RELOP} {printf("\'%s\'->RELOP\n",yytext);return RELOP;}
{PLUS} {printf("\'%s\'->PLUS\n",yytext);return PLUS;}
{MINUS} {printf("\'%s\'->MINUS\n",yytext);return MINUS;}
{STAR} {printf("\'%s\'->STAR\n",yytext);return STAR;}
{DIV} {printf("\'%s\'->DIV\n",yytext);return DIV;}
{AND} {printf("\'%s\'->AND\n",yytext);return AND;}
{OR} {printf("\'%s\'->OR\n",yytext);return OR;}
{DOT} {printf("\'%s\'->DOT\n",yytext);return DOT;}
{NOT} {printf("\'%s\'->NOT\n",yytext);return NOT;}
{TYPE} {printf("\'%s\'->TYPE\n",yytext);return TYPE;}
{LP} {printf("\'%s\'->LP\n",yytext);return LP;}
{RP} {printf("\'%s\'->RP\n",yytext);return RP;}
{LB} {printf("\'%s\'->LB\n",yytext);return LB;}
{RB} {printf("\'%s\'->RB\n",yytext);return RB;}
{LC} {printf("\'%s\'->LC\n",yytext);return LC;}
{RC} {printf("\'%s\'->RC\n",yytext);return RC;}
{STRUCT} {printf("\'%s\'->STRUCT\n",yytext);return STRUCT;}
{RETURN} {printf("\'%s\'->RETRUN\n",yytext);return RETURN;}
{IF} {printf("\'%s\'->IF\n",yytext);return IF;}
{ELSE} {printf("\'%s\'->ELSE\n",yytext);return ELSE;}
{WHILE} {printf("\'%s\'->WHILE\n",yytext);return WHILE;}

{INT} {printf("\'%s\'->INT\n",yytext);return INT;}
{FLOAT} {printf("\'%s\'->FLOAT\n",yytext);return FLOAT;}
{ID} {printf("\'%s\'->ID\n",yytext);return ID;}
\n {printf("\'%s\'->N\n",yytext);yycolumn=1;}
[\t\f\r\v ] {printf("\'%s\'->TFRV\n",yytext);}
.  {printf("ERROR TYPE A at line %d: Mysterious characters \'%s\'\n",yylineno,yytext);}
%%