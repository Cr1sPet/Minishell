#include "minishell.h"

void	echo_work(char **args, int len)
{
	int	j;

	j = 1;
	if (!strcmp(args[1], "-n"))
		j++;
	while (args[j])
	{
		ft_putstr_fd(args[j], STDOUT_FILENO);
		if (j++ < len - 1)
			write(STDOUT_FILENO, " ", STDOUT_FILENO);
	}
}

void	echo(char **args)
{
	int	len;

	len = 0;
	shell.status = 0;
	while (args[len])
		len++;
	if (1 == len)
	{
		write(STDOUT_FILENO, "\n", 1);
		return ;
	}
	if (len >= 2)
		echo_work(args, len);
	if (strcmp(args[1], "-n"))
		write(STDOUT_FILENO, "\n", 1);
}
