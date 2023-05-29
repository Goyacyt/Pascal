#include"objectcode.h"
#include "basicblock.h"
#ifdef VSDEBUG
extern FILE* mipsout;

static int arg_no=-1;
static int param_no=-1;
static int objlinenum=1;

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
    cur_bb=bb_head;

    while(cur_bb){
        InterCodeList irnode=cur_bb->first;
        while(irnode&&(irnode!=cur_bb->last->next)){
            print_ir2(irnode);
            transfer_IR(irnode);
            irnode=irnode->next;
        }
        assert(irnode);
        spill_all();
        cur_bb=cur_bb->nextbb;
        printf(BLUE"********************************\n"NONE);
    }
}

void init_environments(){
    partition();

    varlist_head=(VariableList)malloc(sizeof(struct VariableList_));
    assert(varlist_head);
    varlist_head->var=NULL;
    varlist_head->prev=varlist_head;
    varlist_head->next=varlist_head; 

    objstack_head=init_stacknode(NULL,-1);

    fprintf(mipsout,"%d:    .data\n",objlinenum++);
    fprintf(mipsout,"%d:    _prompt: .asciiz \"Enter an interger:\"\n",objlinenum++);
    fprintf(mipsout,"%d:    _ret: .asciiz \"\\n\"\n",objlinenum++);
    fprintf(mipsout,"%d:    .globl main\n",objlinenum++);

        // read
    fprintf(mipsout,"%d:    .text\n",objlinenum++);
    fprintf(mipsout,"%d:    read:\n",objlinenum++);
    fprintf(mipsout,"%d:      li $v0, 4\n",objlinenum++);
    fprintf(mipsout,"%d:      la $a0, _prompt\n",objlinenum++);
    fprintf(mipsout,"%d:      syscall\n",objlinenum++);
    fprintf(mipsout,"%d:      li $v0, 5\n",objlinenum++);
    fprintf(mipsout,"%d:      syscall\n",objlinenum++);
    fprintf(mipsout,"%d:      jr $ra\n",objlinenum++);
    fprintf(mipsout,"%d:    \n",objlinenum++);

    // write
    fprintf(mipsout,"%d:    write:\n",objlinenum++);
    fprintf(mipsout,"%d:      li $v0, 1\n",objlinenum++);
    fprintf(mipsout,"%d:      syscall\n",objlinenum++);
    fprintf(mipsout,"%d:      li $v0, 4\n",objlinenum++);
    fprintf(mipsout,"%d:      la $a0, _ret\n",objlinenum++);
    fprintf(mipsout,"%d:      syscall\n",objlinenum++);
    fprintf(mipsout,"%d:      move $v0, $0\n",objlinenum++);
    fprintf(mipsout,"%d:      jr $ra\n",objlinenum++);
    fprintf(mipsout,"%d:    \n",objlinenum++);
}


