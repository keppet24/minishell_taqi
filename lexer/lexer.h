/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oettaqi <oettaqi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:52:33 by oettaqi           #+#    #+#             */
/*   Updated: 2025/03/24 18:53:18 by oettaqi          ###   ########.fr       */
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
	WHITESPACE,
	NONE,
	ERROR
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*start;
	int				length;
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

#endif
