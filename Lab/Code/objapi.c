// #include "objectcode.h"
// #include "basicblock.h"
// extern FILE* mipsout;

// static int arg_no=-1;

// void init_varlist(){
//     varlist_head=(VariableList)malloc(sizeof(struct VariableList_));
//     varlist_head->var=NULL;
//     varlist_head->prev=NULL;
//     varlist_head->next=NULL;
//     return;
// }

// Variable insert_varlist(Operand op){
//     Variable var=(Variable)malloc(sizeof(struct Variable_));
//     assert(var);
//     var->op=op;
//     var->regno=-1;

//     VariableList newnode=(VariableList)malloc(sizeof(struct VariableList_));
//     newnode->var=var;
//     newnode->next=varlist_head;
//     newnode->prev=varlist_head->prev;
//     varlist_head->prev->next=newnode;
//     varlist_head->prev=newnode;
//     return var;
// }

// Variable find_var(Operand op){
//     VariableList temp=varlist_head->next;
//     while(temp!=NULL){
//         if(temp->var->op==op){
//             return temp->var;
//         }
//         temp=temp->next;
//     }
//     return NULL;
// }

// ObjStackNode init_stacknode(char *funct_name){
//     ObjStackNode objstack=(ObjStackNode)malloc(sizeof(struct ObjStackNode_));
//     assert(objstack);
//     objstack->functname=funct_name;
//     objstack->stackcnt=0;
//     objstack->prev=NULL;
//     objstack->next=NULL;
//     return objstack;
// }

// void push_objstack(char *funct_name){
//     ObjStackNode newnode=init_stacknode(funct_name);

//     if(objstack_head->next!=NULL){
//         objstack_head->next->prev=newnode;
//     }
//     objstack_head->next=newnode;
//     return;
// }

// void pop_objstack(){
//     ObjStackNode temp=objstack_head->next;
//     if(temp==NULL){
//         return;
//     }
//     objstack_head->next=temp->next;
//     if(temp->next!=NULL){
//         temp->next->prev=objstack_head;
//     }
//     free(temp);
//     return;
// }

// ObjStackNode find_objstack(char* funct_name){
//     ObjStackNode temp=objstack_head->next;
//     while(temp!=NULL){
//         if(strcmp(temp->functname,funct_name)==0){
//             return temp;
//         }
//         temp=temp->next;
//     }
//     return NULL;
// }

// void print_objstack(){
//     ObjStackNode temp=objstack_head->next;
//     while(temp!=NULL){
//         printf("functname:%s stackcnt:%d\n",temp->functname,temp->stackcnt);
//         temp=temp->next;
//     }
//     return;
// }

// void init_regs(){
//     for(int i=0;i<32;i++){
//         regs[i].state=UNUSED;
//         regs[i].var=NULL;
//     }
//     return;
// }

// void free_reg(int reg_no){
//     if(regs[reg_no].state==UNUSED){
//         return;
//     }
//     regs[reg_no].state=UNUSED;
//     regs[reg_no].var=NULL;
//     return;
// }

// void store_reg(int reg_no){
//     if(regs[reg_no].state==UNUSED)
//         assert(0);
//     Variable var=regs[reg_no].var;
//     if(var==NULL)
//         assert(0);
//     fprintf(mipsout,"  addi $sp, $sp, -4");
//     fprintf(mipsout,"  sw %s, 0($sp)\n",regName[reg_no]);
//     return;
// }

// int allocate_reg();

// bool active(BasicBlock bb, InterCodeList irnode,Operand op){
//     InterCodeList irnode_cur=bb->last;
//     while(irnode_cur!=irnode&&irnode_cur!=irlist_head){
//         irnode_cur=irnode_cur->prev;
//         InterCode ir=irnode_cur->code;
//         switch(ir->kind){
//             case IR_PARAM:
//             case IR_ARG:
//             case IR_READ:
//             case IR_WRITE:
//             case IR_RETURN:
//             case IR_GETADDR:
//             case IR_CALL:
//                 if(op==ir->u.one)
//                     return 1;
//                 break;
//             case IR_ASSIGN:
//             case IR_GETVAL:
//             case IR_STOREIN:
//                 if(op==ir->u.two.left)
//                     return 1;
//                 else if(op==ir->u.two.right)
//                     return 1;
//                 break;
//             case IR_ADD:
//             case IR_SUB:
//             case IR_MUL:
//             case IR_DIV:
//                 if((op==ir->u.three.result)||(op==ir->u.three.op1)||(op==ir->u.three.op2))
//                     return 1;
//                 break;
//         }
//     }
//     assert(irnode_cur==irnode);
//     return 0;
// }

