%{
    #define YYDEBUG 1
    #include<stdio.h>
    #include"tree.h"
    #include"lex.yy.c"
    #define YYSTYPE node*
    int yylex(void);
    void yyerror(const char* s);
    extern int yylineno;
    extern char* yytext;
    #define RED "\033[0;32;31m"
    #define NONE "\033[m"
    #define YELLOW "\033[1;33m"
    extern int bisonsim;
    extern node* root;
    extern int haserror;
    extern int error_line;
    extern int errorsim;
%}

%locations  //strange

//declare tokens
%token INT 
%token FLOAT
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
%type Program ExtDefList ExtDef ExtDecList

%type Specifier StructSpecifier OptTag Tag

%type CompSt StmtList Stmt

%type DefList Def DecList Dec

%type Exp Args


%%
//declare high level 
Program: ExtDefList {
    if(!bisonsim)  {printf(YELLOW"     Program:ExtDefList (%d)\n"NONE,@$.first_line);}
    $$=add_nonterminal("Program", @$.first_line, NOTTOKEN, 1,$1);
    root=$$;
}
;
ExtDefList:ExtDef ExtDefList    {if(!bisonsim)  {printf(YELLOW"     ExtDefList:ExtDef ExtDefList (%d)\n"NONE,@$.first_line);}  
        $$=add_nonterminal("ExtDefList", @$.first_line, NOTTOKEN,2,$1,$2);}
    | /*empty*/ {if(!bisonsim)  {printf(YELLOW"     ExtDefList:empty (%d)\n"NONE,@$.first_line);}   $$=NULL;}
