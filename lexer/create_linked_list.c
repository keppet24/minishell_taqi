/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_linked_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othmaneettaqi <othmaneettaqi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:58:32 by othmaneetta       #+#    #+#             */
/*   Updated: 2025/04/19 16:35:10 by othmaneetta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	insert_at_head(t_token **head, t_token *token)
{
	token->next = *head;
	*head = token;
}

void	insert_last(t_token **head, t_token *token_list)
{
	t_token	*parcours;

	parcours = *head;	
	if (*head == NULL)
	{
		*head = token_list;
		token_list->next = NULL;
		return ;
	}
	while (parcours->next)
		parcours = parcours->next;
	parcours->next = token_list;
	token_list->next = NULL;
}


// int	create_list_of_token(t_token **head)
// {
// 	int	j;
// 	t_token	token;
// 	t_token *token_list;

// 	j = 0;
// 	while (!is_at_end())
// 	{
// 		token = scan_one_token();
// 		token_list = malloc(sizeof(t_token));
// 		token_list->start = token.start;
// 		token_list->length = token.length;
// 		token_list->type = token.type;
// 		token_list->next = NULL;
// 		insert_last(head, token_list);
// 		j++;	
// 	}
// 	return (j);
// }

int create_list_of_token(t_token **head)
{
	int j = 0;
	t_token token;
	t_token *token_list;

	while (!is_at_end())
	{
		token = scan_one_token();
		token_list = malloc(sizeof(t_token));
		token_list->start = strndup(token.start, token.length);
		token_list->length = token.length;
		token_list->type = token.type;
		token_list->next = NULL;
		insert_last(head, token_list);
		j++;
	}
	return (j);
}
