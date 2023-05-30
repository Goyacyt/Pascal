#include "symtab.h"
#include "tree.h"
#include "intercode.h"
#include "basicblock.h"

#define MAX_IR 1024
#define MAX_VAR 1024
#define MAX_VAR_NUMBER 1024
#define MAX_LINE 1024


void parse_print_op(Operand op);
void parse_print_ir(InterCode ir);
void parse_print_irlist();

void parse_init_irlist();
void parse_insert_ir(InterCode ir);
Operand get_var(char *p);
Operand get_label(char *p);
Operand get_function(char *p);
void parse(FILE* yyin);
int repeat_name(char *name);
void print_BB(BasicBlock bb);
void partition();
void LA();