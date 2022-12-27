#ifndef SYNTAX_CHECK_H
#define SYNTAX_CHECK_H 1

#include "../common/common.h"
#include "../tokenize/tokenize.h"

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
 *      - invalid_token (Token_t *): pointer to the invalid token
 *  return value:
 *      
*/
int syntax_check(Token_t **tokens, int token_number, Token_t *invalid_token);


#endif