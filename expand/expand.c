/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othmaneettaqi <othmaneettaqi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:43:22 by othmaneetta       #+#    #+#             */
/*   Updated: 2025/04/01 22:44:53 by othmaneetta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer/lexer.h"
#include "expand.h"

void	expand_one_token(t_token *token_node)
{
	char		*value;
	char		*value_token;
	int			i;
	int			j;

	i = 0;
	j = 1;
	value_token = malloc(sizeof(char) * (token_node->length));
	while (i < (token_node->length - 1))
	{
		value_token[i] = token_node->start[j];
		i++;
		j++;
	}
	value_token[i] = 0;
	value = getenv(value_token);
	if (!value)
		return ;
	token_node->start = value;
	token_node->length = ft_strlen(value);
}

int		size_of_merged_string(t_token **sub_linked)
{
	t_token *parcours;
	int		resu;

	parcours = *sub_linked;
	resu = 0;
	printf("================================================================ \n");
	printf("Quand j'appelle size_of_merged_string je suis sur ce token : \n");
	print_one_token(parcours);
	while (parcours != NULL)
	{
		resu += parcours->length;
		parcours = parcours->next;
		printf("je parcours pour size_merged et la j'ai \n");
		//print_one_token(parcours);
	}
	printf("================================================================ \n");
	printf("resu = %d \n",resu );	
	return (resu);
}

// void	merge_string(t_token **head)
// {
	
// }

char	*return_string_from_quote(t_token *node)
{
	char	*value_token;
	int		i;
	int		j;

	i = 0;
	j = 1;
	value_token = malloc(sizeof(char) * (node->length));
	while (i < (node->length - 2))
	{
		value_token[i] = node->start[j];
		i++;
		j++;
	}
	value_token[i] = 0;
	if (!ft_strchr(value_token, '$'))
	{
		free(value_token);
		return (NULL);
	}
	return (value_token);
}

void	expand_string(t_token **head ,t_token *node)
{
	char	*str;
	t_token	*sub_linked_list;
	(void)head;
	int		size;

	sub_linked_list = NULL;
	str = return_string_from_quote(node);
	init_scanner(str);
	create_list_of_token(&sub_linked_list);
	printf("================================================================ \n");	
	printf("Voici  la sous liste chaine de token \n");
	print_list(&sub_linked_list);
	size = size_of_merged_string(&sub_linked_list);
}

void	expand_token(t_token **head)
{
	t_token	*parcours;

	parcours = *head;
	while (parcours)
	{
		if (parcours->type == EXPAND)
			expand_one_token(parcours);
		else if (parcours->type == STRING)
			expand_string(head ,parcours);
		parcours = parcours->next;
	}
}

