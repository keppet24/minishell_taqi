/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_something.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oettaqi <oettaqi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:06:47 by oettaqi           #+#    #+#             */
/*   Updated: 2025/04/23 19:00:22 by oettaqi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	is_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	is_sep(char c)
{
	if (c == ' ')
		return (1);
	else if (is_space(c))
		return (1);
	else if (c == '|')
		return (1);
	else if (c == '>')
		return (1);
	else if (c == '<')
		return (1);
	else if (c == '$')
		return (1);
	else if (c == '"')
		return (1);
	else if (c == 39)
		return (1);
	return (0);
}

int	is_allnum(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else if (c >= 'a' && c <= 'z')
		return (1);
	else if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}
