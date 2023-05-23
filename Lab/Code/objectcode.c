#include"objectcode.h"
#include "basicblock.h"
extern FILE* mipsout;

static int arg_no=-1;
static int param_no=-1;

ObjStackNode objstack_head;
ObjStackNode cur_objstack;
VariableList varlist_head;
BasicBlock cur_bb;
Regs regs[32];

char* regName[]={
    "$zero","$at","$v0","$v1","$a0","$a1","$a2","$a3",
    "$t0","$t1","$t2","$t3","$t4","$t5","$t6","$t7",
    "$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7",
    "$t8","$t9","$k0","$k1","$gp","$sp","$s8","$ra"
};
void gen_objectcodes(){
    init_environments();
    BasicBlock cur_bb=bb_head;
    while(cur_bb){
        InterCodeList irnode=cur_bb->first;
        while(irnode&&(irnode!=cur_bb->last->next)){
            transfer_IR(irnode);
        }
        assert(irnode);
        spill_all();
        cur_bb=cur_bb->nextbb;
    }
}

void init_environments(){
    partition();
    init_varlist();
    objstack_head=init_stacknode(NULL,-1);
    fprintf(mipsout,".data\n");
    fprintf(mipsout,"_prompt: .asciiz \"Enter an interger:\"\n");
    fprintf(mipsout,"_ret: .asciiz \"\\n\"\n");
    fprintf(mipsout,".global main\n");
    fprintf(mipsout,".text\n");
}


void init_varlist(){
    varlist_head=(VariableList)malloc(sizeof(struct VariableList_));
    assert(varlist_head);
    varlist_head->var=NULL;
    varlist_head->prev=NULL;
    varlist_head->next=NULL;
    return;
}
Variable insert2varlist(Operand op){ //若op代表的var不在变量表中，加入。常数不是变量
    if(op->kind==OP_CONSTANT)
        return NULL;
    Variable var=find_var(op);
    if(var)
        return var;
    var=(Variable)malloc(sizeof(struct Variable_));
    assert(var);
    var->op=op;
    var->regno=-1;

    VariableList newnode=(VariableList)malloc(sizeof(struct VariableList_));
    newnode->var=var;
    newnode->next=varlist_head;
    newnode->prev=varlist_head->prev;
    varlist_head->prev->next=newnode;
    varlist_head->prev=newnode;
    return var;
}

void insert_var(InterCode ir){
    switch(ir->kind){
        case IR_STOREIN:
            insert2varlist(ir->u.two.left);
            insert2varlist(ir->u.two.right);
            break;
        case IR_RETURN:
            if(ir->u.one->kind!=OP_CONSTANT)
                assert(find_var(ir->u.one));
            break;
        case IR_PARAM:
        case IR_ARG:
            insert2varlist(ir->u.one);
            break;
        case IR_ASSIGN:
            insert2varlist(ir->u.two.left);
            if(ir->u.two.right->kind!=OP_CONSTANT)
                assert(find_var(ir->u.two.right));
            break;
        case IR_ADD:
        case IR_SUB:
        case IR_MUL:
        case IR_DIV:
            insert2varlist(ir->u.three.result);
            if(ir->u.three.op1->kind!=OP_CONSTANT)
                assert(find_var(ir->u.three.op1));
            if(ir->u.three.op2->kind!=OP_CONSTANT)
                assert(find_var(ir->u.three.op2));
            break;

        default:
            assert(0);
    }
}

Variable find_var(Operand op){
    VariableList temp=varlist_head->next;
    while(temp!=NULL){
        if(temp->var->op==op){
            return temp->var;
        }
        temp=temp->next;
    }
    return NULL;
}

ObjStackNode init_stacknode(char *funct_name,int paramnum){
    ObjStackNode objstack=(ObjStackNode)malloc(sizeof(struct ObjStackNode_));
    assert(objstack);
    objstack->functname=funct_name;
    objstack->paramnum=paramnum;
    objstack->stacksize=0;
    objstack->prev=NULL;
    objstack->next=NULL;
    cur_objstack=objstack;
    return objstack;
}

