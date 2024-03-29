#ifndef _TREE_H_
#define _TREE_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define YYSTYPE node*

//#define NONE "\033[m"
//#define RED "\033[0;32;31m"
#define BLUE "\033[0;32;34m"
#define GREEN "\033[0;32;32m"
#define YELLOW "\033[1;33m"
#define NONE
#define RED

typedef struct NODE{
    char name[32];
    int first_line;
    enum TYPE{OTHERTOKEN,NOTTOKEN,TYPE_ID,TYPE_TYPE,TYPE_INT,TYPE_FLOAT,TYPE_RELOP} type;
    int son_num;
    union{
        char id_val[32];
        char type_val[32];
        int int_val;
        float float_val;
        char relop_val[5];
    }val;
    struct NODE* bro;
    struct NODE* son;
}node;
node* add_token(char* name, int type, void* val);
node* add_nonterminal(char* name, int first_line, int type, int son_num,...);
void print_tree(node* cur_node, int dep);
#endif
