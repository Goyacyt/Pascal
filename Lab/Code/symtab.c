#include"symtab.h"
HashNode* hash_tab[HASHTAB_SIZE+1];
HashNode* stack[STACK_SIZE];

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
HashNode* get(char* name){
    int pos=hash_fun(name);
    HashNode* p=hash_tab[pos];
    while(p!=NULL){
        if(strcmp((*p).value->name,name)==0)
            return p;
        p=p->slot_next;
    }
    return NULL;
}

HashNode* add_sym(FieldList* value,int stack_dep){
    int pos=hash_fun(value->name);
    HashNode* slot_head=hash_tab[pos];
    HashNode* stack_head=stack[stack_dep];

    HashNode* p = (HashNode*)malloc(sizeof (HashNode));
    assert(p!=NULL);
    p->stack_dep=stack_dep;
    p->value=value;
    p->slot_next=NULL;
    p->stack_next=NULL;
    if(slot_head->slot_next!=NULL)
        p->slot_next=slot_head->slot_next;
    slot_head->slot_next=p;

    HashNode* stackP=stack_head;
    while(stackP->stack_next!=NULL){
        stackP=stackP->stack_next;
    }
    stackP->stack_next=p;
    return p;
}

