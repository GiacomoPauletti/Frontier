#ifndef COMMON_H
#define COMMON_H 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdarg.h>

#include "../log/log.h"

// ----------------------- TOKEN -----------------------
#define MAX_TOKENS 4    // opcode + operand0 + operand1 + 1 extra (parenthesis aren't allowed because they are useless)
#define MAX_TOKEN_LEN 10
//#define MIN_TOKEN_LEN 2

// token types
#define OPCODE 0
#define REGISTER 1
#define IMMEDIATE 2
#define MACRO 3

typedef struct tokenType
{
    int type;
    int number;     
    // contains the immediate decimal value if type == IMMEDIATE
} TokenType_t;


#define POSITIVE_SIGN 1
#define NEGATIVE_SIGN -1

typedef struct token
{
    int token_length;
    TokenType_t *token_type;
    char token[MAX_TOKEN_LEN + 1];
} Token_t;

// TokenNode_t: used to sort tokens in a certain order
typedef struct token_node
{
    Token_t *token;
    Token_t *next;
} TokenNode_t;

#define OK 0
#define OK_TOO_MANY 1
#define INTERNAL_ERROR -1
#define NOT_OK_TOO_LONG -2
#define NOT_OK_INVALID_TOKEN -3

// reserved keywords
extern char * reserved_keywords[];

/*  INIT_TOKEN
 *  initialize properly a token
 * 
 *  arguments: 
 *  return value (Token_t *):
 *      - initialized token if successfully allocated
 *      - NULL if unable to malloc it
 *      
*/
Token_t* init_token();

/*  INIT_TOKEN_ARRAY
 *  initialize properly a token array
 * 
 *  arguments: 
 *      - token_number (int): number of tokens in the array
 *  return value (Token_t **):
 *      - initialized token array if successfully allocated
 *      - NULL if unable to malloc it
 *      
*/
Token_t ** init_token_array(int token_number);


/*  INIT_MACRO_ARRAY
 *  initialize properly the token_node
 * 
 *  arguments:
 *  return value (TokenNode_t): the initialized token node
*/
TokenNode_t* init_token_node();

/*  FREE_TOKEN
 *  free properly a token
 * 
 *  arguments: 
 *      - token (Token_t *): pointer to token to free
 *  return value (Token_t **):
 *      - OK if succesfull
 *      - INTERNAL_ERROR if error
 *      
*/
int free_token(Token_t *token);

/*  FREE_TOKEN_ARRAY
 *  free properly a token array
 * 
 *  arguments: 
 *      - tokens (Token_t **): array of tokens to free
 *  return value (Token_t **):
 *      - OK if succesfull
 *      - INTERNAL_ERROR if error
 *      
*/
int free_token_array(Token_t **tokens, int token_number);

// ----------------------- MACRO -----------------------

#define MAX_LABEL_LEN 15    // length of macro label
#define MACRO_DEFINE "#define"  // keyword to define a macro
#define MINIMUM_MACRO_TOKENS 3  // minimum number of tokens in a macro definition
#define MINIMUM_MACROS 4    // minimum number of macros in code_macros

#define NOT_A_MACRO -4  // error raised by _syntax_macro_check if that's not a macro definition

// at the moment a macro can be only a placeholder for a number
typedef struct macro
{
    char label[MAX_LABEL_LEN];
    int label_length;
    int number;
    TokenNode_t *references;

} Macro_t;

// this global variable contain all macros found in code
extern Macro_t **code_macros;
// this global variable contain the number of macros that code_macros can contain
extern int code_macros_length;
// this global variable contain the number of macros found in code
extern int code_macros_number;


/*  INIT_MACRO
 *  initialize properly a macro
 * 
 *  arguments: 
 *  return value (Macro_t *):
 *      - initialized macro if successfully allocated
 *      - NULL if unable to malloc it
 *      
*/
Macro_t* init_macro();

/*  INIT_MACRO_ARRAY
 *  initialize properly a macro array
 * 
 *  arguments: 
 *      - macro_number (int): number of macros in the array
 *  return value (Macro_t **):
 *      - initialized macro array if successfully allocated
 *      - NULL if unable to malloc it
 *      
*/
Macro_t** init_macro_array(int macro_number);

/*  INIT_CODE_MACROS
 *  initialize code macros array at default minimum length
 *  
 *  arguments:
 *  return value (int):
 *      - OK if initialization worked fine
 *      - INTERNAL_ERROR if initialization didn't work 
 */
int init_code_macros();

/*  UPDATE_CODE_MACROS
 *  add the passed macro to the code macro array
 *  
 *  arguments:
 *      - macro (Macro_t *): macro to add to array
 *  return value (int):
 *      - OK if update worked fine
 *      - INTERNAL_ERROR if updated didn't work
 * */
int update_code_macros(Macro_t *macro);


/*  ADD_MACRO_REFERENCE
 *  add a new macro invocation/reference in macro reference linked list
 *  
 *  arguments: 
 *      - macro (Macro_t*): pointer to the invoked macro
 *      - token (Token_t*): pointer to the macro invoker
 *  return value (int):
 *      - OK if update worked fine
 *      - INTERNAL_ERROR if an error occurred 
 */
int add_macro_reference(Macro_t *macro, Token_t* token);

/*  FREE_MACRO
 *  free properly a macro
 * 
 *  arguments: 
 *      - macro (Macro_t *): pointer to macro to free
 *  return value (Macro_t **):
 *      - OK if succesfull
 *      - INTERNAL_ERROR if error
 *      
*/
int free_macro(Macro_t *macro);

/*  FREE_MACRO_ARRAY
 *  free properly a macro array
 * 
 *  arguments: 
 *      - macros (Macro_t **): array of macros to free
 *  return value (Macro_t **):
 *      - OK if succesfull
 *      - INTERNAL_ERROR if error
 *      
*/
int free_macro_array(Macro_t **macros, int macro_number);

/*  STOLOWER
 *  set a string to lowercase
 *
 *  arguments:
 *      - string (char*): string to set to lowercase
 *  return value:
 *      - OK if everything worked fine
 *      - INTERNAL_ERROR if an error occurred 
 */
int stolower(char* string);

/*  STOUPPER
 *  set a string to uppercase
 *
 *  arguments:
 *      - string (char*): string to set to uppercase
 *  return value:
 *      - OK if everything worked fine
 *      - INTERNAL_ERROR if an error occurred 
 */
int stoupper(char* string);
#endif