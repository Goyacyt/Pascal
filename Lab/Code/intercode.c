#include "intercode.h"
InterCodeList irlist_head;
ArgList arglist_head=NULL;
extern int intercode_de;
static int temp_no=1;
static int label_no=1;
static int address_no=1;
void init_irlist(){
    irlist_head=(InterCodeList)malloc(sizeof(struct InterCodeList_));
    assert(irlist_head!=NULL);
    irlist_head->code=NULL;
    irlist_head->prev=irlist_head;
    irlist_head->next=irlist_head;
    return;
}

InterCodeList insert_ir(InterCode ir){
    assert(ir!=NULL);
    InterCodeList irlist_node=NULL;
    irlist_node=(InterCodeList)malloc(sizeof(struct InterCodeList_));
    assert(irlist_node!=NULL);
    irlist_node->code=ir;
    irlist_node->prev=irlist_head->prev;
    irlist_head->prev->next=irlist_node;
    irlist_head->prev=irlist_node;
    irlist_node->next=irlist_head;
    print_ir(ir);
    return irlist_node;
}

InterCodeList get_irlist(InterCode ir){
    assert(ir!=NULL);
    InterCodeList irlist_node=irlist_head;
    while(memcmp(irlist_node->code,ir,sizeof(struct InterCode_))!=0){
        irlist_node=irlist_node->next;
        if(irlist_node==irlist_head)    break;
    }
    if(irlist_node->code==ir)   return irlist_node;
    else    return NULL;
}

void del_ir(InterCode ir){
    assert(ir!=NULL);
    InterCodeList irlist_node=get_irlist(ir);
    irlist_node->prev->next=irlist_node->next;
    irlist_node->next->prev=irlist_node->prev;
    free(irlist_node);
}

void print_irlist(){
    InterCodeList ir=irlist_head->next;
    assert(ir!=NULL);
    while(ir!=irlist_head){
        assert(ir!=NULL);
        print_ir(ir->code);
        ir=ir->next;
    }
    return;
}

Operand gen_op(int kind,char *name,int number){
    Operand op=(Operand)malloc(sizeof(struct Operand_));
    assert(op!=NULL);
    op->kind=kind;
    switch(kind){
        case OP_VARIABLE:
            op->name=name;
            break;
        case OP_CONSTANT:
            op->number=number;
            break;
        case OP_FUNCTIONNAME:
            op->name=name;
            break;
        case OP_TEMP:
            op->no=temp_no;
            temp_no++;
            break;
        case OP_LABEL:
            op->no=label_no;
            label_no++;
            break;
        case OP_ADDRESS:
            op->no=address_no;
            address_no++;
            break;
        case OP_STRUCTURENAME:
            op->name=name;
            break;
        case OP_ARRAYNAME:
            op->name=name;
            break;
        default:
            assert(0);
    }
    assert(op!=NULL);
    return op;
}

void print_op(Operand op){
    switch(op->kind){
        case OP_VARIABLE:
            printf("%s",op->name);
            break;
        case OP_CONSTANT:            
            printf("#");
            printf("%d",op->number);
            break;
        case OP_FUNCTIONNAME:
            printf("%s",op->name);
            break;
        case OP_TEMP:
            printf("t");
            printf("%d",op->no);
            break;
        case OP_LABEL:
            printf("label%d",op->no);
            break;
        case OP_ADDRESS:
            printf("addr%d",op->no);
            break;
        case OP_ARRAYNAME:
            printf("array(%s)",op->name);
            break;
        case OP_STRUCTURENAME:
            printf("structure(%s)",op->name);
            break;
        default:
            printf("operand kind=%d\n",op->kind);
            assert(0);
    }
    return;
}
InterCode gen_ir(int kind,Operand op1,Operand op2,Operand op3){
    InterCode ir=(InterCode)malloc(sizeof(struct InterCode_));
    assert(ir!=NULL);
    ir->kind=kind;
    switch (kind){
        case IR_LABEL:
            ir->u.one=op1;
            break;
        case IR_FUNCTIONNAME:
            ir->u.one=op1;
            break;
        case IR_GOTO:
            ir->u.one=op1;
            break;
        case IR_PARAM:
            ir->u.one=op1;
            break;
        case IR_ASSIGN:
            ir->u.two.left=op1;
            ir->u.two.right=op2;
            break;
        case IR_ADD:
        case IR_SUB:
        case IR_MUL:
        case IR_DIV:
            ir->u.three.result=op3;
            ir->u.three.op1=op1;
            ir->u.three.op2=op2;
            break;
        case IR_ARG:
            ir->u.one=op1;
            break;
        case IR_READ:
            ir->u.one=op1;
            break;
        case IR_WRITE:
            ir->u.one=op1;
            break;
        case IR_RETURN:
            ir->u.one=op1;
            break;
        case IR_GETVAL:
            ir->u.two.left=op1;
            ir->u.two.right=op2;
            break;
        case IR_GETADDR:
            ir->u.two.left=op1;
            ir->u.two.right=op2;
            break;       
        defalut:
            assert(0);
    }
    return ir;
}