// int get_reg(Variable var,bool inreg){
//     assert(var);
//     if(inreg){
//         if(var->regno==-1){
//             assert(0);
//             printf("Error: Operand %s not in register\n",var->op->name);
//         }
//         return var->regno;
//     }
//     else{ //可能已在可能不在reg中
//         if(var->regno>=0) //还在寄存器中
//             return var->regno;
//         for(int regno=t0;regno<=t7;regno++){
//             if(regs[regno].state==UNUSED){
//                 regs[regno].state=USED;
//                 regs[regno].var=var;
//                 var->regno=regno;
//                 return regno;
//             }
//         }
//         for(int regno=t8;regno<=t9;regno++){
//             if(regs[regno].state==UNUSED){
//                 regs[regno].state=USED;
//                 regs[regno].var=var;
//                 var->regno=regno;
//                 return regno;
                
//             }
//         }
        
//     }
// }

// void transfer_IR(InterCode ir){
//     switch(ir->kind){
//         case IR_LABEL:
//             fprintf(mipsout,"%s:\n",ir->u.one->name);
//             break;
//         case IR_FUNCTIONNAME:
//             fprintf(mipsout,"%s:\n",ir->u.one->name);
//             break;
//         case IR_CALL:
//             assert(arg_no==ir->u.one->function_type->u.function.paramnum);
//             transfer_IR_CALL(ir,ir->u.one->function.paramnum);
//             arg_no=-1;
//             stackcnt=-1;
//             break;
//         case IR_PARAM:
//             transfer_IR_PARAM(ir);
//             break;
//         case IR_ARG:
//             int paramnum=ir->u.one->function_type->u.function.paramnum;
//             assert(paramnum>=0);
//             if(arg_no==-1){
//                 arg_no=0;
//                 fprintf(mipsout,"  addi $sp, $sp, -%d\n",(paramnum+2)*4);
//                 for(int i=0;i<paramnum;i++){
//                     fprintf(mipsout,"  sw %s, %d($sp)\n",regName[i+a0],(i+paramnum-2)*4); //参数寄存器入栈
//                 }
//             }
//             transfer_IR_ARG(ir,arg_no);
//             arg_no++;
//         case IR_RETURN:
//             fprintf(mipsout,"  move $v0, %s\n",regName[get_reg(ir->u.one,0)]);
//             fprintf(mipsout,"  jr $ra\n");
//             break;
//         case IR_READ:
//             transfer_IR_READ(ir);
//             break;
//         case IR_WRITE:
//             transfer_IR_WRITE(ir);
//             break;
//         case IR_GOTO:
//             fprintf(mipsout,"  j %s\n",ir->u.one->name);
//             return;
//         case IR_IFGOTO:
//             transfer_IR_IFGOTO(ir);
//             break;
//         case IR_ASSIGN:
//             transfer_IR_ASSIGN(ir);
//             break;
//         case IR_ADD:
//         case IR_SUB:
//         case IR_MUL:
//         case IR_DIV:
//             transfer_IR_CAL(ir);
//         case IR_GETADDR:    //无结构体和数组出现
//         case IR_DEC:
//             assert(0);
//     }
// }

