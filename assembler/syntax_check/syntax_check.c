#include "syntax_check.h"

/*  _IS_TOKEN_LABEL 
 *  checks if token can be a valid label (it has to contain only letters, digits or undercases)
 *  
 *  arguments:
 *      - token (Token_t *): possibile label token
 *  return value (int):
 *      - OK if valid label
 *      - NOT_OK_INVALID_TOKEN if not valid label
 *      - INTERNAL_ERROR if an unexpecter error occurred (ie: token == NULL)
 */
int _is_token_label(Token_t *token);

/*  _SYNTAX_CHECK_MACRO
 *  checks if the token sequence (directive) is macro definition.
 *  If it is a proper macro definition, updates code_macros (and macros_number).
 *  
 *  
 *  arguments:
 *      - tokens (Token_t *): tokens to be checked
 *      - token_number (int): number of tokens to check
 *      - invalid_token (Token_t *): wrong token of the sequence
 *  return value:
 *      - OK if it is a valid macro definition
 *      - NOT_OK_INVALID_TOKEN if it is not
 *      - INTERNAL_ERROR if an unexpecter error occurred (ie: tokens == NULL)
 *
 */
int _syntax_check_macro(Token_t **tokens, int token_number, Token_t *invalid_token);

/*  _SYNTAX_CHECK_SEGSET
 *  checks if the token sequence (directive) is segment set (or segment setup).
 *  If it is a proper segment set, updates the corresponding segment starting address
 *  
 *  
 *  arguments:
 *      - tokens (Token_t *): tokens to be checked
 *      - token_number (int): number of tokens to check
 *      - invalid_token (Token_t *): wrong token of the sequence
 *  return value:
 *      - OK if it is a valid segment set directive
 *      - NOT_OK_INVALID_TOKEN if it is not
 *      - INTERNAL_ERROR if an unexpecter error occurred (ie: tokens == NULL)
 *
 */
int _syntax_check_segset(Token_t **tokens, int token_number, Token_t *invalid_token);

/*  _SYNTAX_CHECK_ALLOCATION
 *  checks if the token sequence (instruction) is data allocation
 *  If it is a proper data allocation, translates the directive in a series of instruction to load the data in memory
 *  
 *  
 *  arguments:
 *      - tokens (Token_t *): tokens to be checked
 *      - token_number (int): number of tokens to check
 *      - invalid_token (Token_t *): wrong token of the sequence
 *      - dimension (int): dimension of the data to be allocated. Can be BYTE_DIMENSION or WORD_DIMENSION since it works on a 16 bit CPU.
 *  return value:
 *      - OK if it is a valid data allocation directive
 *      - NOT_OK_INVALID_TOKEN if it is not
 *      - INTERNAL_ERROR if an unexpecter error occurred (ie: tokens == NULL)
 *
 */
int _syntax_check_allocation(Token_t **tokens, int token_number, Token_t *invalid_token, int dimension);

/*  _SETUP_EXPANSION
 *  function called by _syntax_check_allocation to expand the directive in a series of instruction to load the data in memory
 *
 *  arguments:
 *      - tokens (Token_t *): directive to be expanded
 *      - token_number (int): number of tokens in directive
 *      - invalid_token (Token_t *): wrong token of the sequence
 *      - dimension (int): dimension of the data to be allocated. Can be BYTE_DIMENSION or WORD_DIMENSION since it works on a 16 bit CPU.
 *  return value:
 *      - OK if expansion setup worked correctly
 *      - NOT_OK_INVALID_TOKEN if it did not
 *      - INTERNAL_ERROR if an unexpecter error occurred
 *
*/
int _setup_expansion(Token_t **tokens, int token_number, Token_t *invalid_token, int dimension);

/*  _SYNTAX_CHECK_DIRECTIVES
 *  checks if the token sequence (instruction) is preprocessore directive.
 *  If it is a proper macro definition, calls _syntax_check_macro
 *  If it is a proper segmentatin directive, ...
 *  If it is a proper data allocation directive, ...
 *  
 *  
 *  arguments:
 *      - tokens (Token_t *): tokens to be checked
 *      - token_number (int): number of tokens to check
 *      - invalid_token (Token_t *): wrong token of the sequence
 *  return value:
 *      - OK if token is alphanumeric
 *      - NOT_OK_INVALID_TOKEN if it is not
 *      - INTERNAL_ERROR if an unexpecter error occurred (ie: tokens == NULL)
 *
 */
int _syntax_check_directives(Token_t **tokens, int token_number, Token_t *invalid_token);

/*  _SYNTAX_CHECK_OPCODE
 *  assert opcode is only alphabetic and put it lowercase
 * 
 *  arguments: 
 *      - token (Token_t *): pointer to opcode token
 *  return value:
 *      - OK if alphabetic
 *      - NOT_OK_INVALID_TOKEN if not alphabetic
 *      - INTERNAL_ERROR if an unexpecter error occurred (ie: token == NULL)
 *      
*/
int _syntax_check_opcode(Token_t *token);



