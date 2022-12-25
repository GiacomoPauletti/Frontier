#ifndef LOG_H
#define LOG_H 1

#include "../common/common.h"

// ============================= LOG PRIORITY ===============================
#define NO_LOG                  0x00000000  //no bits to 1

#define BASIC_LOG               0x00000001  //bit1 = 1
#define WARNING_LOG             0x00000002  //bit2 = 1
#define CRITICAL_LOG            0x00000004  //bit3 = 1

#define TOKENIZE_LOG            0x00010000  //bit8 = 1
#define SYNTAX_CHECK_LOG        0x00020000  //bit9 = 1
#define TRANSLATE_TOKEN_LOG     0x00040000  //bit10 = 1
#define SEMANTIC_CHECK_LOG      0x00080000  //bit11 = 1
#define ASSEMBLER_LOG           0x00100000  //bit12 = 1
#define COMMON_LOG              0x00200000  //bit13 = 1

#define ALL_LOG                 0xFFFFFFFF


// ========================== END OF LOG PRIORITY ===========================


// ============================== LOG FILE ==================================
#define LOG_TO_STDOUT           0x0000  //not bits to 1
#define LOG_TO_STDERR           0x0001  //bit1 = 1
#define LOG_TO_FILE             0x0002  //bit2 = 2

// log_to is used to check where the log has to be printed
extern unsigned short log_to;
extern char log_file_name[];
extern FILE* log_file;

// =========================== END OF LOG FILE ==============================

/*
// ===================== MACROS FOR VARIADIC ARGUMENTS ======================

// credits: https://stackoverflow.com/users/233522/kornel-kisielewicz   (wrote the answer)
//          https://stackoverflow.com/users/2752075/holyblackcat        (edited the answer)
//          https://stackoverflow.com/users/54829/dan-fabulich          (reposted the answer)

// GET_NARG is used to get the number of arguments passed as __VA_ARGS__
// it passes all the function arguments to a GET_128TH_ARG, which expects 128 arguments.
// since there wil be probably less than 128 (128 is the maximum), the remaining
// arguments are filled with a reverse sequence, contained in REV_128_SEQ macro.
// If there are 5 arguments in __VA_ARGS_ the last arg will be 5.
// So GET_128TH_ARG will return the number of arguments

// originally PP_NARG
#define GET_NARG(...) \     
        GET_NARG_(__VA_ARGS__,REV_128_SEQ())
// originally PP_NARG_
#define GET_NARG_(...) \    
        GET_128TH_ARG(__VA_ARGS__)

// originally PP_128TH_ARG
#define GET_128TH_ARG( \    
        _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
        _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
        _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
        _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
        _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
        _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
        _61,_62,_63,_64,_65,_66,_67,_68,_69,_70, \
        _71,_72,_73,_74,_75,_76,_77,_78,_79,_80, \
        _81,_82,_83,_84,_85,_86,_87,_88,_89,_90, \
        _91,_92,_93,_94,_95,_96,_97,_98,_99,_100, \
        _101,_102,_103,_104,_105,_106,_107,_108,_109,_110, \
        _111,_112,_113,_114,_115,_116,_117,_118,_119,_120, \
        _121,_122,_123,_124,_125,_126,_127,N,...) N

// originally PP_RSEQ_N
#define REV_128_SEQ() \       
        127,126,125,124,123,122,121,120, \
        119,118,117,116,115,114,113,112,111,110, \
        109,108,107,106,105,104,103,102,101,100, \
        99,98,97,96,95,94,93,92,91,90, \
        89,88,87,86,85,84,83,82,81,80, \
        79,78,77,76,75,74,73,72,71,70, \
        69,68,67,66,65,64,63,62,61,60, \
        59,58,57,56,55,54,53,52,51,50, \
        49,48,47,46,45,44,43,42,41,40, \
        39,38,37,36,35,34,33,32,31,30, \
        29,28,27,26,25,24,23,22,21,20, \
        19,18,17,16,15,14,13,12,11,10, \
        9,8,7,6,5,4,3,2,1,0

// ================== END OF MACROS FOR VARIADIC ARGUMENTS ==================
*/

//int _log(size_t arg_num, int log_level, char* prompt, ...);
//#define log(...) _log(GET_NARG(__VA_ARGS__), __VA_ARGS__)

/*  WRITE_LOG
 *  Write a log in log_file if all set bit of priority are set also in log_priority
 *  (log_priority semantic consequence of priority)
 * 
 *  arguments:
 *      - priority (int): current log priority
 *      - prompt (char*): formatted string to write
 *      - ...: extra parameter for the formatted string
 * return value (int):
 *      - OK if everything worked fine
 *      - INTERNAL ERROR if an error occurred
*/
int write_log(int priority, char* prompt, ...);

//#define write_log(...) _write_log(__VA_ARGS__)

/*  INIT_LOG_FILE
 *  initialize the log file. Creates it if necessary.
 *  
 *  arguments:
 *  return value (int):
 *      - OK if initialization worked fine
 *      - INTERNAL_ERROR if initialization didn't work
*/
int init_log_file();

/*  SET_LOG_PRIORITY
 *  set a new value to log_priority among the values above, in LOG PRIORITY
 *  
 *  arguments:
 *      - new_priority (int): the new value of log_priority
 *  return value:
 *      - OK if everything worked fine
 *      - INTERNAL_ERROR if an error occurred
*/
int set_log_priority(int new_priority);

/*  GET_LOG_PRIORITY
 *  get the current value of log_priority
 *
 *  arguments:
 *  return value (int): current log_priority
*/
int get_log_priority();

#endif