// // void transfer_IR(InterCode ir){
// //     switch(ir->kind){
// //         case IR_LABEL:
// //             fprintf(mipsout,"%s:\n",ir->u.one->name);
// //             break;
// //         case IR_FUNCTIONNAME:
// //             fprintf(mipsout,"%s:\n",ir->u.one->name);
// //             break;
// //         case IR_CALL:
// //             transfer_IR_CALL(ir,ir->u.one->function.paramnum);
// //             arg_no=-1;
// //             cnt_s=-1;
// //             t1_s=-1;
// //             t2_s=-1;
// //             break;
// //         case IR_PARAM:
// //             transfer_IR_PARAM(ir);
// //             break;
// //         case IR_ARG:
// //             if(arg_no==-1){
// //                 arg_no=ir->u.one->function.paramnum;
// //                 cnt_s=0;
// //                 t1_s=0;
// //                 t2_s=0;
// //                 a_s=0;

// //                 for(int regno=a0;regno<a0+ir->u.one->function.paramnum;regno++){
// //                     if(!var_free_after_ir(ir,regs[regno].var)){
// //                         cnt_s++;
// //                         a_s|=1<<(regno-a0);
// //                     }
// //                 }
// //                 for(int regno=t0;regno<=t7;regno++){ //如果调用者保存寄存器中当前存储的变量以后在当前函数中还会用到，那么需要将它保存入栈
// //                     if(!var_free_after_ir(ir,regs[regno].var)){ 
// //                         cnt_s++;
// //                         t1_s|=1<<(regno-t0);
// //                     }
// //                 }
// //                 for(int regno=t8;regno<=t9;regno++){
// //                     if(!var_free_after_ir(ir,regs[regno].var)){
// //                         cnt_s++;
// //                         t2_s|=1<<(regno-t8);
// //                     }
// //                 }

// //                 fprintf(mipsout,"  addi $sp, $sp, -%d\n",cnt_s*4);
// //                 int temp=0;
// //                 //如果传入的参数寄存器中的原变量之后在本函数中之后还会用到，则需要保存入栈
// //                 for(int regno=a0;regno<a0+ir->u.one->function.paramnum;regno++){
// //                     if(a_s&(1<<(regno-a0))){
// //                         fprintf(mipsout, "  sw %s, %d($sp)\n",regName[a0+temp],temp*4);
// //                         temp++;
// //                     }
// //                 }

// //                 //按需保存调用者保存寄存器
// //                 for(int regno=t0;regno<=t7;regno++){
// //                     if(t1_s&(1<<(regno-t0))){
// //                         fprintf(mipsout, "  sw %s, %d($sp)\n",regName[t0+temp],temp*4);
// //                         temp++;
// //                     }
// //                 }
// //                 for(int regno=t8;regno<=t9;regno++){
// //                     if(t2_s&(1<<(regno-t8))){
// //                         fprintf(mipsout, "  sw %s, %d($sp)\n",regName[t8+temp],temp*4);
// //                         temp++;
// //                     }
// //                 }
// //                 assert(cnt_s==temp); //假如需要入栈的有t0,t5,t8,t9,a0,a3,则此刻栈中格局为t9,t8,t5,t0,a3,a0|sp指向此处
            
            
// //             }
// //             arg_no--;
// //             transfer_IR_ARG(ir,arg_no);
// //             break;
// //         case IR_RETURN:
// //             fprintf(mipsout,"  move $v0, %s\n",regName[get_reg(ir->u.one,0)]);
// //             fprintf(mipsout,"  jr $ra\n");
// //             break;
// //         case IR_READ:
// //             transfer_IR_READ(ir);
// //             break;
// //         case IR_WRITE:
// //             transfer_IR_WRITE(ir);
// //             break;
// //         case IR_GOTO:
// //             fprintf(mipsout,"  j %s\n",ir->u.one->name);
// //             return;
// //         case IR_IFGOTO:
// //             transfer_IR_IFGOTO(ir);
// //             break;
// //         case IR_ASSIGN:
// //             transfer_IR_ASSIGN(ir);
// //             break;
// //         case IR_ADD:
// //         case IR_SUB:
// //         case IR_MUL:
// //         case IR_DIV:
// //             transfer_IR_CAL(ir);
// //         case IR_GETADDR:    //无结构体和数组出现
// //         case IR_DEC:
// //             assert(0);
// //     }
// // }