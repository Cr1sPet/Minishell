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
			// free(str);
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

	while (1)
	{
		str = readline("> ");
		if (str && *str)
			add_history(str);
		if (!ft_strcmp(str, limiter))
			return (1);
		str = change_dollar(str);
		ft_putendl_fd(str, f);
	}
	return (1);
}