void print_ir2(InterCodeList irnode){
#ifdef VSDEBUG
    InterCode ir=irnode->code;
    printf(YELLOW"%d ————    "NONE,ir->linenum);
    switch (ir->kind){
        case IR_GETVAL:
            print_op2(ir->u.two.left);
            printf(YELLOW" := *"NONE);
            print_op2(ir->u.two.right);
            break;
        case IR_GETADDR:
            print_op2(ir->u.two.left);
            printf(YELLOW" := &"NONE);
            print_op2(ir->u.two.right);
            break;
        case IR_STOREIN:
            printf(YELLOW"*"NONE);
            print_op2(ir->u.two.left);
            printf(YELLOW" := "NONE);
            print_op2(ir->u.two.right);
            break;
        case IR_LABEL:
            printf(YELLOW"LABEL "NONE);
            assert(ir->u.one->kind==OP_LABEL);
            print_op2(ir->u.one);
            printf(YELLOW" :"NONE);
            break;
        case IR_FUNCTIONNAME:
            printf(YELLOW"FUNCTION "NONE);
            assert(ir->u.one->kind==OP_FUNCTIONNAME);
            print_op2(ir->u.one);
            printf(YELLOW" :"NONE);
            break;
        case IR_CALL:
            print_op2(ir->u.two.left);
            printf(YELLOW" := "NONE);
            printf(YELLOW"CALL "NONE);
            print_op2(ir->u.two.right);
            break;
        case IR_READ:
            printf(YELLOW"READ "NONE);
            print_op2(ir->u.one);
            break;
        case IR_WRITE:
            printf(YELLOW"WRITE "NONE);
            if(ir->u.one->kind==OP_ADDRESS){
                printf(YELLOW"*"NONE);
            }
            print_op2(ir->u.one);
            break;
        case IR_RETURN:
            printf(YELLOW"RETURN "NONE);
            print_op2(ir->u.one);
            break;
        case IR_GOTO:
            printf(YELLOW"GOTO "NONE);
            assert(ir->u.one->kind==OP_LABEL);
            print_op2(ir->u.one);
            break;
        case IR_PARAM:
            printf(YELLOW"PARAM "NONE);
            print_op2(ir->u.one);
            break;
        case IR_ASSIGN:
            print_op2(ir->u.two.left);
            printf(YELLOW" := "NONE);
            print_op2(ir->u.two.right);
            break;
        case IR_ADD:
            print_op2(ir->u.three.result);
            printf(YELLOW" := "NONE);
            print_op2(ir->u.three.op1);
            printf(YELLOW" + "NONE);
            print_op2(ir->u.three.op2);
            break;
        case IR_SUB:
            print_op2(ir->u.three.result);
            printf(YELLOW" := "NONE);
            print_op2(ir->u.three.op1);
            printf(YELLOW" - "NONE);
            print_op2(ir->u.three.op2);
            break;
        case IR_MUL:
            print_op2(ir->u.three.result);
            printf(YELLOW" := "NONE);
            print_op2(ir->u.three.op1);
            printf(YELLOW" * "NONE);
            print_op2(ir->u.three.op2);
            break;
        case IR_DIV:
            print_op2(ir->u.three.result);
            printf(YELLOW" := "NONE);
            print_op2(ir->u.three.op1);
            printf(YELLOW" / "NONE);
            print_op2(ir->u.three.op2);
            break;
        case IR_ARG:
            printf(YELLOW"ARG "NONE);
            Operand this=ir->u.one;
            if(this->kind==OP_ARRAYNAME||this->kind==STRUCTURE_NAME){
                if(this->optype.isparam==notPARAM){
                    printf(YELLOW"&"NONE);
                }
            }
            print_op2(this);
            break;
        case IR_IFGOTO:
            printf(YELLOW"IF "NONE);
            print_op2(ir->u.ifgoto.op1);
            printf(YELLOW" %s "NONE,ir->u.ifgoto.relop);
            print_op2(ir->u.ifgoto.op2);
            printf(YELLOW" GOTO "NONE);
            print_op2(ir->u.ifgoto.label);
            break;
        case IR_DEC:
            printf(YELLOW"DEC "NONE);
            print_op2(ir->u.dec.var);
            printf(YELLOW" %d"NONE,ir->u.dec.size);
            break;
        default:
            assert(0);
    }
    printf(YELLOW"    ————\n"NONE);
    return;
#endif
}

void print_op2(Operand op){
#ifdef VSDEBUG 
    switch(op->kind){
        case OP_VARIABLE:
            printf(YELLOW"%s"NONE,op->name);
            break;
        case OP_CONSTANT:            
            printf(YELLOW"#"NONE);
            printf(YELLOW"%d"NONE,op->number);
            break;
        case OP_FUNCTIONNAME:
            printf(YELLOW"%s"NONE,op->name);
            break;
        case OP_TEMP:
            printf(YELLOW"tmp"NONE);
            printf(YELLOW"%d"NONE,op->no);
            break;
        case OP_LABEL:
            printf(YELLOW"label%d"NONE,op->no);
            break;
        case OP_ADDRESS:
            printf(YELLOW"addr%d"NONE,op->no);
            break;
        case OP_ARRAYNAME:
            printf(YELLOW"array%s"NONE,op->name);
            break;
        default:
            printf(YELLOW"operand kind=%d\n"NONE,op->kind);
            assert(0);
    }
    return;
#endif
}

bool cmp_op(Operand op1,Operand op2){
    if(op1->kind!=op2->kind)
        return 0;
    switch(op1->kind){
        case OP_FUNCTIONNAME:
        case OP_VARIABLE:
        case OP_ARRAYNAME:
            return strcmp(op1->name,op2->name)==0;
        case OP_LABEL:
        case OP_TEMP:
        case OP_ADDRESS:
            return op1->no==op2->no;
        default:
            assert(0);
    }
    assert(0);
}

void funct_init_varlist(InterCodeList functname_irnode){
    InterCodeList irnode=functname_irnode->next;
    while((irnode!=irlist_head)&&(irnode->code->kind!=IR_FUNCTIONNAME)){
        insert_var(irnode);
        irnode=irnode->next;
    }
    return;
}