void push_objstack(char *funct_name,int paramnum){
    ObjStackNode newnode=init_stacknode(funct_name,paramnum);

    if(objstack_head->next!=NULL){
        objstack_head->next->prev=newnode;
    }
    objstack_head->next=newnode;
    return;
}

void pop_objstack(){
    ObjStackNode temp=objstack_head->next;
    if(temp==NULL){
        return;
    }
    objstack_head->next=temp->next;
    if(temp->next!=NULL){
        temp->next->prev=objstack_head;
    }
    cur_objstack=objstack_head->next;
    free(temp);
    return;
}

ObjStackNode find_objstack(char* funct_name){
    ObjStackNode temp=objstack_head->next;
    while(temp!=NULL){
        if(strcmp(temp->functname,funct_name)==0){
            return temp;
        }
        temp=temp->next;
    }
    return NULL;
}

void print_objstack(){
    ObjStackNode temp=objstack_head->next;
    while(temp!=NULL){
        printf("functname:%s stackcnt:%d\n",temp->functname,temp->stacksize);
        temp=temp->next;
    }
    return;
}

void init_regs(){
    for(int i=0;i<32;i++){
        regs[i].state=UNUSED;
        regs[i].var=NULL;
    }
    return;
}

void free_reg(int reg_no){
    assert(regs[reg_no].state==USED);
    regs[reg_no].state=UNUSED;
    regs[reg_no].var=NULL;
    return;
}



void spill_reg(int reg_no){
    assert(regs[reg_no].state==USED);
    Variable var=regs[reg_no].var;
    assert(var);
    fprintf(mipsout,"  addi $sp, $sp, -4");
    fprintf(mipsout,"  sw %s, 0($sp)\n",regName[reg_no]);
    cur_objstack->stacksize++;
    var->state=INSTACK;
    var->offset=-(cur_objstack->stacksize);
    free_reg(reg_no);
    return;
}

void spill_all(){
    for(int regno=0;regno<32;regno++){
        if(regs[regno].state==USED)
            spill_reg(regno);
    }
    return;
}

int allocate_reg(InterCodeList irnode,Variable var){ //t0-t9全满时使用
    for(int regno=t0;regno<=t9;regno++){
        if(active(irnode,regs[regno].var->op)){
            spill_reg(regno);
            regs[regno].var=var;
            return regno;
        }
    }

    //在该基本块内全会继续使用，则比较active distance
    int max_distance=-1;
    int maxdis_regno=-1;
    for(int regno=t0;regno<=t9;regno++){
        int cur_distance=active_distance(irnode,regs[regno].var->op);
        if(cur_distance<max_distance){
            max_distance=cur_distance;
            maxdis_regno=regno;
        }
    }
    spill_reg(maxdis_regno);
    regs[maxdis_regno].var=var;
    return maxdis_regno;  
}

bool active_global(InterCodeList irnode,Operand op){
    InterCodeList cur_irnode=irnode->next;
    while(cur_irnode!=irlist_head){
        InterCode ir=irnode->code;
        switch(ir->kind){
            case IR_PARAM:
            case IR_ARG:
            case IR_READ:
            case IR_WRITE:
            case IR_RETURN:
            case IR_GETADDR:
            case IR_CALL:
                if(op==ir->u.one)
                    return 1;
            case IR_ASSIGN:
            case IR_GETVAL:
            case IR_STOREIN:
                if(op==ir->u.two.left)
                    return 1;
                else if(op==ir->u.two.right)
                    return 1;
            case IR_ADD:
            case IR_SUB:
            case IR_MUL:
            case IR_DIV:
                if((op==ir->u.three.result)||(op==ir->u.three.op1)||(op==ir->u.three.op2))
                    return 1;
            default:
                break;
        }
        irnode=irnode->next;
    }
    assert(irnode==irlist_head);
    return 0;
}

