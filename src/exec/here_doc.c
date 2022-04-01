#include "minishell.h"

static char	*change_dollar(char *str)
{
	int		i;
	char	*temp;
	char	*save;

	i = 0;
	save = ft_strdup(str);
	while (str[i])
	{
		if ('$' == str[i])
		{
			temp = ft_dollar(str, &(i), shell.env);
			if (!temp)
				return (NULL);
			if (!ft_strcmp(save, temp))
			{
				free(save);
				return (temp);
			}
			str = temp;
		}
		i++;
	}
	free(save);
	return (str);
}

int	work_here_doc(char *limiter, int *f)
{
	char	*str;
	int		ret;

	while (1)
	{
		str = readline("> ");
		if (str && *str)
			add_history(str);
		if (!ft_strcmp(str, limiter))
			break ;
		str = change_dollar(str);
		if (!str)
			exit ()
		ft_putendl_fd(str, f[1]);
	}
	close (f[0]);
	close (f[1]);
	return (1);
}
