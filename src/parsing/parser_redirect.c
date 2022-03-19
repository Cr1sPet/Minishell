# include "minishell.h"

char	*correct_test(char *str, char **envp)
{
	int		i;

	i = -1;
	while (str[++i])
	{
        if (str[i] == '\'')
        	    str = ft_quotes(str, &i);
		if (str[i] == '\"')
		        str = ft_quotes_2(str, &i, envp);
	    if (str[i] == '$')
			    str = ft_dollar(str, &i, envp);
	}
	return (str);
}

char *left_redirect(char *str, int *i, char **envp)
{
    char    *ret;
    char    *filename;
    int      j;
    int     type;

    j = *i;
    type = 0;
	shell.cmd_list->redir_in = redir_in_1;
    if (str[j + 1] == '<')
    {
        type = 1;
        j++;
        ++(*i);
		shell.cmd_list->redir_in = redir_in_2;
    }
    while (str[++j] && str[j] != '<' && str[j] != '|' && str[j] != '>')
        ;
    filename = ft_substr(str, *i + 1, j - 1);
    ret = ft_substr(str, ft_strlen(filename), ft_strlen(str) - ft_strlen(filename));
    filename = ft_strtrim(filename, " ");
    filename = correct_test(filename, envp);
    ft_lstadd_back_redir(&ft_lstlast_parse(shell.cmd_list)->redr_list, ft_lstnew_redir(filename, 2, type));
    *i = -1;
    ret = ft_strtrim(ret, " ");
    return ret;
}

char	*right_redirect(char *str, int *i, char **envp)
{
	char	*ret;
	char	*filename;
	int		j;
	int		type;

    j = *i;
    type = 0;
	shell.cmd_list->redir_out = redir_out_1;
    if (str[j + 1] == '>')
    {
        type = 1;
        j++;
        ++(*i);
		shell.cmd_list->redir_out = redir_out_2;
    }
    while (str[++j] && str[j] != '>' && str[j] != '|' && str[j] != '<')
        ;
    filename = ft_substr(str, *i + 1, j - 1);
    ret = ft_substr(str, ft_strlen(filename), ft_strlen(str) - ft_strlen(filename));
    filename = ft_strtrim(filename, " ");
    filename = correct_test(filename, envp);
    ft_lstadd_back_redir(&ft_lstlast_parse(shell.cmd_list)->redr_list, ft_lstnew_redir(filename, 1, type));
    *i = -1;
    ret = ft_strtrim(ret, " ");
    return ret;
}

void	redir(char *str, char **envp)
{
	int	i;

    i = -1;
    (void)envp;
    while (str[++i])
    {
        if (str[i] == '>')
           str = right_redirect(str, &i, envp);
        if (str[i] ==  '<')
            str =  left_redirect(str, &i, envp);
        if (str[i] == '|')
            break ;
    }
}