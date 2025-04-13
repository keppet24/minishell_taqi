/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   template.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taqi <taqi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:17:47 by taqi              #+#    #+#             */
/*   Updated: 2025/04/13 17:25:54 by taqi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

typedef struct s_cmd {
    char            **cmd;
    char            **name_in;
    char            **name_out;
    char            *limiter;
    int             append;
    int             fd_in;
    int             fd_out;
    struct s_cmd    *next;
} t_cmd;

// Prototypes des fonctions utilitaires
// static int     count_commands(t_token *start, t_token *end);
// static char    **create_array_cmd(t_token *start, t_token *end);
// static t_cmd   *create_cmd_node(t_token *start, t_token *end);
// static void    insert_last(t_cmd **head, t_cmd *node);
// static void    free_str_array(char **array);

static int   count_commands(t_token *start, t_token *end)
{
    int     count;

    count = 0;
    while (start && start != end)
    {
        if (start->type == COMMAND)
            count++;
        start = start->next;
    }
    return (count);
}

static char	**create_array_redir_in(t_token *start, t_token *end)
{
	int		count;
	t_token	*current;
	char	**array;
	int		i;
	t_token	*file;

	count = 0;
	current = start;
	while (current && current != end)
	{
		if (current->type == REDIR_IN)
		{
			file = current->next;
			while (file && file != end && file->type == WHITESPACE)
				file = file->next;
			if (file && file != end && file->type == COMMAND)
			{
				count++;
				current = file;
			}
		}
		current = current->next;
	}
	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	i = 0;
	current = start;
	while (current && current != end)
	{
		if (current->type == REDIR_IN)
		{
			file = current->next;
			while (file && file != end && file->type == WHITESPACE)
				file = file->next;
			if (file && file != end && file->type == COMMAND)
			{
				array[i] = strndup(file->start, file->length);
				if (!array[i])
				{
					free_str_array(array);
					return (NULL);
				}
				i++;
				current = file;
			}
		}
		current = current->next;
	}
	array[i] = NULL;
	return (array);
}

static char   **free_str_array(char **array)
{
    int    i;

    if (!array)
        return (NULL);
    i = 0;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
    return (NULL);
}

static char   **create_array_cmd(t_token *start, t_token *end)
{
    int     count;
    char    **cmd;
    int     i;

    count = count_commands(start, end);
    cmd = malloc(sizeof(char *) * (count + 1));
    if (!cmd)
        return (NULL);
    i = 0;
    while (start && start != end)
    {
        if (start->type == COMMAND)
        {
            cmd[i] = strndup(start->start, start->length);
            if (!cmd[i])
            {
                free_str_array(cmd);
                return (NULL);
            }
            i++;
        }
        start = start->next;
    }
    cmd[i] = NULL;
    return (cmd);
}

static t_cmd  *create_cmd_node(t_token *start, t_token *end)
{
    t_cmd   *node;

    node = malloc(sizeof(t_cmd));
    if (!node)
        return (NULL);
    node->cmd = create_array_cmd(start, end);
    if (!node->cmd)
    {
        free(node);
        return (NULL);
    }
    node->name_in = create_array_redir_in(start, end); // Rempli avec les fichiers après <
    node->name_out = NULL; // À adapter pour > et >>
    node->limiter = NULL;
    node->append = 0;
    node->fd_in = 0;
    node->fd_out = 1;
    node->next = NULL;
    return (node);
}

void    parser_2(t_token **head, t_cmd **final)
{
    t_token *current_start;
    t_token *current;
    t_cmd   *node;

    if (!head || !(*head) || !final)
        return;
    current_start = *head;
    current = current_start;
    while (current)
    {
        if (current->type == PIPE)
        {
            node = create_cmd_node(current_start, current);
            if (!node)
                return;
            insert_last(final, node);
            current_start = current->next;
            current = current_start;
        }
        else
            current = current->next;
    }
    if (current_start)
    {
        node = create_cmd_node(current_start, NULL);
        if (node)
            insert_last(final, node);
    }
}



void    parser(t_token **head, t_cmd **final)
{
    t_token *current_start;
    t_token *current;
    t_token *node;
    
    current_start = *head;
    current = current_start;
    while (current)
    {
        if (current->type == PIPE)
        {
            node = create_cmd_node(current_start, current);
            if (!node)
                return ;
            
        }
    }
}

void    free_cmd_list(t_cmd *head)
{
    t_cmd   *next;

    while (head)
    {
        next = head->next;
        free_str_array(head->cmd);
        free_str_array(head->name_in);
        free_str_array(head->name_out);
        free(head->limiter);
        free(head);
        head = next;
    }
}


