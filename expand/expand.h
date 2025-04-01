/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othmaneettaqi <othmaneettaqi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:53:03 by othmaneetta       #+#    #+#             */
/*   Updated: 2025/04/01 22:40:01 by othmaneetta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H 

#include "../lexer/lexer.h"


// expand.c
void	expand_token(t_token **head);
void	expand_one_token(t_token *token_node);
void	expand_string(t_token **head ,t_token *node);
//void	merge_string(t_token **head, int nbr_of_token);
int		size_of_merged_string(t_token **sub_linked);




// expand_utils.c
int	ft_strlen(char *s);
char	*ft_strchr(const char *s, int c);





#endif