/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oettaqi <oettaqi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:33:01 by oettaqi           #+#    #+#             */
/*   Updated: 2025/03/31 19:44:11 by oettaqi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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

void	insert_at_head(t_token **head, t_token *token)
{
	token->next = *head;
	*head = token;
}

void	insert_last(t_token **head, t_token *token_list)
{
	t_token	*parcours;

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

void	print_list(t_token **head)
{
	t_token	*parcours;
	int	j;

	parcours = *head;
	while (parcours != NULL)
	{
		j = 0;
		while(parcours->start[j] && j < parcours->length)
		{
			printf("%c", parcours->start[j]);
			j++;
		}
		printf(" %s \n", type_to_str(parcours->type));
		parcours = parcours->next;
	}
}

int	create_list_of_token(t_token **head)
{
	int	j;
	t_token	token;
	t_token *token_list;

	j = 0;
	while (!is_at_end())
	{
		token = scan_one_token();
		token_list = malloc(sizeof(t_token));
		*token_list = token;
		insert_last(head, token_list);
		j++;	
	}
	return (j);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (unsigned char) c)
		return ((char *)&s[i]);
	return (0);
}

void	expand_one_token(t_token *token_node)
{
	char		*value;
	char		*value_token;
	int			i;
	int			j;

	i = 0;
	j = 1;
	value_token = malloc(sizeof(char) * (token_node->length));
	while (i < (token_node->length - 1))
	{
		value_token[i] = token_node->start[j];
		i++;
		j++;
	}
	value_token[i] = 0;
	value = getenv(value_token);
	if (!value)
		return ;
	token_node->start = value;
	token_node->length = ft_strlen(value);
}

void	print_one_token(t_token *node)
{
	int	i;
	i = 0;
	while (i < node->length)
	{
		printf("%c", node->start[i]);
		i++;
	}
	printf("\n");
}

int		size_of_merged_string(t_token *node, int nbr_of_token)
{
	t_token *parcours;
	int		i;
	int		resu;

	i = 0;
	parcours = node;
	resu = 0;
	printf("================================================================ \n");
	printf("Quand j'appelle size_of_merged_string je suis sur ce token : \n");
	print_one_token(parcours);
	while (i < nbr_of_token)
	{
		resu += parcours->length;
		parcours = parcours->next;
		printf("je parcours pour size_merged et la j'ai \n");
		print_one_token(parcours);
		i++;
	}
	printf("================================================================ \n");	
	return (resu);
}

void	merge_string(t_token **head, int nbr_of_token)
{
	t_token	*parcours;
	int		i;
	int		size;
	
	i = 0;
	parcours = *head;
	while (parcours->type != STRING)
		parcours = parcours->next;
	printf("================================================================ \n");	
	printf("Ensuite je rentre dans la fonction merge string et je parcours jusqu'a\n");
	print_one_token(parcours);
	size = size_of_merged_string(parcours, nbr_of_token);
	printf("la longueur de la nouvelle string a malloc est de %d \n", size);
}

void	expand_string(t_token **head ,t_token *node)
{
	char	*value_token;
	int		i;
	int		j;
	int		nbr_of_token;

	i = 0;
	j = 1;
	value_token = malloc(sizeof(char) * (node->length));
	while (i < (node->length - 2))
	{
		value_token[i] = node->start[j];
		i++;
		j++;
	}
	value_token[i] = 0;
	if (!ft_strchr(value_token, '$'))
	{
		free(value_token);
		return ;
	}
	init_scanner(value_token);
	nbr_of_token = create_list_of_token(head);
	printf("================================================================ \n");	
	printf("Premiere etape je cree les nouveaux tokens \n");
	print_list(head);
	//merge_string(head, nbr_of_token);
}

void	scan_token_list(t_token **head)
{
	t_token	*parcours;

	parcours = *head;
	while (parcours)
	{
		if (parcours->type == EXPAND)
			expand_one_token(parcours);
		else if (parcours->type == STRING)
			expand_string(head ,parcours);
		parcours = parcours->next;
	}
}

int	main(void)
{
	char	*source;
	int		nbr_of_token;
	t_token	*head;

	source = readline("Rentrez une commande: ");
	init_scanner(source);
	head = NULL;
	create_list_of_token(&head);
	scan_token_list(&head);
//	merge_string();
	printf("================================================================ \n");	
	printf("ca c'est mon print_list final \n");
	print_list(&head);
	return (0);
}
