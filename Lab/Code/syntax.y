%{
    #define YYDEBUG 1
    #include<stdio.h>
    #include"lex.yy.c"
    int yylex(void);
    void yyerror(const char* s);
    extern int yylineno;
    extern char* yytext;
    #define RED "\033[0;32;31m"
    #define NONE "\033[m"
    #define YELLOW "\033[1;33m"
    extern int bisonsim;
    extern int error_line;
%}

%locations  //strange

//declare types
%union{
    int type_int;
    float type_float;
    double type_double;
}

//declare tokens
%token <type_int> INT 
%token <type_float> FLOAT
%token ID SEMI COMMA ASSIGNOP RELOP PLUS MINUS STAR DIV AND OR DOT NOT TYPE LP RP LB RB LC RC STRUCT RETURN IF ELSE WHILE

//declare associativity and piority for tokens
%right ASSIGNOP
%left  AND OR
%left  RELOP
%left  PLUS MINUS
%left  STAR DIV
%right NOT NEG
//%right NEG  //  define for 负号,咋用呢...
%left  DOT LP RP LB RB
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE


//declare non-terminals
%type <type_double> Program ExtDefList ExtDef ExtDecList

%type <type_double> Specifier StructSpecifier OptTag Tag

%type <type_double> CompSt StmtList Stmt

%type <type_double> DefList Def DecList Dec

%type <type_double> Exp Args


%%
//declare high level 
Program: ExtDefList {if(!bisonsim)  {printf(YELLOW"     Program:1\n"NONE);}}
;
ExtDefList:ExtDef ExtDefList    {if(!bisonsim)  {printf(YELLOW"     ExtDefList:1\n"NONE);}}
    | /*empty*/ {if(!bisonsim)  {printf(YELLOW"     ExtDefList:2"NONE);}}
;
ExtDef: Specifier ExtDecList SEMI   {if(!bisonsim)  {printf(YELLOW"     ExtDef:1\n"NONE);}}
    | Specifier SEMI    {if(!bisonsim)  {printf(YELLOW"     ExtDef:2\n"NONE);}}
    | Specifier FunDec CompSt   {if(!bisonsim)  {printf(YELLOW"     ExtDef:3\n"NONE);}}
    | error SEMI {printf("Wrong ExtDef\n");yyerrok;}
    | error Specifier {printf("Wrong ExtDef: error Specifier\n");yyerrok;}
;               

ExtDecList: VarDec  {if(!bisonsim)  {printf(YELLOW"     ExtDecList:1\n"NONE);}}
    | VarDec COMMA ExtDecList   {if(!bisonsim)  {printf(YELLOW"     ExtDecList:2\n"NONE);}}
;

//declare Specifiers
Specifier: TYPE     {if(!bisonsim)  {printf(YELLOW"     Specifier:1\n"NONE);}}
    | StructSpecifier   {if(!bisonsim)  {printf(YELLOW"     Specifier:2\n"NONE);}}
;
StructSpecifier: STRUCT OptTag LC DefList RC    {if(!bisonsim)  {printf(YELLOW"     StructSpecifier:1\n"NONE);}}
    | STRUCT Tag    {if(!bisonsim)  {printf(YELLOW"     StructSpecifier:2\n"NONE);}}
;   

OptTag: ID  {if(!bisonsim)  {printf(YELLOW"     OptTag:1\n"NONE);}}
    | /* empty */   {if(!bisonsim)  {printf(YELLOW"     OptTag:2\n"NONE);}}
;
Tag: ID {if(!bisonsim)  {printf(YELLOW"     Tag\n"NONE);}}
;

//decalre Declarators
VarDec: ID  {if(!bisonsim)  {printf(YELLOW"     VarDec:1\n"NONE);}}
    | VarDec LB INT RB  {if(!bisonsim)  {printf(YELLOW"     VarDec:2\n"NONE);}}
;

FunDec: ID LP VarList RP    {if(!bisonsim)  {printf(YELLOW"     FunDec:1\n"NONE);}}
    | ID LP RP  {if(!bisonsim)  {printf(YELLOW"     FunDec:2\n"NONE);}}
    | error RP {printf("Wrong FunDec\n");yyerrok;}
;

VarList: ParamDec COMMA VarList {if(!bisonsim)  {printf(YELLOW"     VarList:1\n"NONE);}}
    | ParamDec  {if(!bisonsim)  {printf(YELLOW"     VarList:2\n"NONE);}}
;
ParamDec: Specifier VarDec {if(!bisonsim)  {printf(YELLOW"     ParamDec:1\n"NONE);}}
;

//declare Statements
CompSt: LC DefList StmtList RC          {if(!bisonsim)  {printf(YELLOW"     CompSt:1\n"NONE);}} 
    //| error RC  {printf("Wrong ComSt\n");yyerrok;}
;

StmtList: Stmt StmtList     {if(!bisonsim)  {printf(YELLOW"     StmtList:1\n"NONE);}}
    | /* empty */   {if(!bisonsim)  {printf(YELLOW"     StmtList:2\n"NONE);}}
;