bool active(InterCodeList irnode,Operand op){ //irnode是当前ir
    InterCodeList irnode_cur=cur_bb->last;
    while(irnode_cur!=irnode&&irnode_cur!=irlist_head){
        irnode_cur=irnode_cur->prev;
        InterCode ir=irnode_cur->code;
        switch(ir->kind){
            case IR_PARAM:
            case IR_ARG:
            case IR_READ:
            case IR_WRITE:
            case IR_RETURN:
            case IR_GETADDR:
            case IR_CALL:
                if(op==ir->u.one)
                    return 1;
            case IR_ASSIGN:
            case IR_GETVAL:
            case IR_STOREIN:
                if(op==ir->u.two.left)
                    return 1;
                else if(op==ir->u.two.right)
                    return 1;
            case IR_ADD:
            case IR_SUB:
            case IR_MUL:
            case IR_DIV:
                if((op==ir->u.three.result)||(op==ir->u.three.op1)||(op==ir->u.three.op2))
                    return 1;
            default:
                break;
        }
    }
    assert(irnode_cur==irnode);
    return 0;
}

int active_distance(InterCodeList irnode,Operand op){
    int distance=0;
    while(irnode!=cur_bb->last->next){
        InterCode ir=irnode->code;
        switch(ir->kind){
            case IR_PARAM:
            case IR_ARG:
            case IR_READ:
            case IR_WRITE:
            case IR_RETURN:
            case IR_GETADDR:
            case IR_CALL:
                if(op==ir->u.one)
                    return distance;
            case IR_ASSIGN:
            case IR_GETVAL:
            case IR_STOREIN:
                if(op==ir->u.two.left)
                    return distance;
                else if(op==ir->u.two.right)
                    return distance;
            case IR_ADD:
            case IR_SUB:
            case IR_MUL:
            case IR_DIV:
                if((op==ir->u.three.result)||(op==ir->u.three.op1)||(op==ir->u.three.op2))
                    return distance;
            default:
                distance++;
        }
        irnode=irnode->next;
    }
    assert(0);
}

int get_reg(Operand op,bool inreg,InterCodeList irnode){
    int regno=-1;
    Variable var=find_var(op);
    assert(var);
    if(inreg){
        if((var->regno==-1)||(regs[var->regno].state==UNUSED)){
            printf("Error: Operand %s not in register\n",var->op->name);
            assert(0);
        }
        regno=var->regno;
    }
    else{ //可能已在可能不在reg中
        if(var->regno>=0){ //还在寄存器中
            assert(regs[var->regno].state==USED);
            regno=var->regno;
        }
        else{
            for(int r=t0;r<=t9;r++){
                if(regs[r].state==UNUSED){
                    regs[r].state=USED;
                    regs[r].var=var;
                    var->regno=r;
                    regno=r;
                }
            }
            if(regno==-1)
                regno=allocate_reg(irnode,var);

            assert(regno!=-1);
            fprintf(mipsout,"  lw %s, %d($fp)\n",regName[regno],var->offset);
        }
    }
    assert(regno!=-1);
    if(!active_global(irnode,var->op)){
        free_reg(regno);
        var->regno=-1;
    }
    return regno;
}

