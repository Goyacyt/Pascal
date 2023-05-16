#include"objectcode.h"
extern FILE* mipsout;

void transfer_IR_GETVAL(InterCode ir){ //虽然其实应该根本不会出现
    Operand op1=ir->u.two.left;
    Operand op2=ir->u.two.right;
    Variable var1=find_var(op1);
    Variable var2=find_var(op1);
    int regno1=get_reg(op1,0);
    int regno2=get_reg(op2,1);
    fprintf(mipsout,"  lw %s,%d(%s)\n",regName[regno1],0,regName[regno2]);
    return;
}

void transfer_IR_PARAM(InterCode ir){

}

void transfer_IR_CALL(InterCode ir,int t1_s,int t2_s,int cnt_s,int arg_cnt){
    //调用前
    // 保存返回地址
    fprintf(mipsout, "  addi $sp, $sp, -%d\n",4);
    fprintf(mipsout, "  sw $ra, %d($sp)\n",0);

    //按需保存其他寄存器


    // 调用函数
    fprintf(mipsout,"  jal %s\n",ir->u.two.right->name);

    //调用后
    // 恢复寄存器和返回地址
    fprintf(mipsout, "  lw $ra, %d($sp)\n",0);
    int temp=0;
    for(int regno=t0;regno<=t7;regno++){
        if(t1&(1<<(regno-t0))){
            fprintf(mipsout, "  lw %s, %d($sp)\n",regName[t0+temp],temp*4+4);
            temp++;
        }
    }
    for(int regno=t8;regno<=t9;regno++){
        if(t2&(1<<(regno-t8))){
            fprintf(mipsout, "  lw %s, %d($sp)\n",regName[t0+temp],temp*4+4);
            temp++;
        }
    }
    assert(cnt_s==temp);
    fprintf(mipsout, "  addi $sp, $sp, %d\n", 4/*ra*/ + (arg_cnt-4) * 4/*部分参数*/+cnt_s);

    fprintf(mipsout, "  move $%s, $v0\n", regName[get_reg(ir->u.two.left,0)]);

    return;
}

void transfer_IR_ARG(InterCode ir, int arg_no){
    if(arg_no<4){
        Operand arg_op=ir->u.one;
        switch(arg_op->kind){
            case OP_VARIABLE:
            case OP_TEMP:
                fprintf(mipsout,"  move %s, %s\n",regName[a0+arg_no],regName[get_reg(arg_op,0)]);
                break;
            case OP_CONSTANT:
                fprintf(mipsout,"  li %s, %d\n",regName[a0+arg_no],arg_op->number);
                break;
            case OP_LABEL:
            case OP_FUNCTIONNAME:
            case OP_ARRAYNAME:                
            case OP_STRUCTURENAME:
            case OP_ADDRESS:
            case OP_ADDRESS_LEFT:
                assert(0);
        }
    }
    else{
        fprintf(mipsout,"  addi $sp, $sp, -4\n");
        fprintf(mipsout,"  sw %s, %d($sp)\n",regName[get_reg(ir->u.one,0)],0);
    }
}

void transfer_IR_READ(InterCode ir){
    fprintf(mipsout,"  li $v0, 4\n");
    fprintf(mipsout,"  la $a0, _prompt\n");
    fprintf(mipsout,"  syscall\n");
    fprintf(mipsout,"  li $v0, 5\n");
    fprintf(mipsout,"  syscall\n");
    fprintf(mipsout,"  jr $ra\n");
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
    return;
}

void transfer_IR_PAR(InterCode ir,int param_num){
    Operand param_op=ir->u.one;
    if(param_num<4){
        switch(param_op->kind){
            case OP_VARIABLE:
            case OP_TEMP:
                fprintf(mipsout,"  move %s, %s\n",regName[4+param_num],regName[get_reg(ir->u.one,0)]);
                break;
            case OP_CONSTANT:
                fprintf(mipsout,"  li %s, %d\n",regName[4+param_num],param_op->number);
                break;
            default:
                assert(0);
        }
    }
    else{
        fprintf(mipsout,"  lw $t0, %d($sp)\n",param_num*4);
        fprintf(mipsout,"  sw $t0, %d($sp)\n",(param_num+1)*4);
    }
    return;
}


