/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oettaqi <oettaqi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:27:06 by taqi              #+#    #+#             */
/*   Updated: 2025/04/24 19:30:05 by oettaqi          ###   ########.fr       */
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

// grep banane < test.txt < banane.txt | wc -l >> nb_ligne.txt

void	initialise_node(t_cmd **node)
{
	(*node)->cmd = malloc(sizeof(char *) * 500);
	if (!(*node)->cmd)
		return ;
	(*node)->name_in = malloc(sizeof(char *) * 500);
	if (!(*node)->name_in)
		return ;
	//(*node)->name_in = NULL;
	(*node)->name_out = malloc(sizeof(char *) * 500);
	if (!(*node)->name_out)
		return ;
	//(*node)->name_out = NULL;
	(*node)->limiter = malloc(sizeof(char) * 500);
	if (!(*node)->limiter)
		return ;
	//(*node)->limiter = NULL;
	(*node)->append = malloc(sizeof(int) * 500);
	if (!(*node)->append)
		return ;
}

void	insert_last_tcmd(t_cmd **head, t_cmd *token_list)
{
	t_cmd	*parcours;

	parcours = *head;	
	if (*head == NULL)
	{
		*head = token_list;
		token_list->next = NULL;
		return ;
	}
	while (parcours->next)
		parcours = parcours->next;
	parcours->next = token_list;
	token_list->next = NULL;
}

//cat < | wc probleme
//cat < segfault
// t_cmd	*create_one_node(t_token *start, t_token *pipe)
// {
// 	t_cmd	*node;
// 	t_token	*parcours;
// 	int		i;
// 	int		j;
// 	int		l;
// 	int		z;

// 	node = malloc(sizeof(t_cmd));
// 	if (!node)
// 		return (NULL);
// 	initialise_node(&node);
// 	parcours = start;
// 	i = 0;
// 	j = 0;
// 	l = 0;
// 	z = 0;
// 	while (parcours != pipe)
// 	{
// 		if (parcours->type == COMMAND)
// 		{
// 			node->cmd[i] = strndup(parcours->start, parcours->length);
// 			i++;
// 		}
// 		else if (parcours->type == STRING)
// 		{
// 			node->cmd[i] = strndup(parcours->start, parcours->length);
// 			i++;
// 		}
// 		else if (parcours->type == EXPAND)
// 		{
// 			node->cmd[i] = strndup(parcours->start, parcours->length);
// 			i++;
// 		}
// 		else if (parcours->type == REDIR_IN)
// 		{
// 			parcours = parcours->next;
// 			while (parcours->type == WHITESPACE)
// 				parcours = parcours->next;
// 			node->name_in[j] = strndup(parcours->start, parcours->length);
// 			j++;
// 		}
// 		else if (parcours->type == REDIR_OUT || parcours->type == APPEND)
// 		{
// 			if (parcours->type == APPEND)
// 			{
// 				node->append[z] = 1;
// 				z++;	
// 			}
// 			else
// 			{
// 				node->append[z] = 0;
// 				z++;
// 			}
// 			parcours = parcours->next;
// 			while (parcours->type == WHITESPACE)
// 				parcours = parcours->next;
// 			node->name_out[l] = strndup(parcours->start, parcours->length);
// 			l++;
// 		}
// 		else if (parcours->type == HEREDOC)
// 		{
// 			parcours = parcours->next;
// 			while (parcours->type == WHITESPACE)
// 				parcours = parcours->next;
// 			node->limiter = strndup(parcours->start, parcours->length);
// 		}
// 		parcours = parcours->next;
// 	}
// 	node->cmd[i] = NULL;
// 	node->name_in[j] = NULL;
// 	node->name_out[l] = NULL;
// 	return (node);
// }

static t_token *handle_cmd_token(t_cmd *node, t_token *token, int *i)
{
    if (token->type == COMMAND || token->type == STRING || token->type == EXPAND)
    {
        node->cmd[*i] = strndup(token->start, token->length);
        (*i)++;
    }
    return (token);
}

static t_token *handle_redir_in(t_cmd *node, t_token *token, int *j)
{
    token = token->next;
    while (token && token->type == WHITESPACE)
        token = token->next;
    if (token)
        node->name_in[*j] = strndup(token->start, token->length);
    (*j)++;
    return (token); 
}

static t_token *handle_redir_out(t_cmd *node, t_token *token, int *l, int *z)
{
    if (token->type == APPEND)
        node->append[*z] = 1;
    else
        node->append[*z] = 0;
    (*z)++;
    token = token->next;
    while (token && token->type == WHITESPACE)
        token = token->next;
    if (token)
        node->name_out[*l] = strndup(token->start, token->length);
    (*l)++;
    return (token);
}

static t_token *handle_heredoc(t_cmd *node, t_token *token)
{
    token = token->next;
    while (token && token->type == WHITESPACE)
        token = token->next;
    if (token)
        node->limiter = strndup(token->start, token->length);
    return (token);
}

void	init_indices(int indices[4])
{
	indices[0] = 0;
    indices[1] = 0;
    indices[2] = 0;
    indices[3] = 0;
}

t_cmd *create_one_node(t_token *start, t_token *pipe)
{
    t_cmd   *node;
    t_token *parcours;
    int     indices[4];

    node = malloc(sizeof(t_cmd));
    if (!node)
        return (NULL);
    initialise_node(&node);
	init_indices(indices);
    parcours = start;
    while (parcours != pipe)
    {
        if (parcours->type == COMMAND || parcours->type == STRING || parcours->type == EXPAND)
            parcours = handle_cmd_token(node, parcours, &indices[0]);
        else if (parcours->type == REDIR_IN)
            parcours = handle_redir_in(node, parcours, &indices[1]);
        else if (parcours->type == REDIR_OUT || parcours->type == APPEND)
            parcours = handle_redir_out(node, parcours, &indices[2], &indices[3]);
        else if (parcours->type == HEREDOC)
            parcours = handle_heredoc(node, parcours);
        parcours = parcours->next;
    }
    node->cmd[indices[0]] = NULL;
    node->name_in[indices[1]] = NULL;
    node->name_out[indices[2]] = NULL;
	if (node->cmd[0] == NULL)
		node->cmd = NULL;
	if (node->name_in[0] == NULL)
		node->name_in = NULL;
	if (node->name_out[0] == NULL)
		node->name_out[0] == NULL;
    return (node);
}

void	parser(t_token **head, t_cmd **final)
{
	t_token	*current_start;
	t_token	*current;
	t_cmd	*node;

	if (syntax_verif(head) == 1)
		return ;
	current_start = *head;
	current = current_start;
	while (current)
	{
		if (current->type == PIPE)
		{
			node = create_one_node(current_start, current);
			insert_last_tcmd(final, node);
			current_start = current->next;
			current = current_start;
		}
		current = current->next;
	}
	if (current_start)
	{
		node = create_one_node(current_start, NULL);
		if (node)
			insert_last_tcmd(final, node);
	}
}



