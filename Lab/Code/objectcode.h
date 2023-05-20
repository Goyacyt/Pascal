#ifndef _OBJECTCODE_H_
#define _OBJECTCODE_H_
#include "intercode.h"
typedef struct Variable_ *Variable;
typedef struct ObjStackNode_ *ObjStackNode;
typedef struct VariableList_ *VariableList;
typedef struct Regs_ Regs;

Regs regs[32];
ObjStackNode objstack_head;
VariableList varlist_head;
enum{zero,at,v0,v1,a0,a1,a2,a3,t0,t1,t2,t3,t4,t5,t6,t7,s0,s1,s2,s3,s4,s5,s6,s7,t8,t9,k0,k1,gp,sp,s8,ra};
char* regName[32]={
    "$zero","$at","$v0","$v1","$a0","$a1","$a2","$a3",
    "$t0","$t1","$t2","$t3","$t4","$t5","$t6","$t7",
    "$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7",
    "$t8","$t9","$k0","$k1","$gp","$sp","$s8","$ra"
};

struct Regs_{
    enum{UNUSED,USED}state;
    Variable var;
};

struct Variable_{
    Operand op;
    int offset; //相对于fp的偏移量
    int regno;
    enum{INSTACK,INREG}state;
};

struct VariableList_{
    Variable var;
    VariableList prev;
    VariableList next;
};

struct ObjStackNode_{
    Variable var;
    ObjStackNode prev;
    ObjStackNode next;
};

#endif
