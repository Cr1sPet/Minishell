#include "../../get_next_line/get_next_line.h"
#include "minishell.h"

static char *change_dollar(char *str)
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
			if (!ft_strcmp(save, temp))
			{
				free(save);
				return (temp);
			}
			free(str);
			str = temp;
		}
		i++;
	}
	free(save);
	return (str);
}

int	work_here_doc(char *limiter, int f)
{
	char	*str;
	int		ret;

	ret = 1;
	while (1)
	{
		if (1 == ret)
			ft_putstr_fd("heredoc> ", STDOUT_FILENO);
		ret = get_next_line(&str, 0);
		if (1 == ret)
		{
			if (ft_strlen(str) - 1 == ft_strlen(limiter)
				&& !ft_strncmp(limiter, str, ft_strlen(limiter)))
					return (1);
			str = change_dollar(str);
			write (f, str, ft_strlen(str));
			free(str);
		}
		else if (-1 == ret)
			return (-1);
	}
	return (1);
}
