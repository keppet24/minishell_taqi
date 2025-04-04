/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taqi <taqi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:53:03 by othmaneetta       #+#    #+#             */
/*   Updated: 2025/04/04 14:21:31 by taqi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H 

#include "../lexer/lexer.h"


// expand.c
void	expand_one_token(t_token *token_node);
void	expand_token(t_token **head);
void	expand_string(t_token **head ,t_token *node);

// expand_string.c
int		size_of_merged_string(t_token **sub_linked);
char	*merge_string(t_token **head, int size);
char	*return_string_from_quote(t_token *node);
void	expand_one_token_sub(t_token **head);

// expand_utils.c
int	    ft_strlen(char *s);
char	*ft_strchr(const char *s, int c);
void    free_token_list(t_token **head);
void	replace_node(t_token *node, char *resu);



#endif