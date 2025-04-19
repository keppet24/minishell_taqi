#ifndef PARSER_H
# define PARSER_H 

# include "../lexer/lexer.h"
# include "../expand/expand.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <ctype.h>


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
void	parser(t_token **head, t_cmd **final);
t_cmd	*create_one_node(t_token *start, t_token *pipe);
char	**create_command_line(t_token *start, t_token *pipe);
int		size_cmd_line(t_token *start, t_token *pipe);


// parser_verif.c
int	syntax_verif(t_token **head);




#endif