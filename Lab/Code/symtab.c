#include "symtab.h"
#include <string.h>
#include "tree.h"
HashNode hash_tab[HASHTAB_SIZE+1];
HashNode stack[STACK_SIZE+1];
node* declare_func[100];
extern int semantic_de;
extern int sdep;
//TODO:错误15涉及到压到不同层栈的问题，还没有解决

unsigned int hash_fun(char* name){
    unsigned int val=0,i;
    for(;*name;++name){
        val=(val<<2)+*name;
        if(i=val&~HASHTAB_SIZE) val=(val^(i>>12))&0x3fff;
    }
    return val;
}

void init_hashtab(){
    for(int i=0;i<=HASHTAB_SIZE;i++)
        hash_tab[i]=NULL;
    return;
}

void init_stack(){
    sdep=0;
    for(int i=0;i<=STACK_SIZE;i++)
        stack[i]=NULL;
    return;
}

HashNode get(char* name){
    debug("get begin");
    int pos=hash_fun(name);
    debugi("get pos",pos);
    HashNode p=hash_tab[pos];
    if(p==NULL)
        debug("not find");
    while(p!=NULL){
        if(strcmp(p->value->name,name)==0)
            return p;
        p=p->slot_next;
    }
    debug("get end");
    return NULL;
}

HashNode add_sym(FieldList value,int stack_dep,int line){
    if(strcmp(value->name,"Stack")==0){
        
    }
    debug("add_sym begin");
    int pos=hash_fun(value->name);
    debugi("hash pos",pos); 
    if(pos>=HASHTAB_SIZE){
        debug("hash overflow");
        assert(0);
    }
    //HashNode slot_head=hash_tab[pos];//hash槽的表头
    if(stack_dep>=STACK_SIZE){
        debug("stack overflow");
        assert(0);
    }
    //HashNode stack_head=stack[stack_dep];//这一层栈的表头
    HashNode p = (HashNode)malloc(sizeof (struct HashNode_));
    assert(p!=NULL);
    p->first_line=line;
    p->stack_dep=stack_dep;
    p->value=value;
    p->slot_next=NULL;
    p->stack_next=NULL;
    //变量插入到hash槽的头部
    debug("add hash");
    p->slot_next=hash_tab[pos];
    hash_tab[pos]=p;
    //变量插入到这一层变量定义栈的头部也可以
    debug("add stack");
    p->stack_next=stack[stack_dep];
    stack[stack_dep]=p;
    debug("add_sym end");
    return p;
}

int push_stack(){
    sdep+=1;
    return sdep;
}

int pop_stack(){
    //栈顶的hashnode肯定都位于hash槽的头部，一个一个删掉
    HashNode stack_head=stack[sdep];
    while(stack_head!=NULL){
        char* name=stack_head->value->name;
        int pos=hash_fun(name);
        HashNode p=hash_tab[pos];
        HashNode last=hash_tab[pos];
        if(strcmp(p->value->name,name)==0){
            hash_tab[pos]=p->slot_next;
        }else{
            p=p->slot_next;
            while(p!=NULL){
                if(strcmp(p->value->name,name)==0){
                    break;
                }
                p=p->slot_next;
                last=last->slot_next;
            }
            if(p==NULL){
                printf("pop_stack error\n");
                assert(0);
            }
            last->slot_next=p->slot_next;
        }
        stack_head=stack_head->stack_next;
    }
    stack[sdep]=NULL;
    sdep-=1;
    return sdep;
}

void check_decfun(){
    HashNode stack_node=stack[0];
    while(stack_node!=NULL){
        if((stack_node->value->type->kind==FUNCTION)&&
        (stack_node->value->type->u.function.declare==DECLARED))
            eprintf(18,stack_node->first_line,"Function declared but not defined");
        stack_node=stack_node->stack_next;
    }
    return;
}




