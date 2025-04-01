/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othmaneettaqi <othmaneettaqi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:43:22 by othmaneetta       #+#    #+#             */
/*   Updated: 2025/04/01 19:01:11 by othmaneetta      ###   ########.fr       */
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

int		size_of_merged_string(t_token *node, int nbr_of_token)
{
	t_token *parcours;
	int		i;
	int		resu;

	i = 0;
	parcours = node;
	resu = 0;
	printf("================================================================ \n");
	printf("Quand j'appelle size_of_merged_string je suis sur ce token : \n");
	print_one_token(parcours);
	while (i < nbr_of_token)
	{
		resu += parcours->length;
		parcours = parcours->next;
		printf("je parcours pour size_merged et la j'ai \n");
		print_one_token(parcours);
		i++;
	}
	printf("================================================================ \n");	
	return (resu);
}

void	merge_string(t_token **head, int nbr_of_token)
{
	t_token	*parcours;
	int		size;
	
	parcours = *head;
	while (parcours->type != STRING)
		parcours = parcours->next;
	printf("================================================================ \n");	
	printf("Ensuite je rentre dans la fonction merge string et je parcours jusqu'a\n");
	print_one_token(parcours);
	size = size_of_merged_string(parcours, nbr_of_token);
	printf("la longueur de la nouvelle string a malloc est de %d \n", size);
}

void	expand_string(t_token **head ,t_token *node)
{
	char	*value_token;
	int		i;
	int		j;
	int		nbr_of_token;

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
		return ;
	}
	init_scanner(value_token);
	nbr_of_token = create_list_of_token(head);
	printf("================================================================ \n");	
	printf("Premiere etape je cree les nouveaux tokens \n");
	print_list(head);
	merge_string(head, nbr_of_token);
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

