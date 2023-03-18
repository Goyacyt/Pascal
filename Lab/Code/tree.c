#include"tree.h"

void* mem_allocate(int size)
{
    void* p = malloc(size);
    if(p==NULL){
        printf("Mem error");
        exit(0);
    }
    return p;
}

node* add_token(char* name, int type, void* val){
    node* p = (node*)mem_allocate(sizeof (node));
    sscanf(name,"%s", p->name);
    p->first_line=-1;
    p->type=type;
    p->son_num=0;
    p->bro=NULL;
    p->son=NULL;
    switch(type){
        case TYPE_ID: 
            sscanf(val,"%s", p->val.id_val);
            break;
        case TYPE_INT:    
            sscanf(val,"%d",&(p->val.int_val));
            break;
        case TYPE_FLOAT:  
            sscanf(val,"%f",&(p->val.float_val));
            break;
        case TYPE_TYPE:
            sscanf(val,"%s",p->val.type_val);
            break;
        default:    break;
    }
    return p;
}

node* add_nonterminal(char* name, int first_line, int type, int son_num,...){
    node* p = (node*)mem_allocate(sizeof (node));
    sscanf(name,"%s", p->name);
    //printf("node %s has %d child\n",p->name,son_num);
    p->first_line=first_line;
    p->type=type;
    p->bro=NULL;
    p->son=NULL;
    p->son_num=son_num;
    va_list valist;
    va_start(valist, son_num);
    node* child=va_arg(valist,node*);
    p->son=child;
    for(int i=0;i<son_num;i++){
        //printf("child %d: %s",i,child->name);
        //if(child->type==NOTTOKEN)   printf("[%d] ",child->first_line);
        node* nextchild=va_arg(valist,node*);
        if(i<son_num-1&&nextchild!=NULL){
            //printf(BLUE"  %s's child %s has bro %s"NONE,p->name,child->name,nextchild->name);
            child->bro=nextchild;
            child=nextchild;
        }
        //printf("\n");
    }
    va_end(valist);
    return p;
}


void print_tree(node* cur_node, int dep){
    if(cur_node==NULL)  {
        //printf(BLUE"reach leaf!\n"NONE);
        return;}
    for(int i=0;i<dep;i++)  printf("  ");
    if(cur_node->type==NOTTOKEN)   printf("%s (%d)\n",cur_node->name, cur_node->first_line);
    else if(cur_node->type==OTHERTOKEN) printf("%s\n",cur_node->name);
    else{
        switch(cur_node->type){
            case TYPE_ID:
                printf("ID: %s\n",cur_node->val.id_val);
                break;
            case TYPE_TYPE:
                printf("TYPE: %s\n",cur_node->val.type_val);
                break;
            case TYPE_INT:
                printf("INT: %d\n",cur_node->val.int_val);
                break;
            case TYPE_FLOAT:
                printf("FLOAT: %f\n",cur_node->val.float_val);
                break;
            default:
                break;
        }
    }
    //printf(BLUE"%s's son:\n"NONE,cur_node->name);
    print_tree(cur_node->son,dep+1);
    //printf(BLUE"%s's bro:\n"NONE,cur_node->name);
    print_tree(cur_node->bro,dep);
}