void Program(node* root){
    debug("program");
    init_hashtab();
    init_stack();
    if(root->son!=NULL){
        ExtDefList(root->son);
    }
    assert(sdep==0);
    check_decfun();
    return ;
}
void ExtDefList(node* root){
    debug("extdeflist");
    if(root==NULL){
        return ;
    }
    node* son1=root->son;
    node* son2=son1->bro;
    ExtDef(son1);
    ExtDefList(son2);
    return ;
}
void ExtDef(node* root){
    debug("extdef");
    node* son1=NULL;
    node* son2=NULL;
    node* son3=NULL;
    son1=root->son;
    Type specifier_type=Specifier(son1);
    son2=son1->bro;
    if(strcmp(son2->name,"ExtDecList")==0){ //ExtDef->Specifier ExtDecList SEMI
        //son3=son2->bro;
        ExtDecList(son2,specifier_type);
    }else if(strcmp(son2->name,"FunDec")==0){ 
        son3=son2->bro;
        if(strcmp(son3->name,"CompSt")==0){ 
            //ExtDef->Specifier FunDef CompSt ： 函数定义
            push_stack();
            FunDec(son2,specifier_type,0);
            CompSt(son3,specifier_type);
            pop_stack();
        }
        else{ //ExtDef->Specifier FunDef ：函数声明
            push_stack();
            FunDec(son2,specifier_type,1);
            pop_stack();
        }
    }else if(strcmp(son2->name,"SEMI")==0){
        //这个其实不用做什么？
    }else{
        printf("！！！！ExtDef error in line %d,",root->first_line);
        node *son=son1;
        printf("ExtDef->");
        while(son!=NULL){
            printf("%s ",son->name);
            son=son->bro;
        }
        printf("\n");
    }
    return ;
}

void ExtDecList(node* root,Type type){
    debug("extdeclist");
    node* son1=root->son;
    node* son2=NULL;
    node* son3=NULL;
    if(root->son_num==3){
        son2=son1->bro;
        son3=son2->bro;
        VarDec(son1,type,type);
        ExtDecList(son3,type);
    }else if(root->son_num==1){
        VarDec(son1,type,type);
    }else{
        printf("ExtDecList error\n");
    }
    return ;
}

Type Specifier(node* root){
    debug("Specifier");
    node* son=root->son;
    Type type=(Type)malloc(sizeof(struct Type_));
    if(strcmp(son->name,"TYPE")==0){
        debug("Type");
        type->kind=BASIC;
        if(strcmp(son->val.type_val,"int")==0){
            debug("type :int");
            type->u.basirc=INT;
        }else if(strcmp(son->val.type_val,"float")==0){
            type->u.basirc=FLOAT;
        }else{
            printf("int/float error\n");
        }
    }else if(strcmp(son->name,"StructSpecifier")==0){
        type=StructSpecifier(son);
    }else{
        printf("Specifier error\n");
    }
    debug("before specifier return");
    return type;
}

Type StructSpecifier(node* root){
    debug("StructSpecifier");
    int line=root->first_line;
    Type type=NULL;
    if(root->son_num==5){   //StructSpecifier->STRUCT OptTag { DefList }
        type=(Type)malloc(sizeof(struct Type_));
        node* son2=root->son->bro;
        node* deflist;
        char* struct_name=NULL;
        if(strcmp(son2->name,"OptTag")==0){
            struct_name=OptTag(son2);
            HashNode this=get(struct_name);
            if(this!=NULL){
                eprintf(16,line,"The name of this structure has been defined");
            }
            deflist=son2->bro->bro;
        }else if(strcmp(son2->name,"LC")==0){  //  don't have OptTag
            debug("what's this?");
            deflist=son2->bro;
        }
        FieldList hash_struct_field=(FieldList)malloc(sizeof(struct FieldList_));
        Type hash_type=(Type)malloc(sizeof(struct Type_));
        hash_struct_field->name=struct_name;
        type->kind=STRUCTURE;
        hash_type->kind=STRUCTURE_NAME;
        hash_struct_field->type=hash_type;
               
        type->u.structval=NULL;
        hash_type->u.structtype.structure=NULL;
        hash_type->u.structtype.defok=0;
        if(struct_name!=NULL){
            add_sym(hash_struct_field,0,line);//添加结构体名字的定义信息
        }
        if(strcmp(deflist->name,"DefList")==0){  //DefList可能没有
            push_stack();
            FieldList deflist_field=DefList(deflist,1);
            type->u.structval=deflist_field;
            hash_type->u.structtype.structure=deflist_field;
            hash_type->u.structtype.defok=1;
            pop_stack();
        }

        
    }else if(root->son_num=2){  //StructSpecifier->STRUCT Tag
        node* son2=root->son->bro;
        char* struct_name=Tag(son2);
        HashNode this=get(struct_name);
        if(this==NULL){
            eprintf(17,line,"Undefined Structure Type");
        }else{
            //type=this->value->type;
            if(this->value->type->kind!=STRUCTURE_NAME){
                eprintf(17,line,"Undefined Structure Type");
                type=NULL;
            }
            else if(this->value->type->u.structtype.defok==0){        
                eprintf(17,line,"Use struct val in STRUCT itself");
                type=NULL;
            }
            else{
                //==STRUCTURE
                type=(Type)malloc(sizeof(struct Type_));
                type->kind=STRUCTURE;
                type->u.structval=this->value->type->u.structtype.structure;
            }
        }
    }else{
        printf("StructSpecifier error\n");
    }
    return type;   
}

