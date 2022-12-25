#ifndef TOKENIZE_H
#define TOKENIZE_H 1

#include "../common/common.h"

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
int tokenize_instruction(char *instruction, Token_t **tokens, int *filled_tokens, Token_t *invalid_token);

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



#endif