void print_ir(InterCode ir){
    switch (ir->kind){
        case IR_GETVAL:
            print_op(ir->u.two.left);
            printf(" := *");
            print_op(ir->u.two.right);
            break;
        case IR_GETADDR:
            print_op(ir->u.two.left);
            printf(" := &");
            print_op(ir->u.two.right);
            break;
        case IR_LABEL:
            printf("LABEL ");
            assert(ir->u.one->kind==OP_LABEL);
            print_op(ir->u.one);
            printf(" :");
            break;
        case IR_FUNCTIONNAME:
            printf("FUNCTION ");
            assert(ir->u.one->kind==OP_FUNCTIONNAME);
            print_op(ir->u.one);
            printf(" :");
            break;
        case IR_READ:
            printf("READ ");
            print_op(ir->u.one);
            break;
        case IR_WRITE:
            printf("WRITE ");
            print_op(ir->u.one);
            break;
        case IR_RETURN:
            printf("RETURN ");
            print_op(ir->u.one);
            break;
        case IR_GOTO:
            printf("GOTO ");
            assert(ir->u.one->kind==OP_LABEL);
            print_op(ir->u.one);
            break;
        case IR_PARAM:
            printf("PARAM ");
            print_op(ir->u.one);
            break;
        case IR_ASSIGN:
            print_op(ir->u.two.left);
            printf(" := ");
            print_op(ir->u.two.right);
            break;
        case IR_ADD:
            print_op(ir->u.three.result);
            printf(" := ");
            print_op(ir->u.three.op1);
            printf(" + ");
            print_op(ir->u.three.op2);
            break;
        case IR_SUB:
            print_op(ir->u.three.result);
            printf(" := ");
            print_op(ir->u.three.op1);
            printf(" - ");
            print_op(ir->u.three.op2);
            break;
        case IR_MUL:
            print_op(ir->u.three.result);
            printf(" := ");
            print_op(ir->u.three.op1);
            printf(" * ");
            print_op(ir->u.three.op2);
            break;
        case IR_DIV:
            print_op(ir->u.three.result);
            printf(" := ");
            print_op(ir->u.three.op1);
            printf(" / ");
            print_op(ir->u.three.op2);
            break;
        case IR_ARG:
            printf("ARG ");
            print_op(ir->u.one);
            break;
        case IR_IFGOTO:
            printf("IF ");
            print_op(ir->u.ifgoto.op1);
            printf(" %s ",ir->u.ifgoto.relop);
            print_op(ir->u.ifgoto.op2);
            printf(" GOTO ");
            print_op(ir->u.ifgoto.label);
            break;
        case IR_DEC:
            printf("DEC ");
            print_op(ir->u.dec.var);
            printf(" %d",ir->u.dec.size);
            break;
        defalut:
            assert(0);
    }
    printf("\n");
    return;
}

int get_size(Type type){ 
    if(type==NULL)
        return 0;
    int size=0;
    switch(type->kind){
        case STRUCTURE:
            FieldList strumb_field=type->u.structval;
            while(strumb_field!=NULL){
                size+=get_size(strumb_field->type);
                strumb_field=strumb_field->tail;
            }
            break;
        case ARRAY:
            Type arrmb_type=type->u.array.elem;
            size=get_size(arrmb_type)*type->u.array.size;
            break;
        case BASIC:
            size=4;
            break;
        default:
            assert(0);
    }
    return size;
}

Operand get_value(Operand addr){
    assert(addr->kind==OP_ADDRESS||addr->kind==OP_ARRAYNAME||addr->kind==OP_STRUCTURENAME);
    Operand value_op=gen_op(OP_TEMP,NULL,-1);
    insert_ir(gen_ir(IR_GETVAL,value_op,addr,NULL));
    return value_op;
}

Operand get_address(Operand value){
    Operand addr_op=gen_op(OP_ADDRESS,NULL,-1);
    insert_ir(gen_ir(IR_GETADDR,value,addr_op,NULL));
    return addr_op;
}

