#include "common.h"

char* reserved_keywords[] = 
{
    "add",
    "addi",
    "and",
    "andi",
    "branch",
    "div",
    "divi",
    "in",
    "j",
    "jal",
    "jalr",
    "jr",
    "load",
    "lui",
    "mul",
    "muli",
    "mv",
    "not",
    "or",
    "ori",
    "out",
    "slli",
    "srli",
    "store",
    "sub",
    NULL
};

TokensNode_t* pending_instructions = NULL;  // has to be initialized

Token_t* init_token()
{
    Token_t *token;
    TokenType_t *token_type;

    // allocating token_type
    token_type = malloc(sizeof(TokenType_t));
    if (token_type == NULL)
    {
        printf("[init_token] Error: unable to malloc token_type\n");
        return NULL;
    }

    // allocating token_type
    token = malloc(sizeof(Token_t));
    if (token == NULL)
    {
        free(token_type);

        printf("[init_token] Error: unable to malloc token\n");
        return NULL;
    }

    token -> token_type = token_type;

    return token;    
} 

Token_t ** init_token_array(int token_number)
{
    Token_t **tokens;
    int counter;
    int free_counter;

    // initializing the token array
    tokens = malloc(token_number * sizeof(Token_t *));

    // initializing the token pointed by each array's element
    for ( counter = 0; counter < token_number; counter++ )
    {
        tokens[counter] = init_token();

        // if an error is met, freeing all memory allocated so far and exiting
        if ( tokens[counter] == NULL )
        {
            for ( free_counter = 0; free_counter < counter - 1; free_counter++ )
            {
                free_token(tokens[free_counter]);
            }
            free(tokens);

            return NULL;
        }
    } // end of for

    return tokens;
}

TokenNode_t* init_token_node()
{ TokenNode_t* token_node;
    token_node = malloc(sizeof(TokenNode_t));

    token_node -> token = NULL;
    token_node -> next = NULL;

    return token_node;
}

TokensNode_t* init_tokens_node()
{
    TokensNode_t* tokens_node;

    tokens_node = malloc(sizeof(TokenNode_t));
    tokens_node -> tokens = NULL;
    tokens_node -> next = NULL;
    tokens_node -> token_number = 0;

    return tokens_node;
}


int free_token(Token_t *token)
{
    int exit_status;

    // first freeing the token type, then token, otherwise fluctuating pointer is created
    free(token -> token_type);
    free(token);

    exit_status = OK;
    return exit_status;
}

int free_token_array(Token_t **tokens, int token_number)
{
    int exit_status;
    int exit_status_routine = OK;
    int counter;

    // first freeing each token of the array, the the array itself 
    for ( counter = 0; counter < token_number; counter++ )
        exit_status_routine = free_token(tokens[counter]);
    
    free(tokens);
    exit_status = exit_status_routine;
    return exit_status;
}

TokenNode_t* free_token_node(TokenNode_t *token_node, int is_free_token)
{
    TokenNode_t* next;

    next = token_node -> next;

    if ( is_free_token == 1 ) 
    {
        free_token(token_node -> token);
    }
    free(token_node);

    return next;
}

int free_token_list(TokenNode_t *head, int is_free_tokens)
{
    int exit_status;

    while ( head != NULL )
    {
        head = free_token_node(head, is_free_tokens);
    }

    exit_status = OK;
    return exit_status;
}

TokensNode_t* free_tokens_node(TokensNode_t *tokens_node, int is_free_token)
{
    TokensNode_t* next;

    next = tokens_node -> next;

    if ( is_free_token == 1 ) 
    {
        free_token_array(tokens_node -> tokens, tokens_node -> token_number);
    }
    free(tokens_node);

    return next;
}

int free_tokens_list(TokensNode_t *head, int is_free_tokens)
{
    int exit_status;

    while ( head != NULL )
    {
        head = free_tokens_node(head, is_free_tokens);
    }

    exit_status = OK;
    return exit_status;
}

// this global variable contain all macros found in code
Macro_t **code_macros = NULL;
// this global variable contain the number of macros that code_macros can contain
int code_macros_length = 0;
// this global variable contain the number of macros found in code
int code_macros_number = 0;

Macro_t* init_macro()
{
    Macro_t *macro;

    macro = malloc(sizeof(Macro_t));
    if (macro == NULL)
    {
        printf("[init_token] Error: unable to malloc token\n");
        return NULL;
    }

    macro -> label_length = 0;
    macro -> references = NULL;

    return macro;

}

Macro_t** init_macro_array(int macro_number)
{
    Macro_t **macros;
    int counter;
    int free_counter;

    // initializing the macro array
    macros = malloc(macro_number * sizeof(Macro_t *));

    // initializing the macro pointed by each array's element
    for ( counter = 0; counter < macro_number; counter++ )
    {
        macros[counter] = init_macro();

        // if an error is met, freeing all memory allocated so far and exiting
        if ( macros[counter] == NULL )
        {
            for ( free_counter = 0; free_counter < counter - 1; free_counter++ )
            {
                free_macro(macros[free_counter]);
            }
            free(macros);

            return NULL;
        }
    } // end of for

    return macros;
}

