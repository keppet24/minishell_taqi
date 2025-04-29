/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othmaneettaqi <othmaneettaqi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 20:30:23 by othmaneetta       #+#    #+#             */
/*   Updated: 2025/04/28 20:31:44 by othmaneetta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"


t_token	*handle_cmd_token(t_cmd *node, t_token *token, int *i)
{
	if (token->type == COMMAND || token->type == STRING
		|| token->type == EXPAND)
	{
		node->cmd[*i] = strndup(token->start, token->length);
		(*i)++;
	}
	return (token);
}

t_token	*handle_redir_in(t_cmd *node, t_token *token, int *r)
{
	token = token->next;
	while (token && token->type == WHITESPACE)
		token = token->next;
	if (token)
	{
		node->names[*r] = strndup(token->start, token->length);
		node->redir_type[*r] = 0;
	}
	(*r)++;
	return (token);
}

t_token	*handle_redir_out(t_cmd *node, t_token *token, int *r)
{
	int	type;

	if (token->type == APPEND)
		type = 2;
	else
		type = 1;
	token = token->next;
	while (token && token->type == WHITESPACE)
		token = token->next;
	if (token)
	{
		node->names[*r] = strndup(token->start, token->length);
		node->redir_type[*r] = type;
	}
	(*r)++;
	return (token);
}

t_token	*handle_heredoc(t_cmd *node, t_token *token, int *r)
{
	token = token->next;
	while (token && token->type == WHITESPACE)
		token = token->next;
	if (token)
	{
		node->names[*r] = strndup(token->start, token->length);
		node->redir_type[*r] = 3;
	}
	(*r)++;
	return (token);
}