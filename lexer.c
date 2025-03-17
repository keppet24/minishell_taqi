

#include <stdio.h>

typedef enum
{
    COMMAND, //0
    PIPE,
    REDIR_IN,
    REDIR_OUT,
    HEREDOC,
    APPEND,
	EMPTY_STRING,
    ERROR
} tokentype;

typedef struct
{
    tokentype type;
    char *start;
    int length;
}   Token;

typedef struct
{
    char    *start;
    char    *current;
}   Scanner;

Scanner scanner;

void    init_scanner(char *source)
{
    scanner.start = source;
    scanner.current = source;
}

char   peek()
{
    return *scanner.current;
}

int isAtEnd()
{
    if (peek() == 0)
        return (1);
    else
        return (0);
}

char    advance()
{
    scanner.current++;
	//printf("scanner.current donne %c\n", scanner.current[0]);
    return scanner.current[-1];
}

char peekNext() 
{
  if (isAtEnd())
    return (0);
  return scanner.current[1];
}

int match(char expected)
{
    if (isAtEnd())
        return (0);
    if (*scanner.current != expected)
        return (0);
    else
        return (1);
}

void    skip_white()
{
    while ((*scanner.current) == 32)
        advance();
}

Token   make_token(tokentype type)
{
    Token token;
    token.type = type;
    token.start = scanner.start;
	if (type == EMPTY_STRING)
	{
		token.length = (int)(scanner.current - scanner.start + 1);
		return token;
	}
    token.length = (int)(scanner.current - scanner.start);
    return token;
}

Token string()
{
	if (peek() == '"')
	{
		//advance();
		return (make_token(EMPTY_STRING));
	}
	while (peek() != '"' && !isAtEnd())
	{
		advance();
	}
	if (isAtEnd())
		return (make_token(ERROR));
	advance();
	return (make_token(COMMAND));
}

Token string_simple()
{
	if (peek() == 39)
	{
		//advance();
		return (make_token(EMPTY_STRING));
	}
	while (peek() != 39 && !isAtEnd())
	{
		advance();
	}
	if (isAtEnd())
		return (make_token(ERROR));
	advance();
	return (make_token(COMMAND));
}

Token scan_one_token()
{
    skip_white();
    scanner.start = scanner.current;
    char c;
    c = advance();
    if (c == '|' && peek() != '|')
        return (make_token(PIPE));
    else if (c == '<' && peek() != '<')
        return (make_token(REDIR_IN));
    else if (c == '>' && peek() != '>')
        return (make_token(REDIR_OUT));
    else if (c == '<' && peek() == '<' && peekNext() != '<')
	{
		advance();
        return (make_token(HEREDOC));
	}
    else if (c == '>' && peek() == '>' && peekNext() != '>')
	{
		advance();
        return (make_token(APPEND));
	}
	else if (c == '"')
		return (string());
	else if (c == 39)
		return (string_simple());
    while (!isAtEnd() && peek() != ' ')
        advance();
    return (make_token(COMMAND));
}

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *s)
{
	while (*s)
	{
		ft_putchar(*s);
		*s++;
	}
}

int	ft_strlen(char *s)
{
	int i;
	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

int	main()
{
	char *source = readline("Rentrez une commande: ");
	init_scanner(source);
	//ft_putchar(source);
	printf("%d\n", ft_strlen(source));
	int j;
	Token token;
	while (!isAtEnd())
	{
		j = 0;
		token = scan_one_token();
		while (j < token.length)
		{
			printf("%c",token.start[j]);
			j++;
		}
		printf("%d", token.type);
		printf("\n");
		ft_putchar(10);
	}
	printf("%c\n",scanner.current[0]);
	return (0);
}