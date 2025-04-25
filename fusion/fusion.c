/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fusion.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oettaqi <oettaqi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 10:05:17 by othmaneetta       #+#    #+#             */
/*   Updated: 2025/04/25 16:55:10 by oettaqi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fusion.h"

int		is_mergeable(t_token *node)
{
	if (node->type == COMMAND || node->type == STRING || node->type == EXPAND)
		return (1);
	return (0);	
}

int		size_new_string(t_token *parcours, t_token *end_of_sequence)
{
	t_token *current;
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
	//resu = malloc(500);
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

void	delete_tokens(t_token *parcours,t_token *end_of_sequence)
{
	t_token *to_delete;
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

void	fusion(t_token **head)
{
	t_token	*parcours;
	t_token	*end_of_sequence;
	int		i;

	parcours = *head;
	while (parcours)
	{
		i = 0;
		if (is_mergeable(parcours))
		{
			end_of_sequence = parcours;
			while (is_mergeable(end_of_sequence))
			{
				i++;
				end_of_sequence = end_of_sequence->next;
				if (end_of_sequence == NULL)
					break;
			}
			if (i > 1)
				merge_tokens(parcours, end_of_sequence);
		}
		parcours = parcours->next;
	}
}
