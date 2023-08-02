#include "vm_riskxvii.h"

void console_write_character(uint32_t a);

void console_write_signedint(struct parsed_hold * current_task);

void console_write_unsignedint(struct parsed_hold * current_task);

void halt();

void console_read_char();

void dump();

void console_read_signed_integer(struct parsed_hold * current_task);

int virtual_routine_check(int a, struct parsed_hold * current_task);