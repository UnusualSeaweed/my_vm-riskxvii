#include "operations.h"
void addi(struct parsed_hold * current_task){
    r[current_task->rd] = r[current_task->rs1] + current_task->immediate;
    pc += 4;
}

void jal(struct parsed_hold * current_task){
    r[current_task->rd] = pc + 4;
    pc += (current_task->immediate << 1);
}

void lui(struct parsed_hold * current_task){
    r[current_task->rd] = current_task->immediate << 12;
    pc += 4;
}

void srl(struct parsed_hold * current_task){
    r[current_task->rd] = r[current_task->rs1] >> r[current_task->rs2];
    pc += 4;
}

void sb(struct parsed_hold * current_task, struct blob* mem){
    //this function below checks whether their is any virtual routines that are being activated. 
    if(virtual_routine_check(r[current_task->rs1] + current_task->immediate, current_task) == TRUE){
        pc += 4;
        return;
    }
    if(r[current_task->rs1] + current_task->immediate < INST_MEM_SIZE){
        pc+=4;
        return; 
    }
    data_mem[r[current_task->rs1] + current_task->immediate - INST_MEM_SIZE] = r[current_task->rs2]; 
    pc += 4;
}


void jalr(struct parsed_hold * current_task){
    r[current_task->rd] = pc + 4;
    pc = r[current_task->rs1] + current_task->immediate;
}

void add(struct parsed_hold * current_task){ 
    r[current_task->rd] = r[current_task->rs1] + r[current_task->rs2];
    pc += 4;
}

void sub(struct parsed_hold * current_task){
    r[current_task->rd] = r[current_task->rs1] - r[current_task->rs2];
    pc += 4;
}

void sll(struct parsed_hold * current_task){
    r[current_task->rd] = r[current_task->rs1] << r[current_task->rs2];
    pc += 4;
}

void slt(struct parsed_hold * current_task){
    if (r[current_task->rs1] < r[current_task->rs2]){
        r[current_task->rd] = 1;
    }
    else{
        r[current_task->rd] = 0;
    }
    pc += 4;
}

void sltu(struct parsed_hold * current_task){
    if ((uint32_t)r[current_task->rs1] < (uint32_t)r[current_task->rs2]){
        r[current_task->rd] = 1;
    }
    else{
        r[current_task->rd] = 0;
    }
    pc += 4;
}

void xor(struct parsed_hold * current_task){
    r[current_task->rd] = r[current_task->rs1] ^ r[current_task->rs2];
    pc += 4;
}

void sra(struct parsed_hold * current_task){
    uint32_t temp = r[current_task->rs1] << (32 - r[current_task->rs2]);
    r[current_task->rd] = r[current_task->rs1] >> r[current_task->rs2];
    r[current_task->rd] = r[current_task->rd] | temp;
    pc += 4;
}

void and(struct parsed_hold * current_task){
    r[current_task->rd] = r[current_task->rs1] & r[current_task->rs2];
    pc += 4;
}

void slti(struct parsed_hold * current_task){
    if (r[current_task->rs1] < current_task->immediate){
        r[current_task->rd] = 1;
    }
    else{
        r[current_task->rd] = 0;
    }
    pc += 4;
}

void xori(struct parsed_hold * current_task){
    r[current_task->rd] = r[current_task->rs1] ^ current_task->immediate;
    pc += 4;
}

void andi(struct parsed_hold * current_task){
    r[current_task->rd] = r[current_task->rs1] & current_task->immediate;
    pc += 4;
}

void lb(struct parsed_hold * current_task, struct blob* mem){
    //this function below checks whether their is any virtual routines that are being activated.
    if(virtual_routine_check(r[current_task->rs1] + current_task->immediate, current_task) == TRUE){
        pc += 4;
        return;
    }
    int address = r[current_task->rs1] + current_task->immediate;
    uint8_t temp;
    if ((uint32_t)r[current_task->rs1] + (uint32_t)current_task->immediate < INST_MEM_SIZE){ //checking it with correct memory.
        temp = mem->inst_mem[address];
    }
    else if ((uint32_t)r[current_task->rs1] + (uint32_t)current_task->immediate < DATA_MEM_SIZE*2){
        temp = mem->data_mem[address - INST_MEM_SIZE];
    }
    else{
 
    }
    r[current_task->rd] = (uint32_t)(uint8_t)temp;
    pc += 4;
}

