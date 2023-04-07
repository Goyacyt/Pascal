#include "symtab.h"
#include <string.h>
#include "tree.h"
HashNode hash_tab[HASHTAB_SIZE+1];
HashNode stack[STACK_SIZE];
extern int de;

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
    for(int i=0;i<=STACK_SIZE;i++)
        stack[i]=NULL;
    return;
}

HashNode get(char* name){
    int pos=hash_fun(name);
    HashNode p=hash_tab[pos];
    while(p!=NULL){
        if(strcmp((*p).value->name,name)==0)
            return p;
        p=p->slot_next;
    }
    return NULL;
}

HashNode add_sym(FieldList value,int stack_dep){
    debug("add_sym begin");
    int pos=hash_fun(value->name);
    if(pos>=HASHTAB_SIZE){
        debug("hash overflow");
        assert(0);
    }
    HashNode slot_head=hash_tab[pos];//hash槽的表头
    if(stack_dep>=STACK_SIZE){
        debug("stack overflow");
        assert(0);
    }
    HashNode stack_head=stack[stack_dep];//这一层栈的表头
    HashNode p = (HashNode)malloc(sizeof (struct HashNode_));
    assert(p!=NULL);
    p->stack_dep=stack_dep;
    p->value=value;
    p->slot_next=NULL;
    p->stack_next=NULL;
    //变量插入到hash槽的头部
    debug("add hash");
    p->slot_next=slot_head;
    slot_head=p;
    //变量插入到这一层变量定义栈的链表尾部，其实头部也可以
    debug("add stack");
    p->stack_next=stack_head;
    stack_head=p;
    debug("add_sym end");
    return p;
}

void Program(node* root){
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
    if(strcmp(son2->name,"ExtDecList")==0){
        //son3=son2->bro;
        ExtDecList(son2,specifier_type);
    }else if(strcmp(son2->name,"FunDec")==0){
        son3=son2->bro;
        FunDec(son2,specifier_type);
        CompSt(son3);
    }else if(strcmp(son2->name,"SEMI")==0){
    }else{
        printf("ExtDef error\n");
    }
    return ;
}

