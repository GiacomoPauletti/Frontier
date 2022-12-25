#include "tokenize.h"

int tokenize_instruction(char *instruction, Token_t **tokens, int *filled_tokens, Token_t *invalid_token)
{
    /* exit_status
    * OK if everything went ok
    * OK_TOO_MANY if it was possible to complete the operation but instruction had too many tokens
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
            memcpy(tokens[token_number] -> token, read_token, token_length);
            tokens[token_number] -> token[token_length] = '\0';
            tokens[token_number] -> token_length = token_length;

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