void lh(struct parsed_hold * current_task, struct blob* mem){
    //this function below checks whether their is any virtual routines that are being activated.
    if(virtual_routine_check(r[current_task->rs1] + current_task->immediate, current_task) == TRUE){
        pc += 4;
        return;
    }
    int address = r[current_task->rs1] + current_task->immediate;
    uint16_t temp;
    if ((uint32_t)r[current_task->rs1] + (uint32_t)current_task->immediate < INST_MEM_SIZE){
        temp = mem->inst_mem[address];
        temp = temp | (mem->inst_mem[address + 1] << 8);
    }
    else if ((uint32_t)r[current_task->rs1] + (uint32_t)current_task->immediate < DATA_MEM_SIZE * 2){
        temp = mem->data_mem[address - INST_MEM_SIZE];
        temp = temp | (mem->data_mem[address - INST_MEM_SIZE + 1] << 8);
    }
    else{
    }
    r[current_task->rd] = (uint32_t)(uint16_t)temp;
    pc += 4;
}

void bgeu(struct parsed_hold * current_task){
    if ((uint32_t)r[current_task->rs1] >= (uint32_t)r[current_task->rs2]){
        pc += current_task->immediate;
        return;
    }
    else{
        pc += 4;
    }
}

void or(struct parsed_hold * current_task){
    r[current_task->rd] = r[current_task->rs1] | r[current_task->rs2];
    pc += 4;
}

void ori(struct parsed_hold * current_task){
    r[current_task->rd] = r[current_task->rs1] | current_task->immediate;
    pc += 4;
}


void lw(struct parsed_hold * current_task, struct blob* mem){
    //this function below checks whether their is any virtual routines that are being activated.
    if(virtual_routine_check((uint32_t)r[current_task->rs1] + current_task->immediate, current_task) == TRUE){
        pc += 4;
        return;
    }
    int address = (uint32_t)r[current_task->rs1] + current_task->immediate;
    uint32_t temp = 0;

    if (address > 0 && address < INST_MEM_SIZE){
        //because there is 32 bits it can only fit 8 bits in any one address in the memory,
        //since there are 4 bytes in a 32 bit integer, we must put it into 4 separated addresses in memory.
        temp = mem->inst_mem[address];
        temp = temp | (uint32_t)(mem->inst_mem[address + 1] << 8); 
        temp = temp | (uint32_t)(mem->inst_mem[address + 2] << 16);
        temp = temp | (uint32_t)(mem->inst_mem[address + 3] << 24);
    }
    else if (address > INST_MEM_SIZE-1 && address < DATA_MEM_SIZE * 2){
        //this following code works exactly the same as the one above except that it is offset for being 
        //in the data memory. 
        temp |= (uint32_t)mem->data_mem[address - INST_MEM_SIZE];
        temp |= (uint32_t)(mem->data_mem[address - INST_MEM_SIZE + 1] << 8);
        temp |= (uint32_t)(mem->data_mem[address - INST_MEM_SIZE + 2] << 16);
        temp |= (uint32_t)(mem->data_mem[address - INST_MEM_SIZE + 3] << 24);
    }
    else{
    }
    r[current_task->rd] = temp;

    pc += 4;
}

void lbu(struct parsed_hold * current_task, struct blob* mem){
    if(virtual_routine_check(r[current_task->rs1] + current_task->immediate, current_task) == TRUE){
        pc += 4;
        return;
    }
    int address = r[current_task->rs1] + current_task->immediate;
    uint8_t temp;
    if ((uint32_t)r[current_task->rs1] + (uint32_t)current_task->immediate < INST_MEM_SIZE){
        temp = mem->inst_mem[address];
    }
    else if ((uint32_t)r[current_task->rs1] + (uint32_t)current_task->immediate < DATA_MEM_SIZE*2){
        temp = mem->data_mem[address - INST_MEM_SIZE];
    }
    else{
 
    }
    r[current_task->rd] = temp;
    pc += 4;
}

