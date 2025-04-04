/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taqi <taqi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:33:01 by oettaqi           #+#    #+#             */
/*   Updated: 2025/04/04 14:27:45 by taqi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "../expand/expand.h"

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
	else if (c == 39)
		return (string(39));
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
		advance();
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
	else if (type == STRING)
		return ("STRING");
	return ("ERROR");
}

void	free_all(t_token **head)
{
	t_token *parcours;
	t_token	*tmp;

	parcours = *head;
	while (parcours)
	{
		tmp = parcours->next;
		free(parcours);
		parcours = tmp;
	}
	*head = NULL;
}

int	main(void)
{
	char	*source;
	//int		nbr_of_token;
	t_token	*head;

	source = readline("Rentrez une commande: ");
	init_scanner(source);
	head = NULL;
	create_list_of_token(&head);
	//printf(" Mon lexer renvoie\n");
	//printf("============================================================== \n");	
	//print_list(&head);
	//printf("============================================================== \n");	
	//printf("Mon expand renvoie \n");
	expand_token(&head);
	//printf("================================================================ \n");	
	printf("maintenant la liste chaine c'est : \n");
	print_list(&head);
	
	free_token_list(&head);
	free(source);
	return (0);
}