FieldList get_struname_field(node* root){  //root:exp->exp.id
    assert(root->son_num==3);
    node* struname=root->son;
    assert(strcmp(struname->bro->name,"DOT")==0);
    assert(struname->bro->bro->type==TYPE_ID);
    while(struname->son_num==3){
        struname=struname->son;
    }
    if(struname->son_num!=1) assert(0);
    HashNode struct_hashnode=get(ID(struname));
    assert(struct_hashnode!=NULL);
    FieldList struct_field=struct_hashnode->value;
    assert(struct_field->type->kind==STRUCTURE);
    return struct_field;
}

FieldList get_arrname_field(node* root){  //Exp->Exp [ INT ]
    assert(root->son_num==4);
    node* arrname=root->son;
    assert(strcmp(arrname->bro->name,"LB")==0);
    assert(arrname->bro->bro->type==TYPE_INT);
    while(arrname->son_num==4){
        arrname=arrname->son;
    }
    if(arrname->son_num!=1) assert(0);
    HashNode arr_hashnode=get(ID(arrname));
    assert(arr_hashnode!=NULL);
    FieldList arr_field=arr_hashnode->value;
    assert(arr_field->type->kind==ARRAY);
    return arr_field;
}


void translate_Program(node* root) {    // Program -> ExtDefList
    assert(root!=NULL);
    assert(root->son_num == 1);
    init_irlist();
    translate_ExtDefList(root->son);
    //print_irlist();
    return;
}

void translate_ExtDefList(node* root){
    if(root==NULL)
        return ;
    if(intercode_de)  printf("%d\n",root->son_num);
    node* son1=root->son;
    node* son2=son1->bro;
    translate_ExtDef(son1);
    translate_ExtDefList(son2);
    return;
}

void translate_ExtDef(node* root){
    if(intercode_de)  printf("%d\n",root->son_num);
    node* son1=NULL;
    node* son2=NULL;
    node* son3=NULL;
    son1=root->son;
    son2=son1->bro;
    if(root->son_num==3){
        if(strcmp(son2->name,"ExtDecList")==0)     //ExtDef->Specifier ExtDecList SEMI：全局变量定义，按要求不会出现
            assert(0);
        else if(strcmp(son2->name,"FunDec")==0){ 
            son3=son2->bro;
            if(strcmp(son3->name,"CompSt")==0){     //ExtDef->Specifier FunDef CompSt ： 函数定义
                translate_FunDec(son2);
                translate_CompSt(son3);
            }
            else                               //ExtDef->Specifier FunDef ：函数声明
                assert(0);
        }
    }
    else if(root->son_num==2){
        if(strcmp(son2->name,"SEMI")==0){ //ExtDef->Specifier SEMI:结构体定义
            //do nothing?
        }
        else    assert(0);
    }
    else    assert(0);
    return ;
}

void translate_FunDec(node* root){
    int line=root->first_line;
    assert(root->son_num==3|root->son_num==4);
    node* id=root->son;
    char* fun_name=ID(id);
    HashNode this=get(fun_name);
    assert(this!=NULL);
    Operand funcname_op=gen_op(OP_FUNCTIONNAME,fun_name,-1);
    InterCode funcname_ir=gen_ir(IR_FUNCTIONNAME,funcname_op,NULL,NULL);
    insert_ir(funcname_ir);
    FieldList function_field=this->value;
    assert(function_field->type->kind==FUNCTION&&function_field->type->u.function.declare==DEFINED);
    assert(function_field!=NULL);
    if(root->son_num==4){   //FunDec->ID ( VarList )
        node* varlist=id->bro->bro;
        FieldList varlist_field=function_field->type->u.function.param;
        while(varlist_field!=NULL){
            assert(varlist_field->type->kind==BASIC||varlist_field->type->kind==STRUCTURE||varlist_field->type->kind==ARRAY);
            Operand param=gen_op(OP_VARIABLE,varlist_field->name,-1);              
            
            InterCode funparam_ir=gen_ir(IR_PARAM,param,NULL,NULL);
            insert_ir(funparam_ir);

            varlist_field=varlist_field->tail;
        }
    }
    else{                  //FunDec->ID ( )
        //skip
    }
    return;
}

void translate_CompSt(node* root){
    //这里面有两个可以为空的指针:deflist 和stmtlist不进行检查就可能把rc当作stmtlist或者deflist
    assert(root->son_num==3||root->son_num==4);
    node* son2=root->son->bro;
    if(strcmp(son2->name,"DefList")==0){    //CompSt->{ DefList StmtList }
        translate_DefList(son2);
        node* son3=son2->bro;
        if(strcmp(son3->name,"StmtList")==0){
            translate_StmtList(son3);
        }
    }else{                                  //CompSt->{ StmtList }
        if(strcmp(son2->name,"StmtList")==0){
            translate_StmtList(son2);
        }
    }
    return;
}