Variable insert2varlist(Operand op,int param_no,int arrsize){ //若op代表的var不在变量表中，加入。常数不是变量
    if(op->kind==OP_CONSTANT)
        return NULL;
    Variable var=find_var(op);
    if(var){
        assert(param_no==-1);
        return var;
    }
    var=(Variable)malloc(sizeof(struct Variable_));
    assert(var);
    var->op=op;
    var->regno=-1;
    var->state=notINREG;

    if(param_no>3)
        var->offset=param_no-2;
    else if(arrsize>0){
        assert(arrsize%4==0);
        cur_objstack->stackdep+=arrsize/4;
        var->offset=-(cur_objstack->stackdep);
    }
    else{
        cur_objstack->stackdep++;
        var->offset=-(cur_objstack->stackdep);
    }
    
    VariableList newnode=(VariableList)malloc(sizeof(struct VariableList_));
    newnode->var=var;
    newnode->next=varlist_head;
    newnode->prev=varlist_head->prev;
    varlist_head->prev->next=newnode;
    varlist_head->prev=newnode;
    return var;
}

void insert_var(InterCodeList irnode){
    InterCode ir=irnode->code;
    int line_number=ir->linenum;
    switch(ir->kind){
        case IR_DEC: //实际栈上只有数组的第一个位置有东西，为数组名（实际上是数组地址），其他位置以后也仍不放置数
            insert2varlist(ir->u.dec.var,-1,ir->u.dec.size);
            break;
        case IR_CALL:
            insert2varlist(ir->u.two.left,-1,-1);
            break;
        case IR_FUNCTIONNAME:
            param_no=-1;
            break;
        case IR_RETURN:
        case IR_WRITE:
        case IR_ARG:
            if(ir->u.one->kind!=OP_CONSTANT){
                assert(find_var(ir->u.one));
                insert2varlist(ir->u.one,-1,-1);
            }
            break;
        case IR_PARAM:
            if(param_no==-1)
                param_no=0;
            insert2varlist(ir->u.one,param_no,-1);
            param_no++;
            break;
        case IR_READ:
            insert2varlist(ir->u.one,-1,-1);
            break;
        case IR_GETADDR:
        case IR_GETVAL:
        case IR_STOREIN:
        case IR_ASSIGN:
            insert2varlist(ir->u.two.left,-1,-1);
            if(ir->u.two.right->kind!=OP_CONSTANT){
                assert(find_var(ir->u.two.right));
                insert2varlist(ir->u.two.right,-1,-1);
            }
            break;
        case IR_ADD:
        case IR_SUB:
        case IR_MUL:
        case IR_DIV:
            insert2varlist(ir->u.three.result,-1,-1);
            if(ir->u.three.op1->kind!=OP_CONSTANT){
                assert(find_var(ir->u.three.op1));
                insert2varlist(ir->u.three.op1,-1,-1);
            }
            if(ir->u.three.op2->kind!=OP_CONSTANT){
                assert(find_var(ir->u.three.op2));
                insert2varlist(ir->u.three.op2,-1,-1);
            }
            break;
        case IR_IFGOTO:
            if(ir->u.ifgoto.op1->kind!=OP_CONSTANT){
                assert(find_var(ir->u.ifgoto.op1));
                insert2varlist(ir->u.ifgoto.op1,-1,-1);
            }
            if(ir->u.ifgoto.op2->kind!=OP_CONSTANT){
                assert(find_var(ir->u.ifgoto.op2));
                insert2varlist(ir->u.ifgoto.op2,-1,-1);
            }
            break;
        default:
            break;
    }
    return;
}

Variable find_var(Operand op){
    VariableList temp=varlist_head->next;
    while(temp!=varlist_head){
        if(temp->var->op==op)
            return temp->var;
        else if(cmp_op(temp->var->op,op)){
            return temp->var;
        }
        temp=temp->next;
    }
    return NULL;
}

int digit(int num){
    int d=0;
    if(num<0){
       num=-num;
       d++; 
    }
    while(num){
        num/=10;
        d++;
    }
    return d;
}

