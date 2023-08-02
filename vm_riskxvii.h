#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define ARRAY_SIZE_CONTENT 256 //was 9 //this is the number of lines in the file and needs to be a variable. 
//this only works for the first example
#define INST_MEM_SIZE 1024
#define DATA_MEM_SIZE 1024
#define FALSE 0
#define TRUE 1

#define OPP_FROM 0
#define OPP_TO 6

// extern struct blob blob;
extern struct blob {
    unsigned char inst_mem[INST_MEM_SIZE];
    unsigned char data_mem[DATA_MEM_SIZE];
} blob;

extern uint32_t r[32];// initializing every single register. 
extern int pc;
extern char data_mem[DATA_MEM_SIZE];

#define ARRAY_SIZE(from,to) (to - from + 1)

// #include "virtual_routines.h"

struct parsed_hold{
    uint32_t rd;
    uint32_t rs1;
    uint32_t rs2;
    uint32_t func3;
    uint32_t func7;
    uint32_t immediate;
    uint32_t oppcode;
};


extern int virtual_routine_check(int a, struct parsed_hold * current_task);

extern void addi(struct parsed_hold * current_task);
extern void jal(struct parsed_hold * current_task);
extern void lui(struct parsed_hold * current_task);
extern void srl(struct parsed_hold * current_task);
extern void sb(struct parsed_hold * current_task, struct blob* mem);
extern void jalr(struct parsed_hold * current_task);
extern void add(struct parsed_hold * current_task);
extern void sub(struct parsed_hold * current_task);
extern void sll(struct parsed_hold * current_task);
extern void slt(struct parsed_hold * current_task);
extern void sltu(struct parsed_hold * current_task);
extern void xor(struct parsed_hold * current_task);
extern void sra(struct parsed_hold * current_task);
extern void and(struct parsed_hold * current_task);
extern void slti(struct parsed_hold * current_task);
extern void xori(struct parsed_hold * current_task);
extern void andi(struct parsed_hold * current_task);
extern void lb(struct parsed_hold * current_task, struct blob* mem);
extern void lh(struct parsed_hold * current_task, struct blob* mem);
extern void bgeu(struct parsed_hold * current_task);
extern void or(struct parsed_hold * current_task);
extern void ori(struct parsed_hold * current_task);
extern void lw(struct parsed_hold * current_task, struct blob* mem);
extern void lbu(struct parsed_hold * current_task, struct blob* mem);
extern void lhu(struct parsed_hold * current_task, struct blob* mem);
extern void sh(struct parsed_hold * current_task, struct blob* mem);
extern void sltiu(struct parsed_hold * current_task);
extern void sw(struct parsed_hold * current_task, struct blob* mem);
extern void beq(struct parsed_hold * current_task);
extern void bne(struct parsed_hold * current_task);
extern void blt(struct parsed_hold * current_task);
extern void bltu(struct parsed_hold * current_task);
extern void bge(struct parsed_hold * current_task);




extern void reverse_array(char * array, int size, char * array_replace);
extern int grab_array(char * binary,char * subset,char * copy_subset,int from, int to);

extern int parse_type_I(struct parsed_hold * input,int oppcode, char * bit_array);
extern int parse_type_R(struct parsed_hold * input,int oppcode, char * bit_array);
extern int parse_type_U(struct parsed_hold * input,int oppcode, char * bit_array);
extern int parse_type_S(struct parsed_hold * input,int oppcode, char * bit_array);
extern int parse_type_UJ(struct parsed_hold * input,int oppcode, char * bit_array);
extern int parse_type_SB(struct parsed_hold * input,int oppcode, char * bit_array);
