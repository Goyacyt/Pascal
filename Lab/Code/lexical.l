%{
    #include "syntax.tab.h"
    #include <stdlib.h>
    int yycolumn =1;
    extern int sim;
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
INT 0|([1-9]{digit}*)|(00)|(0[1-7][0-7]*)|(0x0)|(0x[1-9A-Fa-f][0-9A-Fa-f]*)
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

"//" {
    char c=input();
    printf("//\n");
    while (c!='\n') c=input();
}
"/*" {
    printf("/*\n");
    char c=input();
    while(c!=EOF){
        if (c=='*'){
            c=input();
            if (c=='/'){
                break;
            }
            else{
                continue;
            }
        }
        c=input();
    }
}

{SEMI} {if(!sim) {printf("\'%s\'->SEMI\n",yytext);}return SEMI;}
{COMMA} {if(!sim)  {printf("\'%s\'->COMMA\n",yytext);}return COMMA;}
{ASSIGNOP} {if(!sim) {printf("\'%s\'->ASSIGNOP\n",yytext);}return ASSIGNOP;}
{RELOP} {if(!sim) {printf("\'%s\'->RELOP\n",yytext);}return RELOP;}
{PLUS} {if(!sim) {printf("\'%s\'->PLUS\n",yytext);}return PLUS;}
{MINUS} {if(!sim) {printf("\'%s\'->MINUS\n",yytext);}return MINUS;}
{STAR} {if(!sim) {printf("\'%s\'->STAR\n",yytext);}return STAR;}
{DIV} {if(!sim) {printf("\'%s\'->DIV\n",yytext);}return DIV;}
{AND} {if(!sim) {printf("\'%s\'->AND\n",yytext);}return AND;}
{OR} {if(!sim) {printf("\'%s\'->OR\n",yytext);}return OR;}
{DOT} {if(!sim) {printf("\'%s\'->DOT\n",yytext);}return DOT;}
{NOT} {if(!sim) {printf("\'%s\'->NOT\n",yytext);}return NOT;}
{TYPE} {if(!sim) {printf("\'%s\'->TYPE\n",yytext);}return TYPE;}
{LP} {if(!sim) {printf("\'%s\'->LP\n",yytext);}return LP;}
{RP} {if(!sim) {printf("\'%s\'->RP\n",yytext);}return RP;}
{LB} {if(!sim) {printf("\'%s\'->LB\n",yytext);}return LB;}
{RB} {if(!sim) {printf("\'%s\'->RB\n",yytext);}return RB;}
{LC} {if(!sim) {printf("\'%s\'->LC\n",yytext);}return LC;}
{RC} {if(!sim) {printf("\'%s\'->RC\n",yytext);}return RC;}
{STRUCT} {if(!sim) {printf("\'%s\'->STRUCT\n",yytext);}return STRUCT;}
{RETURN} {if(!sim) {printf("\'%s\'->RETURN\n",yytext);}return RETURN;}
{IF} {if(!sim) {printf("\'%s\'->IF\n",yytext);}return IF;}
{ELSE} {if(!sim) {printf("\'%s\'->ELSE\n",yytext);}return ELSE;}
{WHILE} {if(!sim) {printf("\'%s\'->WHILE\n",yytext);}return WHILE;}

{INT} {
	if(!sim) {printf("\'%s\'->INT\n",yytext);}
	yylval.type_int=atoi(yytext);
 	return INT;}
{FLOAT} {
	if(!sim) {printf("\'%s\'->FLOAT\n",yytext);}
	yylval.type_float=atof(yytext);
	return FLOAT;}
{ID} {if(!sim) {printf("\'%s\'->ID\n",yytext);}return ID;}
\n {if(!sim) {printf("\'%s\'->N\n",yytext);}yycolumn=1;}
[\t\f\r\v ] {if(!sim) {printf("\'%s\'->TFRV\n",yytext);}}
.  {printf("ERROR TYPE A at line %d: Mysterious characters \'%s\'\n",yylineno,yytext);}
%%
