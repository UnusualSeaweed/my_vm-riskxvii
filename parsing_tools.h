#include "vm_riskxvii.h"

int my_strlen(char* array);
int power(int a, int b);
int binary_to_decimal(int size, char binary[]);
uint32_t binary_to_decimal_unsigned(int size, char binary[]);
int array_subset(char* array, char * subset, int from, int to);
extern void reverse_array(char * array, int size, char * array_replace);
extern int grab_array(char * binary,char * subset,char * copy_subset,int from, int to);
int grab_array_signed(char * binary,char * subset,char * copy_subset,int from, int to);

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

extern int parse_type_I(struct parsed_hold * input,int oppcode, char * bit_array);

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

extern int parse_type_R(struct parsed_hold * input,int oppcode, char * bit_array);

#define U_RD_FROM 7
#define U_RD_TO 11

#define U_IMM_FROM 12 
#define U_IMM_TO 31

extern int parse_type_U(struct parsed_hold * input,int oppcode, char * bit_array);

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

extern int parse_type_S(struct parsed_hold * input,int oppcode, char * bit_array);

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

extern int parse_type_UJ(struct parsed_hold * input,int oppcode, char * bit_array);

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

extern int parse_type_SB(struct parsed_hold * input,int oppcode, char * bit_array);

