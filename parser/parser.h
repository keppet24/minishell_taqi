#ifndef PARSER_H
# define PARSER_H 

#include "../lexer/lexer.h"
#include "../expand/expand.h"


typedef struct s_cmd
{
    char            **cmd;
    char            **name_in;
    char            **name_out;
    char            *limiter;
    int             append;
    int             fd_in;
    int             fd_out;
    struct s_cmd    *next;
}	t_cmd;

// parser.c



#endif