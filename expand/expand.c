/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othmaneettaqi <othmaneettaqi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:43:22 by othmaneetta       #+#    #+#             */
/*   Updated: 2025/04/02 11:50:08 by othmaneetta      ###   ########.fr       */
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
		//printf("je parcours pour size_merged et la j'ai \n");
		//print_one_token(parcours);
	}
	printf("================================================================ \n");
	printf("resu  = %d \n",resu );	
	printf("a la fin de la fonction je suis sur \n");
	print_one_token(*sub_linked);
	return (resu);
}

char	*merge_string(t_token **head, int size)
{
	char	*resu;
	t_token	*parcours;
	resu = malloc(sizeof(char) * (size + 1));
	int	i;
	int	j;

	i = 0;
	parcours = *head;
	printf("================================================================ \n");
	printf("la taille de la string a malloc est de %d \n", size + 1);
	while (parcours)
	{
		j = 0;
		while (j < parcours->length)
		{
			resu[i] = parcours->start[j];
			i++;
			j++;
		}
		parcours = parcours->next;
	}
	resu[i] = 0;
	printf("la string reassembler donne : %s", resu);
	return (resu);
}

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

void	expand_one_token_sub(t_token **head)
{
	t_token	*parcours;

	parcours = *head;
	while (parcours)
	{
		if (parcours->type == EXPAND)
			expand_one_token(parcours);
		parcours = parcours->next;
	}
}

void	replace_node(t_token *node, char *resu)
{
	(*node).start = resu;
	(*node).length = ft_strlen(resu);
}

void	expand_string(t_token **head ,t_token *node)
{
	char	*str;
	char	*resu;
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
	printf("================================================================ \n");	
	printf("Voici  la sous liste chaine de token et chaque token est expand \n");
	expand_one_token_sub(&sub_linked_list);
	print_list(&sub_linked_list);
	size = size_of_merged_string(&sub_linked_list);
	printf("size renvoie %d \n", size);
	resu = merge_string(&sub_linked_list, size);
	replace_node(node, resu);
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

