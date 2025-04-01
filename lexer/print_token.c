/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othmaneettaqi <othmaneettaqi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:56:22 by othmaneetta       #+#    #+#             */
/*   Updated: 2025/04/01 18:57:04 by othmaneetta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	print_list(t_token **head)
{
	t_token	*parcours;
	int	j;

	parcours = *head;
	while (parcours != NULL)
	{
		j = 0;
		while(parcours->start[j] && j < parcours->length)
		{
			printf("%c", parcours->start[j]);
			j++;
		}
		printf(" %s \n", type_to_str(parcours->type));
		parcours = parcours->next;
	}
}

void	print_one_token(t_token *node)
{
	int	i;
	i = 0;
	while (i < node->length)
	{
		printf("%c", node->start[i]);
		i++;
	}
	printf("\n");
}

