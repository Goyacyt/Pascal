#include "optimize.h"
//#define DE_BUG

extern FILE* irout;

char def[MAX_IR][MAX_VAR];
char use[MAX_IR][MAX_VAR];

int ircode_no=0;
char *variable[MAX_VAR_NUMBER];
int variable_numer=0;

extern BasicBlock bb_head;
extern BasicBlock bb_tail; //最后一个基本块
extern IRtag tag_head;

#define MAX_BLOCK 528
//#define MAX_VAR 1024
char in[MAX_BLOCK][MAX_VAR];
char out[MAX_BLOCK][MAX_VAR];
char block_def[MAX_BLOCK][MAX_VAR];
char block_use[MAX_BLOCK][MAX_VAR];

void parse_print_op(Operand op){
    switch(op->kind){
        case OP_VARIABLE:
            fprintf(irout,"%s",op->name);
            break;
        case OP_CONSTANT:            
            fprintf(irout,"#");
            fprintf(irout,"%d",op->number);
            break;
        case OP_FUNCTIONNAME:
            fprintf(irout,"%s",op->name);
            break;
        case OP_LABEL:
            fprintf(irout,"%s",op->name);
            break;
        case OP_ADDRESS:
            fprintf(irout,"*%s",op->name);
            break;
        case OP_VAL:
            fprintf(irout,"&%s",op->name);
            break;
        default:
            fprintf(irout,"operand kind=%d\n",op->kind);
            assert(0);
    }
    return;
}

void parse_print_ir(InterCode ir){
    switch (ir->kind){
        case IR_LABEL:
            fprintf(irout,"LABEL ");
            assert(ir->u.one->kind==OP_LABEL);
            parse_print_op(ir->u.one);
            fprintf(irout," :");
            break;
        case IR_FUNCTIONNAME:
            fprintf(irout,"FUNCTION ");
            assert(ir->u.one->kind==OP_FUNCTIONNAME);
            parse_print_op(ir->u.one);
            fprintf(irout," :");
            break;
        case IR_CALL:
            parse_print_op(ir->u.two.left);
            fprintf(irout," := ");
            fprintf(irout,"CALL ");
            parse_print_op(ir->u.two.right);
            break;
        case IR_READ:
            fprintf(irout,"READ ");
            parse_print_op(ir->u.one);
            break;
        case IR_WRITE:
            fprintf(irout,"WRITE ");
            if(ir->u.one->kind==OP_ADDRESS){
                fprintf(irout,"*");
            }
            parse_print_op(ir->u.one);
            break;
        case IR_RETURN:
            fprintf(irout,"RETURN ");
            parse_print_op(ir->u.one);
            break;
        case IR_GOTO:
            fprintf(irout,"GOTO ");
            assert(ir->u.one->kind==OP_LABEL);
            parse_print_op(ir->u.one);
            break;
        case IR_PARAM:
            fprintf(irout,"PARAM ");
            parse_print_op(ir->u.one);
            break;
        case IR_ASSIGN:
            parse_print_op(ir->u.two.left);
            fprintf(irout," := ");
            parse_print_op(ir->u.two.right);
            break;
        case IR_ADD:
            parse_print_op(ir->u.three.result);
            fprintf(irout," := ");
            parse_print_op(ir->u.three.op1);
            fprintf(irout," + ");
            parse_print_op(ir->u.three.op2);
            break;
        case IR_SUB:
            parse_print_op(ir->u.three.result);
            fprintf(irout," := ");
            parse_print_op(ir->u.three.op1);
            fprintf(irout," - ");
            parse_print_op(ir->u.three.op2);
            break;
        case IR_MUL:
            parse_print_op(ir->u.three.result);
            fprintf(irout," := ");
            parse_print_op(ir->u.three.op1);
            fprintf(irout," * ");
            parse_print_op(ir->u.three.op2);
            break;
        case IR_DIV:
            parse_print_op(ir->u.three.result);
            fprintf(irout," := ");
            parse_print_op(ir->u.three.op1);
            fprintf(irout," / ");
            parse_print_op(ir->u.three.op2);
            break;
        case IR_ARG:
            fprintf(irout,"ARG ");
            Operand this=ir->u.one;
            parse_print_op(this);
            break;
        case IR_IFGOTO:
            fprintf(irout,"IF ");
            parse_print_op(ir->u.ifgoto.op1);
            fprintf(irout," %s ",ir->u.ifgoto.relop);
            parse_print_op(ir->u.ifgoto.op2);
            fprintf(irout," GOTO ");
            parse_print_op(ir->u.ifgoto.label);
            break;
        case IR_DEC:
            fprintf(irout,"DEC ");
            parse_print_op(ir->u.dec.var);
            fprintf(irout," %d",ir->u.dec.size);
            break;
        default:
            assert(0);
    }
    fprintf(irout,"\n");
    return;
}