Stmt: Exp SEMI  {if(!bisonsim)  {printf(YELLOW"     Stmt:1\n"NONE);}}
    | CompSt    {if(!bisonsim)  {printf(YELLOW"     Stmt:2\n"NONE);}}
    | RETURN Exp SEMI    {if(!bisonsim)  {printf(YELLOW"     Stmt:3"NONE);}}
    | IF LP Exp RP Stmt %prec LOWER_THAN_ELSE {if(!bisonsim)  {printf(YELLOW"     Stmt:4\n"NONE);}}
    | IF LP Exp RP Stmt ELSE Stmt   {if(!bisonsim)  {printf(YELLOW"     Stmt:5\n"NONE);}}         
    | WHILE LP Exp RP Stmt            {if(!bisonsim)  {printf(YELLOW"     Stmt:6\n"NONE);}} 
    | error SEMI    {printf("Wrong Stmt:error SEMI\n");yyerrok;}
    | error Exp {printf("Wrong Stmt :error Exp\n");yyerrok;}
    | error RETURN {printf("Wrong Stmt:error RETURN\n");yyerrok;}
    | error IF {printf("Wrong Stmt:error IF\n");yyerrok;}
    | error WHILE {printf("Wrong Stmt:error WHILE\n");yyerrok;}
    | error RC {printf("Wrong Stmt:error RC\n");yyerrok;}
;

//declare Local Definitions 
DefList: Def DefList    {if(!bisonsim)  {printf(YELLOW"     DefList:1\n"NONE);}}
    | /* empty */   {if(!bisonsim)  {printf(YELLOW"     DefList:2\n"NONE);}}
;
Def: Specifier DecList SEMI {if(!bisonsim)  {printf(YELLOW"     Def:1\n"NONE);}}
   | error SEMI {printf("Wrong Def:error SEMI\n");yyerrok;}
   | error Specifier{printf("Wrong Def :error Specifier\n");yyerrok;}
   | error Exp {printf("Wrong Def :error Exp\n");yyerrok;}
   | error RETURN {printf("Wrong Def:error RETURN\n");yyerrok;}
   | error IF {printf("Wrong Def:error IF\n");yyerrok;}
   | error WHILE {printf("Wrong Def:error WHILE\n");yyerrok;}
   | error RC {printf("Wrong Def:error RC\n");yyerrok;}
;

DecList: Dec    {if(!bisonsim)  {printf(YELLOW"     DecList:1\n"NONE);}}
    | Dec COMMA DecList {if(!bisonsim)  {printf(YELLOW"     DecList:2\n"NONE);}}                     
;

Dec: VarDec {if(!bisonsim)  {printf(YELLOW"     Dec:1\n"NONE);}}
    | VarDec ASSIGNOP Exp   {if(!bisonsim)  {printf(YELLOW"     Dec:2\n"NONE);}}
;

//declare Expressions
Exp:Exp ASSIGNOP Exp    {if(!bisonsim)  {printf(YELLOW"     Exp:1\n"NONE);}}
	|Exp AND Exp    {if(!bisonsim)  {printf(YELLOW"     Exp:2\n"NONE);}}
	|Exp OR Exp {if(!bisonsim)  {printf(YELLOW"     Exp:3\n"NONE);}}
	|Exp RELOP Exp  {if(!bisonsim)  {printf(YELLOW"     Exp:4\n"NONE);}}
    |Exp PLUS Exp   {if(!bisonsim)  {printf(YELLOW"     Exp:5\n"NONE);}}
    |Exp MINUS Exp  {if(!bisonsim)  {printf(YELLOW"     Exp:6\n"NONE);}}
    |Exp STAR Exp   {if(!bisonsim)  {printf(YELLOW"     Exp:7\n"NONE);}}
    |Exp DIV Exp    {if(!bisonsim)  {printf(YELLOW"     Exp:8\n"NONE);}}
    |LP Exp RP  {if(!bisonsim)  {printf(YELLOW"     Exp:9\n"NONE);}}
    |MINUS Exp  {if(!bisonsim)  {printf(YELLOW"     Exp:10\n"NONE);}}
    |NOT Exp    {if(!bisonsim)  {printf(YELLOW"     Exp:11\n"NONE);}}
    |ID LP Args RP  {if(!bisonsim)  {printf(YELLOW"     Exp:12\n"NONE);}}
    |ID LP RP   {if(!bisonsim)  {printf(YELLOW"     Exp:13\n"NONE);}}
    |Exp LB Exp RB  {if(!bisonsim)  {printf(YELLOW"     Exp:14\n"NONE);}}
    |Exp DOT ID {if(!bisonsim)  {printf(YELLOW"     Exp:15\n"NONE);}}
    |ID {if(!bisonsim)  {printf(YELLOW"     Exp:16\n"NONE);}}
    |INT    {if(!bisonsim)  {printf(YELLOW"     Exp:17\n"NONE);}}
    |FLOAT  {if(!bisonsim)  {printf(YELLOW"     Exp:18\n"NONE);}}
;

Args:Exp COMMA Args {if(!bisonsim)  {printf(YELLOW"     Args:1\n"NONE);}}
    |Exp    {if(!bisonsim)  {printf(YELLOW"     Args:2\n"NONE);}}
;
%%

void yyerror(const char *s) {
    if(yylineno!=error_line){
        printf ("Error type B at Line %d in position(%d-%d), \'%s\'\n", yylineno,yylloc.first_column,yylloc.last_column,yytext);
        error_line=yylineno;
    }
}