void print_varlist(){
    VariableList temp=varlist_head->next;
    int cnt=0;
    while(temp!=varlist_head){
        if(temp->var->op->kind==OP_VARIABLE){
            cnt+=strlen(temp->var->op->name)+digit(temp->var->offset*4)+3;
            if(cnt>=150){
                printf("\n");
                cnt=strlen(temp->var->op->name)+digit(temp->var->offset*4)+3;
            }
            printf(PURPLE"%s[%d] "NONE,temp->var->op->name,temp->var->offset*4);
        }
        else if(temp->var->op->kind==OP_TEMP){
            cnt+=3+digit(temp->var->op->no)+digit(temp->var->offset*4)+3;
            if(cnt>=150){
                printf("\n");
                cnt=3+digit(temp->var->op->no)+digit(temp->var->offset*4)+3;
            }
            printf(PURPLE"tmp%d[%d] "NONE,temp->var->op->no,temp->var->offset*4);
        }
        else if(temp->var->op->kind==OP_ARRAYNAME){
            cnt+=strlen(temp->var->op->name)+digit(temp->var->offset*4)+3+4;
            if(cnt>=150){
                printf("\n");
                cnt=strlen(temp->var->op->name)+digit(temp->var->offset*4)+3+4;
            }
            printf(PURPLE"arr-%s[%d] "NONE,temp->var->op->name,temp->var->offset*4);
        }
        else if(temp->var->op->kind==OP_ADDRESS){
            cnt+=4+digit(temp->var->op->no)+digit(temp->var->offset*4)+3;
            if(cnt>=150){
                printf("\n");
                cnt=4+digit(temp->var->op->no)+digit(temp->var->offset*4)+3;
            }
            printf(PURPLE"addr%d[%d] "NONE,temp->var->op->no,temp->var->offset*4);
        }
        else
            assert(0);
        temp=temp->next;
    }
    printf("\n");
    return;
}

void clear_varlist(){
    VariableList temp=varlist_head->next;
    while(temp!=varlist_head){
        temp->prev->next=temp->next;
        temp->next->prev=temp->prev;
        free(temp);
        temp=varlist_head->next;
    }
}

ObjStackNode init_stacknode(char *funct_name,int paramnum){
    ObjStackNode objstack=(ObjStackNode)malloc(sizeof(struct ObjStackNode_));
    assert(objstack);
    objstack->functname=funct_name;
    objstack->paramnum=paramnum;
    objstack->stackdep=0;
    objstack->prev=NULL;
    objstack->next=NULL;
    cur_objstack=objstack;
    return objstack;
}

void push_objstack(char *funct_name,int paramnum){
    ObjStackNode newnode=init_stacknode(funct_name,paramnum);
    newnode->prev=objstack_head;
    newnode->next=objstack_head->next;
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
        printf("functname:%s stackdep:%d\n",temp->functname,temp->stackdep);
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
    if(var==NULL){ //说明里面存放的类型为OP_CONSTANT
        free_reg(reg_no);
        return;
    }
    assert(var->state==INREG);

    fprintf(mipsout,"%d:      sw %s, %d($fp)\n",objlinenum++,regName[reg_no],var->offset*4);
    var->state=notINREG;    
    var->regno=-1;
    free_reg(reg_no);
    return;
}

void spill_all(){
    printf(GREEN"spill start\n"NONE);
    for(int regno=0;regno<32;regno++){
        if(regs[regno].state==USED)
            spill_reg(regno);
    }
    printf(GREEN"spill end\n"NONE);
    return;
}

int allocate_reg(InterCodeList irnode,Variable var){ //t0-t9全满时使用
    int max_distance=-1;
    int maxdis_regno=-1;
    for(int regno=t0;regno<=t9;regno++){
        int cur_distance=active_distance(irnode,regs[regno].var);
        if(cur_distance+irnode->code->linenum > cur_bb->last->code->linenum){ //下一条使用op的ir已超出本bb范围
            spill_reg(regno);
            regs[regno].var=var;
            printf(GREEN"spill var in %s\n"NONE,regName[regno]);
            return regno;
        }
        if(cur_distance<max_distance){
            max_distance=cur_distance;
            maxdis_regno=regno;
        }
    }
    spill_reg(maxdis_regno);
    printf(GREEN"spill var in %s\n"NONE,regName[maxdis_regno]);
    regs[maxdis_regno].var=var;
    return maxdis_regno;  
}


int active_distance(InterCodeList irnode,Variable var){ //当前ir与当前bb中最后用op的ir间距离。
    if(var==NULL)
        return 0x3f3f3f3f;
    Operand op=var->op;
    int distance=0;
    irnode=irnode->next; //从下一条ir开始计
    while(irnode!=cur_bb->last->next){
        InterCode ir=irnode->code;
        switch(ir->kind){
            case IR_PARAM:
            case IR_ARG:
            case IR_READ:
            case IR_WRITE:
            case IR_RETURN:
                distance++;
                if(cmp_op(op,ir->u.one))
                    return distance;
                break;
            case IR_CALL:
                distance++;
                if(cmp_op(op,ir->u.two.left))
                    return distance;
                break;
            case IR_GETADDR:
            case IR_GETVAL:
            case IR_STOREIN:
            case IR_ASSIGN:
                distance++;
                if(cmp_op(op,ir->u.two.left))
                    return distance;
                else if(cmp_op(op,ir->u.two.right))
                    return distance;
                break;
            case IR_ADD:
            case IR_SUB:
            case IR_MUL:
            case IR_DIV:
                distance++;
                if(cmp_op(op,ir->u.three.result)||cmp_op(op,ir->u.three.op1)||cmp_op(op,ir->u.three.op2))
                    return distance;
                break;
            default:
                distance++;
                break;
        }
        irnode=irnode->next;
    }
    distance=0x3f3f3f3f;
    return distance;
}