char* OptTag(node* root){
    debug("OptTag");
    if(root!=NULL){//OptTag->ID
        node* son=root->son;
        return ID(son);
    }else{
        return NULL;
    }
    return NULL;
}

char* Tag(node* root){
    debug("Tag");
    node* son=root->son;
    return ID(son);
}

void FunDec(node* root,Type type,int declare){
    int line=root->first_line;
    debug("FunDec");
    FieldList field=(FieldList)malloc(sizeof(struct FieldList_));
    node* id=root->son;
    char* fun_name=ID(id);
    HashNode this=get(fun_name);
    field->name=fun_name;
    Type FunType=(Type)malloc(sizeof(struct Type_));
    FunType->kind=FUNCTION;
    FunType->u.function.ret=type;
    FieldList varlist_field;
    if(declare){
        FunType->u.function.declare=DECLARED;
    }else{
        FunType->u.function.declare=DEFINED;
    }
    if(root->son_num==4){   //FunDec->ID ( VarList )
        node* varlist=id->bro->bro;
        varlist_field=VarList(varlist);
        FunType->u.function.param=varlist_field;
    }else{
        debug("fundec->id lp rp");
        varlist_field=NULL;
        FunType->u.function.param=varlist_field;
    }
    field->type=FunType;
    if(this!=NULL){
        Type before_type=this->value->type;
        if(before_type->kind==FUNCTION){
            if(!declare){
                //这是函数定义
                if(before_type->u.function.declare==DECLARED){
                    if(!CompareParam(before_type,FunType)){
                        eprintf(19,line,"Confliction between definition and declaration");
                    }
                    this->value->type->u.function.declare=DEFINED;
                    return ;
                }else{
                    eprintf(4,line,"Repeated defintion of function");
                    return ;
                }
            }else{
                //这是函数声明,前面有声明或者定义都可以，只要匹配就行
                if(!CompareParam(before_type,FunType)){
                    eprintf(19,line,"Confliction bwtween declaration and definition or confliction between declaration and declaration.Here is decalration");
                }
                return ;
            }
        }
    }//函数不存在嵌套定义，所以不需要检查sdep

    if(this==NULL){
        add_sym(field,0,line);
    }
    debug("before fundec return");
    return ;
}

int CompareParam(Type left,Type right){
    //检查返回类型
    int res=1;
    if(!CompareType(left->u.function.ret,right->u.function.ret)){
        res=0;
        return res;
    }
    FieldList field1=left->u.function.param;
    FieldList field2=right->u.function.param;
    while(field1!=NULL&&field2!=NULL){
        if(!CompareType(field1->type,field2->type)){
            res=0;
            break;
        }
        field1=field1->tail;
        field2=field2->tail;
    }
    if(field1!=NULL||field2!=NULL){
        //形参数量不一致
        res=0;
    }
    return res;
}

char* ID(node* root){
    debug("ID");
    assert(root->type==TYPE_ID);
    return root->val.id_val;
}

void CompSt(node* root,Type type){
    //这里面有两个可以为空的指针:deflist 和stmtlist不进行检查就可能把rc当作stmtlist或者deflist
    debug("CompSt");
    node* son2=root->son->bro;
    if(strcmp(son2->name,"DefList")==0){
        DefList(son2,0);
        node* son3=son2->bro;
        if(strcmp(son3->name,"StmtList")==0){
            StmtList(son3,type);
        }
    }else{
        if(strcmp(son2->name,"StmtList")==0){
            StmtList(son2,type);
        }
    }
    debug("before compst return");
}