void translate_DefList(node* root){
    if(root==NULL){ //deflist->null
        return;
    }else{  //DefList->Def DefList
        assert(root->son_num==2);
        node* def=root->son;
        translate_Def(def);
        node* deflist=def->bro;
        translate_DefList(deflist);
        return;
    }
}

void translate_Def(node* root){  //Def->Specifier DecList ;
    assert(root->son_num==3);
    node* declist=root->son->bro;
    translate_DecList(declist);
    return;
}

void translate_DecList(node* root){
    assert(root->son_num==1||root->son_num==3);
    if(root->son_num==1){       //DecList->Dec
        node* dec=root->son;
        translate_Dec(dec);
    }
    else{                       //DecList->Dec COMMA DecList
        node* dec=root->son;
        translate_Dec(dec);
        node* declist=dec->bro->bro;
        translate_DecList(declist);
    }
    return;
}

void translate_Dec(node* root){
    assert(root->son_num==1||root->son_num==3);
    node* vardec=root->son;
    if(root->son_num==1){       //Dec->VarDec
        translate_VarDec(vardec);
    }
    else if(root->son_num==3){ //Dec->VarDec ASSIGNOP Exp
        assert(vardec->son_num==1); //VarDec->ID
        node* exp=vardec->bro->bro;
        Operand id_op=translate_VarDec(vardec); 
        Operand temp=gen_op(OP_TEMP,NULL,-1);
        translate_Exp(exp,temp);

        if(id_op->kind==OP_ADDRESS||id_op->kind==OP_ARRAYNAME||id_op->kind==OP_STRUCTURENAME)
            id_op=get_value(id_op);
        InterCode dec_ir=gen_ir(IR_ASSIGN,id_op,temp,NULL);
        insert_ir(dec_ir);
    }
    return;
}


Operand translate_VarDec(node* root){
    assert(root->son_num==1||root->son_num==4);
    char* id=ID(root->son);
    HashNode this=get(id);
    assert(this!=NULL);
    FieldList vardec_field=this->value;
    Operand id_op=NULL;      

    InterCode vardec_ir=(InterCode)malloc(sizeof(struct InterCode_));
    assert(vardec_ir!=NULL);
    if(root->son_num==1){       //VarDec->ID
        switch(vardec_field->type->kind){
            case BASIC:
                id_op=gen_op(OP_VARIABLE,vardec_field->name,-1);
                break;
            case STRUCTURE:
                id_op=gen_op(OP_STRUCTURENAME,vardec_field->name,-1);
                vardec_ir->kind=IR_DEC;
                vardec_ir->u.dec.size=get_size(vardec_field->type);
                vardec_ir->u.dec.var=id_op;
                insert_ir(vardec_ir); //添加Dec [SIZE] 语句
                break;
            case ARRAY:
                id_op=gen_op(OP_ARRAYNAME,vardec_field->name,-1);
                vardec_ir->kind=IR_DEC;
                vardec_ir->u.dec.size=get_size(vardec_field->type);
                vardec_ir->u.dec.var=id_op;
                insert_ir(vardec_ir); //添加Dec [SIZE] 语句
                break;                
            default:
                assert(0);
            }
    }
    else if(root->son_num==4){ //VarDec->VarDec [ INT ]
        id_op=translate_VarDec(root->son);
    }
    else    assert(0);
    return id_op;
}

void translate_StmtList(node* root){
    assert(root==NULL||root->son_num==2);
    if(root==NULL){ //StmtList->null
        return;
    }
    node* stmt=root->son;
    translate_Stmt(stmt);
    node* stmtlist=stmt->bro;
    translate_StmtList(stmtlist);
    return;
}

