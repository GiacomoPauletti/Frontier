#include "assembler.h"

// parsing (tokenizing text) -> syntax and semantic check -> macro expansion -> translation to binary

int main()
{

}

/* Token_t init_token()
{
    Token_t *token;
    TokenType_t *token_type;
    token_type = malloc(sizeof(TokenType_t));
    token = malloc(sizeof(Token_t));
    
} */

int tokenize_instruction(char *instruction, Token_t tokens[MAX_TOKENS], int *filled_tokens, Token_t *invalid_token)
{
    /* exit_status
    * OK if everything went ok
    * OK_TOO_LONG if it was possible to complete the operation but instruction had too many tokens
    * NOT_OK if if wasn't possible to complete the operation 
    */
    int exit_status;

    int exit_status_routine;    // exit status of routines called by this function
    // points to the beginning of the read token
    char *read_token;
    // length of pointed token
    int token_length;

    int token_number;
    // number of tokens written so far


    // if filled_tokens has no variable address, it's not possible to complete the operation
    if ( filled_tokens == NULL || invalid_token == NULL )
    {
        exit_status = INTERNAL_ERROR;
        return exit_status;
    }

    invalid_token -> token[0] = '\0';  // I change this value only if an invalid_token is found

    // if no instruction is passed, tokens are all empty
    if ( instruction == NULL )
    {

        *filled_tokens = 0;
        exit_status = OK;
        return exit_status;
    }

    // tokenizing
    token_number = 0;
    while ( *instruction != '\0')
    {
        // skipping token separators
        while ( *instruction == ',' || *instruction == ' ' )
        {
            instruction += 1;
        }

        // ending if end of string is reached
        if ( *instruction == '\0' ) 
        {
            *filled_tokens = token_number;

            exit_status = OK;
            return exit_status;
        }

        // fetching next token
        read_token = instruction;
        exit_status_routine = get_next_token(instruction, &token_length);

        // if there are too many tokens, overflowing ones are rejected
        if ( token_number >= MAX_TOKENS)
        {
            *filled_tokens = MAX_TOKENS;
            exit_status = OK_TOO_MANY;
            return exit_status;
        }

        // if token found is too long
        if ( exit_status_routine == NOT_OK_TOO_LONG )
        {
            // saving the partial token into invalid token
            invalid_token -> token_length = token_length;
            memcpy(invalid_token -> token, read_token, MAX_TOKEN_LEN);
            invalid_token -> token[MAX_TOKEN_LEN] = '\0';

            // this token is invalid so token_number is not updated
            *filled_tokens = token_number; 

            // error: a too long token was found
            exit_status = NOT_OK_TOO_LONG;
            return exit_status;
        }
        else if ( exit_status_routine == OK )    // everything went ok
        {
            memcpy(tokens[token_number].token, read_token, token_length);
            tokens[token_number].token[token_length] = '\0';
            tokens[token_number].token_length = token_length;

            instruction += token_length;
            token_number += 1;

        }
        else    // INTERNAL_ERROR or another unexprected error
        {
            *filled_tokens = token_number;
            exit_status = INTERNAL_ERROR;

            return exit_status;

        }


    } // end of while

    // end of instruction tokenization
    *filled_tokens = token_number;

    exit_status = OK;
    return exit_status;
}

int get_next_token(char *instruction, int *token_length)
{
    int exit_status;

    if ( instruction == NULL || token_length == NULL )
    {
        exit_status = INTERNAL_ERROR;    
        return exit_status;
    }
     

    // scrolling the token till the end
    for ( *token_length = 0; *token_length < MAX_TOKEN_LEN && *instruction != ' ' && *instruction != ',' && *instruction != '\0'; *token_length += 1)
    {
        instruction += 1;
    }

    // if a too long token is found
    if ( *token_length == MAX_TOKEN_LEN && *instruction != ' ' && *instruction != ',' && *instruction != '\0' )
    {

        // error: a too long token was found
        exit_status = NOT_OK_TOO_LONG;
        return exit_status;
    }

    exit_status = OK;
    return exit_status;
}