void transfer_IR(InterCodeList irnode){
    InterCode ir=irnode->code;
    insert_var(ir);
    switch(ir->kind){
        case IR_LABEL:
            fprintf(mipsout,"%s:\n",ir->u.one->name);
            break;
        case IR_FUNCTIONNAME:
            fprintf(mipsout,"%s:\n",ir->u.one->name);
            push_objstack(ir->u.one->function_field->name,ir->u.one->function_field->type->u.function.paramnum);
            param_no=-1;
            break;
        case IR_CALL:
            Operand funct_op=ir->u.one;
            assert(arg_no==funct_op->function_field->type->u.function.paramnum);
            transfer_IR_CALL(irnode);
            arg_no=-1;
            break;
        case IR_PARAM:
            if(param_no==-1)
                param_no=0;
            transfer_IR_PARAM(ir,param_no);
            param_no++;
            break;
        case IR_ARG:
            int paramnum=ir->u.one->function_field->type->u.function.paramnum;
            assert(paramnum>=0);
            if(arg_no==-1){
                arg_no=0;
                fprintf(mipsout,"  addi $sp, $sp, -%d\n",(paramnum+2)*4);
                for(int i=0;i<paramnum;i++){
                    if(regs[i+a0].state==USED){ 
                        Variable ori_a_var=regs[i+a0].var;
                        ori_a_var->state=INSTACK;
                        ori_a_var->offset=i+paramnum-2;
                        fprintf(mipsout,"  sw %s, %d($sp)\n",regName[i+a0],(i+paramnum-2)*4); //参数寄存器入栈
                    }
                }
            }
            transfer_IR_ARG(irnode);
            arg_no++;
        case IR_RETURN:
            if(ir->u.one->kind==OP_CONSTANT)
                fprintf(mipsout,"  li $v0, %d\n",ir->u.one->number);
            else
                fprintf(mipsout,"  move $v0, %s\n",regName[get_reg(ir->u.one,1,irnode)]);
            fprintf(mipsout,"  jr $ra\n");
            pop_objstack();
            break;
        case IR_READ:
            transfer_IR_READ(ir);
            break;
        case IR_WRITE:
            transfer_IR_WRITE(ir);
            break;
        case IR_GOTO:
            fprintf(mipsout,"  j %s\n",ir->u.one->name);
            return;
        case IR_IFGOTO:
            transfer_IR_IFGOTO(irnode);
            break;
        case IR_ASSIGN:
            transfer_IR_ASSIGN(irnode);
            break;
        case IR_ADD:
        case IR_SUB:
        case IR_MUL:
        case IR_DIV:
            transfer_IR_CAL(irnode);
        case IR_GETADDR:    //无结构体和数组出现
        case IR_DEC:
            assert(0);
    }
}




void transfer_IR_PARAM(InterCode ir,int param_no){
    Variable var=find_var(ir->u.one);
    if(param_no<4){
        var->state=INREG;
        var->regno=a0+param_no;
    }
    else{
        var->state=INSTACK;
        var->offset=param_no-2;
    }
    return;
}

void transfer_IR_CALL(InterCodeList irnode){
    InterCode ir=irnode->code;
    //调用前
    // 保存返回地址
    fprintf(mipsout, "  addi $sp, $sp, -%d\n",4);
    fprintf(mipsout, "  sw $ra, 4($sp)\n");
    fprintf(mipsout,"  sw $fp, 0($sp)\n");
     fprintf(mipsout, "  move $fp, $sp\n");

    // 调用函数
    fprintf(mipsout,"  jal %s\n",ir->u.two.right->name);

    //调用后
    // 恢复寄存器和返回地址
    fprintf(mipsout,"  lw $sp, $fp\n");
    fprintf(mipsout, "  lw $ra, 4($sp)\n");
    fprintf(mipsout, "  addi $sp, $sp, %d\n",(ir->u.one->function_field->type->u.function.paramnum+2)*4);

    fprintf(mipsout, "  move %s, $v0\n", regName[get_reg(ir->u.two.left,0,irnode)]);

    return;
}

