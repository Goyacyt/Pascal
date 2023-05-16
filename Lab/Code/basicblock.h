#ifndef _BASICBLOCK_H_
#define _BASICBLOCK_H_
#include "intercode.h"
typedef struct BBs_ *BBs;
typedef struct BasicBlock_ *BasicBlock;

BBs bbs_head;
struct BasicBlock_ {
    int bb_no;
    InterCodeList first,last;
    BBs pre,suc; //前驱，后驱
};

struct BBs_ {   //基本块群
    int bb_no;
    BasicBlock bb;
    BBs prev,next,head; //下一个，上一个，链表头
};









#endif