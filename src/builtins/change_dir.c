#include "minishell.h"

int	find_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	change_dir(t_minishell *mshell)
{
	int	len;

	len = find_len(mshell->cmd_list->args);
	mshell->status = 0;
	if (len > 2)
	{
		ft_putendl_fd("No such file or directory", 1);
		mshell->status = 1;
	}
	else if (2 == len)
	{
		if (-1 == chdir(mshell->cmd_list->args[1]))
		{
			perror("Error");
			mshell->status = 1;
		}
	}
}