int get_reg(Operand op,InterCodeList irnode){
    int regno=-1;

    if(op->kind==OP_CONSTANT){
        for(int r=t0;r<=t9;r++){
            if(regs[r].state==UNUSED){
                regno=r;
                break;
            }
        }
        if(regno==-1)
            regno=allocate_reg(irnode,NULL);
        regs[regno].state=USED;
        regs[regno].var=NULL;
        assert(regno!=-1);
        fprintf(mipsout,"%d:      li %s, %d\n",objlinenum++,regName[regno],op->number);
        printf(CYAN"   %s:%d\n"NONE,regName[regno],op->number);
        return regno;
    }


    Variable var=find_var(op);
    assert(var);

    if(var->state==INREG){ //还在寄存器中
        assert(regs[var->regno].state==USED);
        regno=var->regno;
        assert(regno!=-1);
    }
    else{
        assert(var->state==notINREG);
        for(int r=t0;r<=t9;r++){
            if(regs[r].state==UNUSED){
                regno=r;
                break;
            }
        }
        if(regno==-1)
            regno=allocate_reg(irnode,var);

        regs[regno].state=USED;
        regs[regno].var=var;

        switch(op->kind){
            case OP_TEMP:
            case OP_VARIABLE:
            case OP_ADDRESS:
                fprintf(mipsout,"%d:      lw %s, %d($fp)\n",objlinenum++,regName[regno],var->offset*4);
                break;
            default:
                assert(0);
        }
        var->state=INREG;
        var->regno=regno;
        assert(regno!=-1);
    }
    if(op->kind==OP_VARIABLE)
        printf(CYAN"   %s:%s\n"NONE,regName[regno],op->name);
    else if(op->kind==OP_TEMP)
        printf(CYAN"   %s:tmp%d\n"NONE,regName[regno],op->no);
    else if(op->kind==OP_ADDRESS)
        printf(CYAN"   %s:addr%d\n"NONE,regName[regno],op->no);
    else    assert(0);
    return regno;
}

void spill_inactive_var(Operand op,InterCodeList irnode){
    assert(op->kind!=OP_CONSTANT);
    Variable var=find_var(op);
    assert(var);
    if(var->state==INREG){
        if(irnode->code->linenum+active_distance(irnode,var) > cur_bb->last->code->linenum){
            printf(GREEN"free reg %s\n"NONE,regName[var->regno]);
            spill_reg(var->regno);
        }
    }
}

