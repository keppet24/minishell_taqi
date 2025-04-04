/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taqi <taqi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:43:22 by othmaneetta       #+#    #+#             */
/*   Updated: 2025/04/04 14:47:32 by taqi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer/lexer.h"
#include "expand.h"

void expand_one_token(t_token *token_node)
{
    char 	*value_token;
	char	*value;
    int 	i; 
	int		j;

	i = 0;
	j = 1;
	value_token = malloc(token_node->length);
    while (i < (token_node->length - 1))
    {
        value_token[i] = token_node->start[j];
        i++;
        j++;
    }
    value_token[i] = '\0';
    value = getenv(value_token);
    free(value_token);
    if (!value)
    {
        free(token_node->start);
        token_node->start = strdup("");
        token_node->length = ft_strlen(value);
		return ;
    }
    free(token_node->start);
    token_node->start = strdup(value);
    token_node->length = ft_strlen(value);
}

void	expand_token(t_token **head)
{
	t_token	*parcours;

	parcours = *head;
	while (parcours)
	{
		if (parcours->type == EXPAND)
			expand_one_token(parcours);
		else if (parcours->type == STRING && parcours->start[0] == '"')
			expand_string(head ,parcours);
		parcours = parcours->next;
	}
}

