/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oettaqi <oettaqi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:33:01 by oettaqi           #+#    #+#             */
/*   Updated: 2025/04/25 17:12:08 by oettaqi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "../expand/expand.h"
#include "../parser/parser.h"
#include "../fusion/fusion.h"

t_token	create_single_token(char c)
{
	if (c == '|' )
		return (make_token(PIPE));
	else if (c == '<' && peek() != '<')
		return (make_token(REDIR_IN));
	else if (c == '>' && peek() != '>')
		return (make_token(REDIR_OUT));
	else if (c == '<' && peek() == '<' && peek_next() != '<')
	{
		advance();
		return (make_token(HEREDOC));
	}
	else if (c == '>' && peek() == '>' && peek_next() != '>')
	{
		advance();
		return (make_token(APPEND));
	}
	else if (c == '"' )
		return (string(c));
	else if (c == 39)
		return (string(39));
	else if (c == '$')
		return (expand());
	return (make_token(NONE));
}

t_token	scan_one_token(void)
{
	char	*pos;
	int		nbr;
	char	c;
	t_token	lessgo;
			
	pos = skip_white();
	nbr = (int)(scanner()->current - pos);
	if (nbr >= 1)
	{
		scanner()->start = pos;
		return (make_token(WHITESPACE));
	}
	scanner()->start = scanner()->current;
	c = advance();
	lessgo = create_single_token(c);
	if (lessgo.type != NONE)
		return (lessgo);
	while (!is_at_end() && !is_sep(peek()))
		advance();
	return (make_token(COMMAND));
}

const char	*type_to_str(t_token_type type)
{
	if (type == COMMAND)
		return ("COMMAND");
	else if (type == PIPE)
		return ("PIPE");
	else if (type == REDIR_IN)
		return ("REDIR_IN");
	else if (type == REDIR_OUT)
		return ("REDIR_OUT");
	else if (type == HEREDOC)
		return ("HEREDOC");
	else if (type == APPEND)
		return ("APPEND");
	else if (type == EMPTY_STRING)
		return ("EMPTY_STRING");
	else if (type == ERROR)
		return ("ERROR");
	else if (type == EXPAND)
		return ("EXPAND");
	else if (type == WHITESPACE)
		return ("WHITESPACE");
	else if (type == STRING)
		return ("STRING");
	return ("ERROR");
}

void	free_all(t_token **head)
{
	t_token *parcours;
	t_token	*tmp;

	parcours = *head;
	while (parcours)
	{
		tmp = parcours->next;
		free(parcours);
		parcours = tmp;
	}
	*head = NULL;
}

void print_list_cmd(t_cmd *head)
{
    t_cmd *cmd_node = head;
    int i, j, node_num = 0;
    int name_out_count = 0;

    while (cmd_node)
    {
        printf("--- Commande %d ---\n", node_num++);

        printf("  Cmd (argv): ");
        i = 0;
        if (cmd_node->cmd)
        {
            while (cmd_node->cmd[i])
            {
                printf("[%s] ", cmd_node->cmd[i]);
                i++;
            }
            if (i == 0)
                 printf("(aucun)");
        }
        else
            printf("(aucun)");
        printf("\n");

        printf("  Name_in (<): ");
        i = 0;
        if (cmd_node->name_in)
        {
            while (cmd_node->name_in[i])
            {
                printf("[%s] ", cmd_node->name_in[i]);
                i++;
            }
             if (i == 0)
                 printf("(aucun)");
        }
        else
            printf("(aucun)");
        printf("\n");

        printf("  Name_out (>/>>): ");
        i = 0;
        name_out_count = 0;
        if (cmd_node->name_out)
        {
            while (cmd_node->name_out[i])
            {
                printf("[%s] ", cmd_node->name_out[i]);
                i++;
            }
            name_out_count = i;
             if (i == 0)
                 printf("(aucun)");
        }
        else
             printf("(aucun)");
        printf("\n");

        printf("  Limiter (<<): ");
        i = 0;
        if (cmd_node->limiter)
        {
            while (cmd_node->limiter[i])
            {
                printf("[%s] ", cmd_node->limiter[i]);
                i++;
            }
            if (i == 0)
                printf("(aucun)");
        }
        else
            printf("(aucun)");
        printf("\n");
        printf("  Append flags: ");
        if (cmd_node->append && name_out_count > 0)
        {
            printf("[");
            for (j = 0; j < name_out_count; j++)
            {
                printf("%d", cmd_node->append[j]);
                if (j < name_out_count - 1)
                    printf(", ");
            }
            printf("]");
        }
         else
            printf("(aucun)");
        printf("\n");
        cmd_node = cmd_node->next;
        if(cmd_node)
        {
             printf("=======================\n");
        }
    }
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_cmd_list(t_cmd **final)
{
    t_cmd *current;
	
	current = *final;
    t_cmd *next;
    while (current)
    {
        next = current->next;
		if (current->cmd)
        	free_tab(current->cmd);
		if (current->name_in)
			free_tab(current->name_in);
		if (current->name_out)
			free_tab(current->name_out);
		if (current->limiter)
			free_tab(current->limiter);
		if (current->append)
			free(current->append);
        free(current);
        current = next;
    }
    *final = NULL;
}

int	main(void)
{
	char	*source;
	//int		nbr_of_token;
	t_token	*head;
	t_cmd	*final;

	source = readline("Rentrez une commande: "); 
	init_scanner(source);
	head = NULL;
	final = NULL;
	create_list_of_token(&head);
	printf(" Mon lexer renvoie\n");
	//printf("============================================================== \n");	
	print_list(&head);
	//printf("============================================================== \n");	
	//printf("Mon expand renvoie \n");
	expand_token(&head);
	//printf("================================================================ \n");	
	//printf("maintenant la liste chaine c'est : \n");
	//print_list(&head);
	//printf("je teste ma partie de code qui doit fusionner \n");
	fusion(&head);
	//print_list(&head);
	printf("Voici la liste chaine de commande. \n");
	parser(&head, &final);
	print_list_cmd(final);
	free_token_list(&head);
	free_cmd_list(&final);
	free(source);
	return (0);
}
