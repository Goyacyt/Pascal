#ifndef _SYMTAB_H_
#define _SYMTAB_H_

#include<stdio.h>
#include<string.h>
#include<assert.h>
#include <stdlib.h>
#define HASHTAB_SIZE  0x3fff
#define STACK_SIZE  100 //待定
typedef struct Type_* Type;
typedef struct FieldList_* FieldList;
typedef struct HashNode_* HashNode;
typedef struct Type_{
    enum{BASIC,ARRAY,STRUCTURE} kind;
    union{
        int basirc;//基本类型
        struct{
            struct Type* elem;//嵌套
            int size;
        }array;//数组类型信息：元素类型+数组大小
        struct FieldList structure;    //结构体类型信息是一个链表
    }u;
};

typedef struct FieldList_{
    char* name; //域名
    Type* type;  //域类型
    struct FieldList tail; //下一域
};

typedef struct HashNode_{
    FieldList value;
    struct HashNode slot_next;
    struct HashNode stack_next;
    int stack_dep;
};

extern HashNode hash_tab[HASHTAB_SIZE+1];
extern HashNode stack[STACK_SIZE];


void init_hashtab();
void init_stack();
HashNode get(char* name);  //得到符号name对应的HashNode指针,查找出来是空指针就可以报错了
HashNode add_sym(FieldList value,int stack_dep);  //将域结构为value的符号插入到符号表中，返回其对应的HashNode结构
void Program(node* node);
void ExtDefList(node* node);
void ExtDef(node* node);
Type Specifier(node* node);
void ExtDecList(node* node,Type type);
Type VarDec(node* node,Type type);
void FunDec(node* node);
void CompSt(node* node,Type type);
Type StructSpecifier(node* node);
FieldList DefList(node* node);
Type Def(node* node);
void DecList(node* node,Type type);
void Dec(node* node,Type type);
FieldList VarList(node* node);
Type ParamDec(node* node);
void StmtList(node* node);
void Stmt(node* node);
Type Exp(node* node);//可能需要返回一个变量的类型
FieldList Args(node* node);//返回实参的调用，检查调用是否正确
#endif