#define NOT_OK_INVALID_TOKEN -4

int syntax_check(Token_t *tokens, int token_number, Token_t *invalid_token)
{
    int token_counter;
    int char_counter;

    int exit_status;
    int exit_status_routine;

    invalid_token -> token[0] = '\0';

    if ( token_number > MAX_TOKENS )
    {
        printf("[syntax_check] Invalid token_number: token_number > MAX_TOKENS\n");


        exit_status = INTERNAL_ERROR;
        return INTERNAL_ERROR;
    }

    // asserting first token is only alphabetic
    if ( token_number >= 1 )
    {
        exit_status_routine = _syntax_check_opcode(&tokens[0]);
        
        // if opcode is not valid
        if ( exit_status_routine == NOT_OK_INVALID_TOKEN )
        {
            memcpy(invalid_token -> token, tokens[0].token, tokens[0].token_length);
            invalid_token -> token_length = tokens[0].token_length;

            exit_status = exit_status_routine;
            return exit_status;
        }

    }
    else    // token number < 1
    {
        printf("[syntax_check] Warning: no token was passed (token_number = 0)\n");

        exit_status = 0K;
        return exit_status;
    }
    

    tokens[0].token_type.type = OPCODE;

    // checking other tokens
    for ( token_counter = 1; token_counter < token_number; token_counter++ )
    {

    }

}

int _syntax_check_opcode(Token_t *token)
{
    int char_counter;
    int exit_status;
    for ( char_counter = 0; char_counter < token -> token_length; char_counter++ )
    {

        if ( isalpha(token -> token[char_counter]) )
        {
            if ( isupper(token -> token[char_counter]) )
            {
                token -> token[char_counter] = tolower(token -> token[char_counter])
            }
        }
        else    // token is not alphabetic
        {
            exit_status = NOT_OK_INVALID_TOKEN;
            return exit_status;
        }
    }

}

int _syntax_check_operand(Token_t *token)
{
    int exit_status;
    int exit_status_routine;

    // invalid empty token
    if ( token -> token_length < 1 )
    {
        exit_status = NOT_OK_INVALID_TOKEN;
        return exit_status;
    }

    if ( isalpha(token -> token[0]) )   
    {
        // first char is alpha => this token must be a register
        exit_status_routine = _syntax_check_register(token);

        exit_status = exit_status_routine;
        return exit_status;
    }
    else   
    {
        // first char isn't alpha => this token must be an immediate
        exit_status_routine = _syntax_check_immediate(token);

        exit_status = exit_status_routine;
        return exit_status;
    }
}

int _syntax_check_register(Token_t *token)
{
    int char_counter;
    int exit_status;
    // check if each char is alphabetic and lowercase it.
    // if it's not alphabetic, there is a syntax error

    for ( char_counter = 0; char_counter < token -> token_length; char_counter++ )
    {

        if ( isalpha(token -> token[char_counter]) )
        {
            if ( isupper(token -> token[char_counter]) )
            {
                token -> token[char_counter] = tolower(token -> token[char_counter])
            }
        }
        else    // token is not alphabetic
        {
            exit_status = NOT_OK_INVALID_TOKEN;
            return exit_status;
        }
    }

}