void parse_print_irlist(){
    InterCodeList irlist_node=irlist_head->next;
    assert(irlist_node!=NULL);
    while(irlist_node!=irlist_head){
        assert(irlist_node!=NULL);
        parse_print_ir(irlist_node->code);
        irlist_node=irlist_node->next;
    }
    return;
}


void parse_init_irlist(){
    irlist_head=(InterCodeList)malloc(sizeof(struct InterCodeList_));
    assert(irlist_head!=NULL);
    irlist_head->code=NULL;
    irlist_head->prev=irlist_head;
    irlist_head->next=irlist_head;
    return;
}

void parse_insert_ir(InterCode ir){
    assert(ir!=NULL);
    InterCodeList irlist_node=(InterCodeList)malloc(sizeof(struct InterCodeList_));
    assert(irlist_node!=NULL);
    irlist_node->code=ir;
    irlist_node->prev=irlist_head->prev;
    irlist_head->prev->next=irlist_node;
    irlist_head->prev=irlist_node;
    irlist_node->next=irlist_head;
    irlist_node->ir_no=ircode_no;
}

int repeat_name(char *name){
    for(int i=0;i<variable_numer;i++){
        if(strcmp(variable[i],name)==0){
            return 1;
        }
    }
    return 0;
}

int get_name_no(char *name){
    for(int i=0;i<variable_numer;i++){
        if(strcmp(variable[i],name)==0){
            return i;
        }
    }
    return -1;
}

Operand get_var(char *p){
    if(p==NULL){
        return NULL;
    }
    Operand op=malloc(sizeof(struct Operand_));
    if(*p=='#'){
        op->kind=OP_CONSTANT;
        op->number=strtol(p+1,NULL,10);
        op->var_no=-1;//立即数，不存在变量
        return op;
        //printf("%s\n",op->name);
    }else if(*p=='*'){
        op->kind=OP_ADDRESS;
        op->name=p+1;
        int var_no;
        if(!repeat_name(op->name)){
            var_no=variable_numer;
            variable[variable_numer]=op->name;
            variable_numer++;
        }else{
            var_no=get_name_no(op->name);
        }
        op->var_no=var_no;
    }else if(*p=='&'){
        op->kind=OP_VAL;//TODO：不确定，这里的赋值有影响吗
        op->name=p+1;
        int var_no;
        if(!repeat_name(op->name)){
            var_no=variable_numer;
            variable[variable_numer]=op->name;
            variable_numer++;
        }else{
            var_no=get_name_no(op->name);
        }
        op->var_no=var_no;
    }else{
        op->kind=OP_VARIABLE;//中间代码里面变量和临时变量没有什么区别吧。。。
        op->name=p;
        int var_no;
        if(!repeat_name(op->name)){
            var_no=variable_numer;
            variable[variable_numer]=op->name;
            variable_numer++;
        }else{
            var_no=get_name_no(op->name);
        }
        op->var_no=var_no;
    }
    return op;
}

Operand get_label(char *p){
    Operand op=malloc(sizeof(struct Operand_));
    op->kind=OP_LABEL;
    op->name=p;
    return op;
}

Operand get_function(char *p){
    Operand op=malloc(sizeof(struct Operand_));
    op->kind=OP_FUNCTIONNAME;
    op->name=p;
    return op;
}