FieldList Def(node* root,int stru){
    debug("Def");
    node* specifier=root->son;
    node* declist=specifier->bro;
    Type specifier_type=Specifier(specifier);
    if(specifier_type!=NULL)
        return DecList(declist,specifier_type,stru);
    else
        return NULL;
}

FieldList DefList(node* root,int stru){
    debug("DefList");
    if(root==NULL){
        debug("deflist->null");
        return NULL;
    }else{
        node* def=root->son;
        FieldList def_field=Def(def,stru);
        node* deflist=def->bro;
        FieldList deflist_field=DefList(deflist,stru);
        if(def_field==NULL){
            return deflist_field;
        }
        FieldList sub_field=def_field;
        while(sub_field->tail!=NULL){
            sub_field=sub_field->tail;
        }
        sub_field->tail=deflist_field;
        //def_field->tail=deflist_field;
        return def_field;
    }
}

FieldList DecList(node* root,Type type,int stru){
    debug("DecList");
    if(root->son_num==1){   //DecList->Dec
        debug("declist->dec");
        node* dec=root->son;
        return Dec(dec,type,stru);
    }else if(root->son_num==3){ //DecList->Dec COMMA DecList
        node* dec=root->son;
        FieldList dec_field=Dec(dec,type,stru);
        node* declist=dec->bro->bro;
        FieldList declist_field=DecList(declist,type,stru);
        if(dec_field==NULL) return declist_field; 
        FieldList sub_field=dec_field;
        while(sub_field->tail!=NULL){
            sub_field=sub_field->tail;
        }
        sub_field->tail=declist_field;
        //dec_field->tail=declist_field;
        return dec_field;
    }else{
        printf("Declist error\n");
    }
    return NULL;
}

FieldList Dec(node* root,Type type,int stru){
    int line=root->first_line;
    debug("Dec");
    node* vardec=root->son;
    FieldList vardec_field=NULL;
    if(root->son_num==1){   //Dec->VarDec
        if(stru==1){
            node* inner_vardec=vardec;
            while(inner_vardec->son_num==4){//数组Vardec    //bug find in A-20
                inner_vardec=inner_vardec->son;
            }
            if(inner_vardec->son_num==1){   
                HashNode this=get(ID(inner_vardec->son));
                if((this!=NULL)&&(this->stack_dep==sdep)){
                    eprintf(15,line,"Redefined field");
                    return vardec_field;//return NULL
                }
            }
        }
        vardec_field=VarDec(vardec,type,type);
    }else if(root->son_num==3){ //Dec->VarDec ASSIGNOP Exp
        if(stru){
            eprintf(15,line,"Assign value when defining struct variable");
            return vardec_field;//return NULL
        }

        node* exp=vardec->bro->bro;
        vardec_field=VarDec(vardec,type,type);
        Type exp_type=Exp(exp);
        if(vardec_field==NULL||exp_type==NULL){
            //其中一个出错
            return NULL;
        }
        Type vardec_type=vardec_field->type;
        if(vardec_type->kind==ARRAY||exp_type->kind==ARRAY){
            eprintf(5,line,"Assign array to some variable");
            vardec_field=NULL;
            //TODO:不确定
        }
        if(!CompareType(exp_type,vardec_type)){
            eprintf(5,line,"Type not match beside the ASSIGNOP");
            vardec_field=NULL;
        }
    }
    return vardec_field;
}

