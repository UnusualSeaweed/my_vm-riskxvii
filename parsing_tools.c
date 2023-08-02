#include "parsing_tools.h"

int my_strlen(char* array){ //my custom string length function.
    int counter = 0;
    for(int i = 0; array[i] != 0; i++){
        counter++;
    }
    return counter;
}

int power(int a, int b){ //returns a to the power of b.
    int temp = 1;
    for(int i = 0; i < b; i++){
        temp *= a;
    }
    return temp;
}

//converts a binary number to decimal. 
//returning the decimal number, accepts character arrays only.
int binary_to_decimal(int size, char binary[]){
    int temp = 0;
    if(binary[0] == '1'){
        temp -= power(2,size-1);
    }
    for(int i = 1; i < size; i++){
        if(binary[i] == '1'){
            temp += power(2,size-i-1);
        }
    }
    return temp;
}

//converts a binary number to decimal. returning the decimal number, accepts character arrays only.
uint32_t binary_to_decimal_unsigned(int size, char binary[]){ 
    int temp = 0;
    for(int i = 0; i < size; i++){
        if(binary[i] == '1'){
            temp += power(2,size-i-1);
        }
    }
    return temp;
}

//copies the array from index  'from' to index 'to'. from array 'array' to array 'temp'
int array_subset(char* array, char * subset, int from, int to){ 
    if(from > to || from < 0){
        return 0; 
    }
    int k = 0;
    for(int i = from; i <= to; i++){
        subset[k] = array[i];
        k++;
    }
    return 1;
}

//simply reverses the array, leaving the null byte at the end of the array. 
void reverse_array(char * array, int size, char * array_replace){ 
    for (int i = 0; i < size; i++) {
        array_replace[i] = array[size - i - 1];
    }
    for(int i = 0; i < size; i++){ //copying values in reverse order into original array.
        array[i] = array_replace[i];
    }
    return;
}

//grabs an array subset, gets it from binary, puts it in subset, grabs it from index 'from' to 
//index 'to', although returns integers, they are all positive. 
int grab_array(char * binary,char * subset,char * copy_subset,int from, int to){
    for(int i = 0; i < ARRAY_SIZE(from,to); i++){
        subset[i] = 0;
        copy_subset[i] = 0;
    }
    array_subset(binary, subset, from, to);
    reverse_array(subset,ARRAY_SIZE(from,to),copy_subset);
    return binary_to_decimal_unsigned(ARRAY_SIZE(from,to),subset);
}

//same as function above but in signed formate (numbers can have a negative value).
int grab_array_signed(char * binary,char * subset,char * copy_subset,int from, int to){
    for(int i = 0; i < ARRAY_SIZE(from,to); i++){
        subset[i] = 0;
        copy_subset[i] = 0;
    }
    array_subset(binary, subset, from, to);
    reverse_array(subset,ARRAY_SIZE(from,to),copy_subset); //testing this. //THIS WAS CHANGED
    return binary_to_decimal(ARRAY_SIZE(from,to),subset);
}

//all indexes for parsing of type i for each of the instruction values. in binary input.
//(as per assignment descirption)
//all different types have their own set of indexes as seen below. 
#define I_FUNC3_FROM 12
#define I_FUNC3_TO 14

#define I_IMM_FROM 20
#define I_IMM_TO 31

#define I_RD_FROM 7
#define I_RD_TO 11

#define I_RS1_FROM 15
#define I_RS1_TO 19