/*  _SYNTAX_CHECK_LABEL
 *  check if the label syntax is correct (same of opcode one).
 * 
 *  arguments: 
 *      - token (Token_t *): pointer to operand token
 *  return value:
 *      - OK if its syntax is correct
 *      - NOT_OK_INVALID_TOKEN if its syntax is incorrect
 *      - INTERNAL_ERROR if an unexpecter error occurred (ie: token == NULL)
 *      
*/
int _syntax_check_label(Token_t *token);

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
 *      - INTERNAL_ERROR if an unexpecter error occurred (ie: token == NULL)
 *      
*/
int _syntax_check_immediate(Token_t *token);

/*  _SYNTAX_CHECK_OPERAND
 *  check if the operand is immediate or register and then calls the respective function
 * 
 *  arguments: 
 *      - token (Token_t *): pointer to operand token
 *  return value:
 *      - OK if its syntax is correct
 *      - NOT_OK_INVALID_TOKEN if its syntax is incorrect
 *      - INTERNAL_ERROR if an unexpecter error occurred (ie: token == NULL)
 *      
*/
int _syntax_check_operand(Token_t *token);



int _is_token_label(Token_t *token)
{
    int exit_status = OK;
    int counter;

    if ( token == NULL )
    {
        exit_status = INTERNAL_ERROR;
        return exit_status;
    }

    for ( counter = 0; counter < token->token_length; counter++ )
    {
        if ( !isalpha(token->token[counter]) && !isdigit(token->token[counter]) && token->token[counter] != '_')
        {
            exit_status = NOT_OK_INVALID_TOKEN;
            return exit_status;
        }
    }

    exit_status = OK;
    return exit_status;
}

int _syntax_check_directives(Token_t **tokens, int token_number, Token_t *invalid_token)
{
    int exit_status;
    int exit_status_routine;
    int curr_keyword;
    Macro_t *macro;

    // this checks aren't necessary but I wanted to be sure
    if ( tokens == NULL || invalid_token == NULL )
    {
        exit_status = INTERNAL_ERROR;
        return exit_status;
    }

    if ( token_number > MAX_TOKENS )
    {
        printf("[_syntax_check_directives] Invalid token_number: token_number > MAX_TOKENS\n");
        exit_status = INTERNAL_ERROR;
        return exit_status;
    }
    // end of checks

    if ( strncmp(tokens[0] -> token, MACRO_DEFINITION_DIR, tokens[0] -> token_length) == 0 )    // this is a macro definition
    {
        exit_status_routine = _syntax_check_macro(tokens, token_number, invalid_token);
    }

    else if ( strncmp(tokens[0] -> token, SEGMENT_SET_DIR, tokens[0] -> token_length) == 0 )
    {
        exit_status_routine = _syntax_check_segset(tokens, token_number, invalid_token);
    }

    else if ( strncmp(tokens[0] -> token, BYTE_ALLOCATION_DIR,  tokens[0] -> token_length) == 0 )
    {
        exit_status_routine = _syntax_check_allocation(tokens, token_number, invalid_token, BYTE_DIMENSION);
    }
    else if ( strncmp(tokens[0] -> token, WORD_ALLOCATION_DIR,  tokens[0] -> token_length) == 0 )
    {
        exit_status_routine = _syntax_check_allocation(tokens, token_number, invalid_token, WORD_DIMENSION);
    }

    else
    {
        exit_status = NOT_A_DIRECTIVE;
        return exit_status;
    }
}