void translate_Stmt(node* root){
    if(root->son_num==2){           //Stmt->Exp SEMI
        node* exp=root->son;
        Operand t=gen_op(OP_TEMP,NULL,-1);
        translate_Exp(exp,t);
    }else if(root->son_num==1){     //Stmt->CompSt
        node* compst=root->son;
        translate_CompSt(compst);
    }else if(root->son_num==3){     //Stmt->RETURN Exp SEMI
        node* exp=root->son->bro;
        Operand t=gen_op(OP_TEMP,NULL,-1);
        translate_Exp(exp,t);
        //返回值只能是int/float
        InterCode return_ir=gen_ir(IR_RETURN,t,NULL,NULL);
        insert_ir(return_ir);
    }else if(root->son_num==5){
        if(strcmp(root->son->name,"IF")==0){    //Stmt -> IF ( exp ) Stmt
            node* exp=root->son->bro->bro;
            node* stmt=exp->bro->bro;
            Operand label1=gen_op(OP_LABEL,NULL,-1);
            Operand label2=gen_op(OP_LABEL,NULL,-1);
            translate_Cond(exp,label1,label2);

            InterCode label1_ir=gen_ir(IR_LABEL,label1,NULL,NULL);
            insert_ir(label1_ir);
            translate_Stmt(stmt);
            InterCode label2_ir=gen_ir(IR_LABEL,label2,NULL,NULL);      
            insert_ir(label2_ir);

            Operand t=gen_op(OP_TEMP,NULL,-1);
            translate_Exp(exp,t);
        }
        else if(strcmp(root->son->name,"WHILE")==0){     //Stmt -> WHILE ( exp ) Stmt
            node* exp=root->son->bro->bro;
            node* stmt=exp->bro->bro;

            Operand label1=gen_op(OP_LABEL,NULL,-1);
            Operand label2=gen_op(OP_LABEL,NULL,-1);
            Operand label3=gen_op(OP_LABEL,NULL,-1);

            InterCode label1_ir=gen_ir(IR_LABEL,label1,NULL,NULL);  
            insert_ir(label1_ir);

            translate_Cond(exp,label2,label3);

            InterCode label2_ir=gen_ir(IR_LABEL,label2,NULL,NULL);
            insert_ir(label2_ir);

            translate_Stmt(stmt);

            InterCode goto_ir=gen_ir(IR_GOTO,label1,NULL,NULL);
            insert_ir(goto_ir);

            InterCode label3_ir=gen_ir(IR_LABEL,label3,NULL,NULL);
            insert_ir(label3_ir);            
        }
        else    assert(0);
    }
    else if(root->son_num==7){      //Exp->IF ( Exp ) Stmt ELSE Stmt
        node* exp=root->son->bro->bro;
        node* stmt1=exp->bro->bro;
        node* stmt2=stmt1->bro->bro;

        Operand label1=gen_op(OP_LABEL,NULL,-1);
        Operand label2=gen_op(OP_LABEL,NULL,-1);
        Operand label3=gen_op(OP_LABEL,NULL,-1);

        InterCode label1_ir=gen_ir(IR_LABEL,label1,NULL,NULL);
        InterCode label2_ir=gen_ir(IR_LABEL,label2,NULL,NULL);
        InterCode label3_ir=gen_ir(IR_LABEL,label3,NULL,NULL);
        InterCode goto_ir=gen_ir(IR_GOTO,label3,NULL,NULL);

        translate_Cond(exp,label2,label3);
        insert_ir(label1_ir);
        translate_Stmt(stmt1);
        insert_ir(goto_ir);
        insert_ir(label2_ir);
        translate_Stmt(stmt2);
        insert_ir(label3_ir);        
    }
    else assert(0);
    return ;
}

void translate_Cond(node* root,Operand label_true,Operand label_false){
    if((root->son_num==3)&&(strcmp(root->son->bro->name,"RELOP")==0)){  //Cond->Exp RELOPE Exp
        node* exp1=root->son;
        node* relop=exp1->bro;
        node* exp2=relop->bro;
        assert(relop->type==TYPE_RELOP);
        Operand t1=gen_op(OP_TEMP,NULL,-1);
        Operand t2=gen_op(OP_TEMP,NULL,-1);
        InterCode ifgoto_ir=(InterCode)malloc(sizeof(struct InterCode_));
        assert(ifgoto_ir!=NULL);
        ifgoto_ir->kind=IR_IFGOTO;
        ifgoto_ir->u.ifgoto.label=label_true;
        ifgoto_ir->u.ifgoto.op1=t1;
        ifgoto_ir->u.ifgoto.op2=t2;
        sscanf(relop->val.relop_val,"%s",ifgoto_ir->u.ifgoto.relop);
        InterCode goto_ir=gen_ir(IR_GOTO,label_false,NULL,NULL);

        translate_Exp(exp1,t1);
        translate_Exp(exp2,t2);
        insert_ir(ifgoto_ir);
        insert_ir(goto_ir);
    }
    else if((root->son_num==3)&&(strcmp(root->son->bro->name,"AND")==0)){   //Cond->Exp AND Exp
        node* exp1=root->son;
        node* exp2=exp1->bro->bro;
        Operand label=gen_op(OP_LABEL,NULL,-1);
        InterCode label_ir=gen_ir(IR_LABEL,label,NULL,NULL);
        translate_Cond(exp1,label,label_false);
        insert_ir(label_ir);
        translate_Cond(exp2,label_true,label_false);
    }
    else if((root->son_num==3)&&(strcmp(root->son->bro->name,"OR")==0)){    //Cond->Exp OR Exp
        node* exp1=root->son;
        node* exp2=exp1->bro->bro;
        Operand label=gen_op(OP_LABEL,NULL,-1);
        InterCode label_ir=gen_ir(IR_LABEL,label,NULL,NULL); 

        translate_Cond(exp1,label_true,label);
        insert_ir(label_ir);
        translate_Cond(exp2,label_true,label_false);       
    }
    else if((root->son_num==2)&&(strcmp(root->son->name,"NOT")==0)){    //Cond->NOT Exp
        node* exp=root->son->bro;
        translate_Cond(exp,label_false,label_true);
    }
    else{
        Operand t=gen_op(OP_TEMP,NULL,-1);
        Operand c=gen_op(OP_CONSTANT,NULL,0);
        InterCode ifgoto_ir=(InterCode)malloc(sizeof(struct InterCode_));;
        assert(ifgoto_ir!=NULL);
        ifgoto_ir->kind=IR_IFGOTO;
        ifgoto_ir->u.ifgoto.label=label_true;
        ifgoto_ir->u.ifgoto.op1=t;
        ifgoto_ir->u.ifgoto.op2=c;
        sscanf("!=","%s",ifgoto_ir->u.ifgoto.relop);
    }
}

