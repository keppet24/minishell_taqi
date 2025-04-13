/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taqi <taqi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:27:06 by taqi              #+#    #+#             */
/*   Updated: 2025/04/07 10:53:23 by taqi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// typedef struct s_cmd
// {
//     char            **cmd;
//     char            **name_in;
//     char            **name_out;
//     char            *limiter;
//     int             append;
//     int             fd_in;
//     int             fd_out;
//     struct s_cmd    *next;
// }	t_cmd;

int	size_of_array_cmd(t_token **head, t_token *parcours)
{
	t_token	*current;
	int		i;

	i = 0;
	current = *head;
	while (current != parcours)
	{
		i++;
		current = current->next;
	}
	return (i - 1);
}

char	**create_array_cmd(t_token **head, t_token *parcours)
{
	int		nbr_of_command;
	char	**cmd;
	int		i;
	t_token	*current;

	i = 0;
	current = *head;
	nbr_of_command = size_of_array_cmd(head, parcours);
	cmd = malloc(sizeof(char *) * nbr_of_command + 1);
	while (current != parcours)
	{
		if (current->type == COMMAND)
		{
			cmd[i] = strndup(current->start, current->length);
			i++;
		}
		current = current->next;
	}
	cmd[i] = NULL;
	return (cmd);
}

void	create_one_cmd(t_token **head, t_cmd **final, t_token *parcours)
{
	char	**cmd;
	t_cmd	*node;
	cmd = create_array_cmd(head, parcours);
	node->cmd = cmd;
	node->fd_in = 0;
	node->fd_out = 0;
	node->append = 0;
	node->limiter = NULL;
	insert_last(final, node);
}

void	parser(t_token **head, t_cmd **final)
{
	t_token	*parcours;

	parcours = *head;
	while (parcours)
	{
		while (parcours->type != PIPE && parcours)
			parcours = parcours->next;
		create_one_cmd(head, final, parcours);
		parcours = parcours->next;
	}
}
