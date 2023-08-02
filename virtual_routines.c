#include "virtual_routines.h"

//basically used for if statements, making code more readable etc. 
#define FALSE 0
#define TRUE 1

//writes a character 
void console_write_character(uint32_t a){ 
    printf("%c",r[a]);
}

//writes signed int. 
void console_write_signedint(struct parsed_hold * current_task){ 
    printf("%d", r[current_task->rs2]);
}

//writes unsigned int. 
void console_write_unsignedint(struct parsed_hold * current_task){
    printf("%x",r[current_task->rs2]);
}

//halts program.
void halt(){ 
    printf("CPU Halt Requested\n");
    exit(1);
}
//reads char
void console_read_char(){ 
    unsigned char curr;
    scanf("%c", &curr);

}

void dump(){ 
}

//reads signed integer. 
void console_read_signed_integer(struct parsed_hold * current_task){
    uint32_t temp;
    scanf("%d",&temp);
    r[current_task->rd] = temp;
}

//checks if a virtual machine is called from an operation. 
int virtual_routine_check(int a, struct parsed_hold * current_task){
    if(a == 0x0800){
        console_write_character(current_task->rs2);
        return TRUE;
    }
    else if(a == 0x0804){
        console_write_signedint(current_task);
        return TRUE;
    }
    else if(a == 0x0808){
        console_write_unsignedint(current_task);
        return TRUE;
    }
    else if(a == 0x080C){
        halt();

        return TRUE;
    }
    else if(a == 0x0812){
        console_read_char();
        return TRUE;
    }
    else if(a == 0x0816){
        console_read_signed_integer(current_task);
        return TRUE;
    }
    else if(a == 0x0820){
        dump();
        return TRUE;
    }
    return FALSE;
}