void lhu(struct parsed_hold * current_task, struct blob* mem){
    if(virtual_routine_check(r[current_task->rs1] + current_task->immediate, current_task) == TRUE){
        pc += 4;
        return;
    }
    int address = r[current_task->rs1] + current_task->immediate;
    uint16_t temp;
    if ((uint32_t)r[current_task->rs1] + (uint32_t)current_task->immediate < INST_MEM_SIZE){
        temp = mem->inst_mem[address];
        temp = temp | (mem->inst_mem[address + 1] << 8);
    }
    else if ((uint32_t)r[current_task->rs1] + (uint32_t)current_task->immediate < DATA_MEM_SIZE*2){
        temp = mem->data_mem[address - INST_MEM_SIZE];
        temp = temp | (mem->data_mem[address - INST_MEM_SIZE + 1] << 8);
    }
    else{
 
    }
    r[current_task->rd] = (uint32_t)(uint16_t)temp;
    pc += 4;
}

void sh(struct parsed_hold * current_task, struct blob* mem){
    if(virtual_routine_check(r[current_task->rs1] + current_task->immediate, current_task) == TRUE){
        pc += 4;
        return;
    }
    int address = (uint32_t)r[current_task->rs1] + current_task->immediate;
    uint16_t temp = r[current_task->rs2]; // get last 16 bits
    if (address < INST_MEM_SIZE){
        mem->inst_mem[address] = temp; // add last 8 bits
        mem->inst_mem[address + 1] = temp >> 8; // add first 8 bits
    }
    else if (address < DATA_MEM_SIZE*2){
        mem->data_mem[address - INST_MEM_SIZE] = temp;
        mem->data_mem[address - INST_MEM_SIZE + 1] = temp >> 8;
    }
    else{
 
    }
    pc += 4;
}

void sltiu(struct parsed_hold * current_task){
    if((uint32_t)r[current_task->rs1] < current_task->immediate){
        r[current_task->rd] = 1;
    }
    else{
        r[current_task->rd] = 0;
    }
    pc += 4;
}

void sw(struct parsed_hold * current_task, struct blob* mem){
    //this function below checks whether their is any virtual routines that are being activated.
    if(virtual_routine_check(r[current_task->rs1] + current_task->immediate,current_task) == TRUE){
        pc += 4;
        return;
    }

    int address = (uint32_t)r[current_task->rs1] + current_task->immediate;
    if (address >= 0 && address < INST_MEM_SIZE) {
        mem->inst_mem[address] = r[(uint32_t)(current_task->rs2)];
        mem->inst_mem[address + 1] = r[(uint32_t)(current_task->rs2)] >> 8; //to get second batch of 8 bits.
        mem->inst_mem[address + 2] = r[(uint32_t)(current_task->rs2)] >> 16; //to get third batch of 8 bits.
        mem->inst_mem[address + 3] = r[(uint32_t)(current_task->rs2)] >> 24; //to get final batch of 8 bits.
    }
    else if (address >= INST_MEM_SIZE && address < DATA_MEM_SIZE*2) {
        mem->data_mem[address - INST_MEM_SIZE] = r[(uint32_t)(current_task->rs2)];
        mem->data_mem[address - INST_MEM_SIZE + 1] = r[(uint32_t)(current_task->rs2)] >> 8;
        mem->data_mem[address - INST_MEM_SIZE + 2] = r[(uint32_t)(current_task->rs2)] >> 16;
        mem->data_mem[address - INST_MEM_SIZE + 3] = r[(uint32_t)(current_task->rs2)] >> 24;
    }
    else{
 
    }
    pc += 4;
}

void beq(struct parsed_hold * current_task){
    if((uint32_t)r[current_task->rs1] == (uint32_t)r[current_task->rs2]){
        pc += current_task->immediate;
        return;
    }
    pc += 4;
}

void bne(struct parsed_hold * current_task){
    if((uint32_t)r[current_task->rs1] != (uint32_t)r[current_task->rs2]){
        pc += current_task->immediate;
        return;
    }   
    pc += 4;
}

void blt(struct parsed_hold * current_task){
    if(r[current_task->rs1] < r[current_task->rs2]){
        pc += current_task->immediate;
        return;
    }
    pc += 4;
}

void bltu(struct parsed_hold * current_task){
    if((uint32_t)r[current_task->rs1] < (uint32_t)r[current_task->rs2]){
        pc += current_task->immediate;
        return;
    }
    pc += 4;
}

void bge(struct parsed_hold * current_task){
    if(r[current_task->rs1] >= r[current_task->rs2]){
        pc += current_task->immediate;
        return;
    }
    pc += 4;
}