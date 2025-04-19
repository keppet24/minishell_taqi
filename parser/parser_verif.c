/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_verif.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othmaneettaqi <othmaneettaqi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:48:50 by othmaneetta       #+#    #+#             */
/*   Updated: 2025/04/19 15:19:34 by othmaneetta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// cat >   | ok
// Je viens de penser a un soucis si on met les whitespace etre "" ca me tabasse la gueule
// je segfaullt sur cat      >  WHITESPACE* 5
// je segfault sur chaine vide
int	syntax_verif(t_token **head)
{
	t_token	*current;

	current = *head;
	if ( current == NULL || current->type == PIPE)
	{
		printf("ERROR \n");
		return (1);
	}
	while (current)
	{
		if (current->type == REDIR_IN || current->type == REDIR_OUT || current->type == APPEND || current->type == HEREDOC)
		{
			if (current->next == NULL)
			{
				printf("ERROR \n");
				return (1);	
			}
			current = current->next;
			while (current != NULL && current->type == WHITESPACE)
				current = current->next;
			if (current == NULL || current->type != COMMAND)
			{
				printf("ERROR \n");
				return (1);	
			}
		}
		else if (current->type == PIPE)
		{
			current = current->next;
			while (current != NULL && current->type == WHITESPACE)
				current = current->next;
			if (current == NULL || current->type == PIPE)
			{
				printf("ERROR \n");
				return (1);	
			}
		}
		current = current->next;
	}
	return (0);
}

