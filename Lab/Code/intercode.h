#ifndef _INTERCODE_H_
#define _INTERCODE_H_
#include "symtab.h"
#include "tree.h"

typedef struct Operand_* Operand;
typedef struct InterCode_* InterCode;
typedef struct InterCodeList_* InterCodeList;
typedef struct ArgList_* ArgList;
//#define DE
InterCodeList irlist_head;
struct Operand_{
    enum{OP_VARIABLE,OP_CONSTANT,OP_TEMP,OP_LABEL,OP_FUNCTIONNAME,OP_ARRAYNAME,
    OP_STRUCTURENAME,OP_ADDRESS}kind;
    union{
        char *name;
        int no;//OP LABEL ADDRESS
        int number;//CONSTANT
    };
    struct{
        Type type;  //for array and structture
        int isparam;  //是不是函数参数
        int offset;
    }optype;
    
    //for functionname and arg
    FieldList function_field;
};

struct InterCode_{
    enum{IR_GETVAL,IR_GETADDR,IR_STOREIN,IR_LABEL,IR_ASSIGN,IR_ADD,IR_SUB,IR_MUL,IR_DIV,IR_GOTO,IR_IFGOTO,
    IR_FUNCTIONNAME,IR_RETURN,IR_DEC,IR_ARG,IR_CALL,IR_PARAM,IR_READ,IR_WRITE}kind;
    union{
        Operand one; //LABEL,FUNCTION,GOTO,RETURN,ARG,PARAM,READ,WRITE
        struct {Operand left,right;}two;  //ASSIGN,GETADDR,GETVALUE,PASSIGN,CALL
        struct{Operand result,op1,op2;}three;   //ADD,SUB,MUL,DIV
        struct{Operand var;int size;}dec;   //DEC
        struct{Operand op1,op2,label;   char relop[5];}ifgoto; //  IFGOTO:if op1 [relop] op2 goto label
    }u;
};

struct InterCodeList_{ //线性IR双向链表
    InterCode code;
    InterCodeList prev, next;
};

extern InterCodeList irlist_head;

struct ArgList_{
    Operand arg;
    ArgList next;
};
//extern ArgList arglist_head;


void init_irlist();
InterCodeList insert_ir(InterCode ir);
InterCodeList get_irlist(InterCode ir);
void del_ir(InterCode ir);
Operand gen_op(int kind,char *name,int number);
void print_op(Operand op);
InterCode gen_ir(int kind,Operand op1,Operand op2,Operand op3);
void print_ir(InterCode ir);
void print_irlist();
int get_size(Type type);
FieldList get_struname_field(node* root);
FieldList get_arrname_field(node* root);
void translate_Program(node* root);

void translate_ExtDefList(node* root);
void translate_ExtDef(node* root);
void translate_FunDec(node* root);
void translate_CompSt(node* root);
void translate_DefList(node* root);
void translate_Def(node* root);
void translate_DecList(node* root);
void translate_Dec(node* root);
Operand translate_VarDec(node* root);
void translate_StmtList(node* root);
void translate_Stmt(node* root);
void translate_Cond(node* root,Operand label_true,Operand label_false);
void translate_Exp(node* root,Operand place);
ArgList translate_Args(node* root,FieldList arg_field,FieldList funct_field);
void traverse_arglist(ArgList arglist);
#endif