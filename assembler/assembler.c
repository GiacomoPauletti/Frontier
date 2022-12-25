#include "assembler.h"

// parsing (tokenizing text) -> syntax and semantic check -> macro expansion -> translation to binary

/*  _PRINT_TOKENS
 *  prints tokens of a token array
 * 
 *  arguments: 
 *      - tokens (Token_t *): tokens to print
 *      - token_number (int): number of tokens to print
 *  return value:
 *      - always 0
 *      
*/
int _print_tokens(Token_t **tokens, int token_number);

/*  _PRINT_TOKENS
 *  prints macros of a macro array
 * 
 *  arguments: 
 *      - macros (Macro_t *): macros to print
 *      - macro_number (int): number of macros to print
 *  return value:
 *      - always 0
 *      
*/
int _print_macros(Macro_t **macros, int macro_number);

/*  _DEBUG_TOKEN
 *  used to debug tokenize_instruction and all tokenization process
 * 
 *  arguments: 
 *
 *  return value:
 *      
*/
int _debug();

int init_assembler();

int main()
{
    _debug();
    return 0;
}

int init_assembler()
{
    int exit_status;

    // initialization of code macros
    code_macros = init_macro_array(MINIMUM_MACROS);
    code_macros_length = MINIMUM_MACROS;

    exit_status = OK;
    return exit_status;
}

int _print_tokens(Token_t **tokens, int token_number)
{
    int cursor;
            
    printf("\n===============    TOKENS    ===============\n\n");
    for ( cursor = 0; cursor < token_number; cursor++ )
        printf("Token n° %d - %s\n", cursor, tokens[cursor] -> token);

    printf("\n=============== END OF TOKENS ===============\n\n");

    return OK;
}

int _print_macros(Macro_t **macros, int macro_number)
{
    int cursor;

    printf("\n===============    MACROS    ===============\n\n");
    for ( cursor = 0; cursor < macro_number; cursor++ )
        printf("Macro n° %d - %.*s : %d\n", cursor, macros[cursor] -> label_length, macros[cursor] -> label, macros[cursor] -> number);

    printf("\n=============== END OF MACROS ===============\n\n");

}

int _debug()
{

    Token_t **tokens;
    int filled_tokens;
    Token_t *invalid_token;
    int exit_status_routine;

    int main_log_priority = ASSEMBLER_LOG | BASIC_LOG;

    // LOG FILE INITIALIZATION
    init_log_file();
    set_log_priority(main_log_priority);

    // TOKEN INITIALIZATION
    tokens = init_token_array(MAX_TOKENS);
    if ( tokens == NULL )
    {
        
        write_log(main_log_priority, "Error: Unable to malloc tokens\n");
        return -1;
    }

    invalid_token = init_token();
    if ( invalid_token == NULL )
    {
        write_log(main_log_priority,"Error: Unable to malloc invalid_token\n");
        free_token_array(tokens, MAX_TOKENS);
        return -1;
    }
    // end of token initialization

    // CODE MACRO INITIALIZATION
    init_code_macros();
    // end of code macro initialization

    exit_status_routine = tokenize_instruction("#define mv 10", tokens, &filled_tokens, invalid_token);
    write_log(main_log_priority, "Exit_status is %d\n", exit_status_routine);
    if ( exit_status_routine == OK )
        _print_tokens(tokens, filled_tokens);
    else 
        write_log(main_log_priority, "Invalid token begins with: %s\n", invalid_token -> token);

    exit_status_routine = syntax_check(tokens,filled_tokens, invalid_token);

    _print_macros(code_macros, code_macros_number);

    write_log(main_log_priority, "Exit status is %d\n", exit_status_routine);
    write_log(main_log_priority, "Number is: %d\n", tokens[2] -> token_type -> number);

    return 0;
}