int _syntax_check_immediate(Token_t *token)
{
    int exit_status;
    int number_base = NO_BASE;
    int base_index = 0;     // base index where the actual number begins
    char curr_char;

    if ( token -> token[0] == '-' || token -> token[0] == '+' )
    {

        number_base = DEC_BASE;
        base_index = 1;
        // there must be at least a (valid) number after this
        if ( token -> token_length < 2 )
        {
            exit_status = NOT_OK_INVALID_TOKEN;
            return exit_status;
        }

        if ( token -> token[0] == '-' )
            token -> token_type.sign = NEGATIVE_SIGN;
        else token -> token_type.sign = POSITIVE_SIGN;
    }
    
    if ( token -> token[base_index] == '0')
    {
        if ( token -> token_length < base_index + 2 ) // this is the last character of the token
        {
            if ( base_index > 0 )   // if before there is '+' or '-'
                printf("[_syntax_check_immediate] Warning: + or - sign in front of '0' is a bad habit\n");

            exit_status == OK;
            return exit_status;
        }


        curr_char = token -> token[base_index+1];
        if ( isalpha(curr_char) )
        {
            if ( number_base == DEC_BASE )
            {
                if ( curr_char != 'd' && curr_char != 'D' )
                {
                    printf("[_syntax_check_immediate] Error: using '+' or '-' sign with a non decimal number\n");

                    exit_status = NOT_OK_INVALID_TOKEN;
                    return exit_status;
                }

                // if curr_char == 'd' or 'D' then it can be a valid number
            }

            else if ( curr_char == 'd' || curr_char == 'D' )
                number_base = DEC_BASE;
            else if ( curr_char == 'b' || curr_char == 'B' )
                number_base = BIN_BASE;
            else if ( curr_char == 'o' || curr_char == 'O' )
                number_base = OCT_BASE;
            else if ( curr_char == 'x' || curr_char == 'X' )
                number_base = HEX_BASE;
            else
            {
                printf("[_syntax_check_immediate] Error: invalid letter used after 0\n");
                
                exit_status = NOT_OK_INVALID_TOKEN;
                return exit_status;
            }

            base_index += 2;    // actual number starts after this 2 characters

            if ( token -> token_length < base_index + 1 ) // there are no other characters
            {
                // why base_index + 1?
                // eg: +0d10 -> base_index = 3 now because of +0xd
                // adding one makes it become 4
                // if token_length < base_index + 1 then token_length = 3 so there are no other characters

                printf("[_syntax_check_immediate] Error: number composed only by a prefix [+/-]0x (or 0d, ...) is not allowed\n");
                exit_status = NOT_OK_INVALID_TOKEN;
                return exit_status;
            }
        }
        else 
        {
            number_base = DEC_BASE; // starting with 0 with no letter implies it's a decimal number
            
            // base_index = base_index; -> number starts with the 0 because no letter follows it
        }


        // checking the actual number
        for ( base_index = base_index; base_index < token -> token_length; base_index++ )
        {
            curr_char = token -> token[base_index];
            if ( ( number_base == BIN_BASE && ( curr_char != '0' && curr_char != '1' ) ) || 
                 ( number_base == OCT_BASE && ( curr_char < '0' || curr_char > '7' ) ) ||
                 ( number_base == DEC_BASE && ( isdigit(curr_char) == 0 ) ) || 
                 ( number_base == HEX_BASE && ( isxdigit(curr_char) == 0 ) ) )
            {

                printf("[_syntax_check_immediate] Error: current digit is out of range\n");
                exit_status = NOT_OK_INVALID_TOKEN;
                return exit_status;

            }
            
        }

    }
}
int _print_tokens(Token_t *tokens, int token_number)
{
    int cursor;
    for ( cursor = 0; cursor < token_number; cursor++ )
        printf("Token n° %d - %s\n", cursor, tokens[cursor].token);

    return OK;
}

int _debug_token()
{

    Token_t tokens[MAX_TOKENS];
    int filled_tokens;
    Token_t invalid_token;
    int exit_status;

    exit_status = tokenize_instruction(" mv t0,t1", tokens, &filled_tokens, &invalid_token);
    printf("Exit_status is %d\n", exit_status);
    if ( exit_status == OK )
        _print_tokens(tokens, filled_tokens);
    else 
        printf("Invalid token begins with: %s\n", invalid_token.token);
    return 0;
}