void transfer_IR(InterCodeList irnode){
    InterCode ir=irnode->code;
    switch(ir->kind){
        case IR_LABEL:
            fprintf(mipsout,"%d:    label%d:\n",objlinenum++,ir->u.one->no);
            break;
        case IR_FUNCTIONNAME:
            fprintf(mipsout,"%d:    %s:\n",objlinenum++,ir->u.one->name);
            fprintf(mipsout,"%d:      move $fp, $sp\n",objlinenum++);
            push_objstack(ir->u.one->function_field->name,ir->u.one->function_field->type->u.function.paramnum);
            funct_init_varlist(irnode);
            print_varlist();
            fprintf(mipsout,"%d:      addi $sp, $sp, -%d\n",objlinenum++,cur_objstack->stackdep*4);
            param_no=-1;
            break;
        case IR_CALL:
            Operand funct_op=ir->u.two.right;
            assert(arg_no==funct_op->function_field->type->u.function.paramnum);
            transfer_IR_CALL(irnode);
            arg_no=-1;
            break;
        case IR_PARAM:
        case IR_DEC:
            Variable var=find_var(ir->u.one);
            assert(var);
            assert(var->state==notINREG);
            assert(var->regno=-1);
            break;
        case IR_ARG:
            if(arg_no==-1)
                arg_no=0;
            transfer_IR_ARG(irnode,arg_no);
            arg_no++;
            break;
        case IR_RETURN:
            if(ir->u.one->kind==OP_CONSTANT)
                fprintf(mipsout,"%d:      li $v0, %d\n",objlinenum++,ir->u.one->number);
            else{
                fprintf(mipsout,"%d:      move $v0, %s\n",objlinenum++,regName[get_reg(ir->u.one,irnode)]);
                spill_inactive_var(ir->u.one,irnode);
            }
            fprintf(mipsout,"%d:      jr $ra\n",objlinenum++);
            fprintf(mipsout,"%d:    \n",objlinenum++);
            clear_varlist();
            pop_objstack();
            break;
        case IR_READ:
            transfer_IR_READ(irnode);
            break;
        case IR_WRITE:
            transfer_IR_WRITE(irnode);
            break;
        case IR_GOTO:
            fprintf(mipsout,"%d:      j label%d\n",objlinenum++,ir->u.one->no);
            break;
        case IR_IFGOTO:
            transfer_IR_IFGOTO(irnode);
            break;
        case IR_ASSIGN:
            transfer_IR_ASSIGN(irnode);
            break;
        case IR_GETADDR: //a=&b
            assert(ir->u.two.right->kind==OP_ARRAYNAME);
            var=find_var(ir->u.two.right);
            assert(var);
            fprintf(mipsout,"%d:      addi %s, $fp, %d\n",objlinenum++,regName[get_reg(ir->u.two.left,irnode)],var->offset*4);
            spill_inactive_var(ir->u.two.left,irnode);
            break;
        case IR_GETVAL:  //a=*b
            fprintf(mipsout,"%d:      lw %s, 0(%s)\n",objlinenum++,regName[get_reg(ir->u.two.left,irnode)],regName[get_reg(ir->u.two.right,irnode)]);
            break;
        case IR_STOREIN:  //*a=b
            fprintf(mipsout,"%d:      sw %s, 0(%s)\n",objlinenum++,regName[get_reg(ir->u.two.right,irnode)],regName[get_reg(ir->u.two.left,irnode)]);
            break;
        case IR_ADD:
        case IR_SUB:
        case IR_MUL:
        case IR_DIV:
            transfer_IR_CAL(irnode);
            break;
        default:
            assert(0);
    }
    return;
}

void transfer_IR_CALL(InterCodeList irnode){
    InterCode ir=irnode->code;
    //调用前
    // 保存返回地址
    fprintf(mipsout,"%d:      addi $sp, $sp, -8\n",objlinenum++);
    fprintf(mipsout,"%d:      sw $ra, 4($sp)\n",objlinenum++);
    fprintf(mipsout,"%d:      sw $fp, 0($sp)\n",objlinenum++);

    // 调用函数
    fprintf(mipsout,"%d:      jal %s\n",objlinenum++,ir->u.two.right->name);

    //调用后
    // 恢复寄存器和返回地址
    fprintf(mipsout,"%d:      lw $sp, $fp\n",objlinenum++);
    fprintf(mipsout,"%d:      lw $ra, 4($sp)\n",objlinenum++);
    fprintf(mipsout,"%d:      addi $sp, $sp, %d\n",objlinenum++,(ir->u.one->function_field->type->u.function.paramnum+2)*4);
    fprintf(mipsout,"%d:      move %s, $v0\n",objlinenum++, regName[get_reg(ir->u.two.left,irnode)]);
    spill_inactive_var(ir->u.two.left,irnode);
    return;
}

void transfer_IR_ARG(InterCodeList irnode,int arg_no){
    InterCode ir=irnode->code;
    Operand arg_op=ir->u.one;
    Variable var=find_var(arg_op); //原参数并没有真的移动位置。
    if(arg_no<4) //将参数移动到对应参数寄存器
        switch(arg_op->kind){
            case OP_VARIABLE:
            case OP_TEMP:
                if(var->state==INREG){   
                    fprintf(mipsout,"%d:      move %s, %s\n",objlinenum++,regName[a0+arg_no],regName[get_reg(arg_op,irnode)]);
                    spill_inactive_var(arg_op,irnode);
                }
                else{
                    fprintf(mipsout,"%d:      lw %s, %d($fp)\n",objlinenum++,regName[a0+arg_no],var->offset*4);
                }
                break;
            case OP_CONSTANT:
                fprintf(mipsout,"%d:      li %s, %d\n",objlinenum++,regName[a0+arg_no],arg_op->number);
                break;
            default:
                assert(0);
        }
    else{ //将参数保存到栈中
        fprintf(mipsout,"%d:      addi $sp, $sp, -4\n",objlinenum++);
        int arg_regno=get_reg(arg_op,irnode);
        fprintf(mipsout,"%d:      sw %s, 0($sp)\n",objlinenum++,regName[arg_regno]);
        if(arg_op->kind!=OP_CONSTANT){
            free_reg(arg_regno);
            printf(GREEN"free reg %s\n"NONE,regName[arg_regno]);
        }
        else
            spill_inactive_var(arg_op,irnode);
    }
}

