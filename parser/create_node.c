/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othmaneettaqi <othmaneettaqi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 20:30:17 by othmaneetta       #+#    #+#             */
/*   Updated: 2025/04/28 21:16:53 by othmaneetta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void finalize_node(t_cmd *node, int cmd_count, int redir_count)
{
    node->cmd[cmd_count] = NULL;
    node->names[redir_count] = NULL;
    if (node->cmd[0] == NULL)
    {
        free(node->cmd);
        node->cmd = NULL;
    }
    if (node->names[0] == NULL)
    {
        free(node->names);
        node->names = NULL;
        free(node->redir_type);
        node->redir_type = NULL;
    }
}

t_cmd	*create_one_node(t_token *start, t_token *pipe)
{
	t_cmd	*node;
	t_token	*parcours;
	int		indices[2];

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	initialise_node(&node);
	init_indices(indices);
	parcours = start;
	while (parcours != pipe)
	{
		if (parcours->type == COMMAND || parcours->type == STRING
			|| parcours->type == EXPAND)
			parcours = handle_cmd_token(node, parcours, &indices[0]);
		else if (parcours->type == REDIR_IN)
			parcours = handle_redir_in(node, parcours, &indices[1]);
		else if (parcours->type == REDIR_OUT || parcours->type == APPEND)
			parcours = handle_redir_out(node, parcours, &indices[1]);
		else if (parcours->type == HEREDOC)
			parcours = handle_heredoc(node, parcours, &indices[1]);
		parcours = parcours->next;
	}
	finalize_node(node, indices[0], indices[1]);
	return (node);
}