// puts all of the values, e.g. rd, imm etc into the parsed_hold struct, for type i.
int parse_type_I(struct parsed_hold * input,int oppcode, char * bit_array){ 
    char func3_array[ARRAY_SIZE(I_FUNC3_FROM,I_FUNC3_TO)]; 
    char func3_array_cpy[ARRAY_SIZE(I_FUNC3_FROM,I_FUNC3_TO)]; 

    input->func3 = grab_array(bit_array,func3_array,func3_array_cpy,I_FUNC3_FROM,I_FUNC3_TO);

    char imm_array[ARRAY_SIZE(I_IMM_FROM,I_IMM_TO)]; 
    char imm_array_cpy[ARRAY_SIZE(I_IMM_FROM,I_IMM_TO)]; 

    input->immediate = grab_array_signed(bit_array,imm_array,imm_array_cpy,I_IMM_FROM,I_IMM_TO);

    char rd_array[ARRAY_SIZE(I_RD_FROM,I_RD_TO)]; 
    char rd_array_cpy[ARRAY_SIZE(I_RD_FROM,I_RD_TO)]; 

    input->rd = grab_array(bit_array,rd_array,rd_array_cpy,I_RD_FROM,I_RD_TO);

    char rs1_array[ARRAY_SIZE(I_RS1_FROM,I_RS1_TO)]; 
    char rs1_array_cpy[ARRAY_SIZE(I_RS1_FROM,I_RS1_TO)]; 

    input->rs1 = grab_array(bit_array,rs1_array,rs1_array_cpy,I_RS1_FROM,I_RS1_TO);
    return 1;
}

//all indexes for parsing of type r for each of the instruction values. in binary input. 
#define R_RD_FROM 7
#define R_RD_TO 11

#define R_FUNC3_FROM 12
#define R_FUNC3_TO 14

#define R_RS1_FROM 15
#define R_RS1_TO 19

#define R_RS2_FROM 20
#define R_RS2_TO 24

#define R_FUNC7_FROM 25
#define R_FUNC7_TO 31

// puts all of the values, e.g. rd, imm etc into the parsed_hold struct, for type r.
int parse_type_R(struct parsed_hold * input,int oppcode, char * bit_array){
    char rd_array[ARRAY_SIZE(R_RD_FROM,R_RD_TO)]; 
    char rd_array_cpy[ARRAY_SIZE(R_RD_FROM,R_RD_TO)]; 

    input->rd = grab_array(bit_array,rd_array,rd_array_cpy,R_RD_FROM,R_RD_TO);

    char func3_array[ARRAY_SIZE(R_FUNC3_FROM,R_FUNC3_TO)]; 
    char func3_array_cpy[ARRAY_SIZE(R_FUNC3_FROM,R_FUNC3_TO)]; 

    input->func3 = grab_array(bit_array,func3_array,func3_array_cpy,R_FUNC3_FROM,R_FUNC3_TO);

    char rs1_array[ARRAY_SIZE(R_RS1_FROM,R_RS1_TO)]; 
    char rs1_array_cpy[ARRAY_SIZE(R_RS1_FROM,R_RS1_TO)]; 

    input->rs1 = grab_array(bit_array,rs1_array,rs1_array_cpy,R_RS1_FROM,R_RS1_TO);

    char rs2_array[ARRAY_SIZE(R_RS2_FROM,R_RS2_TO)]; 
    char rs2_array_cpy[ARRAY_SIZE(R_RS2_FROM,R_RS2_TO)]; 

    input->rs2 = grab_array(bit_array,rs2_array,rs2_array_cpy,R_RS2_FROM,R_RS2_TO);

    char func7_array[ARRAY_SIZE(R_FUNC7_FROM,R_FUNC7_TO)]; 
    char func7_array_cpy[ARRAY_SIZE(R_FUNC7_FROM,R_FUNC7_TO)]; 

    input->func7 = grab_array(bit_array,func7_array,func7_array_cpy,R_FUNC7_FROM,R_FUNC7_TO);

    return 1;
}

//all indexes for parsing of type s for each of the instruction values. in binary input. 
#define U_RD_FROM 7
#define U_RD_TO 11

#define U_IMM_FROM 12 
#define U_IMM_TO 31

