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
	char			**cmd;
	char			**names;
	int				*redir_type;
	int				fd_in;
	int				fd_out;
	struct s_cmd	*next;
}	t_cmd;

// parser.c
void	parser(t_token **head, t_cmd **final);
char	**create_command_line(t_token *start, t_token *pipe);
int		size_cmd_line(t_token *start, t_token *pipe);
void	initialise_node(t_cmd **node);


// handle.c functions
t_token	*handle_cmd_token(t_cmd *node, t_token *token, int *i);
t_token	*handle_redir_in(t_cmd *node, t_token *token, int *r);
t_token	*handle_redir_out(t_cmd *node, t_token *token, int *r);
t_token	*handle_heredoc(t_cmd *node, t_token *token, int *r);

// parser.c helper
void	init_indices(int indices[2]);

// parser_verif.c
int		syntax_verif(t_token **head);

// create_node.c
t_cmd	*create_one_node(t_token *start, t_token *pipe);
t_cmd	*create_one_node(t_token *start, t_token *pipe);





#endif