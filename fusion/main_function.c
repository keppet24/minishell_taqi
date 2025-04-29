/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othmaneettaqi <othmaneettaqi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:13:50 by othmaneetta       #+#    #+#             */
/*   Updated: 2025/04/28 16:13:59 by othmaneetta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fusion.h"

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
					break ;
			}
			if (i > 1)
				merge_tokens(parcours, end_of_sequence);
		}
		parcours = parcours->next;
	}
}
