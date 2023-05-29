#ifndef _OBJECTCODE_H_
#define _OBJECTCODE_H_
#define VSDEBUG
#include "basicblock.h"
typedef struct Variable_ *Variable;
typedef struct ObjStackNode_ *ObjStackNode;
typedef struct VariableList_ *VariableList;
typedef struct BlockVariables_ *BlockVariables;
typedef struct Regs_ Regs;

enum{zero,at,v0,v1,a0,a1,a2,a3,t0,t1,t2,t3,t4,t5,t6,t7,s0,s1,s2,s3,s4,s5,s6,s7,t8,t9,k0,k1,gp,sp,s8,ra};


struct Regs_{
    enum{UNUSED,USED}state;
    Variable var;
};

struct Variable_{
    Operand op;
    int offset; //相对于fp的偏移量
    int regno;
    enum{notINREG,INREG}state;
};

struct VariableList_{
    Variable var;
    VariableList prev;
    VariableList next;
}; //双向循环列表，头节点不保存数据。每次总在链尾插入

struct ObjStackNode_{
    char* functname;
    int paramnum;
    int stackdep;
    ObjStackNode prev;
    ObjStackNode next;
}; //单向非循环链表，头节点不保存数据。每次总在链头（头节点的下一个节点）插入



extern ObjStackNode objstack_head;
extern ObjStackNode cur_objstack;
extern VariableList varlist_head;
extern BasicBlock cur_bb;
extern char* regName[32];
extern Regs regs[32];

void print_ir2(InterCodeList irnode);
void print_op2(Operand op);
bool cmp_op(Operand op1,Operand op2);
void gen_objectcodes();
void init_environments();
void funct_init_varlist(InterCodeList functname_irnode);
Variable insert2varlist(Operand op,int param_no,int arrsize);
void insert_var(InterCodeList irnode);
Variable find_var(Operand op);
ObjStackNode init_stacknode(char *funct_name,int paramnum);
void push_objstack(char *funct_name,int paramnum);
void pop_objstack();
ObjStackNode find_objstack(char* funct_name);
void print_objstack();
void init_regs();
void free_reg(int reg_no);
void spill_reg(int reg_no);
void spill_all();
int allocate_reg(InterCodeList irnode,Variable var);
int active_distance(InterCodeList irnode,Variable var);
int get_reg(Operand op,InterCodeList irnode);
void spill_inactive_var(Operand op,InterCodeList irnode);
void transfer_IR(InterCodeList irnode);
void transfer_IR_CALL(InterCodeList irnode);
void transfer_IR_ARG(InterCodeList irnode,int arg_no);
void transfer_IR_READ(InterCodeList irnode);
void transfer_IR_WRITE(InterCodeList irnode);
void transfer_IR_IFGOTO(InterCodeList irnode);
void  transfer_IR_ASSIGN(InterCodeList irnode);
void transfer_IR_CAL(InterCodeList irnode);

#endif
