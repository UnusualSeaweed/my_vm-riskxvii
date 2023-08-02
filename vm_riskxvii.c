#include "vm_riskxvii.h"

uint32_t r[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // initializing every single register. 
int pc = 0; // program counter
char data_mem[DATA_MEM_SIZE] ={0};

enum OPPCODE{ //all oppcode values.
    R_OPP=51, 
    S_OPP=35,  
    SB_OPP=99, 
    U_OPP=55, 
    UJ_OPP=111, 
    I_OPP=19, 
    II_OPP=3, 
    III_OPP=103,
};

enum FUNC3{ //all func3 values, comment is respective parse type.
    ADD3 = 0, //R
    SUB3 = 0, //R
    SLL3 = 1, //R
    SLT3 = 2, //R
    SLTU3 = 3, //R
    XOR3 = 4, //R
    SRL3 = 5, //R
    SRA3 = 5, //R
    OR3 = 6, //R
    AND3 = 7, //R

    ADDI3 = 0, //I 
    JALR3 = 0, //III 
    LB3 = 0, //II 
    LH3 = 1, //II 
    LW3 = 2, //II 
    SLTI3 = 2, //I 
    SLTIU3 = 3, //I 
    XORI3 = 4, //I 
    LBU3 = 4, //II 
    LHU3 = 5, //II 
    ORI3 = 6, //I 
    ANDI3 = 7, //I 

    SB3 = 0, //S
    SH3 = 1, //S
    SW3 = 2, //S

    BEQ3 = 0, //SB
    BNE3 = 1, //SB
    BLT3 = 4, //SB
    BLTU3 = 6, //SB
    BGE3 = 5, //SB
    BGEU3 = 7, //SB
};

enum FUNC7{ //all func7 values
    ADD7 = 0, //R
    SUB7 = 32, //R
    XOR7 = 0, //R
    OR7 = 0, //R
    AND7 = 0, //R
    SLL7 = 0, //R
    SRL7 = 0, //R
    SRA7 = 32, //R
    SLT7 = 0, //R
    SLTU7 = 0, //R
};

void to_bit_arr(char curr, char temp[8]) {
    for (int i = 0; i < 8; i ++) {
        if ((curr >> i) & 1){
            temp[i] = '1';
        } else {
            temp[i] = '0';
        } 
    }
}

int main(int argc, char * argv[]){
    FILE * file = fopen(argv[1], "rb"); // this needs to be put in the command line.
    unsigned char buffer[INST_MEM_SIZE];
    char content[256][4];
    char parse_array[ARRAY_SIZE_CONTENT][33]; //parse_array and bit_array take the input and is parsed 
    char bit_array[ARRAY_SIZE_CONTENT][33]; //into bit_array, (33 is for each 32 bit instruction plue a
    //null byter.

    fread(buffer, INST_MEM_SIZE,1,file); //simply reading into the file from the buffer, moving
    // it into content array.
    for(int k = 0; k < ARRAY_SIZE_CONTENT; k++){
        for(int n = 0; n < 4; n++){
                content[k][3 - n] = buffer[k * 4 + n];            
        }
    }
    struct blob mem;
    // go back to beginning of file
    fseek(file, 0, SEEK_SET);
    fread(mem.inst_mem, INST_MEM_SIZE, 1, file);
    fread(mem.data_mem, DATA_MEM_SIZE, 1, file);


    for(int i = 0; i < ARRAY_SIZE_CONTENT; i++){
        for(int j = 0; j < 4; j++){
            char q = content[i][j];
            char single_byte[8]; // a byte has 8 bits, hence length. 
            to_bit_arr(q, single_byte);
            
            for(int k = 0; k < 8; k++){
                parse_array[i][(j * 8) + k] = single_byte[7-k]; //this reverses the way that the array
                // is put into the parse_array.
            }
        }
        parse_array[i][32] = '\0'; //adding null byter at the end. 
    }

    for (int i = 0; i < ARRAY_SIZE_CONTENT; i++){
        for (int j = 0; j < 33; j++){
            bit_array[i][j] = parse_array[i][j];
        } 
    }

    for (int i = 0; i < 256; i++) {
        char bit_array_cpy[33];
        reverse_array(bit_array[i], 32, bit_array_cpy); //flips the array around. (essentially the 
        //grab_array function subset function will flip the individual code back.)
    }
    // int counter = 0;
    for(int index = 0; index < 256; index = pc/4){
        r[0] = 0;
        char oppcode_array[ARRAY_SIZE(OPP_FROM,OPP_TO)]; 
        char oppcode_array_cpy[ARRAY_SIZE(OPP_FROM,OPP_TO)];
        int oppcode = grab_array(bit_array[index],oppcode_array,oppcode_array_cpy,OPP_FROM,OPP_TO);
        struct parsed_hold current_task;
        current_task.oppcode = oppcode; //initializing struct to 0.
        current_task.rd = 0;
        current_task.rs1 = 0;
        current_task.rs2 = 0;
        current_task.immediate = 0;
        current_task.func3 = 0;
        current_task.func7 = 0;
        if(oppcode == R_OPP){
            parse_type_R(&current_task,oppcode,bit_array[index]); //parse in accordance to R Type.
            if(current_task.func3 == ADD3 || current_task.func3 == SUB3){ //using func3 to identify
            //instruction command, func7 is used if necessary for the function. 
                if(current_task.func7 == ADD7){
                    add(&current_task);
                }else if(current_task.func7 == SUB7){
                    sub(&current_task);
                }
            }else if(current_task.func3 == SLL3){
                sll(&current_task);
            }else if(current_task.func3 == SLT3){
                slt(&current_task);
            }else if(current_task.func3 == SLTU3){
                sltu(&current_task);
            }else if(current_task.func3 == XOR3){
                xor(&current_task);
            }else if(current_task.func3 == SRL3 || current_task.func3 == SRA3){
                if(current_task.func7 == SRL7){
                    srl(&current_task);
                }else if(current_task.func7 == SRA7){
                    sra(&current_task);
                }
            }else if(current_task.func3 == OR3){
                or(&current_task);
            }else if(current_task.func3 == AND3){
                and(&current_task);
            }
            //then go to type r_opp code function to complete the parsing. 
        }else if(oppcode == I_OPP || oppcode == II_OPP || oppcode == III_OPP){
            parse_type_I(&current_task,oppcode,bit_array[index]); 
            if(oppcode == I_OPP){
                if(current_task.func3 == ADDI3){
                    addi(&current_task);
                }else if(current_task.func3 == SLTI3){
                    slti(&current_task);
                }else if(current_task.func3 == SLTIU3){
                    sltiu(&current_task);
                }else if(current_task.func3 == XORI3){
                    xori(&current_task);
                }else if(current_task.func3 == ORI3){
                    ori(&current_task);
                }else if(current_task.func3 == ANDI3){
                    andi(&current_task);
                }
            }else if(oppcode == II_OPP){
                if(current_task.func3 == LB3){
                    lb(&current_task, &mem);
                }else if(current_task.func3 == LH3){
                    lh(&current_task, &mem);
                }else if(current_task.func3 == LW3){
                    lw(&current_task, &mem);
                }else if(current_task.func3 == LBU3){
                    lbu(&current_task, &mem);
                }else if(current_task.func3 == LHU3){
                    lhu(&current_task, &mem);
                }
            }else if(oppcode == III_OPP){
                jalr(&current_task);
            }
        }else if(oppcode == S_OPP){
            parse_type_S(&current_task,oppcode,bit_array[index]); 
            if(current_task.func3 == SB3){
                sb(&current_task, &mem);
            }else if(current_task.func3 == SH3){
                sh(&current_task, &mem);
            }else if(current_task.func3 == SW3){
                sw(&current_task, &mem);
            }
        }else if(oppcode == SB_OPP){
            parse_type_SB(&current_task,oppcode,bit_array[index]); 
            if(current_task.func3 == BEQ3){
                beq(&current_task);
            }else if(current_task.func3 == BNE3){
                bne(&current_task);
            }else if(current_task.func3 == BLT3){
                blt(&current_task);
            }else if(current_task.func3 == BLTU3){
                bltu(&current_task);
            }else if(current_task.func3 == BGE3){
                bge(&current_task);
            }else if(current_task.func3 == BGEU3){
                bgeu(&current_task);
            }
        }else if(oppcode == U_OPP){
            parse_type_U(&current_task,oppcode,bit_array[index]);  
            lui(&current_task);
        }else if(oppcode == UJ_OPP){
            parse_type_UJ(&current_task,oppcode,bit_array[index]); 
            jal(&current_task);
        }else{ //if oppcode not recognised.
            printf("Instruction not implemented\n"); 
            exit(1);
        }
    }
    fclose(file); //close file.
    exit(0);
}