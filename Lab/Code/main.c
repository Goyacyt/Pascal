#include <stdio.h>

int yylex();    //词法分析
int yyparse();  //对输入文件语法分析
void yyrestart(FILE *file); //重置yyin指针为开头
extern FILE* yyin;

int main(int argc, char** argv){
	if (argc==1){
		return 1;
	}
	if(argc>1){
		if (!(yyin=fopen(argv[1],"r"))){
			perror(argv[1]);
			return 1;
		}
	}
    yyrestart(yyin);
    yyparse();
    fclose(yyin);
    return 0;
}