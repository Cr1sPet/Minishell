#include "minishell.h"

unsigned long long int	ft_atoi_ull(const char *str)
{
	int						i;
	int						check_neg;
	long long unsigned int	res;

	i = 0;
	res = 0;
	check_neg = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			check_neg = -1;
	}
	while (ft_isdigit(str[i]))
	{
		res = (res * 10) + (str[i] - 48);
		if (res > __LONG_MAX__ && res - __LONG_MAX__ > 1 && check_neg == -1)
			return (0);
		if (res > __LONG_MAX__ && check_neg == 1)
			return (-1);
		i++;
	}
	return (res * check_neg);
}

int	check_atoi(char *str)
{
	int			i;
	unsigned long long int	res;

	i = 0;
	while (str[i])
	{
		if (('-' == str[i] || '+' == str[i]) && i != 0)
			return (0);
		if (!ft_isdigit(str[i]) && str[i] != '-' && str[i] != '+')
			return (0);
		i++;
	}
	res = ft_atoi_ull(str);
	if ((2 < ft_strlen(str)) && (-1 == res || 0 == res))
		return (0);
	return (1);
}

void	ft_exit(char **args)
{
	if (len_2d_str(args) > 2)
	{
		if (check_atoi(args[1]))
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd("exit: ", STDERR_FILENO);
			ft_putendl_fd("too many arguments", STDERR_FILENO);
			shell.status = 1;
			return ;
		}
	}
	if (args[1])
	{
		if (check_atoi(args[1]))
		{

			ft_putendl_fd("exit", STDOUT_FILENO);
			exit (ft_atoi_ull(args[1]));
		}
		else
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd("exit: ", STDERR_FILENO);
			ft_putendl_fd("numeric argement required", STDERR_FILENO);
			exit (2);
		}
		return ;
		// exit (ft_atoi(args[1]));
	}
	// memclean(shell.env, len_2d_str(shell.env) + 1);
	clean_env_store(shell.env_store, len_env_store(shell.env_store) + 1);
	clean_env_store(shell.export, len_env_store(shell.export) + 1);
	clean_cmd_list();
	exit (shell.status);
}
