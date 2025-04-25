

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