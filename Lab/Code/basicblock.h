#ifndef _BASICBLOCK_H_
#define _BASICBLOCK_H_
#include "intercode.h"
typedef struct BBs_ *BBs;
typedef struct BasicBlock_ *BasicBlock;
typedef struct IRtag_ *IRtag;

extern BasicBlock bb_head; //第一个基本块
extern IRtag tag_head;  //当扫描到一个标号类ir，加入该链表，它可能是作为某个连接的目标。首结点不存放数据


struct BasicBlock_ {
    int bb_no; //基本块编号
    InterCodeList first,last;
    BBs pre,suc; //前驱，后驱:双向链表表头指针。注意：头结点含数据
    BasicBlock nextbb; //下一个基本块
};

struct BBs_ {   //基本块群,双向循环链表
    BasicBlock bb;
    BBs prev,next,head; //下一个，上一个，链表头head存放数据
};

struct IRtag_{
    InterCodeList irnode;
    IRtag nexttag;
};//当扫描到一个标号类ir，加入该链表，它可能是作为某个连接的目标。首结点不存放数据

BasicBlock init_bb(InterCodeList irnode);
BBs init_bbs(BasicBlock bb);
IRtag init_tag(InterCodeList irnode);
void insert_tag(InterCodeList irnode);
InterCodeList searchtag(Operand label);
void insert_bb2bbs(BasicBlock bb, BBs bbs);
void link(BasicBlock bbson,BasicBlock bbpar);
InterCodeList get_jmp(InterCodeList end_irnode);
BasicBlock search_bb(InterCodeList irnode);
void partition();

#endif