int init_code_macros()
{
    int exit_status;

    code_macros = init_macro_array(MINIMUM_MACROS);
    if ( code_macros == NULL )
    {
        exit_status = INTERNAL_ERROR;
        return INTERNAL_ERROR;
    }

    code_macros_length = MINIMUM_MACROS;

    exit_status = OK;
    return exit_status;
}

int update_code_macros(Macro_t *macro)
{
    int exit_status;
    int macro_counter;


    if ( code_macros_length == 0 || code_macros == NULL )
    {
        printf("[update_code_macros] Error: code_macros is not initialized\n");

        exit_status = INTERNAL_ERROR;
        return exit_status;
    }

    if ( macro == NULL )
    {
        printf("[update_code_macros] Error: cannot add NULL macro to code_macros\n");
        
        exit_status = INTERNAL_ERROR;
        return exit_status;
        
    }

    // checking if macro label is already used. If so, exits
    for ( macro_counter = 0; macro_counter < code_macros_number; macro_counter++ )
    {
        if ( strcmp(code_macros[macro_counter] -> label, macro -> label) == 0 )
        {
            write_log(COMMON_LOG | CRITICAL_LOG, "[update_code_macros] Error: macro with label %s exists already\n", macro -> label);

            exit_status = INTERNAL_ERROR;
            return exit_status;
        }
    }

    // extending code_macros array if there is no space left
    if ( code_macros_number >= code_macros_length )
    {
        code_macros = realloc(code_macros, code_macros_length * 2);

        if ( code_macros == NULL )
        {
            printf("[update_code_macros] Unable to realloc code_macros\n");
            exit_status = INTERNAL_ERROR;
            return exit_status;
        }

        code_macros_length *= 2;

        exit_status = OK;
        return exit_status;
    }

    code_macros[code_macros_number] = macro;
    code_macros_number++;

    exit_status = OK;
    return exit_status;
}

int add_macro_reference(Macro_t *macro, Token_t* token)
{
    int exit_status;
    TokenNode_t **token_node;

    if ( macro == NULL )
    {
        write_log(COMMON_LOG | CRITICAL_LOG, "[add_macro_reference] Error: macro is NULL\n");
        exit_status = INTERNAL_ERROR;
        return exit_status;
    }
    if ( token == NULL)
    {
        write_log(COMMON_LOG | WARNING_LOG, "[add_macro_reference] Warning: token is NULL. Nothing added to macro references\n");
        exit_status = OK;
        return exit_status;
    }

    token_node = &(macro -> references);
    while ( *token_node != NULL )
    {
        token_node = &((*token_node) -> next);
    }
    *token_node = init_token_node();
    if ( *token_node == NULL )
    {
        write_log(COMMON_LOG | CRITICAL_LOG, "[add_macro_reference] Error: unable to initialize token_node\n");

        exit_status = INTERNAL_ERROR;
        return INTERNAL_ERROR;
    }
    (*token_node) -> token = token;
    (*token_node) -> next = NULL;

    exit_status = OK;
    return exit_status;
}

/*  TODO:
        -check add_macro_reference
        -use add_macro_reference when a macro is found
        -modify _syntax_check_label such that macro label are found
            -if there is no macro with that label, if it cannot be a register label, raise an error
            -if there is no register and no macro, raise an error
*/

int free_macro(Macro_t *macro)
{
    int exit_status;

    free(macro);

    exit_status = OK;
    return exit_status;
}

int free_macro_array(Macro_t **macros, int macro_number)
{
    int exit_status;
    int exit_status_routine = OK;
    int counter;

    // first freeing each token of the array, then the array itself 
    for ( counter = 0; counter < macro_number; counter++ )
        exit_status_routine = free_macro(macros[counter]);
    
    free(macros);
    exit_status = exit_status_routine;
    return exit_status;
}


unsigned short curr_segment = CODE_SEGMENT;
unsigned short is_dataseg_set = 0;
unsigned short dataseg_address = 0x0000;

unsigned short is_codeseg_set = 0;
unsigned short codeseg_address = 0x0000;

unsigned short free_data_address = 0x0000;
unsigned short free_code_address = 0x0000;

int stolower(char *string)
{
    int exit_status;

    if ( string != NULL)
    {
        while ( *string != '\0' )
        {
            *string = tolower(*string);
            string++;
        }
    }
    
    exit_status = OK;
    return exit_status;
}

int stoupper(char *string)
{
    int exit_status;

    while ( string != NULL )
    {
        *string = toupper(*string);
        string++;
    }
    
    exit_status = OK;
    return exit_status;
}