FieldList VarDec(node* root,Type type,Type elemtype){
    int line=root->first_line;
    debug("VarDec");
    if(root->son_num==1){   //VarDec->ID
        char* id=ID(root->son);
        HashNode this=get(id);
        if(this!=NULL){
            if(this->stack_dep==sdep){
                eprintf(3,line,"Redefined variable name");
                return NULL;
            }
            if(this->value->type->kind==STRUCTURE_NAME){
                eprintf(3,line,"definition of variable name the same as structure name before");
                return NULL;
            }
        }
        FieldList field=(FieldList)malloc(sizeof(struct FieldList_));
        field->name=id;
        field->tail=NULL;
        if(elemtype==NULL){
            return NULL;
        }
        if(elemtype->kind==STRUCTURE||elemtype->kind==BASIC||elemtype->kind==STRUCTURE_NAME){
            field->type=elemtype;
        }else if(elemtype->kind==FUNCTION){
            debug("VarDec function error");
        }else{//==ARRAY
            Type subtype=elemtype;
            while(subtype->u.array.elem!=NULL){
                subtype=subtype->u.array.elem;
            }
            subtype->u.array.elem=type;
            field->type=elemtype;
        }
        add_sym(field,sdep,line);
        return field;
    }else if(root->son_num==4){ //VarDec->VarDec [ INT ]
        node* vardec=root->son;
        node* int_node=vardec->bro->bro;
        if(elemtype->kind==ARRAY){//不是第一层数组嵌套
            Type thistype=(Type)malloc(sizeof(struct Type_));
            thistype->kind=ARRAY;
            thistype->u.array.size=int_node->val.int_val;
            thistype->u.array.elem=NULL;
            Type subtype=elemtype;
            while(subtype->u.array.elem!=NULL){
                subtype=subtype->u.array.elem;
            }
            subtype->u.array.elem=thistype;
            return VarDec(vardec,type,elemtype);
        }else{
            //是第一层数组嵌套
            Type thistype=(Type)malloc(sizeof(struct Type_));
            thistype->kind=ARRAY;
            thistype->u.array.size=int_node->val.int_val;
            thistype->u.array.elem=NULL;
            return VarDec(vardec,type,thistype);
        }
    }
    printf("VarDec error\n");
    return NULL;
}

FieldList VarList(node* root){
    debug("VarList");
    if(root->son_num==1){
        //ParamDec
        return ParamDec(root->son);
    }else if(root->son_num==3){
        node* paramdec=root->son;
        node* varlist=paramdec->bro->bro;
        FieldList param_field=ParamDec(paramdec);
        FieldList varlist_field=VarList(varlist);
        if(param_field==NULL){
            return varlist_field;
        }
        param_field->tail=varlist_field;
        return param_field;
    }
    printf("VarList error\n");
}

FieldList ParamDec(node* root){
    debug("ParamDec");
    node* specifier=root->son;
    Type type=Specifier(specifier);
    node* vardec=specifier->bro;
    return VarDec(vardec,type,type);
}

void StmtList(node* root,Type type){
    debug("StmtList");
    if(root==NULL){
        debug("stmtlist->null");
        return;
    }
    debug("stmtlist->stmt stmtlist");
    node* stmt=root->son;
    Stmt(stmt,type);

    node* stmtlist=stmt->bro;
    StmtList(stmtlist,type);
}

void Stmt(node* root,Type type){
    debug("Stmt");
    int line=root->first_line;
    if(root->son_num==2){// Stmt->Exp SEMI
        node* exp=root->son;
        Exp(exp);
    }else if(root->son_num==1){//Stmt->CompSt
        node* compst=root->son;
        push_stack();   //bug in E2.2
        CompSt(compst,type);//这里应该也需要传入类型，因为可以函数中途return
        pop_stack();
    }else if(root->son_num==3){//Stmt->REtURN Exp Semi
        node* exp=root->son->bro;
        Type exp_type=Exp(exp);
        //返回值实际上只能是int float 和结构体类型
        if(exp_type!=NULL){
            int comp=CompareType(exp_type,type);
            if(!comp){
                eprintf(8,line,"Return type not match in function");
            }
        }
    }else if(root->son_num==5){//Stmt->if lp exp rp stmt
                               //Stmt->while lp exp rp stmt
        node* exp=root->son->bro->bro;
        Type exp_type=NULL;
        exp_type=Exp(exp);
        if(exp_type!=NULL){
            if((exp_type->kind!=BASIC)||(exp_type->u.basirc!=INT))
                eprintf(7,line,"Not INT for condition of IF or WHILE");
        }
        node* stmt=exp->bro->bro;
        push_stack();
        Stmt(stmt,type);
        pop_stack();
    }else if(root->son_num==7){
        node* exp=root->son->bro->bro;
        Type exp_type=NULL;
        exp_type=Exp(exp);
        if(exp_type!=NULL){
            if((exp_type->kind!=BASIC)||(exp_type->u.basirc!=INT))
                eprintf(7,line,"Not INT for condition of IF ELSE");
        }
        node* stmt1=exp->bro->bro;
        push_stack();
        Stmt(stmt1,type);
        pop_stack();
        node* stmt2=stmt1->bro->bro;
        push_stack();
        Stmt(stmt2,type);
        pop_stack();
    }
    return ;
}

