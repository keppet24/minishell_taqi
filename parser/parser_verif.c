/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_verif.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othmaneettaqi <othmaneettaqi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:48:50 by othmaneetta       #+#    #+#             */
/*   Updated: 2025/05/05 12:39:49 by othmaneetta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// cat >   | ok
// Je viens de penser a un soucis si on met les whitespace etre "" ca me tabasse la gueule
// je segfaullt sur cat      >  WHITESPACE* 5
// je segfault sur chaine vide



// int syntax_verif(t_token **head)
// {
//     t_token *current;
//     t_token *next_significant;

//     current = *head;
//     if (current == NULL || current->type == PIPE)
//     {
//         printf("ERROR\n");
//         return (1);
//     }
//     while (current)
//     {
//         if (current->type == REDIR_IN || current->type == REDIR_OUT || current->type == APPEND || current->type == HEREDOC)
//         {
//             next_significant = current->next;
//             while (next_significant != NULL && next_significant->type == WHITESPACE)
//                 next_significant = next_significant->next;

//             if (next_significant == NULL || (next_significant->type != COMMAND && next_significant->type != EXPAND && next_significant->type != STRING))
//             {
//                 printf("ERROR\n");
//                 return (1);
//             }
//             current = next_significant->next;
//             continue;
//         }
//         else if (current->type == PIPE)
//         {
//             next_significant = current->next;
//             while (next_significant != NULL && next_significant->type == WHITESPACE)
//                 next_significant = next_significant->next;

//             if (next_significant == NULL || next_significant->type == PIPE)
//             {
//                 printf("ERROR\n");
//                 return (1);
//             }
//             current = next_significant;
//              continue;
//         }
//         else if (current->type == ERROR)
//         {
//             printf("ERROR\n");
//             return (1);
//         }
//         current = current->next;
//     }
//     return (0);
// }

t_token	*find_next_significant(t_token *current)
{
	t_token	*next;

	next = NULL;
	if (current)
	{
		next = current->next;
		while (next != NULL && next->type == WHITESPACE)
		{
			next = next->next;
		}
	}
	return (next);
}

int	is_valid_redir_target_type(t_token_type type)
{
	return (type == COMMAND || type == EXPAND || type == STRING);
}

int	handle_redir_syntax(t_token **current_ptr)
{
	t_token	*next_significant;

	next_significant = find_next_significant(*current_ptr);
	if (next_significant == NULL || \
		!is_valid_redir_target_type(next_significant->type))
	{
		printf("ERROR\n");
		return (1);
	}
	*current_ptr = next_significant->next;
	return (0);
}

int	handle_pipe_syntax(t_token **current_ptr)
{
	t_token	*next_significant;

	next_significant = find_next_significant(*current_ptr);
	if (next_significant == NULL || next_significant->type == PIPE)
	{
		printf("ERROR\n");
		return (1);
	}
	*current_ptr = next_significant;
	return (0);
}

int	is_redir_type(t_token_type type)
{
	return (type == REDIR_IN || type == REDIR_OUT
		|| type == APPEND || type == HEREDOC);
}