int _syntax_check_macro(Token_t **tokens, int token_number, Token_t *invalid_token)
{
    int exit_status, exit_status_routine;
    int curr_keyword;

    Macro_t *macro;

    // a macro definition has to be 3 elements at least (condition 1) and has to start with MACRO_DEFINE macro (condition 2)
    if ( token_number >= MINIMUM_MACRO_TOKENS )
    {
        // checking if the first token (macro label) is a valid label
        exit_status_routine = _is_token_label(tokens[1]);
        if ( exit_status_routine != OK )
        {
            write_log(SYNTAX_CHECK_LOG | CRITICAL_LOG, "[_syntax_check_macro] Error: instruction starting with token definition but wrong macro label\n");
            printf(SYNTAX_CHECK_LOG | CRITICAL_LOG, "[_syntax_check_macro] Error: token which caused this error: %s\n", tokens[1] -> token);
            memcpy(invalid_token -> token, tokens[1] -> token, tokens[1] -> token_length);
            invalid_token -> token_length = tokens[1] -> token_length;
            exit_status = NOT_OK_INVALID_TOKEN;
            return exit_status;
        }

        // checking if the first token is a forbidden label
        tokens[1] -> token[tokens[1] -> token_length] = '\0';
        stolower(tokens[1] -> token);
        
        curr_keyword = 0;
        while ( reserved_keywords[curr_keyword] != NULL )
        {
            if ( strcmp(reserved_keywords[curr_keyword], tokens[1] -> token) == 0 )
            {
                printf("[_syntax_check_macro] Error: macro declaration uses a reserved keyword as label\n");

                memcpy(invalid_token -> token, tokens[1] -> token, tokens[1] -> token_length);
                invalid_token -> token_length = tokens[1] -> token_length;
                exit_status = NOT_OK_INVALID_TOKEN;
                return exit_status;
            }

            curr_keyword++;
        }

        // checking if the second token (expanded number) is an immediate
        exit_status_routine = _syntax_check_immediate(tokens[2]);
        if ( exit_status_routine != OK )
        {
            printf("[_syntax_check_macro] Error: instruction starting with token definition but wrong expanded number\n");
            printf("[_syntax_check_macro] Error: token which caused this error: %s\n", tokens[2] -> token);
            memcpy(invalid_token -> token, tokens[2] -> token, tokens[2] -> token_length);
            exit_status = NOT_OK_INVALID_TOKEN;
            return exit_status;
        }


        // if no errors has been raised, it is a valid macro definition
        // creating the macro "token"
        macro = init_macro();
        memcpy(macro -> label, tokens[1] -> token, tokens[1] -> token_length);
        macro -> label_length = tokens[1] -> token_length;
        macro -> number = tokens[2] -> token_type -> number;

        // updating macro list
        exit_status_routine = update_code_macros(macro);
        
        if ( exit_status_routine != OK )
        {
            write_log(SYNTAX_CHECK_LOG | CRITICAL_LOG, "[_syntax_check_macro] Error: unable to update code_macros. Current macro definition (%.*s) wasn't completed\n", 
            macro -> label_length, macro -> label);

            exit_status = INTERNAL_ERROR;
            return exit_status;
        }
    } 
    else // if token_number < MINIMUM_MACRO_TOKENS 
    {
        printf(SYNTAX_CHECK_LOG | CRITICAL_LOG, "[_syntax_check_macro] Invalid token_number: token_number < MINIMUM_MACRO_TOKENS\n");

        exit_status = INTERNAL_ERROR;
        return exit_status;
    }

    return OK;


}

int _syntax_check_segset(Token_t **tokens, int token_number, Token_t *invalid_token)
{
    int exit_status, exit_status_routine;
    int is_valid_segset = 0;
    unsigned short *seg_address;


    if ( token_number >= MINIMUM_SEGSET_TOKENS )
    {
        if ( token_number > MAXIMUM_SEGSET_TOKENS )
        {
            write_log(SYNTAX_CHECK_LOG | WARNING_LOG, "[_syntax_check_segset] Warning: too many arguments, exprected %d. Ignoring other arguments.\n", MINIMUM_SEGSET_TOKENS);
        }

        // data segment set
        if ( strncmp(tokens[1] -> token, "data", tokens[1] -> token_length) == 0 )
        {
            if ( is_dataseg_set == 1 )  // "#segset data ..." has been already written
            {
                write_log(SYNTAX_CHECK_LOG | WARNING_LOG, "[_syntax_check_segset] Warning: there has been already a data segment set. Ignoring data address of this directive\n");
                
                exit_status = OK;
                return exit_status;
            }
            curr_segment = DATA_SEGMENT; // following directives must be data allocation
            is_dataseg_set = 1;

            is_valid_segset = 1;
            seg_address = &dataseg_address; // used later to update segment beginning address
        }
        else if ( strncmp(tokens[1] -> token, "code", tokens[1] -> token_length) == 0 )
        {
            if ( is_codeseg_set == 1 )  // "#segset data ..." has been already written
            {
                write_log(SYNTAX_CHECK_LOG | WARNING_LOG, "[_syntax_check_segset] Warning: there has been already a code segment set. Ignoring code address of this directive\n");
                
                exit_status = OK;
                return exit_status;
            }
            curr_segment = CODE_SEGMENT; // following directives must be instructions
            is_codeseg_set = 1;

            is_valid_segset = 1;
            seg_address = &codeseg_address; // used later to update segment beginning address

        }

        // following code is done by all segset types (if it is a valid one)
        if ( is_valid_segset == 1 )
        {
            if ( token_number >= MAXIMUM_SEGSET_TOKENS )    // if there is a segment address it is check and translated into decimal
            {
                exit_status_routine = _syntax_check_immediate(tokens[2]); 
            }

            if ( exit_status_routine == OK ) 
            {
                if ( tokens[2] -> token_type -> number < 0 || tokens[2] -> token_type -> number > MAX_SEG_SPACE ) 
                {
                    write_log(SYNTAX_CHECK_LOG | CRITICAL_LOG, "[_syntax_check_segset] Critical warning: invalid segment address. Using default one\n");
                }
                else
                {
                    *seg_address = tokens[2] -> token_type -> number;
                }
            }
            else    // exit_status_routine != OK
            {
                write_log(SYNTAX_CHECK_LOG | CRITICAL_LOG, "[_syntax_check_segset] Error: invalid segment address. Aborting.\n");

                exit_status = INTERNAL_ERROR;
                return exit_status;
            }

        }
        else // is_valid_segset == 0
        {
            write_log(SYNTAX_CHECK_LOG | CRITICAL_LOG, "[_syntax_check_segset] Error: invalid segment set. Aborting.\n");

            exit_status = INTERNAL_ERROR;
            return exit_status;
        }

        exit_status = OK;
        return exit_status;
        
    }    
    else // if token_number < MINIMUM_SEGSET_TOKENS 
    {
            printf(SYNTAX_CHECK_LOG | CRITICAL_LOG, "[_syntax_check_segset] Invalid token_number: token_number < MINIMUM_SEGSET_TOKENS\n");

            exit_status = INTERNAL_ERROR;
            return exit_status;

    }
}