Type Exp(node* root){
    debug("Exp");
    int line=root->first_line;
    //printf("%d\n",root->son_num);
    Type type=NULL;//出现错误时一律return NULL
    if(root->son_num==1){
        debug("ID INT FLOAT");
        node* son=root->son;
        if(strcmp(son->name,"ID")==0){  //Exp->ID
            debug("Exp->ID");
            char* name=ID(son);
            HashNode this=get(name);
            if(this==NULL){
                eprintf(1,line,"Undefined ID in Exp");//是普通变量或者是结构体变量
            }else{
                //函数的ID是不应该进入到这里的
                //结构体到这里只需要直接反应结构体信息,所以只有数组的type需要处理一下？？？TODO
                type=this->value->type;
                /*
                if(type->kind==ARRAY){
                    while(type->kind==ARRAY){
                        type=type->u.array.elem;
                    }
                }
                */
            }
        }else if(strcmp(son->name,"INT")==0){   //Exp->INT
            debug("Exp->INT");
            type=(Type)malloc(sizeof(struct Type_));
            type->kind=BASIC;
            type->u.basirc=INT;
        }else if(strcmp(son->name,"FLOAT")==0){ //Exp->FLOAT
            debug("Exp->FLOAT");
            type=(Type)malloc(sizeof(struct Type_));
            type->kind=BASIC;
            type->u.basirc=FLOAT;
        }
    }else if(root->son_num==2){
        debug(" MINUS EXP    NOT EXP");
        if(strcmp(root->son->name,"MINUS")==0){
            node* exp=root->son->bro;
            type=Exp(exp);
        }
        else if(strcmp(root->son->name,"NOT")==0){
            Type logictype=(Type)malloc(sizeof(struct Type_));
            logictype->kind=BASIC;
            logictype->u.basirc=INT;
            type=Exp(root->son->bro);
            if(type==NULL)
                return logictype;
            if(type->kind!=BASIC){
                eprintf(7,line,"Operation for logic caculate not INT");
                return logictype;
            }
            else if(type->u.basirc!=INT){
                eprintf(7,line,"Operation for logic caculate not INT");
                return logictype;
            }

        }
    }else if(root->son_num==3){
        node* son1=root->son;
        node* son2=son1->bro;
        node* son3=son2->bro;
        if(strcmp(son1->name,"Exp")==0&&strcmp(son2->name,"DOT")==0){   //Exp->Exp DOT ID
            debug("Exp->Exp DOT ID");
            Type struct_type=Exp(son1);
            if(struct_type!=NULL){
                if(struct_type->kind!=STRUCTURE){
                    eprintf(13,line,"Not a structure variable");
                    type=NULL;
                }else{
                    FieldList struct_field=struct_type->u.structval;
                    char* id_name=ID(son3);
                    FieldList sub_field=struct_field;
                    type=NULL;
                    while(sub_field!=NULL){
                        if(strcmp(sub_field->name,id_name)==0){
                            type=sub_field->type;
                            break;
                        }
                        sub_field=sub_field->tail;
                    }
                    if(type==NULL){
                        eprintf(14,line, "Undefined variable in structure variable");
                    }
                }
            }
        }else if(strcmp(son1->name,"ID")==0){   //Exp->ID LP RP
            debug("Exp->ID LP RP");
            char* funid_name=ID(son1);
            HashNode this=get(funid_name);
            if(this==NULL){
                printf("Error type 2 at Line %d: Undefined function %s.\n",line,funid_name);

            }else{
                if(this->value->type->kind!=FUNCTION){
                    eprintf(11,line,"() used for a not function variable");
                }else if(this->value->type->u.function.param!=NULL){
                    printf("Error type 9 at Line %d: There should be no paramof %s.\n",line,funid_name);                    
                }else{
                    type=this->value->type->u.function.ret;
                }
            }
        }else if(strcmp(son1->name,"Exp")==0&&strcmp(son3->name,"Exp")==0){
            debug("Exp->exp 各种操作 exp");
            //printf("%s\n",son2->name);

            Type left=Exp(son1);
            debug("finish son1");
            Type right=Exp(son3);
            debug("finish son3");
            if(left==NULL||right==NULL){
                return type;//也就是exp1或exp2有一个是出错了，所以返回了空的类型信息，就不需要再比较下去了
            }
            else if(strcmp(son2->name,"ASSIGNOP")==0){   //Exp->Exp ASSIGNOP Exp
                if(!( ((son1->son_num==1)&&(strcmp(son1->son->name,"ID")==0) ) ||   //Exp->ID
               ((son1->son_num==3)&&((strcmp(son1->son->bro->name,"DOT")==0)) )   ||    //Exp->Exp.ID
               ((son1->son_num==4)&&(strcmp(son1->son->name,"Exp")==0) ) ))  //Exp->Exp [ Exp ]
                    eprintf(6,line,"lvalue required as left operand of assignment");
                else if(left->kind==BASIC){
                    if(left->u.basirc!=right->u.basirc)
                        printf("Error type 5 at Line %d: Operation type not match, Left is %d and right is %d.\n",line,left->u.basirc,right->u.basirc);
                    else
                        type=left;
                }else if(left->kind!=right->kind){//左右类型不匹配
                    printf("Error type 5 at Line %d: Operation type not match, They are %d,%d.\n",line,left->kind,right->kind);
                }else{//类型相同，但要做进一步检查
                //数组也可以赋值：
                    if(!CompareType(left,right)){
                        eprintf(5,line,"Type not match in ASSIGNOP");
                    }else{
                        type=left;
                    }
                }
            }else if(strcmp(son2->name,"RELOP")==0){ //Exp RELOP Exp
                Type reloptype=(Type)malloc(sizeof(struct Type_));
                reloptype->kind=BASIC;
                reloptype->u.basirc=INT;
                if(left->kind!=BASIC||right->kind!=BASIC){
                    eprintf(7,line,"Wrong operation type surrounding RELOP");
                }else if((left->u.basirc!=INT) && (left->u.basirc!=FLOAT)){
                    eprintf(7,line,"Operation type left by RELOP not INT or FLOAT");
                }else if((right->u.basirc!=INT) && (right->u.basirc!=FLOAT)){
                    eprintf(7,line,"Operation type right by RELOP not INT or FLOAT");
                }else if(left->u.basirc!=right->u.basirc){
                    eprintf(7,line,"Operation type surrounding RELOP not match");
                }
                return reloptype;
            }else if((strcmp(son2->name,"AND")==0)||(strcmp(son2->name,"OR")==0)){//Exp->Exp AND OR Exp
                Type logictype=(Type)malloc(sizeof(struct Type_));
                logictype->kind=BASIC;
                logictype->u.basirc=INT;
                if((left->kind!=BASIC)||(right->kind!=BASIC))
                    eprintf(7,line,"Operation for logic caculate not INT");
                else if((left->u.basirc!=INT)|| (right->u.basirc!=INT))
                    eprintf(7,line,"Operation for logic caculate not INT");
                return logictype;
            }else{  //PLUS,MINUS,STAR,DIV
                if(left->kind!=right->kind){
                    eprintf(7,line,"Operation type not match at kind level");
                }else if(left->kind==BASIC){
                    if(left->u.basirc!=right->u.basirc){
                        printf("Error type 7 at Line %d: Operation type not match, Left is %d and right is %d.\n",line,left->u.basirc,right->u.basirc);
                    }else{
                        type=left;
                    }
                }else{
                    eprintf(7,line,"Operation type not BASIC for +-*/");
                }
            }
        }else if(strcmp(son1->name,"LP")==0){   //Exp->( Exp )
            debug("Exp->(Exp)");
            type=Exp(son2);
        }
    }else if(root->son_num==4){
        if(strcmp(root->son->name,"ID")==0){    //Exp->ID( Args )
            debug("Exp=>ID (args)");
            char* id_name=ID(root->son);
            HashNode this=get(id_name);
            if(this==NULL){
                eprintf(2,line,"Undefined Function");
            }else{
                if(this->value->type->kind!=FUNCTION){
                    eprintf(11,line,"() used for a not function variable");
                    return type;
                }
                type=this->value->type->u.function.ret;
                FieldList id_param=this->value->type->u.function.param;
                FieldList exp_param=Args(root->son->bro->bro);
                FieldList sub_id=id_param;
                FieldList sub_exp=exp_param;
                while(sub_id!=NULL||sub_exp!=NULL){
                    if(sub_id==NULL){
                        eprintf(9,line,"Function param not match");
                        break;
                    }
                    if(sub_exp==NULL){
                        eprintf(9,line,"Function param not match");
                        break;
                    }
                    if(!CompareType(sub_id->type,sub_exp->type)){
                        eprintf(9,line,"Function param not match");
                        break;
                    }
                    sub_id=sub_id->tail;
                    sub_exp=sub_exp->tail;
                }
            }
        }else if(strcmp(root->son->name,"Exp")==0){ //Exp->Exp [ Exp ] 第二个exp一定得是整数
            node* exp1=root->son;
            node* exp2=exp1->bro->bro;
            Type exp2_type=Exp(exp2);
            if(exp2_type!=NULL){
                if(exp2_type->kind!=BASIC||exp2_type->u.basirc!=INT){
                    eprintf(12,line,"array access operator is not int");
                }
                Type exp1_type=Exp(exp1);
                if(exp1_type!=NULL){
                    if(exp1_type->kind!=ARRAY){
                        eprintf(10,line,"[] used for a not array variable");
                    }else{
                        type=exp1_type->u.array.elem;
                    }
                }
            }
        }
    }
    return type;
}

