%{
    #define YYSTYPE node*
    #include "syntax.tab.h"
    #include <stdlib.h>
    #include <stdio.h>
    #include"tree.h"
    int yycolumn =1;
    extern int sim;
    extern int haserror;
    #define YY_USER_ACTION  \
        yylloc.first_line=yylloc.last_line=yylineno;    \
        yylloc.first_column=yycolumn;   \
        yylloc.last_column=yycolumn+yyleng-1;   \
        yycolumn+=yyleng;
    
    #define GREEN "\033[0;32;32m"
    #define NONE "\033[m"
%}

%option yylineno
yylineno=1;

letter [_a-zA-z]
digit [0-9]
INT 0|([1-9]{digit}*)|(00)|(0[1-7][0-7]*)|(0x0)|(0x[1-9A-Fa-f][0-9A-Fa-f]*)|(0X0)|(0X[1-9A-Fa-f][0-9A-Fa-f]*)
EXPPART [Ee][+-]?{INT}
FLOAT (({digit}*\.{digit}+|{digit}+\.{digit}*){EXPPART})|{digit}+\.{digit}+
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
    //printf("//\n");
    while (c!='\n') c=input();
}


"/*" {
    //printf("/*\n");
    int c=input();
    while(c!=0){
        //printf("%u ",c);
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
    //printf("error comment\n");
}



{SEMI} {if(!sim) {printf(GREEN"\'%s\'->SEMI\n"NONE,yytext);} yylval=add_token("SEMI", OTHERTOKEN, NULL); return SEMI;}
{COMMA} {if(!sim)  {printf(GREEN"\'%s\'->COMMA\n"NONE,yytext);}  yylval=add_token("COMMA", OTHERTOKEN, NULL);    return COMMA;}
{ASSIGNOP} {if(!sim) {printf(GREEN"\'%s\'->ASSIGNOP\n"NONE,yytext);} yylval=add_token("ASSIGNOP", OTHERTOKEN, NULL);    return ASSIGNOP;}
{RELOP} {if(!sim) {printf(GREEN"\'%s\'->RELOP\n"NONE,yytext);}   yylval=add_token("RELOP", OTHERTOKEN, NULL);    return RELOP;}
{PLUS} {if(!sim) {printf(GREEN"\'%s\'->PLUS\n"NONE,yytext);} yylval=add_token("PLUS", OTHERTOKEN, NULL);    return PLUS;}
{MINUS} {if(!sim) {printf(GREEN"\'%s\'->MINUS\n"NONE,yytext);}   yylval=add_token("MINUS", OTHERTOKEN, NULL);    return MINUS;}
{STAR} {if(!sim) {printf(GREEN"\'%s\'->STAR\n"NONE,yytext);} yylval=add_token("STAR", OTHERTOKEN, NULL);    return STAR;}
{DIV} {if(!sim) {printf(GREEN"\'%s\'->DIV\n"NONE,yytext);}   yylval=add_token("DIV", OTHERTOKEN, NULL);    return DIV;}
{AND} {if(!sim) {printf(GREEN"\'%s\'->AND\n"NONE,yytext);}   yylval=add_token("AND", OTHERTOKEN, NULL);    return AND;}
{OR} {if(!sim) {printf(GREEN"\'%s\'->OR\n"NONE,yytext);} yylval=add_token("OR", OTHERTOKEN, NULL);    return OR;}
{DOT} {if(!sim) {printf(GREEN"\'%s\'->DOT\n"NONE,yytext);}   yylval=add_token("DOT", OTHERTOKEN, NULL);    return DOT;}
{NOT} {if(!sim) {printf(GREEN"\'%s\'->NOT\n"NONE,yytext);}   yylval=add_token("NOT", OTHERTOKEN, NULL);    return NOT;}
{TYPE} {if(!sim) {printf(GREEN"\'%s\'->TYPE\n"NONE,yytext);} yylval=add_token("TYPE", TYPE_TYPE, yytext);    return TYPE;}
{LP} {if(!sim) {printf(GREEN"\'%s\'->LP\n"NONE,yytext);} yylval=add_token("LP", OTHERTOKEN, NULL);    return LP;}
{RP} {if(!sim) {printf(GREEN"\'%s\'->RP\n"NONE,yytext);} yylval=add_token("RP", OTHERTOKEN, NULL); return RP;}
{LB} {if(!sim) {printf(GREEN"\'%s\'->LB\n"NONE,yytext);} yylval=add_token("LB", OTHERTOKEN, NULL); return LB;}
{RB} {if(!sim) {printf(GREEN"\'%s\'->RB\n"NONE,yytext);} yylval=add_token("RB", OTHERTOKEN, NULL); return RB;}
{LC} {if(!sim) {printf(GREEN"\'%s\'->LC\n"NONE,yytext);} yylval=add_token("LC", OTHERTOKEN, NULL); return LC;}
{RC} {if(!sim) {printf(GREEN"\'%s\'->RC\n"NONE,yytext);} yylval=add_token("RC", OTHERTOKEN, NULL); return RC;}
{STRUCT} {if(!sim) {printf(GREEN"\'%s\'NONE->STRUCT\n",yytext);} yylval=add_token("STRUCT", OTHERTOKEN, NULL); return STRUCT;}
{RETURN} {if(!sim) {printf(GREEN"\'%s\'->RETURN\n"NONE,yytext);} yylval=add_token("RETURN", OTHERTOKEN, NULL); return RETURN;}
{IF} {if(!sim) {printf(GREEN"\'%s\'->IF\n"NONE,yytext);} yylval=add_token("IF", OTHERTOKEN, NULL); return IF;}
{ELSE} {if(!sim) {printf(GREEN"\'%s\'->ELSE\n"NONE,yytext);} yylval=add_token("ELSE", OTHERTOKEN, NULL); return ELSE;}
{WHILE} {if(!sim) {printf(GREEN"\'%s\'->WHILE\n"NONE,yytext);}   yylval=add_token("WHILE", OTHERTOKEN, NULL); return WHILE;}

{INT} {
	if(!sim) {printf(GREEN"\'%s\'->INT\n"NONE,yytext);}
	yylval=add_token("INT", TYPE_INT, yytext);
 	return INT;}
{FLOAT} {
	if(!sim) {printf(GREEN"\'%s\'->FLOAT\n"NONE,yytext);}
	yylval=add_token("FLOAT", TYPE_FLOAT, yytext);
	return FLOAT;}
{ID} {if(!sim) {printf(GREEN"\'%s\'->ID\n"NONE,yytext);} yylval=add_token("ID", TYPE_ID, yytext);  return ID;}
\n {if(!sim) {printf(GREEN"NN\n"NONE);}yycolumn=1;}
[\t\f\r\v ] {}
.  {printf("ERROR TYPE A at line %d: Mysterious characters \'%s\'\n",yylineno,yytext);haserror=1;}
%%