int _syntax_check_allocation(Token_t **tokens, int token_number, Token_t *invalid_token, int dimension)
{
    int exit_status = OK; 
    int exit_status_routine;

    int value;
    // I gotta change arguments: Token_t* has to be TokensNode_t *
    // In this way I can easily replace this instruction with other instructions



    Macro_t *address_macro;

    //============================ ALLOCATION SYNTAX CHECK ============================
    // allocation directive syntax: #byte/word macro_label, address, [value]
    // macro is used to reference this memory space (so macro_label will be replaced in further code by "address")
    // if no macro want to be used, please use _trash

    // "value" (last directive parameter) can be obmitted. In that case memory is not initialized

    if ( token_number < MINIMUM_ALLOCATION_TOKENS )
    {
        write_log(SYNTAX_CHECK_LOG | CRITICAL_LOG, "[_syntax_check_allocation] Error: expected %d tokens, got %d\n", MINIMUM_ALLOCATION_TOKENS, token_number);

        exit_status = INTERNAL_ERROR;
        return exit_status;
    }
    if ( token_number > MAXIMUM_ALLOCATION_TOKENS )
    {
        write_log(SYNTAX_CHECK_LOG | CRITICAL_LOG, "[_syntax_check_allocation] Warning: expected %d tokens, got %d. Ignoring exceding ones\n", MINIMUM_ALLOCATION_TOKENS, token_number);
    }

    // checking if address is valid
    exit_status_routine = _syntax_check_immediate(tokens[2]);
    if ( exit_status_routine != OK || tokens[2] -> token_type -> number < 0 || tokens[2] -> token_type -> number > MAX_SEG_SPACE)
    {
        // address is invalid if it's not a number or if it's out of range 
        write_log(SYNTAX_CHECK_LOG | CRITICAL_LOG, "[_syntax_check_allocation] Error: address %s is not valid\n", tokens[2] -> token);

        exit_status = INTERNAL_ERROR;
        return exit_status;
    }

    if ( token_number > MINIMUM_ALLOCATION_TOKENS ) // if there is also value field
    {
        exit_status_routine = _syntax_check_immediate(tokens[3]);

        value = tokens[3] -> token_type -> number;

        if ( exit_status_routine != OK ||   // value is not a number
            ( dimension == BYTE_DIMENSION &&    // number is greater than 1111 1111 = 127 if unsigned, else less than 1000 0001 = -63 is signed
                ( ( value >= 128 ) || (value <= -64) )
            ) || 
            ( dimension == WORD_DIMENSION && // number is greater than 1111 1111 1111 1111 = 131071 if unsigned, else less than 1000 0000 0000 0001 = -65536 is signed
                ( ( value >= 131072) || (value <= -65536))
            )
           )
        {
            write_log(SYNTAX_CHECK_LOG | CRITICAL_LOG, "[_syntax_check_allocation] Error: value %d is not a number or it is too great (or too small if negative\n", 
            value);

            exit_status = INTERNAL_ERROR;
            return exit_status;
        }

        // if here then "value" is valid, then macro can be created

        exit_status_routine = _is_token_label(tokens[1]);
        if ( exit_status_routine != OK )
        {
            write_log(SYNTAX_CHECK_LOG | CRITICAL_LOG, "[_syntax_check_allocation] Error: macro_label %s is invalid. It must follow label syntax rules\n", 
            tokens[1] -> token);

            exit_status = INTERNAL_ERROR;
            return INTERNAL_ERROR;
        }

        if ( strcmp("_trash", tokens[1] -> token) != 0 && tokens[1] -> token_length == 6 ) // macro_label is not _trash
        {
            // creating the macro containing the address
            address_macro = init_macro();
            strncpy(address_macro -> label, tokens[1] -> token, tokens[1] -> token_length);
            address_macro -> label_length = tokens[1] -> token_length;
            address_macro -> number = value;

            exit_status_routine = update_code_macros(address_macro);
            if ( exit_status_routine != OK )
            {
                write_log(SYNTAX_CHECK_LOG | CRITICAL_LOG, "[_syntax_check_allocation] Error: it exists already a macro named. Ignoring this definition %s\n", address_macro -> label);

                free_macro(address_macro);
            }
        }
        // if macro_label == _trash, macro is not created


        // preparing for directive expansion
        // note that this is executed only if 
        exit_status_routine = _setup_expansion(tokens, token_number, invalid_token, dimension);

        if ( exit_status_routine != OK )
        {
            write_log(SYNTAX_CHECK_LOG | CRITICAL_LOG, "[_syntax_check_allocation] Error: unable to setup directive expansion\n");

            exit_status = INTERNAL_ERROR;
            return exit_status;
        }

    }// end if token_number > MINIMUM_ALLOCATION_TOKENS

    free_data_address += dimension/BYTE_DIMENSION;  // incrementing by 1 if a byte has been allocated, 2 for a word
    // address contained in free_data_address is now occupied

    exit_status = OK;
    return exit_status;
}