int CompareType(Type left,Type right){//比较类型信息，相同输出1，不相同输出0
    debug("CompareType");
    if(left==NULL||right==NULL){
        return 0;
    }
    int res=1;
    if(left->kind!=right->kind){
        res=0;
    }else{
        if(left->kind==BASIC){
            if(left->u.basirc!=right->u.basirc){
                res=0;
            }else{
                res=1;
            }
         }else if(left->kind==ARRAY){
            Type sub_left=left,sub_right=right;
            while(sub_left->kind==ARRAY&&sub_right->kind==ARRAY){
                sub_left=sub_left->u.array.elem;
                sub_right=sub_right->u.array.elem;
            }
            res=CompareType(sub_left,sub_right);
         }else if(left->kind==STRUCTURE){
            //实现的：结构体的结构等价
            FieldList field1=left->u.structval;
            FieldList field2=right->u.structval;
            while(field1!=NULL&&field2!=NULL){
                if(!CompareType(field1->type,field2->type)){
                    res=0;
                    break;
                }
                field1=field1->tail;
                field2=field2->tail;
            }
            if(field1!=NULL||field2!=NULL){
                //域数量不一致
                res=0;
            }
         }else if(left->kind==FUNCTION){
            debug("Compare type between two function");
            assert(0);
            res=0;
         }
    }
    return res;
}

FieldList Args(node* root){
    debug("Args");
    FieldList field=(FieldList)malloc(sizeof(struct FieldList_));
    if(root->son_num==1){   //Args->Exp
        Type exp_type=Exp(root->son);
        if(exp_type==NULL)  return NULL;//exp_type不可为空
        field->type=exp_type;
        field->tail=NULL;
    }else if(root->son_num==3){
        Type exp_type=Exp(root->son);
        FieldList args_field=Args(root->son->bro->bro);
        if(exp_type==NULL){
            field=args_field;
        }else{
            FieldList exp_field=(FieldList)malloc(sizeof(struct FieldList_));
            exp_field->type=exp_type;
            exp_field->tail=args_field;
            field=exp_field;
        }
    }
    return field;
}

void debug(char* s){
    if(semantic_de){
        printf("%s\n",s);
    }
}

void debugi(char* s,int d){
    if(semantic_de)
        printf("%s %d\n",s,d);
}

void eprintf(int error_number,int line,char* message){
    printf("Error type %d at Line %d: %s.\n",error_number,line,message);
}
