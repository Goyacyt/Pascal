#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
typedef struct NODE{
    char name[32];
    int first_line;
    int last_line;
    union{
        char id_val[32];
        char type_val[20];
        int int_val;
        float float_val;
    }val;
    struct NODE* bro;
    struct NODE* son;
}node;