void transfer_IR_READ(InterCodeList irnode){
    spill_all();

    // 保存返回地址
    fprintf(mipsout,"%d:      addi $sp, $sp, -4\n",objlinenum++);
    fprintf(mipsout,"%d:      sw $ra, 0($sp)\n",objlinenum++);
    // 调用read函数
    fprintf(mipsout,"%d:      jal read\n",objlinenum++);
    // 恢复栈指针和返回地址
    fprintf(mipsout,"%d:      lw $ra, 0($sp)\n",objlinenum++);
    fprintf(mipsout,"%d:      addi $sp, $sp, 4\n",objlinenum++);
    fprintf(mipsout,"%d:      move %s, $v0\n",objlinenum++, regName[get_reg(irnode->code->u.one,irnode)]);
    spill_inactive_var(irnode->code->u.one,irnode);
    return;
}

void transfer_IR_WRITE(InterCodeList irnode){
    spill_all();
   
    fprintf(mipsout,"%d:      move $a0, %s\n",objlinenum++, regName[get_reg(irnode->code->u.one,irnode)]);
    spill_inactive_var(irnode->code->u.one,irnode);
    // 保存返回地址
    fprintf(mipsout,"%d:      addi $sp, $sp, -4\n",objlinenum++);
    fprintf(mipsout,"%d:      sw $ra, 0($sp)\n",objlinenum++);
    // 调用write函数
    fprintf(mipsout,"%d:      jal write\n",objlinenum++);
    // 恢复栈指针和返回地址
    fprintf(mipsout,"%d:      lw $ra, 0($sp)\n",objlinenum++);
    fprintf(mipsout,"%d:      addi $sp, $sp, 4\n",objlinenum++);
    return;
}


void transfer_IR_IFGOTO(InterCodeList irnode){
    InterCode ir=irnode->code;
    char* relop=ir->u.ifgoto.relop;
    Operand op1=ir->u.ifgoto.op1;
    Operand op2=ir->u.ifgoto.op2;
    Operand label=ir->u.ifgoto.label;

    if(strcmp(relop,"==")==0){
        fprintf(mipsout,"%d:      beq %s, %s, label%d\n",objlinenum++,regName[get_reg(op1,irnode)],regName[get_reg(op2,irnode)],label->no);
        spill_inactive_var(op1,irnode);
        spill_inactive_var(op2,irnode);
    }
    else if(strcmp(relop,"!=")==0){
        fprintf(mipsout,"%d:      bne %s, %s, label%d\n",objlinenum++,regName[get_reg(op1,irnode)],regName[get_reg(op2,irnode)],label->no);
        spill_inactive_var(op1,irnode);
        spill_inactive_var(op2,irnode);
    }
    else if(strcmp(relop,">")==0){
        fprintf(mipsout,"%d:      bgt %s, %s, label%d\n",objlinenum++,regName[get_reg(op1,irnode)],regName[get_reg(op2,irnode)],label->no);
        spill_inactive_var(op1,irnode);
        spill_inactive_var(op2,irnode);
    }
    else if(strcmp(relop,"<")==0){
        fprintf(mipsout,"%d:      blt %s, %s, label%d\n",objlinenum++,regName[get_reg(op1,irnode)],regName[get_reg(op2,irnode)],label->no);
        spill_inactive_var(op1,irnode);
        spill_inactive_var(op2,irnode);
    }
    else if(strcmp(relop,">=")==0){
        fprintf(mipsout,"%d:      bge %s, %s, label%d\n",objlinenum++,regName[get_reg(op1,irnode)],regName[get_reg(op2,irnode)],label->no);
        spill_inactive_var(op1,irnode);
        spill_inactive_var(op2,irnode);
    }
    else if(strcmp(relop,"<=")==0){
        fprintf(mipsout,"%d:      ble %s, %s, label%d\n",objlinenum++,regName[get_reg(op1,irnode)],regName[get_reg(op2,irnode)],label->no);
        spill_inactive_var(op1,irnode);
        spill_inactive_var(op2,irnode);
    }
    else
        assert(0);
    return;
}   