int _setup_expansion(Token_t **tokens, int token_number, Token_t *invalid_token, int dimension)
{
    int exit_status = OK; 
    int exit_status_routine;

    unsigned short address, value;  // look at the allocation syntax down below
    unsigned short upper_address, upper_value;
    unsigned short lower_address, lower_value;

    char upper_address_string[LUI_IMMEDIATE_LENGTH], upper_value_string[LUI_IMMEDIATE_LENGTH];
    char lower_address_string[ADDI_IMMEDIATE_LENGTH], lower_value_string[ADDI_IMMEDIATE_LENGTH];

    char instruction[30];

    Token_t **_expanded0, **_expanded1, **_expanded2, **_expanded3, **_expanded4;
    TokensNode_t *expanded0, *expanded1, *expanded2, *expanded3, *expanded4;
    int filled_tokens;

    //===================== DIRECTIVE EXPANSION INTO INSTRUCTIONS =====================
    /*  directive gets expanded in:
    *       - lui t0, upper_address (+1)
    *       - addi t0, lower_address
    *       - lui t1, upper_immediate (+1)
    *       - addi t1, lower_immediate
    *       - storeb / storew t0, t1 
    */ 
    
    // initializing tokens
    pending_instructions = expanded0;
    expanded0 = init_tokens_node();
    _expanded0 = init_token_array(MAX_TOKENS);
    expanded0 -> tokens = _expanded0;
    expanded0 -> next = expanded1;

    expanded1 = init_tokens_node();
    _expanded1 = init_token_array(MAX_TOKENS);
    expanded1 -> tokens = _expanded1;
    expanded1 -> next = expanded2;

    expanded2 = init_tokens_node();
    _expanded2 = init_token_array(MAX_TOKENS);
    expanded2 -> tokens = _expanded2;
    expanded2 -> next = expanded3;

    expanded3 = init_tokens_node();
    _expanded3 = init_token_array(MAX_TOKENS);
    expanded3 -> tokens = _expanded3;
    expanded3 -> next = expanded4;

    expanded4 = init_tokens_node();
    _expanded4 = init_token_array(MAX_TOKENS);
    expanded4 -> tokens = _expanded4;
    expanded4 -> next = NULL;

    //setting current address
    if ( free_data_address < dataseg_address )  // starting from the first free address
        free_data_address = dataseg_address;

    address = free_data_address;

    lower_address = (address & LOWER_IMMEDIATE_MASK);   // fetching lower part of address

    if ( address > 31)    // last lower bit = 1
        upper_address = (address & UPPER_IMMEDIATE_MASK) + 1;
    else
        upper_address = (address & UPPER_IMMEDIATE_MASK);

    value = tokens[2] -> token_type -> number;

    lower_value = (value & LOWER_IMMEDIATE_MASK);
    if ( value > 31)
        upper_value = (value & UPPER_IMMEDIATE_MASK) + 1;
    else
        upper_value = (value & UPPER_IMMEDIATE_MASK);
        

    /* N.B.: why adding +1 if address > 31?
     *  if address > 31 then 6th bit of lower_address = 1 (lower_address[5] = 1).
     *  The expanded1 instruction adds lower_address to upper_address (which is in the upper part of the register)
     *  If lower_address[5] = 1, then the 6bit-immediate is expanded WITH 1 (negative number expansion).
     *  This would "corrupt" upper_address, so by adding 1 to upper_address the sequence of ones gets canceled.
     * EXAMPLE:
     *  upper = 1100 1000 00 
     *  lower = 11 1001
     * 
     *  1100 1000 0000 0000 +
     *  0000 0000 0100 0000 +   -> that's the +1 we talking about, lui instruction shift it by 6 bits
     *  1111 1111 1111 1001 =
     *  1101 1000 0011 1001
     */


    sprintf(upper_address_string, "%010d", upper_address);      // converting upper part of free_data_address to string
    sprintf(lower_address_string, "%06d", lower_address);      // converting lower part of free_data_address to string
    sprintf(upper_value_string, "%010d", upper_value);      // converting upper part of free_data_address to string
    sprintf(lower_value_string, "%06d", lower_value);      // converting lower part of free_data_address to string


    // EXPANDED0: loading upper part of address ->  lui t0, upper_10bits_of_address
    strcpy(instruction, "lui t0, ");
    strcat(instruction, upper_address_string); 
    exit_status_routine = tokenize_instruction(instruction, _expanded0, &filled_tokens, invalid_token);   
    expanded0 -> token_number = filled_tokens;
    if ( exit_status_routine != OK )
    {
        write_log(SYNTAX_CHECK_LOG | CRITICAL_LOG, "[_syntax_check_allocation] Error: unable to tokenize expanded instruction 0\n");

        exit_status = INTERNAL_ERROR;
        
    }
    

    // EXPANDED1: loading lower part of address -> addi t0, lower_6bits_of_address
    strcpy(instruction, "addi t0, ");
    strcat(instruction, lower_address_string); 
    exit_status_routine = tokenize_instruction(instruction, _expanded1, &filled_tokens, invalid_token);   
    expanded1 -> token_number = filled_tokens;
    if ( exit_status_routine != OK )
    {
        write_log(SYNTAX_CHECK_LOG | CRITICAL_LOG, "[_syntax_check_allocation] Error: unable to tokenize expanded instruction 1\n");

        exit_status = INTERNAL_ERROR;
    }


    // EXPANDED2: loading upper part of immediate -> lui t1, upper_10bits_of_value
    strcpy(instruction, "lui t1, ");
    strcat(instruction, upper_value_string);    
    exit_status_routine = tokenize_instruction("", _expanded2, &filled_tokens, invalid_token);
    expanded2 -> token_number = filled_tokens;
    if ( exit_status_routine != OK )
    {
        write_log(SYNTAX_CHECK_LOG | CRITICAL_LOG, "[_syntax_check_allocation] Error: unable to tokenize expanded instruction 2\n");

        exit_status = INTERNAL_ERROR;
    }

    // EXPANDED3: loading lower part of immediate -> addi t1, lower_6bits_of_value
    strcpy(instruction, "addi t1, ");
    strcat(instruction, lower_value_string);
    exit_status_routine = tokenize_instruction("", _expanded3, &filled_tokens, invalid_token);
    expanded3 -> token_number = filled_tokens;
    if ( exit_status_routine != OK )
    {
        write_log(SYNTAX_CHECK_LOG | CRITICAL_LOG, "[_syntax_check_allocation] Error: unable to tokenize expanded instruction 3\n");

        exit_status = INTERNAL_ERROR;
    }

    // EXPANDED4: storing to memory the immediate -> storeb / storew t0, t1
    if ( dimension == BYTE_DIMENSION )
        strcpy(instruction, "storeb t0, t1");
    else // dimension == WORD_DIMENSION
        strcpy(instruction, "storew t0, t1");
    exit_status_routine = tokenize_instruction("", _expanded4, &filled_tokens, invalid_token);
    expanded4 -> token_number = filled_tokens;
    if ( exit_status_routine != OK )
    {
        write_log(SYNTAX_CHECK_LOG | CRITICAL_LOG, "[_syntax_check_allocation] Error: unable to tokenize expanded instruction 3\n");

        exit_status = INTERNAL_ERROR;
    }


    // if an error occurred, delete all
    if ( exit_status == INTERNAL_ERROR)
    {
        free_tokens_node(expanded0, 1);
        free_tokens_node(expanded1, 1);
        free_tokens_node(expanded2, 1);
        free_tokens_node(expanded3, 1);
        free_tokens_node(expanded4, 1);

        pending_instructions = NULL;

        return exit_status;
    }


    exit_status = OK;
    return exit_status;

}

