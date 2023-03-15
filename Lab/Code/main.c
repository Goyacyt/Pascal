#include <stdio.h>

int yylex();    //词法分析
int yyparse();  //对输入文件语法分析
void yyrestart(FILE *file); //重置yyin指针为开头
extern FILE* yyin;
int sim;
extern int yydebug;                // bison debug mode
int bisonsim;


int main(int argc, char** argv){
	yydebug=0;
	sim=0;		//简洁打印模式
	bisonsim=0;
	if (argc==1){
		return 1;
	}
	if(argc>1){
		if (!(yyin=fopen(argv[1],"r"))){
			perror(argv[1]);
			return 1;
		}
		printf("--------test file <%s>---------\n",argv[1]);
	}
    yyrestart(yyin);
    yyparse();
    fclose(yyin);
    return 0;
}
