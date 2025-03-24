/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oettaqi <oettaqi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:33:01 by oettaqi           #+#    #+#             */
/*   Updated: 2025/03/24 18:51:54 by oettaqi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	create_single_token(char c)
{
	if (c == '|' )
		return (make_token(PIPE));
	else if (c == '<' && peek() != '<')
		return (make_token(REDIR_IN));
	else if (c == '>' && peek() != '>')
		return (make_token(REDIR_OUT));
	else if (c == '<' && peek() == '<' && peek_next() != '<')
	{
		advance();
		return (make_token(HEREDOC));
	}
	else if (c == '>' && peek() == '>' && peek_next() != '>')
	{
		advance();
		return (make_token(APPEND));
	}
	else if (c == '"' )
		return (string(c));
	else if (c == '$')
		return (expand());
	return (make_token(NONE));
}

t_token	scan_one_token(void)
{
	char	*pos;
	int		nbr;
	char	c;
	t_token	lessgo;

	pos = skip_white();
	nbr = (int)(scanner()->current - pos);
	if (nbr >= 1)
	{
		scanner()->start = pos;
		return (make_token(WHITESPACE));
	}
	scanner()->start = scanner()->current;
	c = advance();
	lessgo = create_single_token(c);
	if (lessgo.type != NONE)
		return (lessgo);
	while (!is_at_end() && !is_sep(peek()))
	{
		advance();
		if (peek() == '"' || peek() == 39)
		{
			advance();
			return (string(peek()));
		}
	}
	return (make_token(COMMAND));
}

const char	*type_to_str(t_token_type type)
{
	if (type == COMMAND)
		return ("COMMAND");
	else if (type == PIPE)
		return ("PIPE");
	else if (type == REDIR_IN)
		return ("REDIR_IN");
	else if (type == REDIR_OUT)
		return ("REDIR_OUT");
	else if (type == HEREDOC)
		return ("HEREDOC");
	else if (type == APPEND)
		return ("APPEND");
	else if (type == EMPTY_STRING)
		return ("EMPTY_STRING");
	else if (type == ERROR)
		return ("ERROR");
	else if (type == EXPAND)
		return ("EXPAND");
	else if (type == WHITESPACE)
		return ("WHITESPACE");
	return ("ERROR");
}

int	main(void)
{
	char	*source;
	int		j;
	t_token	token;

	source = readline("Rentrez une commande: ");
	init_scanner(source);
	while (!is_at_end())
	{
		j = 0;
		token = scan_one_token();
		while (token.start[j] && j < token.length)
		{
			printf("%c", token.start[j]);
			j++;
		}
		printf(" %s", type_to_str(token.type));
		printf("\n");
	}
	return (0);
}
