/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fusion.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othmaneettaqi <othmaneettaqi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 10:05:40 by othmaneetta       #+#    #+#             */
/*   Updated: 2025/04/28 21:15:59 by othmaneetta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../lexer/lexer.h"
#include "../expand/expand.h"
#include "../parser/parser.h"

#ifndef FUSION_H
# define FUSION_H 

// main_function.c
void	fusion(t_token **head);

// fusion.c
int		is_mergeable(t_token *node);
int		size_new_string(t_token *parcours, t_token *end_of_sequence);
char	*create_new_string(t_token *parcours, t_token *end_of_sequence, int i);
void	delete_tokens(t_token *parcours, t_token *end_of_sequence);
void	merge_tokens(t_token *parcours, t_token *end_of_sequence);


#endif