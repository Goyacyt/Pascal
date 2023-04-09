#include "symtab.h"
#include <string.h>
#include "tree.h"
HashNode hash_tab[HASHTAB_SIZE+1];
HashNode stack[STACK_SIZE+1];
extern int de;
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

HashNode add_sym(FieldList value,int stack_dep){
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

void Program(node* root){   //Program->ExtDefList
    debug("program");
    init_hashtab();
    init_stack();
    if(root->son!=NULL){
        ExtDefList(root->son);
    }
    return ;
}
void ExtDefList(node* root){
    debug("extdeflist");
    if(root==NULL){
        return ;
    }
    //ExtDefList->ExtDef ExtDefList
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
    if(strcmp(son2->name,"ExtDecList")==0){ //ExtDef->Specifier ExtDecLit SEMI
        //son3=son2->bro;
        ExtDecList(son2,specifier_type);
    }else if(strcmp(son2->name,"FunDec")==0){   //ExtDef->Specifier FunDec CompSt
        son3=son2->bro;
        if(strcmp(son3->name,"CompSt")==0){
            push_stack();
            FunDec(son2,specifier_type,0);
            CompSt(son3,specifier_type);
            pop_stack();
        }else{
            push_stack();
            FunDec(son2,specifier_type,1);
            pop_stack();
        }
    }else if(strcmp(son2->name,"SEMI")==0){
        //这个其实不用做什么？
    }else{
        printf("ExtDef error\n");
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
    if(root->son_num==5){
        type=(Type)malloc(sizeof(struct Type_));
        node* son2=root->son->bro;
        node* deflist;
        char* struct_name;
        if(strcmp(son2->name,"OptTag")==0){
            struct_name=OptTag(son2);
            HashNode this=get(struct_name);
            if(this!=NULL){
                eprintf(16,line,"The name of this structure has been defined");
            }
            deflist=son2->bro->bro;
        }else{
            deflist=son2->bro;
        }
        FieldList struct_field=(FieldList)malloc(sizeof(struct FieldList_));
        struct_field->name=struct_name;
        struct_field->type=type;
        type->kind=STRUCTURE;
        push_stack();
        FieldList deflist_field=DefList(deflist,1);
        pop_stack();
        type->u.structure=deflist_field;
        
        add_sym(struct_field,sdep);//添加结构体名字的定义信息
    }else if(root->son_num=2){
        node* son2=root->son->bro;
        char* struct_name=Tag(son2);
        HashNode this=get(struct_name);
        if(this==NULL){
            printf("Error type 17 at Line %d:Undefined Structure Type\n",line);
        }else{
            type=this->value->type;
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
<<<<<<< HEAD
    if(root->son_num==4){   //FundDec->ID LP VarList RP
        node* varlist=id->bro->bro;
        FunType->u.function.param=VarList(varlist);
    }else{  //FundDec->ID LP RP
=======
    FieldList varlist_field;
    if(root->son_num==4){
        node* varlist=id->bro->bro;
        varlist_field=VarList(varlist);
        FunType->u.function.param=varlist_field;
    }else{
>>>>>>> 9ef39a815d25f1f83bc30c9a60ef953148053466
        debug("fundec->id lp rp");
        varlist_field=NULL;
        FunType->u.function.param=varlist_field;
    }
    field->type=FunType;
    if(this!=NULL){
        Type before_type=this->value->type;
        if(before_type->kind!=FUNCTION){
            eprintf(4,line,"Repeated definition of function:the name before is not a function");
            return ;
        }else{
            if(!declare){
                //这是函数定义
                if(before_type->u.function.declare==DECLARED){
                    if(!CompareParam(before_type,FunType)){
                        eprintf(19,line,"Confliction between definition and declaration");
                        return ;
                    }else{
                        this->value->type->u.function.declare=DEFINED;
                        return ;
                    }
                }else{
                    eprintf(4,line,"Repeated defintion of function");
                    return ;
                }
            }else{
                //这是函数声明,前面有声明或者定义都可以，只要匹配就行
                if(!CompareParam(before_type,FunType)){
                    eprintf(19,line,"Confliction bwtween declaration and dedinition or confliction between declaration and declaration.Here is decalration");
                }
                return ;
            }
        }
    }//函数不存在嵌套定义，所以不需要检查sdep

    if(declare){
        FunType->u.function.declare=DECLARED;
    }else{
        FunType->u.function.declare=DEFINED;
    }
    add_sym(field,sdep);
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
    return root->val.id_val;
}

void CompSt(node* root,Type type){
    //这里面有两个可以为空的指针:deflist 和stmtlist不进行检查就可能把rc当作stmtlist或者deflist
    debug("CompSt");
    //CompSt->LC DefList StmtList RC
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

<<<<<<< HEAD
FieldList Def(node* root){ //Def->Specifier DecList SEMI
=======
FieldList Def(node* root,int stru){
>>>>>>> 9ef39a815d25f1f83bc30c9a60ef953148053466
    debug("Def");
    node* specifier=root->son;
    node* declist=specifier->bro;
    Type specifier_type=Specifier(specifier);
    return DecList(declist,specifier_type,stru);
}

FieldList DefList(node* root,int stru){
    debug("DefList");
    if(root==NULL){
        debug("deflist->null");
        return NULL;
    }else{  //DefList->Def DefList
        node* def=root->son;
        FieldList def_field=Def(def,stru);

        node* deflist=def->bro;
        FieldList deflist_field=DefList(deflist,stru);
        def_field->tail=deflist_field;
        return def_field;
    }
    return NULL;
}

FieldList DecList(node* root,Type type,int stru){
    debug("DecList");
    if(root->son_num==1){   //DecList->Dec
        debug("declist->dec");
        node* dec=root->son;
<<<<<<< HEAD
        return Dec(dec,type);
    }else if(root->son_num==3){ //DecList->Dec COMMA DecList
=======
        return Dec(dec,type,stru);
    }else if(root->son_num==3){
>>>>>>> 9ef39a815d25f1f83bc30c9a60ef953148053466
        node* dec=root->son;
        FieldList dec_field=Dec(dec,type,stru);
        node* declist=dec->bro->bro;
        FieldList declist_field=DecList(declist,type,stru);
        dec_field->tail=declist_field;
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
<<<<<<< HEAD
    FieldList vardec_field;
    if(root->son_num==1){   //Dec->VarDec
        vardec_field=VarDec(vardec,type,type);
    }else if(root->son_num==3){ //Dec->VarDec ASIIGNOP Exp
=======
    FieldList vardec_field=NULL;
    if(root->son_num==1){
        vardec_field=VarDec(vardec,type,type);
    }else if(root->son_num==3){
        if(stru){
            eprintf(15,line,"Assign value when defining struct variable");
            return vardec_field;
        }

>>>>>>> 9ef39a815d25f1f83bc30c9a60ef953148053466
        node* exp=vardec->bro->bro;
        vardec_field=VarDec(vardec,type,type);
        Type exp_type=Exp(exp);
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
    if(root->son_num==1){ //VarDec->ID
        char* id=ID(root->son);
        HashNode this=get(id);
        if(this!=NULL){
            if(this->stack_dep==sdep){
                eprintf(3,line,"Redefined variable name");
                return NULL;
            }
        }
        FieldList field=(FieldList)malloc(sizeof(struct FieldList_));
        field->name=id;
        if(elemtype->kind==STRUCTURE||elemtype->kind==BASIC){
            field->type=elemtype;
        }
        else{
            Type subtype=elemtype;
            while(subtype->u.array.elem!=NULL){
                subtype=subtype->u.array.elem;
            }
            subtype->u.array.elem=type;
            field->type=elemtype;
        }
        add_sym(field,sdep);
        return field;
    }else if(root->son_num==4){
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
        param_field->tail=varlist_field;
        return param_field;
    }
    printf("VarList error\n");
    return NULL;
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
        CompSt(compst,type);//这里应该也需要传入类型，因为可以函数中途return
    }else if(root->son_num==3){//Stmt->REtURN Exp Semi
        node* exp=root->son->bro;
        Type exp_type=Exp(exp);
        //返回值实际上只能是int float 和结构体类型
        int comp=CompareType(exp_type,type);
        if(!comp){
            eprintf(8,line,"Return type not match in function");
        }
    }else if(root->son_num==5){//Stmt->if lp exp rp stmt
                               //Stmt->while lp exp rp stmt
        node* exp=root->son->bro->bro;
        Exp(exp);
        node* stmt=exp->bro->bro;
        push_stack();
        Stmt(stmt,type);
        pop_stack();
    }else if(root->son_num==7){
        node* exp=root->son->bro->bro;
        Exp(exp);
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
    printf("%d\n",root->son_num);
    Type type=NULL;
    if(root->son_num==1){
        debug("ID INT FLOAT");
        node* son=root->son;
        if(strcmp(son->name,"ID")==0){  //Exp->ID
            debug("Exp->ID");
            char* name=ID(son);
            HashNode this=get(name);
            if(this==NULL){
                printf("Error type 1 at Line %d : Undefined ID in Exp\n",line);
            }else{
                //函数的ID是不应该进入到这里的
                //结构体到这里只需要直接反应结构体信息,所以只有数组的type需要处理一下
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
        node* exp=root->son->bro;
        type=Exp(exp);
    }else if(root->son_num==3){
        debug("数量是三个");
        node* son1=root->son;
        node* son2=son1->bro;
        node* son3=son2->bro;
        debug(son1->name);
        debug(son2->name);
        debug(son3->name);
        if(strcmp(son1->name,"Exp")==0&&strcmp(son2->name,"DOT")==0){
            debug("Exp->Exp DOT ID");
            Type struct_type=Exp(son1);
            if(struct_type->kind!=STRUCTURE){
                printf("Error type 13 at Line %d : Not a structure variable\n",line);
                type=NULL;
            }else{
                FieldList struct_field=struct_type->u.structure->tail;
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
                    printf("Error type 14 at Line %d : Undefined variable in structure variable\n",line);
                }
            }
        }else if(strcmp(son1->name,"ID")==0){
            debug("Exp->ID LP RP");
            char* funid_name=ID(son1);
            HashNode this=get(funid_name);
            if(this==NULL){
                printf("Error type 2 at Line %d : Undefined function %s\n",line,funid_name);
            }else{
                if(this->value->type->kind!=FUNCTION){
                    eprintf(11,line,"() used for a not function variable");
                }else if(this->value->type->u.function.declare==DECLARED){
                    eprintf(18,line,"Function declared but not defined");
                }else if(this->value->type->u.function.param!=NULL){
                    printf("Error type 9 at Line %d : There should be no paramof %s \n",line,funid_name);
                }else{
                    type=this->value->type->u.function.ret;
                }
            }
        }else if(strcmp(son1->name,"Exp")==0&&strcmp(son3->name,"Exp")==0){
            debug("Exp->exp 各种操作 exp");
            printf("%s\n",son2->name);
            Type left=Exp(son1);
            debug("finish son1");
            Type right=Exp(son3);
            debug("finish son3");
            //比较两边类型是否一致
            //TODO: 只有右值的表达式，还没有做
            int errortype=7;
            if(strcmp(son2->name,"ASSIGNOP")==0){
                errortype=5;
            }
            if(left==NULL||right==NULL){
                return type;//也就是exp1或exp2有一个是出错了，所以返回了空的类型信息，就不需要再比较下去了
            }
            if(left->kind!=right->kind){
                printf("Error type %d at Line %d : Operation type not match at kind level \n",errortype,line);
            }else{
                if(left->kind==BASIC){
                    if(left->u.basirc!=right->u.basirc){
                        printf("Error type %d at Line %d : Operation type not match. Left is %d and right is %d \n",errortype,line,left->u.basirc,right->u.basirc);
                    }else{
                        type=left;
                    }
                }else{
                    //TODO:not sure
                    //函数肯定不能做这些操作，数组应该也不可以，但结构体应该可以进行赋值
                    if(strcmp(son2->name,"ASSIGNOP")==0){
                        if(left->kind!=STRUCTURE){
                             printf("Error type %d at Line %d : Operation type not match. They are %d \n",errortype,line,left->kind);
                        }//STRUCTURE是可以赋值，其他不可以
                        else{
                            if(!CompareType(left,right)){
                                eprintf(5,line,"Type not match in ASSIGNOP");
                            }
                        }
                    }else{
                        printf("Error type %d at Line %d : Operation type not match. They are %d \n",errortype,line,left->kind);
                    }
                }
            }
        }else if(strcmp(son1->name,"LP")==0){
            debug("Exp->(Exp)");
            type=Exp(son2);
        }
    }else if(root->son_num==4){
        if(strcmp(root->son->name,"ID")==0){
            debug("Exp=>ID (args)");
            char* id_name=ID(root->son);
            HashNode this=get(id_name);
            if(this==NULL){
                printf("Error type 2 at Line %d : Undefined Function\n",line);
            }else{
                type=this->value->type->u.function.ret;
                FieldList id_param=this->value->type->u.function.param;
                FieldList exp_param=Args(root->son->bro->bro);
                FieldList sub_id=id_param;
                FieldList sub_exp=exp_param;
                while(sub_id!=NULL||sub_exp!=NULL){
                    if(sub_id==NULL){
                        printf("Error type 9 at Line %d : Function param not match \n",line);
                        break;
                    }
                    if(sub_exp==NULL){
                        printf("Error type 9 at Line %d : Function param not match \n",line);
                        break;
                    }
                    if(!CompareType(sub_id->type,sub_exp->type)){
                        printf("Error type 9 at Line %d : Function param not match \n",line);
                        break;
                    }
                    sub_id=sub_id->tail;
                    sub_exp=sub_exp->tail;
                }
            }
        }else if(strcmp(root->son->name,"Exp")==0){
            debug("Exp-> exp[exp]第二个exp一定得是整数");
            node* exp1=root->son;
            node* exp2=exp1->bro->bro;
            Type exp2_type=Exp(exp2);
            if(exp2_type->kind!=BASIC||exp2_type->u.basirc!=INT){
                eprintf(12,line,"array access operator is not int");
            }
            Type exp1_type=Exp(exp1);
            if(exp1_type->kind!=ARRAY){
                eprintf(10,line,"[] used for a not array variable");
            }else{
                type=exp1_type->u.array.elem;
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
            while(sub_left!=NULL&&sub_right!=NULL){
                if(sub_left->kind!=ARRAY){
                    if(sub_right->kind==BASIC&&sub_right->u.basirc==sub_left->u.basirc){
                    }else{
                        res=0;
                    }
                    break;
                }else if(sub_right->kind!=ARRAY){
                    if(sub_left->kind==BASIC&&sub_left->u.basirc==sub_right->u.basirc){
                    }else{
                        res=0;
                    }
                    break;
                }else{
                    if(sub_left->u.array.size!=sub_right->u.array.size){
                        res=0;
                        break;
                    }
                    sub_left=sub_left->u.array.elem;
                    sub_right=sub_right->u.array.elem;
                }
            }
            if(sub_left!=NULL||sub_right!=NULL){
                //数组维度不一致
                res=0;
            }
         }else if(left->kind==STRUCTURE){
            /*char* name_left=left->u.structure->name;
            char* name_right=right->u.structure->name;
            if(strcmp(name_left,name_right)!=0){
                res=0;
            }
            */
            //实现的：结构体的结构等价
            FieldList field1=left->u.structure;
            FieldList field2=right->u.structure;
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
    if(root->son_num==1){
        Type exp_type=Exp(root->son);
        field->type=exp_type;
        field->tail=NULL;
    }else if(root->son_num==3){
        field->type=Exp(root->son);
        field->tail=Args(root->son->bro->bro);
    }
    return field;
}

void debug(char* s){
    if(de){
        printf("%s\n",s);
    }
}

void debugi(char* s,int d){
    printf("%s %d\n",s,d);
}

void eprintf(int error_number,int line,char* message){
    printf(RED"Error type %d at Line %d : %s\n"NONE,error_number,line,message);
}