void  transfer_IR_ASSIGN(InterCodeList irnode){
    InterCode ir=irnode->code;
    switch(ir->u.two.right->kind){
        case OP_CONSTANT:
            fprintf(mipsout,"%d:      li %s, %d\n",objlinenum++,regName[get_reg(ir->u.two.left,irnode)],ir->u.two.right->number);
            spill_inactive_var(ir->u.two.left,irnode);
            break;
        case OP_VARIABLE:
        case OP_TEMP:
        case OP_ADDRESS:
            int left_regno=get_reg(ir->u.two.left,irnode);
            int right_regno=get_reg(ir->u.two.right,irnode);
            fprintf(mipsout,"%d:      move %s, %s\n",objlinenum++,regName[left_regno],regName[right_regno]);
            spill_inactive_var(ir->u.two.left,irnode);
            spill_inactive_var(ir->u.two.right,irnode);
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
    char* res_regname=regName[get_reg(result,irnode)];
    assert(op1->kind!=OP_ARRAYNAME &&op2->kind!=OP_ARRAYNAME);
    switch(ir->kind){
        case IR_ADD:
            if(op1->kind==OP_CONSTANT){
                assert(op2->kind!=OP_CONSTANT);
                fprintf(mipsout,"%d:      addi %s, %s, %d\n",objlinenum++,res_regname,regName[get_reg(op2,irnode)],op1->number);
                spill_inactive_var(op2,irnode);
            }
            else if(op2->kind==OP_CONSTANT){
                assert(op1->kind!=OP_CONSTANT);
                fprintf(mipsout,"%d:      addi %s, %s, %d\n",objlinenum++,res_regname,regName[get_reg(op1,irnode)],op2->number);
                spill_inactive_var(op1,irnode);
            }
            else{
                fprintf(mipsout,"%d:      add %s, %s, %s\n",objlinenum++,res_regname,regName[get_reg(op1,irnode)],regName[get_reg(op2,irnode)]);
                spill_inactive_var(op1,irnode);
                spill_inactive_var(op2,irnode);
            }
            break;
        case IR_SUB:
            if(op2->kind==OP_CONSTANT){
                assert(op1->kind!=OP_CONSTANT);
                fprintf(mipsout,"%d:      addi %s, %s, -%d\n",objlinenum++,res_regname,regName[get_reg(op1,irnode)],op2->number);
                spill_inactive_var(op1,irnode);
            }
            else if(op1->kind==OP_CONSTANT){
                assert(op2->kind!=OP_CONSTANT);
                int const_regno=get_reg(op1,irnode);
                fprintf(mipsout,"%d:      sub %s, %s, %s\n",objlinenum++,res_regname,regName[const_regno],regName[get_reg(op2,irnode)]);
                free_reg(const_regno);
                printf(GREEN"free reg %s\n"NONE,regName[const_regno]);
                spill_inactive_var(op2,irnode);
            }
            else{
                fprintf(mipsout,"%d:      sub %s, %s, %s\n",objlinenum++,res_regname,regName[get_reg(op1,irnode)],regName[get_reg(op2,irnode)]);
                spill_inactive_var(op1,irnode);
                spill_inactive_var(op2,irnode);
            }
            break;
        case IR_MUL:
            if(op1->kind==OP_CONSTANT||op2->kind==OP_CONSTANT){
                int const_regno=-1,var_regno=-1;
                if(op1->kind==OP_CONSTANT){
                    assert(op2->kind==OP_CONSTANT);
                    const_regno=get_reg(op1,irnode);
                    var_regno=get_reg(op2,irnode);
                }
                else{
                    const_regno=get_reg(op2,irnode);
                    var_regno=get_reg(op1,irnode);
                }
                fprintf(mipsout,"%d:      mul %s, %s, %s\n",objlinenum++,res_regname,regName[var_regno],regName[const_regno]);
                free_reg(const_regno);
                printf(GREEN"free reg %s\n"NONE,regName[const_regno]);
                spill_inactive_var(regs[var_regno].var->op,irnode);
            }
            else{
                fprintf(mipsout,"%d:      mul %s, %s, %s\n",objlinenum++,res_regname,regName[get_reg(op1,irnode)],regName[get_reg(op2,irnode)]);
                spill_inactive_var(op1,irnode);
                spill_inactive_var(op2,irnode);
            }
            break;
        case IR_DIV:
            assert(op1->kind==OP_TEMP||op1->kind==OP_VARIABLE);
            assert(op2->kind==OP_TEMP||op2->kind==OP_VARIABLE);
            fprintf(mipsout,"%d:      div %s, %s\n",objlinenum++,regName[get_reg(op1,irnode)],regName[get_reg(op2,irnode)]);
            fprintf(mipsout,"%d:      mflo %s\n",objlinenum++,res_regname);
            spill_inactive_var(op1,irnode);
            spill_inactive_var(op2,irnode);
            break;         
        default:
            assert(0);   
    }
    spill_inactive_var(result,irnode);
    return;
}

#endif



