#include "basicblock.h"


BasicBlock bb_head; //第一个基本块
IRtag tag_head;  //当扫描到一个标号类ir，加入该链表，它可能是作为某个连接的目标。首结点不存放数据

static int bbno=0;

BasicBlock init_bb(InterCodeList irnode){
    BasicBlock bb=(BasicBlock)malloc(sizeof(struct BasicBlock_));
    assert(bb);
    bb->bb_no=bbno;
    bbno++;
    bb->first=irnode;  //第一条irlist
    bb->last=irnode;   //最后一条irlist
    bb->pre=NULL;    //bb的前驱bbs群
    bb->suc=NULL;    //bb的后继bbs群
    bb->nextbb=NULL; //下一个bb

    return bb;
}

BBs init_bbs(BasicBlock bb){
    BBs bbs=(BBs)malloc(sizeof(struct BBs_));
    assert(bbs);
    bbs->bb=bb; //bbs中的数据节点bb
    bbs->next=bbs;  //bbs链表下一个结点
    bbs->prev=bbs;  //bbs链表上一个结点
    bbs->head=bbs;  //bbs链表头设为它自己
    return bbs;
}

IRtag init_tag(InterCodeList irnode){
    IRtag tag=(IRtag)malloc(sizeof(struct IRtag_));
    assert(tag);
    tag->irnode=irnode;
    tag->nexttag=NULL;
    return tag;
}

void insert_tag(InterCodeList irnode){
    IRtag tag=init_tag(irnode);
    IRtag tag_tmp=tag_head;
    while(tag_tmp->nexttag)
        tag_tmp=tag_tmp->nexttag;
    tag_tmp->nexttag=tag;
    return;
}

bool cmp_label(Operand op1,Operand op2){
    if(op1->kind!=op2->kind)
        return false;
    if(op1->kind==OP_LABEL)
        return op1->no==op2->no;
    else if(op1->kind==OP_FUNCTIONNAME)
        return strcmp(op1->name,op2->name)==0;
}


InterCodeList searchtag(Operand label){
    IRtag tag_tmp=tag_head;
    InterCodeList res_irnode=NULL;
    while(tag_tmp->nexttag){
        if(cmp_label(tag_tmp->nexttag->irnode->code->u.one,label)){
            res_irnode=tag_tmp->nexttag->irnode;
            tag_tmp->nexttag=tag_tmp->nexttag->nexttag;
            return res_irnode;
        }
        tag_tmp=tag_tmp->nexttag;
    }
    assert(0);
}

void insert_bb2bbs(BasicBlock bb, BBs bbs){
    BBs bbs_head=bbs->head;
    if(bbs_head==NULL){
        bbs_head=init_bbs(bb);
        return;
    }
    BBs bbs_new=init_bbs(bb);
    bbs_head->prev->next=bbs_new;
    bbs_new->prev=bbs_head->prev;
    bbs_new->next=bbs_head;
    bbs_new->head=bbs_head;
    bbs_head->prev=bbs_new;
    return;
}

void link(BasicBlock bbson,BasicBlock bbpar){
    //阶段1：将bbson插入bbpar的后继bbs群
    BBs children=bbpar->suc;
    if(children==NULL){
        children=init_bbs(bbson);
        bbpar->suc=children;
    }
    else{
        insert_bb2bbs(bbson,children->head);
    }

    //阶段2：将bbpar插入bbson的前驱bbs群
    BBs parents=bbson->pre;
    if(parents==NULL){
        parents=init_bbs(bbpar);
        bbson->pre=parents;
    }
    else{
        insert_bb2bbs(bbpar,parents->head);
    }
    return;
}

InterCodeList get_jmp(InterCodeList end_irnode){ //输入一个irnode，假如它是BB块末尾，则输出它除下一条指令外跳转到的目标irnode
    Operand label_op=NULL;
    switch(end_irnode->code->kind){
        case IR_IFGOTO:
            label_op=end_irnode->code->u.ifgoto.label;
            return searchtag(label_op);
        case IR_GOTO:
        case IR_CALL:
            label_op=end_irnode->code->u.one;
            return searchtag(label_op);
        default:
            return NULL;
    }
}

BasicBlock search_bb(InterCodeList irnode){ //搜索首句为irnode的BB
    BasicBlock bb_tmp=bb_head;
    while(bb_tmp!=NULL){
        if(bb_tmp->first==irnode)
            return bb_tmp;
        bb_tmp=bb_tmp->nextbb;
    }
    assert(0);
} 

void partition(){
    //分割基本块
    bb_head=NULL;
    InterCodeList cur_irnode=irlist_head->next;
    BasicBlock cur_bb=init_bb(cur_irnode);
    bb_head=cur_bb;
    tag_head=init_tag(NULL);
    if(cur_irnode->code->kind==IR_FUNCTIONNAME)
        insert_tag(cur_irnode);
    cur_irnode=cur_irnode->next;
    while(cur_irnode!=irlist_head){
        switch(cur_irnode->code->kind){
            case IR_IFGOTO:
            case IR_GOTO:
            case IR_CALL:
            case IR_READ:
            case IR_WRITE:
            case IR_RETURN:
                cur_bb->last=cur_irnode;
                cur_irnode=cur_irnode->next;
                break;

            case IR_LABEL:
            case IR_FUNCTIONNAME:
                BasicBlock new_bb=init_bb(cur_irnode);
                cur_bb->nextbb=new_bb;
                cur_bb=new_bb;
                insert_tag(cur_irnode);
                cur_irnode=cur_irnode->next;
                break;
            default:
                cur_irnode=cur_irnode->next;
        }
    }
    cur_bb->last=irlist_head->prev;

    //连缀基本块
    cur_irnode=irlist_head->next;
    cur_bb=bb_head;
    while(cur_bb){
        if(cur_bb->nextbb)
            link(cur_bb->nextbb,cur_bb);
        InterCodeList jmp_irnode=get_jmp(cur_bb->last);
        BasicBlock jmp_bb=NULL;
        if(jmp_irnode){
            jmp_bb=search_bb(jmp_irnode);
            link(jmp_bb,cur_bb);
            assert(jmp_bb);
        }
        cur_bb=cur_bb->nextbb;
    }
}