// puts all of the values, e.g. rd, imm etc into the parsed_hold struct, for type u.
int parse_type_U(struct parsed_hold * input,int oppcode, char * bit_array){
    char rd_array[ARRAY_SIZE(U_RD_FROM,U_RD_TO)]; 
    char rd_array_cpy[ARRAY_SIZE(U_RD_FROM,U_RD_TO)]; 

    input->rd = grab_array(bit_array,rd_array,rd_array_cpy,U_RD_FROM,U_RD_TO);

    char imm_array[ARRAY_SIZE(U_IMM_FROM,U_IMM_TO)]; 
    char imm_array_cpy[ARRAY_SIZE(U_IMM_FROM,U_IMM_TO)]; 

    input->immediate = grab_array_signed(bit_array,imm_array,imm_array_cpy,U_IMM_FROM,U_IMM_TO);

    return 0;
}

//all indexes for parsing of type s for each of the instruction values. in binary input. 
#define S_IMM1_FROM 7
#define S_IMM1_TO 11

#define S_IMM2_FROM 25
#define S_IMM2_TO 31

#define S_IMM_FROM 0
#define S_IMM_TO 11

#define S_FUNC3_FROM 12
#define S_FUNC3_TO 14

#define S_RS1_FROM 15
#define S_RS1_TO 19

#define S_RS2_FROM 20
#define S_RS2_TO 24

// puts all of the values, e.g. rd, imm etc into the parsed_hold struct, for type s.
int parse_type_S(struct parsed_hold * input,int oppcode, char * bit_array){
    char imm_array1[ARRAY_SIZE(S_IMM1_FROM,S_IMM1_TO)]; //there are 11 bits in an s_type immediate number. 
    char imm_array1_cpy[ARRAY_SIZE(S_IMM1_FROM,S_IMM1_TO)]; 

    //grabbing the first bunch of immediate numbers.
    grab_array_signed(bit_array,imm_array1,imm_array1_cpy,S_IMM1_FROM,S_IMM1_TO); 

    char imm_array2[ARRAY_SIZE(S_IMM2_FROM,S_IMM2_TO)]; 
    char imm_array2_cpy[ARRAY_SIZE(S_IMM2_FROM,S_IMM2_TO)]; 

    grab_array_signed(bit_array,imm_array2,imm_array2_cpy,S_IMM2_FROM,S_IMM2_TO);
    char imm_array[ARRAY_SIZE(S_IMM_FROM,S_IMM_TO)+1]; //there are 11 bits in an s_type immediate number. 
    for(int i = 0; i < ARRAY_SIZE(S_IMM_FROM,S_IMM_TO)+1; i++){
        imm_array[i] = 0;
    }

    //this is a combination of all the different chunks of immediate bits being combined into a single array.
    strncat(imm_array,imm_array2,ARRAY_SIZE(S_IMM2_FROM,S_IMM2_TO));
    strncat(imm_array,imm_array1,ARRAY_SIZE(S_IMM1_FROM,S_IMM1_TO));

    input->immediate = binary_to_decimal(ARRAY_SIZE(0,11),imm_array);

    char func3_array[ARRAY_SIZE(S_FUNC3_FROM,S_FUNC3_TO)]; 
    char func3_array_cpy[ARRAY_SIZE(S_FUNC3_FROM,S_FUNC3_TO)]; 

    input->func3 = grab_array(bit_array,func3_array,func3_array_cpy,S_FUNC3_FROM,S_FUNC3_TO);

    char rs1_array[ARRAY_SIZE(S_RS1_FROM,S_RS1_TO)]; 
    char rs1_array_cpy[ARRAY_SIZE(S_RS1_FROM,S_RS1_TO)]; 

    input->rs1 = grab_array(bit_array,rs1_array,rs1_array_cpy,S_RS1_FROM,S_RS1_TO);

    char rs2_array[ARRAY_SIZE(S_RS2_FROM,S_RS2_TO)]; 
    char rs2_array_cpy[ARRAY_SIZE(S_RS2_FROM,S_RS2_TO)]; 

    input->rs2 = grab_array(bit_array,rs2_array,rs2_array_cpy,S_RS2_FROM,S_RS2_TO);
    return 0;
}

//all indexes for parsing of type uj for each of the instruction values. in binary input. 
#define UJ_RD_FROM 7
#define UJ_RD_TO 11

#define UJ_IMM1_FROM 21
#define UJ_IMM1_TO 30

