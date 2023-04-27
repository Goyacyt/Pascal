#ifndef _SYMTAB_H_
#define _SYMTAB_H_

#include<stdio.h>
#include<string.h>
#include<assert.h>
#include <stdlib.h>
#include "tree.h"
#define HASHTAB_SIZE  0x3fff
#define STACK_SIZE  10000 //待定
typedef struct Type_* Type;
typedef struct FieldList_* FieldList;
typedef struct HashNode_* HashNode;
typedef struct DecFun_List_* DecFun_List;
struct Type_{
    enum{BASIC,ARRAY,STRUCTURE,STRUCTURE_NAME,FUNCTION} kind;
    union{
        enum {INT,FLOAT} basirc;//基本类型
        struct{
            Type elem;//嵌套
            int size;
        }array;//数组类型信息：元素类型+数组大小
           //结构体类型信息是一个链表
        FieldList structval;
        struct{
            int defok;
            FieldList structure;
        }structtype;
        struct{
            int paramnum;//形参个数
            enum {DECLARED,DEFINED} declare;//如果有声明没有定义就是DECLARE,只要有定义就是DEFILED
            Type ret;//返回值类型
            FieldList param;//形参列表
        }function;
    }u;
};
struct FieldList_{
    char* name; //域名
    Type type;  //域类型
    FieldList tail; //下一域
};//在结构体定义的时候，name为结构体的名字,type中的structure 指向一个新的fieldlist，从那里开始结构体里面变量的记录

struct HashNode_{
    int first_line;
    int stack_dep;
    FieldList value;
    HashNode slot_next;
    HashNode stack_next;
};


extern HashNode hash_tab[HASHTAB_SIZE+1];
extern HashNode stack[STACK_SIZE+1];


void init_hashtab();
void init_stack();
HashNode get(char* name);  //得到符号name对应的HashNode指针,查找出来是空指针就可以报错了
HashNode add_sym(FieldList value,int stack_dep,int line);  //将域结构为value的符号插入到符号表中，返回其对应的HashNode结构
void check_decfun();
int push_stack();
int pop_stack();
void add_ReadandWrite();
void Program(node* root);
void ExtDefList(node* root);
void ExtDef(node* root);
Type Specifier(node* root);
void ExtDecList(node* root,Type type);
FieldList VarDec(node* root,Type type,Type elemtype);
void FunDec(node* root,Type type,int declare);
int CompareParam(Type now,Type before);
char* OptTag(node* root);
char* Tag(node* root);
char* ID(node* root);
void CompSt(node* root,Type type);
Type StructSpecifier(node* root);
FieldList DefList(node* root,int stru);
FieldList Def(node* root,int stru);
FieldList DecList(node* root,Type type,int stru);
FieldList Dec(node* root,Type type,int str);
FieldList VarList(node* root);
FieldList ParamDec(node* root);
void StmtList(node* root,Type type);
void Stmt(node* root,Type type);
Type Exp(node* root);//可能需要返回一个变量的类型
FieldList Args(node* root);//返回实参的调用，检查调用是否正确
int CompareType(Type left,Type right);
void debug(char* s);
void eprintf(int error_number,int line,char* message);
void debugi(char* s,int d);

#endif