int _syntax_check_opcode(Token_t *token)
{
    int char_counter;
    int exit_status;

    if ( token == NULL )
    {
        exit_status = INTERNAL_ERROR;
        return exit_status;
    }

    for ( char_counter = 0; char_counter < token -> token_length; char_counter++ )
    {

        if ( isalpha(token -> token[char_counter]) )
        {
            if ( isupper(token -> token[char_counter]) )
            {
                token -> token[char_counter] = tolower(token -> token[char_counter]);
            }

        }
        else    // token is not alphabetic
        {
            exit_status = NOT_OK_INVALID_TOKEN;
            return exit_status;
        }
    }

    exit_status = OK;
    return exit_status;
}

int _syntax_check_label(Token_t *token)
{
    int char_counter;
    int exit_status;

    // first digit must be alphabetic

    if ( token == NULL )
    {
        exit_status = INTERNAL_ERROR;
        return exit_status;
    }

    if ( isalpha(token -> token[0]) )
    {
        if ( isupper(token -> token[0]) )
        {
            token -> token[0] = tolower(token -> token[0]);
        }
    } else
    {
        printf("[_syntax_check_register] Error: register token is not starting with an alphabetic character\n");
        printf("[_syntax_check_register] Error: previous error caused by 1st character: '%c' \n", token -> token[0]);
        exit_status = NOT_OK_INVALID_TOKEN;
        return exit_status;

    }

    // check if each char is alphabetic and lowercase it.
    // if it's not alphanumeric, there is a syntax error
    for ( char_counter = 1; char_counter < token -> token_length; char_counter++ )
    {

        if ( isalpha(token -> token[char_counter]) )
        {
            if ( isupper(token -> token[char_counter]) )
            {
                token -> token[char_counter] = tolower(token -> token[char_counter]);
            }
        }
        else if ( !isdigit(token -> token[char_counter]) )
        {
            printf("[_syntax_check_register] Error: register token is not alphanumeric\n");
            printf("[_syntax_check_register] Error: previous error caused by '%c' character\n", token -> token[char_counter]);
            exit_status = NOT_OK_INVALID_TOKEN;
            return exit_status;
        }
    }

    exit_status = OK;
    return exit_status;
}