void parse(FILE* yyin){
    parse_init_irlist();
    while(!feof(yyin)){
        memset(def[ircode_no],0,sizeof(def[ircode_no]));
        memset(use[ircode_no],0,sizeof(use[ircode_no]));

        char *fileline=malloc(MAX_LINE);
        memset(fileline,0,sizeof(fileline));
        fgets(fileline,MAX_LINE,yyin);
        int len=strlen(fileline);
        fileline[len-1]='\0';
        if(fileline[len-2]=='\r'){
            fileline[len-2]='\0';
        }
        #ifdef DE_BUG
        printf("%s",fileline);
        #endif
        //字符串转化为intercode数据格式
        InterCode code=malloc(sizeof(struct InterCode_));

        char *p=strtok(fileline," ");
        if(strcmp(p,"LABEL")==0){
            code->kind=IR_LABEL;
            code->u.one=get_label(strtok(NULL," "));
        }else if(strcmp(p,"FUNCTION")==0){
            code->kind=IR_FUNCTIONNAME;
            code->u.one=get_function(strtok(NULL," "));
        }else if(strcmp(p,"GOTO")==0){
            code->kind=IR_GOTO;
            code->u.one=get_label(strtok(NULL," "));
        }else if(strcmp(p,"IF")==0){
            code->kind=IR_IFGOTO;
            code->u.ifgoto.op1=get_var(strtok(NULL," "));
            code->u.ifgoto.relop=strtok(NULL," ");
            code->u.ifgoto.op2=get_var(strtok(NULL," "));
            strtok(NULL," ");
            code->u.ifgoto.label=get_label(strtok(NULL," "));
        }else if(strcmp(p,"RETURN")==0){
            code->kind=IR_RETURN;
            code->u.one=get_var(strtok(NULL," "));
            int var_no=code->u.one->var_no;
            if(var_no!=-1){
                use[ircode_no][var_no]=1;
            }
        }else if(strcmp(p,"DEC")==0){
            code->kind=IR_DEC;
            code->u.dec.var=get_var(strtok(NULL," "));
        }else if(strcmp(p,"ARG")==0){
            code->kind=IR_ARG;
            code->u.one=get_var(strtok(NULL," "));
            int var_no=code->u.one->var_no;
            if(var_no!=-1){
                use[ircode_no][var_no]=1;
            }
        }else if(strcmp(p,"PARAM")==0){
            code->kind=IR_PARAM;
            code->u.one=get_var(strtok(NULL," "));
            int var_no=code->u.one->var_no;
            if(var_no!=-1){
                def[ircode_no][var_no]=1;
            }
        }else if(strcmp(p,"READ")==0){
            code->kind=IR_READ;
            code->u.one=get_var(strtok(NULL," "));
            int var_no=code->u.one->var_no;
            if(var_no!=-1){
                def[ircode_no][var_no]=1;
            }
        }else if(strcmp(p,"WRITE")==0){
            code->kind=IR_WRITE;
            code->u.one=get_var(strtok(NULL," "));
            int var_no=code->u.one->var_no;
            if(var_no!=-1){
                use[ircode_no][var_no]=1;
            }
        }else{
            Operand result;
            Operand op1;
            Operand op2;
            result=get_var(p);
            strtok(NULL," ");
            p=strtok(NULL," ");
            if(strcmp(p,"CALL")==0){
                code->kind=IR_CALL;
                code->u.two.left=result;
                code->u.two.right=get_function(strtok(NULL," "));
            }else{
                int var_no;
                op1=get_var(p);
                p=strtok(NULL," ");
                if(p==NULL){
                    code->kind=IR_ASSIGN;//包括取地址，取值，左取地址
                    code->u.two.left=result;
                    var_no=code->u.two.left->var_no;
                    assert(var_no!=-1);
                    if(result->kind==OP_ADDRESS){
                        use[ircode_no][var_no]=1;
                    }else{
                        def[ircode_no][var_no]=1;
                    }

                    code->u.two.right=op1;
                    var_no=code->u.two.right->var_no;
                    if(var_no!=-1){
                        use[ircode_no][var_no]=1;
                    }
                }else{
                    code->u.three.result=result;
                    var_no=result->var_no;
                    assert(var_no!=-1);
                    if(result->kind==OP_ADDRESS){
                        use[ircode_no][var_no]=1;
                    }else{
                        def[ircode_no][var_no]=1;
                    }

                    code->u.three.op1=op1;
                    var_no=op1->var_no;
                    if(var_no!=-1){
                        use[ircode_no][var_no]=1;
                    }
                    switch (*p)
                    {
                    case '+':
                        code->kind=IR_ADD;
                        break;
                    case '-':
                        code->kind=IR_SUB;
                        break;
                    case '*':
                        code->kind=IR_MUL;
                        break;
                    case '/':
                        code->kind=IR_DIV;
                        break;
                    default:
                        break;
                    }
                    code->u.three.op2=get_var(strtok(NULL," "));
                    var_no=code->u.three.op2->var_no;
                    if(var_no!=-1){
                        use[ircode_no][var_no]=1;
                    }
                }
            }
        }
        parse_insert_ir(code);
        ircode_no++;
    }
}

