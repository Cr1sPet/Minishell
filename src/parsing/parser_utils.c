# include "minishell.h"

//void	parse_error(char *str)
//{
//	printf("Error\n");
//	return (NULL);
//}

// char	*ft_space(char *str, int i)
// {
// 	char	*tmp;
// 	char	*tmp2;
// 	int		j;

// 	j = i;
// 	while (str[i] == ' ')
// 		++i;
// 	tmp = ft_substr(str, 0, j + 1);
// 	tmp2 = ft_strdup(str + i);
// 	tmp = ft_strjoin(tmp, tmp2);
// 	free(tmp2);
// 	free(str);
// 	return (tmp);
// }

void	ft_lstadd_back_parse(t_cmd **lst, t_cmd *new)
{
	t_cmd	*tmp;

	if (lst)
	{
		if (*lst)
		{
			tmp = ft_lstlast_parse(*lst);
			tmp->next = new;
		}
		else
		{
			*lst = new;
		}
	}
}

t_cmd	*ft_lstlast_parse(t_cmd *lst)
{
	if ((void *)0 == lst)
		return ((void *)0);
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

t_cmd	*ft_lstnew_parse(void *content)
{
	t_cmd	*new_list;

	new_list = (t_cmd *)malloc(sizeof(t_cmd));
	if ((void *)0 == new_list)
		return ((void *)0);
	new_list->args = content;
	new_list->next = (void *)0;
	return (new_list);
}

void	ft_lstadd_back_redir(t_redir **lst, t_redir *new)
{
	t_redir	*tmp;

	if (lst)
	{
		if (*lst)
		{
			tmp = ft_lstlast_redir(*lst);
			tmp->next = new;
		}
		else
		{
			*lst = new;
		}
	}
}

t_redir	*ft_lstlast_redir(t_redir *lst)
{
	if ((void *)0 == lst)
		return ((void *)0);
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

t_redir	*ft_lstnew_redir(void *content, int type, int db)
{
	t_redir	*new_list;

	new_list = (t_redir *)malloc(sizeof(t_redir));
	if ((void *)0 == new_list)
		return ((void *)0);
	new_list->filename = content;
	new_list->double_redir = db;
	new_list->type_redr = type;
	new_list->next = (void *)0;
	return (new_list);
}

int	prepars(const char *str)
{
	char	ch;
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			ch = str[i];
			i++;
			while (str[i] && str[i] != ch)
				i++;
			if (!str[i] || str[i] != ch)
				return (0);
		}
        if (str[i] == '|')
        {
			while (str[++i] && str[i] == ' ')
                    ;
            if (str[i + 1] == ' ' || str[i + 1] == '\0')
                return (0);
        }
	}
	return (1);
}

char	**correct_str(char **str, char **envp)
{
	int		i;
    int     j;

	i = -1;
	while (str[++i])
	{
        j = -1;
        while (str[i][++j]) 
        {
            if (str[i][j] == '\'')
			    str[i] = ft_quotes(str[i], &j);
		    if (str[i][j] == '\"')
			    str[i] = ft_quotes_2(str[i], &j, envp);
		    if (str[i][j] == '$')
			    str[i] = ft_dollar(str[i], &j, envp);
        }
	}
	return (str);
}