// macros used by _syntax_check_immediate
#define NO_BASE    -1
#define BIN_BASE    2
#define OCT_BASE    8
#define DEC_BASE    10
#define HEX_BASE    16

int _syntax_check_immediate(Token_t *token)
{
    int exit_status;
    int number_base = NO_BASE;
    int base_index = 0;     // base index where the actual number begins
    char curr_char;

    int dec_immediate = 0;
    int immediate_sign = POSITIVE_SIGN;

    //printf("[_syntax_check_immediate] In here\n");

    if ( token == NULL )
    {
        exit_status = INTERNAL_ERROR;
        return exit_status;
    }

    // checking for + or -
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
            immediate_sign = NEGATIVE_SIGN;
        else 
            immediate_sign = POSITIVE_SIGN;
            

    }
    
    // checking for 0 and 0x/0d/0b/...
    if ( token -> token[base_index] == '0')
    {
        if ( token -> token_length < base_index + 2 ) // this is the last character of the token
        {
            if ( base_index > 0 )   // if before there is '+' or '-'
                printf("[_syntax_check_immediate] Warning: + or - sign in front of '0' is a bad habit\n");
            exit_status = OK;
            return exit_status;
        }


        // checking for the letter after the 0
        curr_char = token -> token[base_index+1];
        if ( isalpha(curr_char) )
        {
            if ( number_base == DEC_BASE )      // iff + or - was found at the beginning
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

                printf("[_syntax_check_immediate] Error: number composed only by a prefix [+/-]0x (or 0d, 0b, ...) is not allowed\n");
                exit_status = NOT_OK_INVALID_TOKEN;
                return exit_status;
            }
        }
        else 
        {
            number_base = DEC_BASE; // starting with 0 not followed by any letter implies it's a decimal number
            
            // there is should set base_index = base_index; -> number starts with the 0 because no letter follows it
        }
    

    } // end if "first char == '0'"
    else 
    {
        number_base = DEC_BASE;
    }
    // checking the actual number
    for ( base_index = base_index; base_index < token -> token_length; base_index++ )
    {
        curr_char = token -> token[base_index];
        // checking if current digit is out of range
        if ( ( number_base == BIN_BASE && ( curr_char != '0' && curr_char != '1' ) ) || 
                ( number_base == OCT_BASE && ( curr_char < '0' || curr_char > '7' ) ) ||
                ( number_base == DEC_BASE && ( isdigit(curr_char) == 0 ) ) || 
                ( number_base == HEX_BASE && ( isxdigit(curr_char) == 0 ) ) )
        {

            printf("[_syntax_check_immediate] Error: current digit is out of range\n");
            exit_status = NOT_OK_INVALID_TOKEN;
            return exit_status;

        }

        
        if ( curr_char >= 'a' && curr_char <= 'f') 
            curr_char = 10 + curr_char - 'a';
        else if ( curr_char >= 'A' && curr_char <= 'F') 
            curr_char = 10 + curr_char - 'A';
        else 
            curr_char = curr_char - '0';

        // DEBUG
        write_log(SYNTAX_CHECK_LOG ,"[_syntax_check_immediate] Updating dec_immediate:\n");
        write_log(SYNTAX_CHECK_LOG | BASIC_LOG ,"[_syntax_check_immediate] dec_immediate before udate: %d\n", dec_immediate);
        write_log(SYNTAX_CHECK_LOG | BASIC_LOG ,"[_syntax_check_immediate] number_base = %d, token_length - base_index - 1 = %d, curr_char = %d\n", 
                number_base, token -> token_length - base_index - 1, curr_char);
        dec_immediate += pow(number_base, token -> token_length - base_index - 1) * curr_char;
        // DEBUG
        write_log(SYNTAX_CHECK_LOG | BASIC_LOG ,"[dec_immediate after udate: %d\n", dec_immediate);
        

    } // end for

    
    write_log(SYNTAX_CHECK_LOG | BASIC_LOG ,"[_syntax_check_immediate] Now dec_immediate is %d and immediate_sign is %d\n", dec_immediate, immediate_sign);
    token -> token_type -> number = immediate_sign * dec_immediate;
    write_log(SYNTAX_CHECK_LOG | BASIC_LOG ,"[_syntax_check_immediate] Now token_number is %d\n", token -> token_type -> number);

    exit_status = OK;
    return exit_status;
}

