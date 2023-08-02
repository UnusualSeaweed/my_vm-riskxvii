#include "vm_riskxvii.h"



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