;
ExtDef: Specifier ExtDecList SEMI   {if(!bisonsim)  {printf(YELLOW"     ExtDef:Specifier ExtDecList SEMI (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("ExtDef", @$.first_line, NOTTOKEN, 3,$1,$2,$3);}
    | Specifier SEMI    {if(!bisonsim)  {printf(YELLOW"     ExtDef:Specifier SEMI (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("ExtDef", @$.first_line, NOTTOKEN,2,$1,$2);}
    | Specifier FunDec CompSt   {if(!bisonsim)  {printf(YELLOW"     ExtDef:Specifier FunDec CompSt (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("ExtDef", @$.first_line, NOTTOKEN, 3,$1,$2,$3);} 
    | error SEMI {if (!errorsim) {printf("Wrong ExtDef\n");}yyerrok;}
    | error Specifier {if (!errorsim) {printf("Wrong ExtDef: error Specifier\n");}yyerrok;}
;               
ExtDecList: VarDec  {if(!bisonsim)  {printf(YELLOW"     ExtDecList:VarDec (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("ExtDecList", @$.first_line, NOTTOKEN, 1,$1);}
    | VarDec COMMA ExtDecList   {if(!bisonsim)  {printf(YELLOW"     ExtDecList:VarDec COMMA ExtDecList (%d)\n"NONE,@$.first_line);}
         $$=add_nonterminal("ExtDefList", @$.first_line, NOTTOKEN, 3,$1,$2,$3);}
;

//declare Specifiers
Specifier: TYPE     {if(!bisonsim)  {printf(YELLOW"     Specifier:TYPE (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("Specifier", @$.first_line, NOTTOKEN, 1,$1);}
    | StructSpecifier   {if(!bisonsim)  {printf(YELLOW"     Specifier:StructSpecifier (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("Specifier", @$.first_line, NOTTOKEN, 1,$1);}
;
StructSpecifier: STRUCT OptTag LC DefList RC    {if(!bisonsim)  {printf(YELLOW"     StructSpecifier:STRUCT OptTag LC DefList RC (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("StructSpecifier", @$.first_line, NOTTOKEN, 5,$1,$2,$3,$4,$5);}
    | STRUCT Tag    {if(!bisonsim)  {printf(YELLOW"     StructSpecifier:STRUCT Tag (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("StructSpecifier", @$.first_line, NOTTOKEN, 2,$1,$2);}
   // |error RC {printf("Wrong StructSpecifier\n");yyerrok;}
;   

OptTag: ID  {if(!bisonsim)  {printf(YELLOW"     OptTag:ID (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("OptTag", @$.first_line, NOTTOKEN, 1,$1);}
    | /* empty */   {if(!bisonsim)  {printf(YELLOW"     OptTag:empty (%d)\n"NONE,@$.first_line);} $$=NULL;}
;
Tag: ID {if(!bisonsim)  {printf(YELLOW"     Tag:ID (%d)\n"NONE,@$.first_line);}
    $$=add_nonterminal("Tag", @$.first_line, NOTTOKEN, 1,$1);}
;

//decalre Declarators
VarDec: ID  {if(!bisonsim)  {printf(YELLOW"     VarDec:ID (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("VarDec", @$.first_line, NOTTOKEN, 1,$1);}
    | VarDec LB INT RB  {if(!bisonsim)  {printf(YELLOW"     VarDec:VarDec LB INT RB (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("VarDec", @$.first_line, NOTTOKEN, 4,$1,$2,$3,$4);}
//  | error RB {printf("Wrong VarDec\n");yyerrok;}
;

FunDec: ID LP VarList RP    {if(!bisonsim)  {printf(YELLOW"     FunDec:ID LP VarList RP (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("FunDec", @$.first_line, NOTTOKEN, 4,$1,$2,$3,$4);}
    | ID LP RP  {if(!bisonsim)  {printf(YELLOW"     FunDec:ID LP RP (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("FunDec", @$.first_line, NOTTOKEN, 3,$1,$2,$3);}
    | error RP {if (!errorsim) {printf("Wrong FunDec\n");}yyerrok;}
;
VarList: ParamDec COMMA VarList {if(!bisonsim)  {printf(YELLOW"     VarList:ParamDec COMMA VarList (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("VarList", @$.first_line, NOTTOKEN, 3,$1,$2,$3);}
    | ParamDec  {if(!bisonsim)  {printf(YELLOW"     VarList:ParamDec (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("VarList", @$.first_line, NOTTOKEN, 1,$1);}
;
ParamDec: Specifier VarDec {if(!bisonsim)  {printf(YELLOW"     ParamDec:Specifier VarDec (%d)\n"NONE,@$.first_line);}
    $$=add_nonterminal("ParamDec", @$.first_line, NOTTOKEN, 2,$1,$2);}
;

//declare Statements
CompSt: LC DefList StmtList RC          {if(!bisonsim)  {printf(YELLOW"     CompSt:LC DefList StmtList RC (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("CompSt", @$.first_line, NOTTOKEN, 4,$1,$2,$3,$4);} 
   // | error RC  {printf("Wrong ComSt\n");yyerrok;}
;
StmtList: Stmt StmtList     {if(!bisonsim)  {printf(YELLOW"     StmtList:Stmt StmtList (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("StmtList", @$.first_line, NOTTOKEN, 2,$1,$2);}
    | /* empty */   {if(!bisonsim)  {printf(YELLOW"     StmtList:empty (%d)\n"NONE,@$.first_line);}    $$=NULL;}
;
Stmt: Exp SEMI  {if(!bisonsim)  {printf(YELLOW"     Stmt:Exp SEMI (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("Stmt", @$.first_line, NOTTOKEN, 2,$1,$2);}
    | CompSt    {if(!bisonsim)  {printf(YELLOW"     Stmt:CompSt (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("Stmt", @$.first_line, NOTTOKEN, 1,$1);}
    | RETURN Exp SEMI    {if(!bisonsim)  {printf(YELLOW"     Stmt:RETURN Exp SEMI (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("Stmt", @$.first_line, NOTTOKEN, 3,$1,$2,$3);}
    | IF LP Exp RP Stmt %prec LOWER_THAN_ELSE {if(!bisonsim)  {printf(YELLOW"     Stmt:IF LP Exp RP Stmt LOWER_THAN_ELSE (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("Stmt", @$.first_line, NOTTOKEN, 5,$1,$2,$3,$4,$5);}
    | IF LP Exp RP Stmt ELSE Stmt   {if(!bisonsim)  {printf(YELLOW"     Stmt:IF LP Exp RP Stmt ELSE Stmt (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("Stmt", @$.first_line, NOTTOKEN, 7,$1,$2,$3,$4,$5,$6,$7);}         
    | WHILE LP Exp RP Stmt            {if(!bisonsim)  {printf(YELLOW"     Stmt:6WHILE LP Exp RP Stmt (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("Stmt", @$.first_line, NOTTOKEN, 5,$1,$2,$3,$4,$5);} 
    | error SEMI    {if (!errorsim) {printf("Wrong Stmt\n");}yyerrok;}                      
    | error Exp {if (!errorsim) {printf("Wrong Stmt :error Exp\n");}yyerrok;}
    | error RETURN {if (!errorsim) {printf("Wrong Stmt:error RETURN\n");}yyerrok;}
    | error IF {if (!errorsim) {printf("Wrong Stmt:error IF\n");}yyerrok;}
    | error WHILE {if (!errorsim) {printf("Wrong Stmt:error WHILE\n");}yyerrok;}
    | error RC {if (!errorsim) {printf("Wrong Stmt:error RC\n");}yyerrok;}
    | error Specifier {if (!errorsim) {printf("Wrong Stmt: error Specifier\n");}yyerrok;}
;

//declare Local Definitions 
DefList: Def DefList    {if(!bisonsim)  {printf(YELLOW"     DefList:Def DefList (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("DefList", @$.first_line, NOTTOKEN, 2,$1,$2);}
    | /* empty */   {if(!bisonsim)  {printf(YELLOW"     DefList:empty (%d)\n"NONE,@$.first_line);} $$=NULL;}
;
Def: Specifier DecList SEMI {if(!bisonsim)  {printf(YELLOW"     Def:Specifier DecList SEMI (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("Def", @$.first_line, NOTTOKEN, 3,$1,$2,$3);}
   | error SEMI {if (!errorsim) {printf("Wrong Def:semi exist\n");}yyerrok;}
   | error Specifier{if (!errorsim) {printf("Wrong Def :error Specifier\n");}yyerrok;}
   | error Exp {if (!errorsim) {printf("Wrong Def :error Exp\n");}yyerrok;}
   | error RETURN {if (!errorsim) {printf("Wrong Def:error RETURN\n");}yyerrok;}
   | error IF {if (!errorsim) {printf("Wrong Def:error IF\n");}yyerrok;}
   | error WHILE {if (!errorsim) {printf("Wrong Def:error WHILE\n");}yyerrok;}
   | error RC {if (!errorsim) {printf("Wrong Def:error RC\n");}yyerrok;}
;
DecList: Dec    {if(!bisonsim)  {printf(YELLOW"     DecList:Dec (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("DecList", @$.first_line, NOTTOKEN, 1,$1);}
    | Dec COMMA DecList {if(!bisonsim)  {printf(YELLOW"     DecList:Dec COMMA DecList (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("DecList", @$.first_line, NOTTOKEN, 3,$1,$2,$3);}                     
;
Dec: VarDec {if(!bisonsim)  {printf(YELLOW"     Dec:VarDec (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("Dec", @$.first_line, NOTTOKEN, 1,$1);}
    | VarDec ASSIGNOP Exp   {if(!bisonsim)  {printf(YELLOW"     Dec:VarDec ASSIGNOP Exp (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("Dec", @$.first_line, NOTTOKEN, 3,$1,$2,$3);}
;

//declare Expressions
Exp:Exp ASSIGNOP Exp    {if(!bisonsim)  {printf(YELLOW"     Exp:Exp ASSIGNOP Exp (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("Exp", @$.first_line, NOTTOKEN, 3,$1,$2,$3);}
	|Exp AND Exp    {if(!bisonsim)  {printf(YELLOW"     Exp:Exp AND Exp (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("Exp", @$.first_line, NOTTOKEN, 3,$1,$2,$3);}
	|Exp OR Exp {if(!bisonsim)  {printf(YELLOW"     Exp:Exp OR Exp (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("Exp", @$.first_line, NOTTOKEN, 3,$1,$2,$3);}
	|Exp RELOP Exp  {if(!bisonsim)  {printf(YELLOW"     Exp:Exp RELOP Exp (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("Exp", @$.first_line, NOTTOKEN, 3,$1,$2,$3);}
    |Exp PLUS Exp   {if(!bisonsim)  {printf(YELLOW"     Exp:Exp PLUS Exp (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("Exp", @$.first_line, NOTTOKEN, 3,$1,$2,$3);}
    |Exp MINUS Exp  {if(!bisonsim)  {printf(YELLOW"     Exp:Exp MINUS Exp (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("Exp", @$.first_line, NOTTOKEN, 3,$1,$2,$3);}
    |Exp STAR Exp   {if(!bisonsim)  {printf(YELLOW"     Exp:Exp STAR Exp (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("Exp", @$.first_line, NOTTOKEN, 3,$1,$2,$3);}
    |Exp DIV Exp    {if(!bisonsim)  {printf(YELLOW"     Exp:Exp DIV Exp (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("Exp", @$.first_line, NOTTOKEN, 3,$1,$2,$3);}
    |LP Exp RP  {if(!bisonsim)  {printf(YELLOW"     Exp:LP Exp RP (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("Exp", @$.first_line, NOTTOKEN, 3,$1,$2,$3);}
    |MINUS Exp  {if(!bisonsim)  {printf(YELLOW"     Exp:MINUS Exp (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("Exp", @$.first_line, NOTTOKEN, 2,$1,$2);}
    |NOT Exp    {if(!bisonsim)  {printf(YELLOW"     Exp:NOT Exp (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("Exp", @$.first_line, NOTTOKEN, 2,$1,$2);}
    |ID LP Args RP  {if(!bisonsim)  {printf(YELLOW"     Exp:ID LP Args RP (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("Exp", @$.first_line, NOTTOKEN, 4,$1,$2,$3,$4);}
    |ID LP RP   {if(!bisonsim)  {printf(YELLOW"     Exp:ID LP RP (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("Exp", @$.first_line, NOTTOKEN, 3,$1,$2,$3);}
    |Exp LB Exp RB  {if(!bisonsim)  {printf(YELLOW"     Exp:Exp LB Exp RB (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("Exp", @$.first_line, NOTTOKEN, 4,$1,$2,$3,$4);}
    |Exp DOT ID {if(!bisonsim)  {printf(YELLOW"     Exp:Exp DOT ID (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("Exp", @$.first_line, NOTTOKEN, 3,$1,$2,$3);}
    |ID {if(!bisonsim)  {printf(YELLOW"     Exp:ID (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("Exp", @$.first_line, NOTTOKEN, 1,$1);}
    |INT    {if(!bisonsim)  {printf(YELLOW"     Exp:INT (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("Exp", @$.first_line, NOTTOKEN, 1,$1);}
    |FLOAT  {if(!bisonsim)  {printf(YELLOW"     Exp:FLOAT (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("Exp", @$.first_line, NOTTOKEN, 1,$1);}
;

Args:Exp COMMA Args {if(!bisonsim)  {printf(YELLOW"     Args:Exp COMMA Args (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("Args", @$.first_line, NOTTOKEN, 3,$1,$2,$3);}
    |Exp    {if(!bisonsim)  {printf(YELLOW"     Args:Exp (%d)\n"NONE,@$.first_line);}
        $$=add_nonterminal("Exp", @$.first_line, NOTTOKEN, 1,$1);}
;
%%

void yyerror(const char *s) {
    if (yylineno!=error_line){
        printf ("Error type B at Line %d: in position(%d-%d), \'%s\' %s \n", yylineno,yylloc.first_column,yylloc.last_column,yytext,s);
        error_line=yylineno;
    }
    haserror=1;
}
