#ifndef _SYMTAB_H_
#define _SYMTAB_H_

#include<stdio.h>
#include<string.h>
#include<assert.h>
#include <stdlib.h>
#define HASHTAB_SIZE  0x3fff
#define STACK_SIZE  100 //待定
typedef struct Type_{
    enum{BASIC,ARRAY,STRUCTURE} kind;
    union{
        int basirc;//基本类型
        struct{
            struct Type* elem;
            int size;
        }array;//数组类型信息：元素类型+数组大小
        struct FieldList* structure;    //结构体类型信息是一个链表
    }u;
}Type;

typedef struct FieldList_{
    char* name; //域名
    Type* type;  //域类型
    struct FieldList* tail; //下一域
}FieldList;

typedef struct HashNode_{
    FieldList* value;
    struct HashNode_* slot_next;
    struct HashNode_* stack_next;
    int stack_dep;
}HashNode;

extern HashNode* hash_tab[HASHTAB_SIZE+1];
extern HashNode* stack[STACK_SIZE];


void init_hashtab();
void init_stack();
HashNode* get(char* name);  //得到符号name对应的HashNode指针
HashNode* add_sym(FieldList* value,int stack_dep);  //将域结构为value的符号插入到符号表中，返回其对应的HashNode结构
#endif