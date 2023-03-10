%{
#include<stdio.h>
%}

/*declared types*/
%union{
	int type_int;
 
	float type_float;
}
/*declared tokens*/


/*declared non-terminal*/


%%
Exp:Exp ASSIGNOP Exp
	|Exp ADN Exp
	|Exp OR Exp
	|Exp RELOP Exp
    |Exp PLUS Exp
    |Exp MINUS Exp
    |Exp STAR Exp
    |Exp DIV Exp
    |LP Exp RP
    |MINUS Exp
    |NOT Exp
    |ID LP Args RP
    |ID LP RP
    |Exp LB Exp RB
    |Exp DOT ID
    |ID
    |INT
    |FLOAT
    ;
Args:Exp COMMA Args
    |Exp
    ;