#define UJ_IMM2_FROM 20
#define UJ_IMM2_TO 20

#define UJ_IMM3_FROM 12
#define UJ_IMM3_TO 19

#define UJ_IMM4_FROM 31
#define UJ_IMM4_TO 31

#define UJ_IMM_FROM 1
#define UJ_IMM_TO 20

// puts all of the values, e.g. rd, imm etc into the parsed_hold struct, for type uj.
int parse_type_UJ(struct parsed_hold * input,int oppcode, char * bit_array){
    char rd_array[ARRAY_SIZE(UJ_RD_FROM,UJ_RD_TO)]; 
    char rd_array_cpy[ARRAY_SIZE(UJ_RD_FROM,UJ_RD_TO)];
    input->rd = grab_array(bit_array,rd_array,rd_array_cpy,UJ_RD_FROM,UJ_RD_TO);

    char imm_array1[ARRAY_SIZE(UJ_IMM1_FROM,UJ_IMM1_TO)]; 
    char imm_array1_cpy[ARRAY_SIZE(UJ_IMM1_FROM,UJ_IMM1_TO)]; 
    
    grab_array_signed(bit_array,imm_array1,imm_array1_cpy,UJ_IMM1_FROM,UJ_IMM1_TO);

    char imm_array2[ARRAY_SIZE(UJ_IMM2_FROM,UJ_IMM2_TO)]; 
    char imm_array2_cpy[ARRAY_SIZE(UJ_IMM2_FROM,UJ_IMM2_TO)]; 

    grab_array_signed(bit_array,imm_array2,imm_array2_cpy,UJ_IMM2_FROM,UJ_IMM2_TO);

    char imm_array3[ARRAY_SIZE(UJ_IMM3_FROM,UJ_IMM3_TO)]; 
    char imm_array3_cpy[ARRAY_SIZE(UJ_IMM3_FROM,UJ_IMM3_TO)]; 

    grab_array_signed(bit_array,imm_array3,imm_array3_cpy,UJ_IMM3_FROM,UJ_IMM3_TO);

    char imm_array4[ARRAY_SIZE(UJ_IMM4_FROM,UJ_IMM4_TO)]; 
    char imm_array4_cpy[ARRAY_SIZE(UJ_IMM4_FROM,UJ_IMM4_TO)]; 

    grab_array_signed(bit_array,imm_array4,imm_array4_cpy,UJ_IMM4_FROM,UJ_IMM4_TO); 

    char imm_array[ARRAY_SIZE(UJ_IMM_FROM,UJ_IMM_TO)+1]; 
    for(int i = 0; i < ARRAY_SIZE(UJ_IMM_FROM,UJ_IMM_TO)+1; i++){
        imm_array[i] = 0;
    }
    //this is a combination of all the different chunks of immediate bits being combined into a single array.
    strncat(imm_array,imm_array4,ARRAY_SIZE(UJ_IMM4_FROM,UJ_IMM4_TO));   
    strncat(imm_array,imm_array3,ARRAY_SIZE(UJ_IMM3_FROM,UJ_IMM3_TO));
    strncat(imm_array,imm_array2,ARRAY_SIZE(UJ_IMM2_FROM,UJ_IMM2_TO));
    strncat(imm_array,imm_array1,ARRAY_SIZE(UJ_IMM1_FROM,UJ_IMM1_TO));

    input->immediate = binary_to_decimal(ARRAY_SIZE(0,20),imm_array);
    input->immediate >>= 1; 
    return 0;
}

//all indexes for parsing of type sb for each of the instruction values. in binary input. 
#define SB_IMM1_FROM 8
#define SB_IMM1_TO 11

#define SB_IMM2_FROM 25
#define SB_IMM2_TO 30

#define SB_IMM3_FROM 7
#define SB_IMM3_TO 7

#define SB_IMM4_FROM 31
#define SB_IMM4_TO 31

#define SB_FUNC3_FROM 12
#define SB_FUNC3_TO 14

#define SB_RS1_FROM 15
#define SB_RS1_TO 19

#define SB_RS2_FROM 20
#define SB_RS2_TO 24

