#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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


#define MAX_TOKENS 4    // opcode + operand0 + comma + operand1 (parenthesis aren't allowed because they are useless)
//#define MIN_TOKEN_LEN 2
#define MAX_TOKEN_LEN 10

#define OPCODE 0
#define REGISTER 1
#define IMMEDIATE 2

typedef struct tokenType
{
    char type;
    int sign;
    int dec_number;
} TokenType_t;

#define POSITIVE_SIGN 1
#define NEGATIVE_SIGN -1

typedef struct token
{
    int token_length;
    TokenType token_type;
    char token[MAX_TOKEN_LEN + 1];
} Token_t;


#define OK 0
#define OK_TOO_MANY 1
#define INTERNAL_ERROR -1
#define NOT_OK_TOO_LONG -2

/*  TOKENIZE
 *  takes an instruction and save each significant part (opcode, operands or immediate) into Token_t variables.
 *
 *  arguments: 
 *      - instruction (char *): string containing the instruction to tokenize
 *      - tokens (Token_t *): array of structs Token_t, each one will be a token (+ it's length)
 *      - filled_tokens (int *): number of tokens filled from the tokens array (1st argument)
 *      - invalid_token (Token_t): token representing the invalid token that caused the error
 *  return value:
 *      - exit_status (int): 
 *          - OK if everything went ok
 *          - OK_TOO_MANY if it was possible to complete the operation but instruction had too many tokens
 *          - INTERNAL_ERROR if it wasn't possible to complete the operation 
 *          - NOT_OK_TOO_LONG if it wasn't possible to complete the operation due to a too long token
 *      
*/
int tokenize_instruction(char *instruction, Token_t tokens[MAX_TOKENS], int *filled_tokens, Token_t *invalid_token);

/*  GET_NEXT_TOKEN
 *  get a token from the instruction
 *  WARNING: this function does not skip spaces or other separators, so it has to be done by the caller function
 * 
 *  arguments: 
 *      - instruction (char *): string containing the instruction to tokenize
 *      - tokens (Token_t *): array of structs Token_t, each one will be a token (+ it's length)
 *      - filled_tokens (int *): number of tokens filled from the tokens array (1st argument)
 *      - invalid_token (Token_t): token representing the invalid token that caused the error
 *  return value:
 *      - exit_status (int): 
 *          - OK if everything went ok
 *          - OK_TOO_MANY if it was possible to complete the operation but instruction had too many tokens
 *          - INTERNAL_ERROR if it wasn't possible to complete the operation 
 *          - NOT_OK_TOO_LONG if it wasn't possible to complete the operation due to a too long token
 *      
*/
int get_next_token(char *instruction, int *token_length);



/*  SYNTAX_CHECK
 *  check if syntax is correct in this way:
 *      - first token must be composed only of letters
 *      - other tokens are considered
 *          1] register, if starting with a letter 
 *          2] immediate, if starting with a number or with +/- signs
 *               
 *  for a detailed analysis of syntax check of register and immediate, look at the rispective
 *  functions down below
 *  arguments: 
 *      - tokens (Token_t *): array of structs Token_t, each one is a token (+ it's length)
 *      - token_number (int): number of tokens to check
 *  return value:
 *      
*/
int syntax_check(Token_t *tokens, int token_number);


/*  _SYNTAX_CHECK_OPCODE
 *  assert opcode is only alphabetic and put it lowercase
 * 
 *  arguments: 
 *      - token (Token_t *): pointer to opcode token
 *  return value:
 *      - OK if alphabetic
 *      - NOT_OK_INVALID_TOKEN if not alphabetic
 *      
*/
int _syntax_check_opcode(Token_t *token);

/*  _SYNTAX_CHECK_OPERAND
 *  check if the operand is immediate or register and then calls the respective function
 * 
 *  arguments: 
 *      - token (Token_t *): pointer to operand token
 *  return value:
 *      - OK if its syntax is correct
 *      - NOT_OK_INVALID_TOKEN if its syntax is incorrect
 *      
*/
int _syntax_check_operand(Token_t *token);

/*  _SYNTAX_CHECK_REGISTER
 *  check if the register syntax is correct (same of opcode one)
 * 
 *  arguments: 
 *      - token (Token_t *): pointer to operand token
 *  return value:
 *      - OK if its syntax is correct
 *      - NOT_OK_INVALID_TOKEN if its syntax is incorrect
 *      
*/
int _syntax_check_register(Token_t *token);

/*  _SYNTAX_CHECK_IMMEDIATE
 *  check if the immediate syntax is correct.
 *  This syntax is more complex than other syntaxes:
 *  - they must be composed as follows :
 *          [+/-][0 b/B/o/O/d/D/x/X] digits
 *      - if surrounded by square brackets, it means it can be omitted
 *      - first char can be + o -
 *          - + is the default value
 *          - + and - are allowend only with decimal numbers, for making it easier to develop it
 *      - second/third char can be x/X, d/D, o/O or b/B if previous char is 0
 *           eg: 0b1001 is ok
 *      - other chars depend on the second/third one:
 *          - b/B allows only binary digits (1 or 0)
 *          - o/O allows only octal digits (0 to 7)
 *          - d/D (which is the default if 0+char construct is missing) allows only decimal digits
 *          - x/X allows only hexadecimal digits (0 to 9 and A to F)
 * 
 * 
 *  arguments: 
 *      - token (Token_t *): pointer to operand token
 *  return value:
 *      - OK if its syntax is correct
 *      - NOT_OK_INVALID_TOKEN if its syntax is incorrect
 *      
*/

#define NO_BASE    -1
#define BIN_BASE    0
#define OCT_BASE    1
#define DEC_BASE    2
#define HEX_BASE    3

int _syntax_check_immediate(Token_t *token);

/*  _PRINT_TOKENS
 *  local function used for printing tokens of a token array
 * 
 *  arguments: 
 *      - tokens (Token_t *): array of structs Token_t, each one will be a token (+ it's length)
 *      - token_number (int): number of tokens to print
 *  return value:
 *      - always 0
 *      
*/
int _print_tokens(Token_t *tokens, int token_number);

/*  _DEBUG_TOKEN
 *  used to debug tokenize_instruction and all tokenization process
 * 
 *  arguments: 
 *
 *  return value:
 *      
*/
int _debug_token()