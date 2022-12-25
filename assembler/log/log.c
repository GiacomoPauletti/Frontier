#include "log.h"

// log_priority is used to check if a log has to be printed or not
int _log_priority = NO_LOG;

unsigned short log_to = LOG_TO_STDOUT;
char log_file_name[] = "logs.txt";
FILE* log_file = NULL;


int init_log_file()
{
    int exit_status;

    if ( log_file == NULL && log_to == LOG_TO_FILE )
    {
        log_file = fopen(log_file_name, "w");

    }
    else if ( log_to == LOG_TO_STDERR )
    {
        log_file = stderr;
    }
    else
    {
        log_file = stdout;
    }

    if ( log_file == NULL )
    {
        printf("[init_log_file] Error: unable to init log_file\n");
        exit_status = INTERNAL_ERROR;
        return exit_status;
    }

    exit_status = OK;
    return exit_status;
}

int set_log_priority(int new_priority)
{
    int exit_status;
    
    _log_priority = new_priority;

    exit_status = OK;
    return exit_status; 
}

int get_log_priority()
{
    return _log_priority;
}

int write_log(int priority, char* prompt, ...)
{
        int exit_status;

        va_list ap;
        va_start(ap, prompt);

        if ( ( priority & get_log_priority() ) == priority )
        {
            if ( log_to == LOG_TO_FILE )
                log_file = fopen(log_file_name, "a");

            if ( log_file == NULL )
            {
                printf("[write_log] Error: unable to open log file. Maybe it's not initialized\n");

                va_end(ap);

                exit_status = INTERNAL_ERROR;
                return exit_status;
            }

            vfprintf(log_file, prompt, ap);
            if ( log_to == LOG_TO_FILE)
                fclose(log_file);
        }
        
        va_end(ap);

        exit_status = OK;
        return exit_status;
}
