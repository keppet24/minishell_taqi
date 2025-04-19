/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othmaneettaqi <othmaneettaqi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:52:33 by oettaqi           #+#    #+#             */
/*   Updated: 2025/04/15 13:31:25 by othmaneetta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H 

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <ctype.h>
# include <string.h>

typedef enum e_token_type
{
	COMMAND,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND,
	EMPTY_STRING,
	EXPAND,
	STRING,
	WHITESPACE,
	NONE,
	ERROR
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*start;
	int				length;
	struct s_token	*next;
}	t_token;

typedef struct s_scanner
{
	char	*start;
	char	*current;
}	t_scanner;

// init_scanner.c

t_scanner	*scanner(void);
void		init_scanner(char *source);

// is_something.c

int			is_space(char c);
int			is_sep(char c);
int			is_allnum(char c);

// scan_scanner.c
char		peek(void);
int			is_at_end(void);
char		advance(void);
char		peek_next(void);

//make_token.c
t_token		make_token(t_token_type type);
t_token		string(char quote);
char		*skip_white(void);
t_token		expand(void);

//  lexer.c
t_token		create_single_token(char c);
t_token		scan_one_token(void);
const char	*type_to_str(t_token_type type);
void		free_all(t_token **head);


//create_linked_list.c
void	insert_at_head(t_token **head, t_token *token);
void	insert_last(t_token **head, t_token *token_list);


//print_token.c
void	print_list(t_token **head);
void	print_one_token(t_token *node);
int		create_list_of_token(t_token **head);


#endif