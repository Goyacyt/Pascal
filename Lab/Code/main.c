#include <stdio.h>
#include"tree.h"
#include "symtab.h"
#include "intercode.h"
#include "objectcode.h"
#include "basicblock.h"

int yylex();    //词法分析
int yyparse();  //对输入文件语法分析
void yyrestart(FILE *file); //重置yyin指针为开头
extern FILE* yyin;
FILE* irout;
FILE* mipsout;

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
int objectcode;
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
	objectcode=1;
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
		if(objectcode){
			if(!(irout=fopen("/home/lyt/myfile/Pascal/Lab/TestTools/workdir/a.ir","w"))){
				perror("~/myfile/Pascal/Lab/TestTools/workdir/a.ir");
				return 1;
			}
			translate_Program(root);
			fclose(irout);
			if (!(mipsout=fopen("/home/lyt/myfile/Pascal/Lab/TestTools/workdir/a.s","w"))){
				perror("~/myfile/Pascal/Lab/TestTools/workdir/a.s");
				return 1;
			}
			gen_objectcodes();
			fclose(mipsout);
		}
		else{
			irout=stdout;
			translate_Program(root);
			fclose(irout);
		}
	}else if(argc>2){
		if(objectcode){
			if(!(irout=fopen("/home/lyt/myfile/Pascal/Lab/TestTools/workdir/a.ir","w"))){
				perror("~/myfile/Pascal/Lab/TestTools/workdir/a.ir");
				return 1;
			}
			translate_Program(root);
			fclose(irout);

			if (!(mipsout=fopen(argv[2],"w"))){
				perror(argv[2]);
				return 1;
			}
			gen_objectcodes();
			
			fclose(mipsout);
		}
		else{
			if (!(irout=fopen(argv[2],"w"))){
				perror(argv[2]);
				return 1;
			}
			translate_Program(root);
			fclose(irout);
		}
	}

    return 0;
}
