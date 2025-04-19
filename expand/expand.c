/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othmaneettaqi <othmaneettaqi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:43:22 by othmaneetta       #+#    #+#             */
/*   Updated: 2025/04/19 16:11:26 by othmaneetta      ###   ########.fr       */
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
	if (!value_token)
		return ;
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

int		will_expand(t_token *node)
{
	char	*test;
	test = malloc(sizeof(char) *(node->length + 1));
	test = strndup(node->start, node->length);
	if (node->start[0] == '"' && ft_strchr(test, '$'))
		return (1);
	else
		return (0);
}

void	without_quote(t_token **head ,t_token *node)
{
	char	*str;
	(void)head;

	str = return_string(node);
	replace_node(node, str);
}

void	expand_token(t_token **head)
{
	t_token	*parcours;

	parcours = *head;
	while (parcours)
	{
		if (parcours->type == EXPAND)
			expand_one_token(parcours);
		else if (parcours->type == STRING && will_expand(parcours))
			expand_string(head ,parcours);
		else if (parcours->type == STRING)
			without_quote(head, parcours);
		parcours = parcours->next;
	}
}

