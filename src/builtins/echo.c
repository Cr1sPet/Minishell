#include "minishell.h"




void	echo(char **args, int fd)
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
		write(fd, "\n", fd);
		return ;
	}
	if (i >= 2)
	{
		if (!strcmp(args[1], "-n"))
			j++;
		while (args[j])
		{
			ft_putstr_fd(args[j], fd);
			if (j++ < i - 1)
				write(fd, " ", fd);
		}
	}
	if (strcmp(args[1], "-n"))
		write(fd, "\n", fd);
}
