#include "../../get_next_line/get_next_line.h"
#include "minishell.h"
void	work_here_doc(char *limiter, int f)
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
					return ;
			write (f, str, ft_strlen(str));
			free(str);
		}
		else if (-1 == ret)
		{
			puts("ERROR WITH GET_NEXT_LINE");
			exit (1);
		}
	}
}
