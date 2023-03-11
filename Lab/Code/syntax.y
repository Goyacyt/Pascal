%{
    #define YYDEBUG 1
    #include<stdio.h>
    #include"lex.yy.c"
    int yylex(void);
    void yyerror(const char* s);
    extern int yylineno;
    extern char* yytext;
%}

%locations  //strange

//declare types
%union{
    int type_int;
    float type_float;
    double type_double;
}

//declare tokens
%token INT 
%token EXPRART FLOAT
%token ID SEMI COMMA ASSIGNOP RELOP PLUS MINUS STAR DIV AND OR DOT NOT TYPE LP RP LB RB LC RC STRUCT RETURN IF ELSE WHILE

//declare associativity and piority for tokens
%right ASSIGNOP
%left  AND OR
%left  RELOP
%left  PLUS MINUS
%left  STAR DIV
%right NOT
%right NEG  //  define for 负号,咋用呢...
%left  DOT LP RP LB RB
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

/*
//declare non-terminals
%type <type_double> Program ExtDefList ExtDef ExtDecList

%type <type_double> Specifier StructSpecifier OptTag Tag

%type <type_double> CompSt StmtList Stmt

%type <type_double> DefList Def DecList Dec

%type <type_double> Exp Args
*/

%%
//declare high level 
Program: ExtDefList {}
;
ExtDefList:ExtDef ExtDefList    {}
    | /*empty*/ {}
;
ExtDef: Specifier ExtDecList SEMI   {}
    | Specifier SEMI    {}
    | Specifier FunDec CompSt   {}
;               
ExtDecList: VarDec
    | VarDec COMMA ExtDecList   {}
;

//declare Specifiers
Specifier: TYPE     {}
    | StructSpecifier   {}
;
StructSpecifier: STRUCT OptTag LC DefList RC    {}
    | STRUCT Tag    {}
;   
OptTag: ID  {}
    | /* empty */   {}
;
Tag: ID {}
;

//decalre Declarators
VarDec: ID  {}
    | VarDec LB INT RB  {}
;
FunDec: ID LP VarList RP    {}
    | ID LP RP  {}
;
VarList: ParamDec COMMA VarList {}
    | ParamDec  {}
;
ParamDec : Specifier VarDec {}
;

//declare Statements
CompSt: LC DefList StmtList RC          {} 
    | error RC  {printf("Wrong ComSt: \n");yyerrok;}
;
StmtList: Stmt StmtList     {}
    | /* empty */   {}
;
Stmt: Exp SEMI  {}
    | CompSt    {}
    | RETURN Exp SEMI    {}
    | IF LP Exp RP Stmt %prec LOWER_THAN_ELSE {}
    | IF LP Exp RP Stmt ELSE Stmt   {}         
    | WHILE LP Exp RP Stmt            {} 
    | error SEMI    {printf("Wrong Stmt: \n");yyerrok;}                      
;

//declare Local Definitions 
DefList: Def DefList    {}
    | /* empty */   {}
;
Def: Specifier DecList SEMI {}
;
DecList: Dec    {}
    | Dec COMMA DecList {}                     
;
Dec: VarDec {}
    | VarDec ASSIGNOP Exp   {}
;

//declare Expressions
Exp:Exp ASSIGNOP Exp    {}
	|Exp AND Exp    {}
	|Exp OR Exp {}
	|Exp RELOP Exp  {}
    |Exp PLUS Exp   {}
    |Exp MINUS Exp  {}
    |Exp STAR Exp   {}
    |Exp DIV Exp    {}
    |LP Exp RP  {}
    |MINUS Exp  {}
    |NOT Exp    {}
    |ID LP Args RP  {}
    |ID LP RP   {}
    |Exp LB Exp RB  {}
    |Exp DOT ID {}
    |ID {}
    |INT    {}
    |FLOAT  {}
    |error RP   {printf("Wrong Exp: \n");yyerrok;}
;
Args:Exp COMMA Args {}
    |Exp    {}
;
%%

void yyerror(const char *s) {
    fprintf (stderr, "Error type B at Line %d in position(%d-%d), \'%s\'\n", yylineno,yylloc.first_column,yylloc.last_column,yytext);
}