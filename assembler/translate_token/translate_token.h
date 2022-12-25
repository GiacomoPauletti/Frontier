#ifndef TRANSLATE_TOKEN_H
#define TRANSLATE_TOKEN 1

#include "../common/common.h"

/*  TRANSLATE_TOKEN
 *  this function takes a token and translate it into decimal
 *  In this way semantic_check uses integer comparison rather than string comparison,
 *  which is harder, slower and bug prone.
 *
 *  arguments:
 *      - token (Token_t *): token to be translated
 *      - translation (int *): translated token value
 *  return value:
 *      - OK if translation went fine
 *      - TRANSLATION_ERROR if translation raised an error
*/
int translate_token(Token_t *token, int *translation);

/*  TRANSLATE_TOKENS
 *  this function translates into decimal multiple tokens
 *  see translate_token for further details. 
 * 
 *  arguments:
 *      - tokens (Token_t **): array of pointer to tokens that will be translated
 *      - token_number (int): number of tokens to translate
 *      - translation (int *): translated token values
 *  return value:
 *      - OK if translation went fine
 *      - TRANSLATION_ERROR if translation raised an error
 */
int translate_tokens(Token_t **tokens, int token_number, int *translation);

#endif