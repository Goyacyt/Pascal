#include "basicblock.h"

BasicBlock init_bb(InterCodeList irnode){
    BasicBlock bb=(BasicBlock)malloc(sizeof(struct BasicBlock_));
    assert(bb);
    bb->bb_no=bbno;
    bbno++;
    bb->first=irnode;  //第一条irlist
    bb->last=NULL;   //最后一条irlist
    bb->pre=NULL;    //bb的前驱bbs群
    bb->suc=NULL;    //bb的后继bbs群
    
    BasicBlock tmp_bb=bb_head;
    while(tmp_bb!=NULL){
        if(tmp_bb->nextbb==NULL){
            tmp_bb->nextbb=bb;
            break;
        }
        tmp_bb=tmp_bb->nextbb;
    }
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
    tag->irnode=irnode;
    tag->nexttag=NULL;
    return tag;
}

void insert_tag(InterCodeList irnode){
    IRtag tag=init_tag(irnode);
    IRtag tag_tmp=tag_head;
    while(tag_tmp!=NULL)
        tag_tmp=tag_tmp->nexttag;
    tag_tmp=tag;
    return;
}

InterCodeList searchtag(Operand label){
    IRtag tag_tmp=tag_head;
    IRtag res_irnode=NULL;
    while(tag_tmp->nexttag){
        if(tag_tmp->nexttag->irnode->code->u.one==label){
            res_irnode=tag_tmp->nexttag->irnode;
            tag_tmp->nexttag=tag_tmp->nexttag->nexttag;
            return res_irnode;
        }
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
        return;
    }
    else{
        insert_bb2bbs(bbson,children->head);
    }

    //阶段2：将bbpar插入bbson的前驱bbs群
    BBs parents=bbson->pre;
    if(parents==NULL){
        parents=init_bbs(bbpar);
        bbson->pre=parents;
        return;
    }
    else{
        insert_bb2bbs(bbpar,parents->head);
    }
    return;
}

InterCodeList get_jmp(InterCodeList end_irnode){ //输入一个irnode，假如它是BB块末尾，则输出它除下一条指令外跳转到的目标irnode
    switch(end_irnode->code->kind){
        Operand label_op=NULL;
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

BasicBlock search_bb(InterCode irnode){ //搜索irnode所在的BB
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
    InterCodeList cur_irnode=irlist_head->next;
    BasicBlock cur_bb=init_bb(cur_irnode);
    bb_head=cur_bb;
    tag_head=init_tag(NULL);
    while(cur_irnode!=NULL){
        if(cur_irnode->next==NULL){
            cur_bb->last=cur_irnode;
            break;
        }
        switch(cur_irnode->code->kind){
            case IR_IFGOTO:
            case IR_GOTO:
            case IR_CALL:
            case IR_RETURN:
                cur_bb->last=cur_irnode;
                cur_bb=init_bb(cur_irnode->next);
                if(cur_irnode->next->next)
                    cur_irnode=cur_irnode->next->next;
                break;

            case IR_LABEL:
            case IR_FUNCTIONNAME:
                cur_bb=init_bb(cur_irnode);
                insert_tag(cur_irnode);
                assert(cur_irnode->next);
                cur_irnode=cur_irnode->next;
                break;
            default:
                cur_irnode=cur_irnode->next;
        }
    }
    
    //连缀基本块
    cur_irnode=irlist_head->next;
    BasicBlock cur_bb=bb_head;
    while(cur_irnode!=NULL){
        switch(cur_irnode->code->kind){
            case IR_IFGOTO:
            case IR_GOTO:
            case IR_CALL:
            case IR_RETURN:
                cur_bb=search_bb(cur_irnode);
                BasicBlock jmp_bb=search_bb(get_jmp(cur_irnode));
                BasicBlock next_bb=search_bb(cur_irnode);
                link(jmp_bb,cur_bb);
                link(next_bb,cur_bb);
                cur_irnode=cur_irnode->next;
                break;
            default:
                cur_irnode=cur_irnode->next;
        }
    }
}

