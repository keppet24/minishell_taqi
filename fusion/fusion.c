/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fusion.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othmaneettaqi <othmaneettaqi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 10:05:17 by othmaneetta       #+#    #+#             */
/*   Updated: 2025/04/28 16:19:20 by othmaneetta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fusion.h"

int	is_mergeable(t_token *node)
{
	if (node->type == COMMAND || node->type == STRING || node->type == EXPAND)
		return (1);
	return (0);
}

int	size_new_string(t_token *parcours, t_token *end_of_sequence)
{
	t_token	*current;
	int		resu;

	current = parcours;
	resu = 0;
	while (current != end_of_sequence)
	{
		resu += current->length;
		current = current->next;
	}
	return (resu);
}

char	*create_new_string(t_token *parcours, t_token *end_of_sequence, int i)
{
	char		*resu;
	int			j;
	int			l;
	t_token		*current;

	resu = malloc(sizeof(char) * (i + 1));
	j = 0;
	current = parcours;
	while (current != end_of_sequence)
	{
		l = 0;
		while (l < current->length)
		{
			resu[j] = current->start[l];
			j++;
			l++;
		}
		current = current->next;
	}
	resu[j] = 0;
	return (resu);
}

void	delete_tokens(t_token *parcours, t_token *end_of_sequence)
{
	t_token	*to_delete;
	t_token	*temp;

	to_delete = parcours->next;
	while (to_delete != end_of_sequence)
	{
		temp = to_delete->next;
		free(to_delete->start);
		free(to_delete);
		to_delete = temp;
	}
}

void	merge_tokens(t_token *parcours, t_token *end_of_sequence)
{
	char	*resu;
	int		size;

	size = size_new_string(parcours, end_of_sequence);
	resu = create_new_string(parcours, end_of_sequence, size);
	replace_node(parcours, resu);
	delete_tokens(parcours, end_of_sequence);
	parcours->next = end_of_sequence;
}

