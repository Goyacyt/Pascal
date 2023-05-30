#include <stdio.h>
#include"tree.h"
#include "symtab.h"
#include "intercode.h"
#include "optimize.h"
#include "basicblock.h"

int yylex();    //词法分析
int yyparse();  //对输入文件语法分析
void yyrestart(FILE *file); //重置yyin指针为开头
extern FILE* yyin;
FILE* irout;
int sim;
extern int yydebug;                // bison debug mode
int semantic_de;
int intercode_de;
int bisonsim;
int errorsim;
int error_line;
int haserror;
int syntax;
int sdep;
int intercode;
int optimize;
node* root;

int main(int argc, char** argv){
	yydebug=0;
	sim=1;		//简洁打印模式
	bisonsim=1;
    errorsim=0;
	haserror=0;
    syntax=0;
    semantic_de=0;
	intercode_de=0;
    error_line=0;//记录上一个出错的行数，如果当前错误仍然在这一行，就不要输出
	intercode=1;
	optimize=1;
	if(optimize){
		if(argc==1){
			return 1;
		}
		if(argc>1){
			if (!(yyin=fopen(argv[1],"r"))){
				perror(argv[1]);
				return 1;
			}
		}
		if(argc==2){
			irout=stdout;
		}else if(argc>2){
			if (!(irout=fopen(argv[2],"w"))){
				perror(argv[2]);
				return 1;
			}
		}
		parse(yyin);
		partition();
		LA();
	}else{
		if (argc==1){
			return 1;
		}
		if(argc>1){
			if (!(yyin=fopen(argv[1],"r"))){
				perror(argv[1]);
				return 1;
			}
			//printf("--------test file <%s>---------\n",argv[1]);
		}
		yyrestart(yyin);
		yyparse();
		fclose(yyin);
		if(haserror==0&&syntax==1)	{
			print_tree(root, 0);
		}
		Program(root);
		if(argc==2){
			irout=stdout;
		}else if(argc>2){
			if (!(irout=fopen(argv[2],"w"))){
				perror(argv[2]);
				return 1;
			}
		}
		//translate_Program(root);
	}
    return 0;
}