void transfer_IR_IFGOTO(InterCode ir){
    char* relop=ir->u.ifgoto.relop;
    Operand op1=ir->u.ifgoto.op1;
    Operand op2=ir->u.ifgoto.op2;
    Operand label=ir->u.ifgoto.label;

    if(strcmp(relop,"==")==0)
        fprintf(mipsout,"  beq %s, %s, %s\n",regName[get_reg(op1,1)],regName[get_reg(op2,1)],label->name);
    else if(strcmp(relop,"!=")==0)
        fprintf(mipsout,"  bne %s, %s, %s\n",regName[get_reg(op1,1)],regName[get_reg(op2,1)],label->name);
    else if(strcmp(relop,">")==0)
        fprintf(mipsout,"  bgt %s, %s, %s\n",regName[get_reg(op1,1)],regName[get_reg(op2,1)],label->name);
    else if(strcmp(relop,"<")==0)
        fprintf(mipsout,"  blt %s, %s, %s\n",regName[get_reg(op1,1)],regName[get_reg(op2,1)],label->name);
    else if(strcmp(relop,">=")==0)
        fprintf(mipsout,"  bge %s, %s, %s\n",regName[get_reg(op1,1)],regName[get_reg(op2,1)],label->name);
    else if(strcmp(relop,"<=")==0)
        fprintf(mipsout,"  ble %s, %s, %s\n",regName[get_reg(op1,1)],regName[get_reg(op2,1)],label->name);
    else
        assert(0);
    return;
}   


void  transfer_IR_ASSIGN(InterCode ir){
    switch(ir->u.two.right->kind){
        case OP_CONSTANT:
            fprintf(mipsout,"  li %s, %d\n",regs[get_reg(ir->u.two.left,0)],ir->u.two.right->number);
            break;
        case OP_VARIABLE:
        case OP_TEMP:
            fprintf(mipsout,"  move %s, %s\n",regs[get_reg(ir->u.two.left,0)],regs[get_reg(ir->u.two.right,1)]);
            break;
        default:
            assert(0);
    }
}

void transfer_IR_CAL(InterCode ir){
    Operand op1=ir->u.three.op1;
    Operand op2=ir->u.three.op2;
    Operand result=ir->u.three.result;
    assert(result->kind==OP_TEMP||result->kind==OP_VARIABLE);
    char* res_regname=regName[get_reg(result,0)];
    switch(ir->kind){
        case IR_ADD:
            if(op1->kind==OP_CONSTANT){
                assert(op2->kind==OP_TEMP||op2->kind==OP_VARIABLE);
                fprintf(mipsout,"  addi %s, %s, %d\n",res_regname,regName[get_reg(op2,1)],op1->number);
            }
            else if(op2->kind==OP_CONSTANT){
                assert(op1->kind==OP_TEMP||op1->kind==OP_VARIABLE);
                fprintf(mipsout,"  addi %s, %s, %d\n",res_regname,regName[get_reg(op1,1)],op2->number);
            }
            else{
                assert(op1->kind==OP_TEMP||op1->kind==OP_VARIABLE);
                assert(op2->kind==OP_TEMP||op2->kind==OP_VARIABLE);
                fprintf(mipsout,"  add %s, %S, %s",res_regname,regName[get_reg(op1,1)],regName[get_reg(op2,1)]);
            }
            break;
        case IR_SUB:
            if(op1->kind==OP_CONSTANT){
                assert(op2->kind==OP_TEMP||op2->kind==OP_VARIABLE);
                fprintf(mipsout,"  addi %s, %s, -%d\n",res_regname,regName[get_reg(op1,1)],op2->number);
                fprintf(mipsout,"  neg %s, %s\n",res_regname,res_regname);
            }
            else if(op2->kind==OP_CONSTANT){
                assert(op1->kind==OP_TEMP||op1->kind==OP_VARIABLE);
                fprintf(mipsout,"  addi %s, %s, -%d\n",res_regname,regName[get_reg(op1,1)],op2->number);
            }
            else{
                assert(op1->kind==OP_TEMP||op1->kind==OP_VARIABLE);
                assert(op2->kind==OP_TEMP||op2->kind==OP_VARIABLE);
                fprintf(mipsout,"  sub %s, %S, %s\n",res_regname,regName[get_reg(op1,1)],regName[get_reg(op2,1)]);
            }
            break;
        case IR_MUL:
            char *op1_regname=NULL;
            char *op2_regname=NULL;
            if(op1->kind==OP_CONSTANT)
                op1_regname=regName[get_reg(op1,0)];
            else
                op1_regname=regName[get_reg(op1,1)];
            if(op2->kind==OP_CONSTANT)
                op2_regname=regName[get_reg(op2,0)];
            else
                op2_regname=regName[get_reg(op2,1)];
            fprintf(mipsout,"  mul, %s, %s, %s\n",res_regname,op1_regname,op2_regname);
            break;
        case IR_DIV:
            char *op1_regname=NULL;
            char *op2_regname=NULL;
            if(op1->kind==OP_CONSTANT)
                op1_regname=regName[get_reg(op1,0)];
            else
                op1_regname=regName[get_reg(op1,1)];
            if(op2->kind==OP_CONSTANT)
                op2_regname=regName[get_reg(op2,0)];
            else
                op2_regname=regName[get_reg(op2,1)];
            fprintf(mipsout,"  div, %s, %s, %s\n",res_regname,op1_regname,op2_regname);
            fprintf(mipsout,"  mflo %s\n",res_regname);
            break;         
        default:
            assert(0);   
    }
    return;
}