//基本块之间没有包含关系，基本块的起点指令有下面这样的情况：
//第一条指令
//跳转指令的目标指令：函数名指令，label指令
//跳转指令之后的第一条指令
//而起点指令之前的指令就是结束指令

void print_BB(BasicBlock bb){
    parse_print_ir(bb->first->code);
    parse_print_ir(bb->last->code);
    printf("\n");
}

void partition(){
    //分割基本块
    //基本块表头
    bb_head=NULL;


    InterCodeList cur_irnode=irlist_head->next;
    BasicBlock cur_bb=init_bb(cur_irnode);
    cur_irnode->block_no=cur_bb->bb_no;
    bb_head=cur_bb;
    //标识（函数开头和label）表头
    tag_head=init_tag(NULL);

    cur_irnode=cur_irnode->next;
    while(cur_irnode!=irlist_head){
        switch(cur_irnode->code->kind){
            case IR_IFGOTO:
                if(cur_bb->last!=NULL){
                    BasicBlock new_bb=init_bb(cur_irnode);
                    cur_bb->nextbb=new_bb;
                    new_bb->lastbb=cur_bb;
                    cur_bb=new_bb;
                }
                cur_bb->last=cur_irnode;
                cur_irnode->block_no=cur_bb->bb_no;

                cur_irnode=cur_irnode->next;
                break;
            case IR_GOTO:
                if(cur_bb->last!=NULL){
                    BasicBlock new_bb=init_bb(cur_irnode);
                    cur_bb->nextbb=new_bb;
                    new_bb->lastbb=cur_bb;
                    cur_bb=new_bb;
                }
                cur_bb->last=cur_irnode;
                cur_irnode->block_no=cur_bb->bb_no;

                cur_irnode=cur_irnode->next;
                break;
            case IR_RETURN:
                cur_bb->last=cur_irnode;
                cur_irnode->block_no=cur_bb->bb_no;

                cur_irnode=cur_irnode->next;
                break;
            case IR_LABEL:
                insert_tag(cur_irnode);
                cur_bb->last=cur_irnode->prev;
                if(cur_irnode->next!=irlist_head){
                    BasicBlock new_bb=init_bb(cur_irnode);
                    cur_bb->nextbb=new_bb;
                    new_bb->lastbb=cur_bb;
                    cur_bb=new_bb;
                    
                }
                cur_irnode->block_no=cur_bb->bb_no;

                cur_irnode=cur_irnode->next;
                break;
            case IR_FUNCTIONNAME:
                insert_tag(cur_irnode);
                if(cur_irnode->next!=irlist_head){
                    BasicBlock new_bb=init_bb(cur_irnode);
                    cur_bb->nextbb=new_bb;
                    new_bb->lastbb=cur_bb;
                    cur_bb=new_bb;
                    
                }
                cur_irnode->block_no=cur_bb->bb_no;

                cur_irnode=cur_irnode->next;
                break;
            default:
                if(cur_bb->last!=NULL){
                    BasicBlock new_bb=init_bb(cur_irnode);
                    cur_bb->nextbb=new_bb;
                    new_bb->lastbb=cur_bb;
                    cur_bb=new_bb;
                }
                cur_irnode->block_no=cur_bb->bb_no;

                cur_irnode=cur_irnode->next;
        }
    }
    bb_tail=cur_bb;
    //cur_bb->last=irlist_head->prev;

    //连缀基本块
    cur_irnode=irlist_head->next;
    cur_bb=bb_head;
    while(cur_bb){
        #ifdef DEBUG
        printf("cur_bb:\n");
        parse_print_ir(cur_bb->first->code);
        parse_print_ir(cur_bb->last->code);
        #endif
        if(cur_bb->nextbb&&cur_bb->last->code->kind!=IR_GOTO&&cur_bb->last->code->kind!=IR_RETURN){
            #ifdef DEBUG
            printf("next bb:\n");
            parse_print_ir(cur_bb->nextbb->first->code);
            parse_print_ir(cur_bb->nextbb->last->code);
            #endif

            link(cur_bb->nextbb,cur_bb);
        }
        InterCodeList jmp_irnode=get_jmp(cur_bb->last);
        BasicBlock jmp_bb=NULL;
        if(jmp_irnode){
            #ifdef DEBUG
            printf("jump code:\n");
            parse_print_ir(jmp_irnode->code);
            #endif

            jmp_bb=search_bb(jmp_irnode);

            #ifdef DEBUG
            printf("jump bb:\n");
            parse_print_ir(jmp_bb->first->code);
            parse_print_ir(jmp_bb->last->code);
            #endif

            link(jmp_bb,cur_bb);
            assert(jmp_bb);
        }
        cur_bb=cur_bb->nextbb;
        #ifdef DEBUG
        printf("\n\n");
        #endif
    }
    
    #ifdef DEBUG

    printf("total\n");
    cur_bb=bb_head;
    while(cur_bb){
        print_BB(cur_bb);
        printf("suc:\n");
        if(cur_bb->suc==NULL){
            printf("\n");
            cur_bb=cur_bb->nextbb;
            continue;
        }
        BBs head=cur_bb->suc->head;
        BBs temp_bbs=head;
        if(temp_bbs){
            print_BB(temp_bbs->bb);
        }
        temp_bbs=temp_bbs->next;
        while(temp_bbs!=head){
            print_BB(temp_bbs->bb);
            temp_bbs=temp_bbs->next;
        }

        printf("\n");

        printf("pre:\n");
        if(cur_bb->pre==NULL){
            printf("\n");
            cur_bb=cur_bb->nextbb;
            continue;
        }
        head=cur_bb->pre->head;
        temp_bbs=head;
        if(temp_bbs){
            print_BB(temp_bbs->bb);
        }
        temp_bbs=temp_bbs->next;
        while(temp_bbs!=head){
            print_BB(temp_bbs->bb);
            temp_bbs=temp_bbs->next;
        }

        printf("\n");
        cur_bb=cur_bb->nextbb;
    }
    #endif
}