int _syntax_check_operand(Token_t *token)
{
    int exit_status;
    int exit_status_routine;

    if ( token == NULL )
    {
        exit_status = INTERNAL_ERROR;
        return exit_status;
    }

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

    exit_status = OK;
    return exit_status;
}

int syntax_check(Token_t **tokens, int token_number, Token_t *invalid_token)
{
    int token_counter;

    int exit_status;
    int exit_status_routine;

    invalid_token -> token[0] = '\0';
    invalid_token -> token_length = 0;

    if ( tokens == NULL || invalid_token == NULL )
    {
        exit_status = INTERNAL_ERROR;
        return exit_status;
    }

    if ( token_number > MAX_TOKENS )
    {
        printf("[syntax_check] Error: invalid token_number, token_number > MAX_TOKENS\n");


        exit_status = INTERNAL_ERROR;
        return INTERNAL_ERROR;
    }

    if ( token_number >= 1 )
    {
        // checking the whole instruction and not just the first token because there are no operands, so _syntax_check_operand is not appropriate
        exit_status_routine = _syntax_check_macro(tokens, token_number, invalid_token);

        if ( exit_status_routine == OK )    // macro definition found
        {
            printf("[syntax_check] Found a new macro definition\n");

            exit_status = OK;
            return exit_status;
        }
        else if ( exit_status_routine == NOT_OK_INVALID_TOKEN )     // macro definition found but invalid
        {
            printf("[syntax_check] Error: token (%.*s) is invalid.\n", invalid_token -> token_length, invalid_token -> token);

            exit_status = NOT_OK_INVALID_TOKEN;
            return exit_status;
        }
        else if ( exit_status_routine == INTERNAL_ERROR )   // instruction is too short or invalid parameters were passed
        {
            printf("[syntax_check] Error: something unexpected happened while checking macro definition. Aborting check.\n");
            
            exit_status = NOT_OK_INVALID_TOKEN;
            return exit_status;
        }

        // if here, then exit_status_routine = NOT_A_MACRO -> it's not a macro definition

        // checking for segmentation label
        exit_status_routine = _syntax_check_segmentation_label(tokens, token_number, invalid_token);

        // checking opcode
        exit_status_routine = _syntax_check_opcode(tokens[0]);
        
        // if opcode is not valid
        if ( exit_status_routine != OK )
        {
            memcpy(invalid_token -> token, tokens[0] -> token, tokens[0] -> token_length);
            invalid_token -> token_length = tokens[0] -> token_length;

            exit_status = exit_status_routine;
            return exit_status;
        }

    }
    else    // token number < 1
    {
        printf("[syntax_check] Warning: no token was passed (token_number = 0)\n");
        
        exit_status = OK;
        return exit_status;
    }
    
    tokens[0] -> token_type = OPCODE;

    // checking other tokens
    for ( token_counter = 1; token_counter < token_number; token_counter++ )
    {
        //printf("Checking token at index %d: %s\n", token_counter, tokens[token_counter] -> token);
        exit_status_routine = _syntax_check_operand(tokens[token_counter]);
        if ( exit_status_routine != OK )
        {
            exit_status = exit_status_routine;
            return exit_status;
        }
    }
    exit_status = OK;
    return exit_status;

}