void ExtDecList(node* root,Type type){
    debug("extdeclist");
    node* son1=root->son;
    node* son2=son1->bro;
    node* son3=son2->bro;
    if(strcmp(son2->name,"COMMA")==0){
        VarDec(son1,type,type);
        ExtDecList(son3,type);
    }else if(son2==NULL){
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
    int line=root->first_line;
    Type type=NULL;
    if(root->son_num==5){
        type=(Type)malloc(sizeof(struct Type_));
        type->kind=STRUCTURE;
        node* son2=root->son->bro;
        char* struct_name=OptTag(son2);
        node* son4=son2->bro->bro;
        FieldList struct_field=(FieldList)malloc(sizeof(struct FieldList_));
        type->u.structure=struct_field;
        struct_field->name=struct_name;
        Type second_type=(Type)malloc(sizeof(struct Type_));
        struct_field->type=second_type;
        second_type->kind=STRUCTURE;
        FieldList deflist_field=DefList(son4);
        second_type->u.structure=deflist_field;
        
        add_sym(struct_field,0);//添加结构体名字的定义信息
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
    if(root!=NULL){//OptTag->ID
        node* son=root->son;
        return ID(son);
    }else{
        return NULL;
    }
    return NULL;
}

char* Tag(node* root){
    node* son=root->son;
    return ID(son);
}

void FunDec(node* root,Type type){
    debug("fundec");
    FieldList field=(FieldList)malloc(sizeof(struct FieldList_));
    node* id=root->son;
    field->name=ID(id);

    Type FunType=(Type)malloc(sizeof(struct Type_));
    FunType->kind=FUNCTION;
    FunType->u.function.ret=type;
    if(root->son_num==4){
        node* varlist=id->bro->bro;
        FunType->u.function.param=VarList(varlist);
    }else{
        debug("fundec->id lp rp");
        FunType->u.function.param=NULL;
    }
    field->type=FunType;

    add_sym(field,0);
    debug("before fundec return");
    return ;
}

char* ID(node* root){
    return root->val.id_val;
}

void CompSt(node* root){
    //这里面有两个可以为空的指针:deflist 和stmtlist不进行检查就可能把rc当作stmtlist或者deflist
    debug("compst");
    node* son2=root->son->bro;
    if(strcmp(son2->name,"DefList")==0){
        DefList(son2);
        node* son3=son2->bro;
        if(strcmp(son3->name,"StmtList")==0){
            StmtList(son3);
        }
    }else{
        if(strcmp(son2->name,"StmtList")==0){
            StmtList(son2);
        }
    }
    debug("before compst return");
}

FieldList Def(node* root){
    debug("def");
    node* specifier=root->son;
    node* declist=specifier->bro;
    Type specifier_type=Specifier(specifier);
    return DecList(declist,specifier_type);
}

FieldList DefList(node* root){
    debug("deflist");
    if(root==NULL){
        debug("deflist->null");
        return NULL;
    }else{
        node* def=root->son;
        FieldList def_field=Def(def);

        node* deflist=def->bro;
        FieldList deflist_field=DefList(deflist);
        def_field->tail=deflist_field;
        return def_field;
    }
    return NULL;
}

FieldList DecList(node* root,Type type){
    debug("declist");
    if(root->son_num==1){
        debug("declist->dec");
        node* dec=root->son;
        return Dec(dec,type);
    }else if(root->son_num==3){
        node* dec=root->son;
        FieldList dec_field=Dec(dec,type);
        node* declist=dec->bro->bro;
        FieldList declist_field=DecList(declist,type);
        dec_field->tail=declist_field;
        return dec_field;
    }else{
        printf("Declist error\n");
    }
    return NULL;
}

FieldList Dec(node* root,Type type){
    debug("dec");
    node* vardec=root->son;
    FieldList vardec_field;
    if(root->son_num==1){
        vardec_field=VarDec(vardec,type,type);
    }else if(root->son_num==3){
        node* exp=vardec->bro->bro;
        vardec_field=VarDec(vardec,type,type);
        Type exp_type=Exp(exp);
    }
    return vardec_field;
    //TODO:
    //比较赋值号两边的type是否一致
}

FieldList VarDec(node* root,Type type,Type elemtype){
    debug("vardec");
    if(root->son_num==1){
        char* id=ID(root->son);
        FieldList field=(FieldList)malloc(sizeof(struct FieldList_));
        field->name=id;
        if(elemtype->kind==STRUCTURE||elemtype->kind==BASIC){
            field->type=elemtype;
        }else{
            Type subtype=elemtype;
            while(subtype->u.array.elem!=NULL){
                subtype=subtype->u.array.elem;
            }
            subtype->u.array.elem=type;
            field->type=elemtype;
        }
        add_sym(field,0);
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
    node* specifier=root->son;
    Type type=Specifier(specifier);
    node* vardec=specifier->bro;
    return VarDec(vardec,type,type);
}

void StmtList(node* root){
    debug("stmtlist");
    if(root==NULL){
        debug("stmtlist->null");
        return;
    }
    debug("stmtlist->stmt stmtlist");
    node* stmt=root->son;
    Stmt(stmt);

    node* stmtlist=stmt->bro;
    StmtList(stmtlist);
}

void Stmt(node* root){
    if(root->son_num==2){// Stmt->Exp SEMI
        node* exp=root->son;
        Exp(exp);
    }else if(root->son_num==1){//Stmt->CompSt
        node* compst=root->son;
        CompSt(compst);
    }else if(root->son_num==3){//Stmt->REtURN Exp Semi
        node* exp=root->son->bro;
        Exp(exp);
    }else if(root->son_num==5){//Stmt->if lp exp rp stmt
                               //Stmt->while lp exp rp stmt
        node* exp=root->son->bro->bro;
        Exp(exp);
        node* stmt=exp->bro->bro;
        Stmt(stmt);
    }else if(root->son_num==7){
        node* exp=root->son->bro->bro;
        Exp(exp);
        node* stmt1=exp->bro->bro;
        Stmt(stmt1);
        node* stmt2=stmt1->bro->bro;
        Stmt(stmt2);
    }
    return ;
}

Type Exp(node* root){
    int line=root->first_line;
    Type type=NULL;
    if(root->son_num==1){
        //ID INT FLOAT
        node* son=root->son;
        if(strcmp(son->name,"ID")==0){
            char* name=ID(son);
            HashNode this=get(name);
            if(this==NULL){
                printf("Error type 1 at Line %d : Undefined ID in Exp\n",line);
            }else{
                type=this->value->type;
            }
        }else if(strcmp(son->name,"INT")==0){
            type=(Type)malloc(sizeof(struct Type_));
            type->kind=BASIC;
            type->u.basirc=INT;
        }else if(strcmp(son->name,"FLOAT")==0){
            type=(Type)malloc(sizeof(struct Type_));
            type->kind=BASIC;
            type->u.basirc=FLOAT;
        }
    }else if(root->son_num==2){
        // MINUS EXP    NOT EXP
        node* exp=root->son->bro;
        type=Exp(exp);
    }else if(root->son_num==3){
        node* son1=root->son;
        node* son2=son1->bro;
        node* son3=son2->bro;
        if(strcmp(son1->name,"Exp")==0&&strcmp(son2->name,"DOT")==0){
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
                }
                if(type==NULL){
                    printf("Error type 14 at Line %d : Undefined variable in structure variable\n",line);
                }
            }
        }else if(strcmp(son1->name,"ID")==0){
            //Exp->IF LP RP
            char* funid_name=ID(son1);
            HashNode this=get(funid_name);
            if(this==NULL){
                printf("Error type 2 at Line %d : Undefined function %s\n",line,funid_name);
            }
            else if(this->value->type->u.function.param!=NULL){
                printf("Error type 9 at Line %d : There should be no paramof %s \n",line,funid_name);
            }else{
                type=this->value->type->u.function.ret;
            }
        }else if(strcmp(son1->name,"Exp")==0&&strcmp(son3->name,"Exp")==0){
            Type left=Exp(son1);
            Type right=Exp(son2);
            //比较两边类型是否一致
            //TODO: 对赋值号进行特别的检查
            int errortype=7;
            if(strcmp(son2->name,"ASSIGNOP")==0){
                errortype=5;
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
                    printf("Error type %d at Line %d : Operation type not match. They are %d \n",errortype,line,left->kind);
                }
            }
        }
    }else if(root->son_num==4){
        if(strcmp(root->son->name,"ID")==0){
            char* id_name=ID(root->son);
            HashNode this=get(id_name);
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
        }else if(strcmp(root->name,"Exp")==0){
        //TODO:还没想好怎么做
        }
    }
}

int CompareType(Type left,Type right){//比较类型信息，相同输出1，不相同输出0
    int res=1;
    if(left->kind!=right->kind){
        res=0;
    }else{
        if(left->kind==BASIC){
            if(left->u.basirc!=right->u.basirc){
                res=0;
            }
         }else if(left->kind==ARRAY){
            Type sub_left=left,sub_right=right;
            while(sub_left->u.array.elem!=NULL&&sub_right->u.array.elem!=NULL){
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
         }else if(left->kind==STRUCTURE){
            //TODO:这里只实现了名等价，结构等价还没想好怎么实现
            char* name_left=left->u.structure->name;
            char* name_right=right->u.structure->name;
            if(strcmp(name_left,name_right)!=0){
                res=0;
            }
         }else if(left->kind==FUNCTION){
            res=0;
         }
    }
    return res;
}

FieldList Args(node* root){
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