// puts all of the values, e.g. rd, imm etc into the parsed_hold struct, for type sb.
int parse_type_SB(struct parsed_hold * input,int oppcode, char * bit_array){
    char imm_array1[ARRAY_SIZE(SB_IMM1_FROM,SB_IMM1_TO)]; 
    char imm_array1_cpy[ARRAY_SIZE(SB_IMM1_FROM,SB_IMM1_TO)]; 

    //grabbing first bunch of immediate numbers. 
    grab_array_signed(bit_array,imm_array1,imm_array1_cpy,SB_IMM1_FROM,SB_IMM1_TO);

    char imm_array2[ARRAY_SIZE(SB_IMM2_FROM,SB_IMM2_TO)]; //there are 11 bits in an s_type immediate number. 
    char imm_array2_cpy[ARRAY_SIZE(SB_IMM2_FROM,SB_IMM2_TO)]; 

    //grabbing the second bunch of immediate numbers.
    grab_array_signed(bit_array,imm_array2,imm_array2_cpy,SB_IMM2_FROM,SB_IMM2_TO); 

    char imm_array3[ARRAY_SIZE(SB_IMM3_FROM,SB_IMM3_TO)]; 
    char imm_array3_cpy[ARRAY_SIZE(SB_IMM3_FROM,SB_IMM3_TO)]; 

    //grabbing the 3rd bunch of immediate numbers.
    grab_array_signed(bit_array,imm_array3,imm_array3_cpy,SB_IMM3_FROM,SB_IMM3_TO); 

    char imm_array4[ARRAY_SIZE(SB_IMM4_FROM,SB_IMM4_TO)]; 
    char imm_array4_cpy[ARRAY_SIZE(SB_IMM4_FROM,SB_IMM4_TO)]; 

    //grabbing the 4th bunch of immediate numbers.
    grab_array_signed(bit_array,imm_array4,imm_array4_cpy,SB_IMM4_FROM,SB_IMM4_TO);

    char imm_array[ARRAY_SIZE(0,12)]; //there are 11 bits in an sb_type immediate number.

    for(int i = 0; i < ARRAY_SIZE(0,12); i++){
        imm_array[i] = 0;
    }

    //this is a combination of all the different chunks of immediate bits being combined into a single array.
    strncat(imm_array,imm_array4,ARRAY_SIZE(SB_IMM4_FROM,SB_IMM4_TO));
    strncat(imm_array,imm_array3,ARRAY_SIZE(SB_IMM3_FROM,SB_IMM3_TO));
    strncat(imm_array,imm_array2,ARRAY_SIZE(SB_IMM2_FROM,SB_IMM2_TO));
    strncat(imm_array,imm_array1,ARRAY_SIZE(SB_IMM1_FROM,SB_IMM1_TO));

    input->immediate = binary_to_decimal(ARRAY_SIZE(0,12),imm_array);

    char func3_array[ARRAY_SIZE(SB_FUNC3_FROM,SB_FUNC3_TO)]; 
    char func3_array_cpy[ARRAY_SIZE(SB_FUNC3_FROM,SB_FUNC3_TO)]; 

    input->func3 = grab_array(bit_array,func3_array,func3_array_cpy,SB_FUNC3_FROM,SB_FUNC3_TO);

    char rs1_array[ARRAY_SIZE(SB_RS1_FROM,SB_RS1_TO)]; 
    char rs1_array_cpy[ARRAY_SIZE(SB_RS1_FROM,SB_RS1_TO)]; 

    input->rs1 = grab_array(bit_array,rs1_array,rs1_array_cpy,SB_RS1_FROM,SB_RS1_TO);

    char rs2_array[ARRAY_SIZE(SB_RS2_FROM,SB_RS2_TO)]; 
    char rs2_array_cpy[ARRAY_SIZE(SB_RS2_FROM,SB_RS2_TO)]; 

    input->rs2 = grab_array(bit_array,rs2_array,rs2_array_cpy,SB_RS2_FROM,SB_RS2_TO);


    return 0;
}