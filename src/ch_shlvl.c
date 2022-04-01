#include "minishell.h"

static int	get_shlvl(void)
{
	char	*val;

	val = get_env("SHLVL", shell.env_list);
	if (NULL == val)
		return (1);
	if (check_atoi(val))
	{
		if (val[0] == '-')
			return (0);
	}
	else
		return (1);
	return (ft_atoi(val) + 1);
}

void	change_shlvl(void)
{
	char		*val;
	int			val_int;
	char		*item;
	t_env_list	*elem;

	elem = malloc(sizeof(t_env_list));
	if (NULL == elem)
		exit_with_error("Malloc error");
	val_int = get_shlvl();
	val = ft_itoa(val_int);
	if (NULL == val)
		exit_with_error("Malloc error");
	elem->key = ft_strdup("SHLVL");
	elem->val = val;
	item = collect_str_env(elem);
	if (NULL == item)
		exit_with_error("Malloc error");
	change_env_val(item, &shell.env_list);
	free (item);
	del_lst_env_elem(elem);
}
