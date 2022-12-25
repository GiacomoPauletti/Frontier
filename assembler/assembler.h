#ifndef ASSEMBLER 
#define ASSEMBLER 1

#include "common/common.h"
#include "tokenize/tokenize.h"
#include "syntax_check/syntax_check.h"
#include "log/log.h"

#define MAX_BIN_DIGITS 32   // dimension of int = 4 byte = 2^32 (so 32 bit)
#define MAX_OCT_DIGITS 10   // 1 octal "bit" represent 3 binary bit -> 32 / 3 = 10 (almost)
#define MAX_DEC_DIGITS 10   // 2^32 is made of 10 decimal digits
#define MAX_HEX_DIGITS 8    // 1 hex "bit" represent 4 binary bit -> 32 / 4 = 8

// using decimal not hexadecimal

#define t0_CODE 0    //0000
#define t1_CODE 1    //0001
#define t2_CODE 2    //0010
#define t3_CODE 3    //0011
#define a0_CODE 4    //0100
#define a1_CODE 5    //0101
#define a2_CODE 6    //0110
#define sp_CODE 7    //0111

// ARITHMETICAL OPERATIONS
#define not_CODE    0
#define add_CODE    1
#define sub_CODE    2
#define and_CODE    3
#define or_CODE     7
#define mul_CODE    4
#define div_CODE    6
#define addi_CODE   9
#define andi_CODE   11
#define ori_CODE    15
#define muli_CODE   12
#define divi_CODE   14
#define slli_CODE   8
#define srli_CODE   10
// JUMP OPERATIONS
#define jal_CODE    13
#define jalr_CODE   29
#define j_CODE      28
#define branch_CODE 30
// MEMORY OPERATIONS
#define load_CODE   18
#define store_CODE  19     
// MISCELLANEOUS
#define mv_CODE     5   
#define lui_CODE    24
#define in_CODE     16
#define out_CODE    17


/* 
typedef struct registerCode {

    char t0;
    char t1;
    char t2;
    char t3;
    char a0;
    char a1;
    char a2;
    char sp;

} RegisterCode_t;

typedef struct opCode {
    char t0
}

RegisterCode registercode = 
{
    .t0 = t0_CODE;
    .t1 = t1_CODE;
    .t2 = t2_CODE;
    .t3 = t3_CODE;
    .a0 = a0_CODE;
    .a1 = a1_CODE;
    .a2 = a2_CODE;
    .sp = sp_CODE;
};
*/


#endif