#include "minishell.h"




void	echo(char **args)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	shell.status = 0;
	while (args[i])
		i++;
	if (1 == i)
	{
		write(1, "\n", 1);
		return ;
	}
	if (i >= 2)
	{
		if (!strcmp(args[1], "-n"))
			j++;
		while (args[j])
		{
			ft_putstr_fd(args[j], 1);
			if (j++ < i - 1)
				write(1, " ", 1);
		}
	}
	if (strcmp(args[1], "-n"))
		write(1, "\n", 1);
}