void transfer_IR_ARG(InterCodeList irnode){
    InterCode ir=irnode->code;
    Operand arg_op=ir->u.one;
    Variable var=find_var(arg_op); //原参数并没有真的移动位置。
    if(arg_no<4) //将参数移动到对应参数寄存器
        switch(arg_op->kind){
            case OP_VARIABLE:
            case OP_TEMP:
                if(var->state==INREG){   
                    fprintf(mipsout,"  move %s, %s\n",regName[a0+arg_no],regName[get_reg(arg_op,1,irnode)]);
                }
                else{
                    fprintf(mipsout,"  lw %s, -%d($fp)\n",regName[a0+arg_no],var->offset);
                }
                break;
            case OP_CONSTANT:
                fprintf(mipsout,"  li %s, %d\n",regName[a0+arg_no],arg_op->number);
                break;
            default:
                assert(0);
        }
    else{ //将参数保存到栈中
        switch(arg_op->kind){
            case OP_VARIABLE:
            case OP_TEMP:
                if(var->state==INREG){  
                    fprintf(mipsout,"  sw %s, %d($sp)\n",regName[get_reg(arg_op,1,irnode)],arg_no-2);
                }
                else{
                    fprintf(mipsout,"  lw %s, -%d($fp)\n",regName[a0+arg_no],var->offset);
                }
                break;
            case OP_CONSTANT:
                fprintf(mipsout,"  li %s, %d\n",regName[a0+arg_no],arg_op->number);
                break;
            default:
                assert(0);
        }

    }
}

void transfer_IR_READ(InterCode ir){
    fprintf(mipsout,"  li $v0, 4\n");
    fprintf(mipsout,"  la $a0, _prompt\n");
    fprintf(mipsout,"  syscall\n");
    fprintf(mipsout,"  li $v0, 5\n");
    fprintf(mipsout,"  syscall\n");
    fprintf(mipsout,"  jr $ra\n");

    spill_all();
    return;
}

void transfer_IR_WRITE(InterCode ir){
    fprintf(mipsout,"  li $v0, 1\n");
    fprintf(mipsout,"  syscall\n");
    fprintf(mipsout,"  li $v0, 4\n");
    fprintf(mipsout,"  la $a0, _ret\n");
    fprintf(mipsout,"  syscall\n");
    fprintf(mipsout,"  move $v0, $0\n");
    fprintf(mipsout,"  jr $ra\n");

    spill_all();
    return;
}


void transfer_IR_IFGOTO(InterCodeList irnode){
    InterCode ir=irnode->code;
    char* relop=ir->u.ifgoto.relop;
    Operand op1=ir->u.ifgoto.op1;
    Operand op2=ir->u.ifgoto.op2;
    Operand label=ir->u.ifgoto.label;

    if(strcmp(relop,"==")==0)
        fprintf(mipsout,"  beq %s, %s, %s\n",regName[get_reg(op1,1,irnode)],regName[get_reg(op2,1,irnode)],label->name);
    else if(strcmp(relop,"!=")==0)
        fprintf(mipsout,"  bne %s, %s, %s\n",regName[get_reg(op1,1,irnode)],regName[get_reg(op2,1,irnode)],label->name);
    else if(strcmp(relop,">")==0)
        fprintf(mipsout,"  bgt %s, %s, %s\n",regName[get_reg(op1,1,irnode)],regName[get_reg(op2,1,irnode)],label->name);
    else if(strcmp(relop,"<")==0)
        fprintf(mipsout,"  blt %s, %s, %s\n",regName[get_reg(op1,1,irnode)],regName[get_reg(op2,1,irnode)],label->name);
    else if(strcmp(relop,">=")==0)
        fprintf(mipsout,"  bge %s, %s, %s\n",regName[get_reg(op1,1,irnode)],regName[get_reg(op2,1,irnode)],label->name);
    else if(strcmp(relop,"<=")==0)
        fprintf(mipsout,"  ble %s, %s, %s\n",regName[get_reg(op1,1,irnode)],regName[get_reg(op2,1,irnode)],label->name);
    else
        assert(0);
    return;
}   


void  transfer_IR_ASSIGN(InterCodeList irnode){
    InterCode ir=irnode->code;
    switch(ir->u.two.right->kind){
        case OP_CONSTANT:
            fprintf(mipsout,"  li %s, %d\n",regName[get_reg(ir->u.two.left,0,irnode)],ir->u.two.right->number);
            break;
        case OP_VARIABLE:
        case OP_TEMP:
            fprintf(mipsout,"  move %s, %s\n",regName[get_reg(ir->u.two.left,0,irnode)],regName[get_reg(ir->u.two.right,1,irnode)]);
            break;
        default:
            assert(0);
    }
}