void OR(char *result,char * op){
    for(int i=0;i<variable_numer;i++){
        result[i]=result[i]||op[i];
    }
}

void print_activate_variable(char *act){
    for(int i=0;i<variable_numer;i++){
        if(act[i]){
            printf("%s ",variable[i]);
        }
    }
    printf("\n");
}

void LA(){
    //起码是现在的想法：我不需要知道每一句是否是活跃的，只要按照基本块来划分就可以
    
    BasicBlock cur_bb=bb_tail;
    while(cur_bb){
        //先统计基本块的 use define
        InterCodeList first=cur_bb->first;
        InterCodeList last=cur_bb->last;
        InterCodeList cur_irlist=first;
        int cur_bb_no=cur_bb->bb_no;

        memset(block_def[cur_bb_no],0,sizeof(block_def[cur_bb_no]));
        memset(block_use[cur_bb_no],0,sizeof(block_use[cur_bb_no]));

        while(cur_irlist!=last){
            int ir_no=cur_irlist->ir_no;
            OR(block_def[cur_bb_no],def[ir_no]);
            OR(block_use[cur_bb_no],use[ir_no]);
        }
        int ir_no=cur_irlist->ir_no;
        OR(block_def[cur_bb_no],def[ir_no]);
        OR(block_use[cur_bb_no],use[ir_no]);


        print_BB(cur_bb);
        printf("def variable:\n");
        print_activate_variable(block_def[cur_bb_no]);
        printf("use variable:\n");
        print_activate_variable(block_use[cur_bb_no]);

        cur_bb=cur_bb->lastbb;
    }
}