void translate_Exp(node* root,Operand place){
    if(root->son_num==1){
        if(strcmp(root->son->name,"INT")==0){
            node* int_node=root->son;
            assert(int_node->type==TYPE_INT);
            Operand c=gen_op(OP_CONSTANT,NULL,int_node->val.int_val);
            InterCode assign_ir=gen_ir(IR_ASSIGN,place,c,NULL);
            insert_ir(assign_ir);
        }
        else if(strcmp(root->son->name,"ID")==0){
            node* id_node=root->son;
            char* idchar=ID(id_node);
            HashNode id_hashnode=get(idchar);
            assert(id_hashnode!=NULL);
            FieldList id_field=id_hashnode->value;
            switch(id_field->type->kind){
                case BASIC:
                    place->kind=OP_VARIABLE;
                    place->name=idchar;
                    break;
                case ARRAY:
                    place->kind=OP_ARRAYNAME;
                    place->type=id_field->type;
                    place->name=idchar;
                    break;
                case STRUCTURE:
                    place->kind=OP_STRUCTURENAME;
                    place->type=id_field->type;
                    place->name=idchar;
                    break;
                defalut: assert(0);
            }
            // Operand id_op=gen_op(OP_VARIABLE,ID(id_node),-1);
            // InterCode assign_ir=gen_ir(IR_ASSIGN,place,id_op,NULL);
            // insert_ir(assign_ir);
        }
        else if(strcmp(root->son->name,"FLOAT")==0){
            //按要求应该不会出现浮点型常数，应该也不会出现浮点型数组吧
            assert(0);
        }
        else    assert(0);
    }
    else if(root->son_num==2){
        if(strcmp(root->son->name,"MINUS")==0){  //Exp->MINUS Exp
            node* exp=root->son->bro;
            Operand t1=gen_op(OP_TEMP,NULL,-1);
            Operand c=gen_op(OP_CONSTANT,NULL,0);
            InterCode neg_ir=gen_ir(IR_SUB,c,t1,place);
            translate_Exp(exp,t1);
            insert_ir(neg_ir);

        }
        else if(strcmp(root->son->name,"NOT")==0){   //Exp->NOT Exp
            node* exp=root;
            Operand label1=gen_op(OP_LABEL,NULL,-1);
            Operand label2=gen_op(OP_LABEL,NULL,-1);
            Operand c0=gen_op(OP_CONSTANT,NULL,0);
            Operand c1=gen_op(OP_CONSTANT,NULL,1);
            InterCode assign0_ir=gen_ir(IR_ASSIGN,place,c0,NULL);
            InterCode label1_ir=gen_ir(IR_LABEL,label1,NULL,NULL);
            InterCode assign1_ir=gen_ir(IR_ASSIGN,place,c1,NULL);
            InterCode label2_ir=gen_ir(IR_LABEL,label2,NULL,NULL);

            insert_ir(assign0_ir);
            translate_Cond(exp,label1,label2);
            insert_ir(label1_ir);
            insert_ir(assign1_ir);
            insert_ir(label2_ir);

        }
        else    assert(0);
    }
    else if(root->son_num==3){
        if((strcmp(root->son->bro->name,"RELOP")||(strcmp(root->son->bro->name,"AND")==0)||(strcmp(root->son->bro->name,"OR")==0))==0){ 
            node* exp=root;
            Operand label1=gen_op(OP_LABEL,NULL,-1);
            Operand label2=gen_op(OP_LABEL,NULL,-1);
            Operand c0=gen_op(OP_CONSTANT,NULL,0);
            Operand c1=gen_op(OP_CONSTANT,NULL,1);
            InterCode assign0_ir=gen_ir(IR_ASSIGN,place,c0,NULL);
            InterCode label1_ir=gen_ir(IR_LABEL,label1,NULL,NULL);
            InterCode assign1_ir=gen_ir(IR_ASSIGN,place,c1,NULL);
            InterCode label2_ir=gen_ir(IR_LABEL,label2,NULL,NULL);

            insert_ir(assign0_ir);
            translate_Cond(exp,label1,label2);
            insert_ir(label1_ir);
            insert_ir(assign1_ir);
            insert_ir(label2_ir);
        }
        else if((strcmp(root->son->bro->name,"ASSIGNOP")==0)){   //Exp->Exp ASSIGN Exp
            node* exp1=root->son;
            node* exp2=exp1->bro->bro;
            Operand t1=gen_op(OP_TEMP,NULL,-1);
            Operand t2=gen_op(OP_TEMP,NULL,-1);
            translate_Exp(exp1,t1);
            translate_Exp(exp2,t2);
            InterCode assign_ir=gen_ir(IR_ASSIGN,t1,t2,NULL);
            insert_ir(assign_ir);
        }
        else if(strcmp(root->son->bro->name,"PLUS")==0){
            node* exp1=root->son;
            node* exp2=exp1->bro->bro;
            Operand t1=gen_op(OP_LABEL,NULL,-1);
            Operand t2=gen_op(OP_LABEL,NULL,-1);
            InterCode add_ir=gen_ir(IR_ADD,t1,t2,place);

            translate_Exp(exp1,t1);
            translate_Exp(exp2,t2);
            insert_ir(add_ir);
        }
        else if(strcmp(root->son->bro->name,"MINUS")==0){
            node* exp1=root->son;
            node* exp2=exp1->bro->bro;
            Operand t1=gen_op(OP_LABEL,NULL,-1);
            Operand t2=gen_op(OP_LABEL,NULL,-1);
            InterCode sub_ir=gen_ir(IR_SUB,t1,t2,place);

            translate_Exp(exp1,t1);
            translate_Exp(exp2,t2);
            insert_ir(sub_ir);
        }
        else if(strcmp(root->son->bro->name,"STAR")==0){
            node* exp1=root->son;
            node* exp2=exp1->bro->bro;
            Operand t1=gen_op(OP_LABEL,NULL,-1);
            Operand t2=gen_op(OP_LABEL,NULL,-1);
            InterCode mul_ir=gen_ir(IR_MUL,t1,t2,place);

            translate_Exp(exp1,t1);
            translate_Exp(exp2,t2);
            insert_ir(mul_ir);
        }
        else if(strcmp(root->son->bro->name,"DIV")==0){
            node* exp1=root->son;
            node* exp2=exp1->bro->bro;
            Operand t1=gen_op(OP_LABEL,NULL,-1);
            Operand t2=gen_op(OP_LABEL,NULL,-1);
            InterCode div_ir=gen_ir(IR_DIV,t1,t2,place);
            translate_Exp(exp1,t1);
            translate_Exp(exp2,t2);
            insert_ir(div_ir);
        }

        else if(strcmp(root->son->name,"ID")==0){   //Exp->ID ( )
            node* funct_name=root->son;
            HashNode funct_hashnode=get(ID(funct_name));
            assert(funct_hashnode!=NULL);
            FieldList funct_field=funct_hashnode->value;
            InterCode call_ir=NULL;
            if(strcmp(funct_field->name,"read")==0)
                call_ir=gen_ir(IR_READ,gen_op(OP_TEMP,NULL,-1),NULL,NULL);
            else{
                call_ir=gen_ir(IR_FUNCTIONNAME,gen_op(OP_FUNCTIONNAME,funct_field->name,-1),NULL,NULL);
            }
            insert_ir(call_ir);
        }
        else if(strcmp(root->son->bro->name,"DOT")==0){ //Exp->Exp.ID :得到addr类place
            node* exp=root->son;
            node* id=exp->bro->bro;
            char* id_char=ID(id);
            Operand base_op=gen_op(OP_ADDRESS,NULL,-1);
            translate_Exp(exp,base_op);

            place->kind=OP_ADDRESS;
            place->no=address_no;
            address_no++;

            FieldList structmb_field=base_op->type->u.structval;
            int off=0;
            while((structmb_field!=NULL)&&(strcmp(structmb_field->name,id_char)==0)){
                off+=get_size(structmb_field->type);
                structmb_field=structmb_field->tail;
            }
            assert(structmb_field);
            place->type=structmb_field->type;


            if(base_op->kind==OP_STRUCTURENAME){
                assert(exp->son->type==TYPE_ID);
                assert(base_op->type->kind==STRUCTURE);
                base_op=get_address(base_op);
            }
            else
                assert(base_op->kind==OP_ADDRESS);
            
            Operand offset=gen_op(OP_CONSTANT,NULL,off);
            insert_ir(gen_ir(IR_ADD,base_op,offset,NULL));
        }

        else if(strcmp(root->son->name,"LP")==0){    //Exp->(Exp)
            translate_Exp(root->son,place);
        }
        else assert(0);
    }
    else if(root->son_num==4){
        if(strcmp(root->son->bro->name,"LP")==0){    //Exp->ID ( Args )
            node* funct_name=root->son;
            node* args=funct_name->bro->bro;
            HashNode funct_hashnode=get(ID(funct_name));
            assert(funct_hashnode!=NULL);
            FieldList funct_field=funct_hashnode->value;
            Operand functname_op=gen_op(OP_FUNCTIONNAME,funct_field->name,-1);

            if(arglist_head!=NULL){
                ArgList arglist=arglist_head->next;
                while(arglist!=NULL){
                    ArgList freearg=arglist;
                    arglist=arglist->next;
                    free(freearg);
                    freearg=NULL;
                }
            }
            arglist_head=NULL;
            translate_Args(args);
            InterCode call_ir=NULL;
            if(strcmp(funct_field->name,"write")==0){
                call_ir=gen_ir(IR_WRITE,arglist_head->arg,NULL,NULL);
                insert_ir(call_ir);
            }
            else{
                ArgList arglist=arglist_head;
                while(arglist!=NULL){
                    call_ir=gen_ir(IR_ARG,arglist->arg,NULL,NULL);
                    arglist=arglist->next;
                    insert_ir(call_ir);
                }
                call_ir=gen_ir(IR_FUNCTIONNAME,functname_op,NULL,NULL);
                insert_ir(call_ir);
            }
        }
        else if(strcmp(root->son->bro->name,"LB")==0){   //Exp->Exp [ Exp ]
            node* exp1=root->son;
            node* exp2=exp1->bro->bro;

            Operand base_op=gen_op(OP_ADDRESS,NULL,-1);
            translate_Exp(exp1,base_op);

            place->kind=OP_ADDRESS;
            place->no=address_no;
            address_no++;
            place->type=base_op->type->u.array.elem;

            if(base_op->kind==OP_ARRAYNAME){
                assert(exp1->type==TYPE_ID);
                assert(base_op->type->kind==ARRAY);
                base_op=get_address(base_op);
            }
            else    assert(base_op->kind==OP_ADDRESS);


            Operand index_op=gen_op(OP_TEMP,NULL,-1);   //偏移值
            translate_Exp(exp2,index_op);
            if(index_op->kind==OP_ADDRESS)  index_op=get_value(index_op);

            Operand offset=gen_op(OP_TEMP,NULL,-1); //[]内总偏移量
            Operand intvl=gen_op(OP_CONSTANT,NULL,get_size(base_op->type)); //数组元素宽度
            if(index_op->kind==OP_CONSTANT){
                offset->kind=OP_CONSTANT;
                offset->number=index_op->number*intvl->number;
            }
            else{
                insert_ir(gen_ir(IR_MUL,index_op,intvl,offset));  //{offset:=index*intvl}
            }
            insert_ir(gen_ir(IR_ADD,base_op,offset,place));

        }
        else    assert(0);
    }
}
void translate_Args(node* root) {
    assert(root->son_num == 1 || root->son_num == 3);
    node* exp=root->son;

    Operand temp=gen_op(OP_TEMP,NULL,-1);
    translate_Exp(exp,temp);
    

    if(arglist_head!=NULL){
        ArgList arglist=arglist_head;
        ArgList argnode=(ArgList)malloc(sizeof(struct ArgList_));
        assert(argnode!=NULL);
        argnode->arg=temp;
        argnode->next=NULL;
        while(arglist->next==NULL){
            arglist=arglist->next;
        }
        arglist->next=argnode;
    }
    else{
        arglist_head=(ArgList)malloc(sizeof(struct ArgList_));
        assert(arglist_head);
        arglist_head->arg=temp;
        arglist_head->next=NULL;
    }
    
    if(root->son_num==3){    //Args->Exp COMMA Args
        translate_Args(exp->bro->bro);
    }

    return;
}