void transfer_IR_CAL(InterCodeList irnode){
    InterCode ir=irnode->code;
    Operand op1=ir->u.three.op1;
    Operand op2=ir->u.three.op2;
    Operand result=ir->u.three.result;
    assert(result->kind==OP_TEMP||result->kind==OP_VARIABLE);
    char* res_regname=regName[get_reg(result,0,irnode)];
    switch(ir->kind){
        case IR_ADD:
            if(op1->kind==OP_CONSTANT){
                assert(op2->kind==OP_TEMP||op2->kind==OP_VARIABLE);
                fprintf(mipsout,"  addi %s, %s, %d\n",res_regname,regName[get_reg(op2,1,irnode)],op1->number);
            }
            else if(op2->kind==OP_CONSTANT){
                assert(op1->kind==OP_TEMP||op1->kind==OP_VARIABLE);
                fprintf(mipsout,"  addi %s, %s, %d\n",res_regname,regName[get_reg(op1,1,irnode)],op2->number);
            }
            else{
                assert(op1->kind==OP_TEMP||op1->kind==OP_VARIABLE);
                assert(op2->kind==OP_TEMP||op2->kind==OP_VARIABLE);
                fprintf(mipsout,"  add %s, %s, %s",res_regname,regName[get_reg(op1,1,irnode)],regName[get_reg(op2,1,irnode)]);
            }
            break;
        case IR_SUB:
            if(op1->kind==OP_CONSTANT){
                assert(op2->kind==OP_TEMP||op2->kind==OP_VARIABLE);
                fprintf(mipsout,"  addi %s, %s, -%d\n",res_regname,regName[get_reg(op1,1,irnode)],op2->number);
                fprintf(mipsout,"  neg %s, %s\n",res_regname,res_regname);
            }
            else if(op2->kind==OP_CONSTANT){
                assert(op1->kind==OP_TEMP||op1->kind==OP_VARIABLE);
                fprintf(mipsout,"  addi %s, %s, -%d\n",res_regname,regName[get_reg(op1,1,irnode)],op2->number);
            }
            else{
                assert(op1->kind==OP_TEMP||op1->kind==OP_VARIABLE);
                assert(op2->kind==OP_TEMP||op2->kind==OP_VARIABLE);
                fprintf(mipsout,"  sub %s, %s, %s\n",res_regname,regName[get_reg(op1,1,irnode)],regName[get_reg(op2,1,irnode)]);
            }
            break;
        case IR_MUL:
            char *op1_regname=NULL;
            char *op2_regname=NULL;
            if(op1->kind==OP_CONSTANT)
                op1_regname=regName[get_reg(op1,0,irnode)];
            else
                op1_regname=regName[get_reg(op1,1,irnode)];
            if(op2->kind==OP_CONSTANT)
                op2_regname=regName[get_reg(op2,0,irnode)];
            else
                op2_regname=regName[get_reg(op2,1,irnode)];
            fprintf(mipsout,"  mul, %s, %s, %s\n",res_regname,op1_regname,op2_regname);
            break;
        case IR_DIV:
            op1_regname=NULL;
            op2_regname=NULL;
            if(op1->kind==OP_CONSTANT)
                op1_regname=regName[get_reg(op1,0,irnode)];
            else
                op1_regname=regName[get_reg(op1,1,irnode)];
            if(op2->kind==OP_CONSTANT)
                op2_regname=regName[get_reg(op2,0,irnode)];
            else
                op2_regname=regName[get_reg(op2,1,irnode)];
            fprintf(mipsout,"  div, %s, %s, %s\n",res_regname,op1_regname,op2_regname);
            fprintf(mipsout,"  mflo %s\n",res_regname);
            break;         
        default:
            assert(0);   
    }
    return;
}