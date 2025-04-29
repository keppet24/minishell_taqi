/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othmaneettaqi <othmaneettaqi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:45:55 by othmaneetta       #+#    #+#             */
/*   Updated: 2025/04/28 16:16:50 by othmaneetta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer/lexer.h"
#include "expand.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (unsigned char) c)
		return ((char *)&s[i]);
	return (0);
}

void	free_token_list(t_token **head)
{
	t_token	*current;
	t_token	*next;

	current = *head;
	while (current)
	{
		next = current->next;
		free(current->start);
		free(current);
		current = next;
	}
	*head = NULL;
}

void	replace_node(t_token *node, char *resu)
{
	free(node->start);
	(*node).start = resu;
	(*node).length = ft_strlen(resu);
}

int	size_of_merged_string(t_token **sub_linked)
{
	t_token	*parcours;
	int		resu;

	parcours = *sub_linked;
	resu = 0;
	while (parcours != NULL)
	{
		resu += parcours->length;
		parcours = parcours->next;
	}
	return (resu);
}