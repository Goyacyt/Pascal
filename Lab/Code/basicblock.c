#include "basicblock.h"
static int bbno=0;
BasicBlock init_bb(){
    BasicBlock bb=(BasicBlock)malloc(sizeof(struct BasicBlock_));
    assert(bb);
    bb->bb_no=bbno;
    bbno++;
    bb->first=NULL;
    bb->last=NULL;
    bb->pre=NULL;
    bb->last=NULL;
}

BBs init_bbs(BasicBlock bb){
    BBs bbs=(BBs)malloc(sizeof(struct BBs_));
    assert(bbs);
    bbs->bb=bb;
    bbs->bb_no=bb->bb_no;
    bbs->next=bbs;
    bbs->prev=bbs;
    return bbs;
}

void insert_bb2bbs(BasicBlock bb, BBs bbs_head){
    BBs bbs_new=init_bbs(bb);
    bbs_head->prev->next=bbs_new;
    bbs_new->prev=bbs_head->prev;
    bbs_new->next=bbs_head;
    bbs_head->prev=bbs_new;
    return;
}

void set_bbsson2bbspar(BBs bbsson_head,BBs bbspar_head){
    
}