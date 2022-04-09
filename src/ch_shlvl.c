/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch_shlvl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spurple <spurple@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 19:13:53 by spurple           #+#    #+#             */
/*   Updated: 2022/04/09 12:40:47 by spurple          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_shlvl(void)
{
	char	*val;

	val = get_env("SHLVL", g_shell.env_list);
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
	t_env_list	*elem;

	elem = malloc(sizeof(t_env_list));
	if (NULL == elem)
		exit_with_error("minishell: -: malloc error");
	val_int = get_shlvl();
	val = ft_itoa(val_int);
	if (NULL == val)
		exit_with_error("minishell: -: malloc error");
	elem->key = ft_strdup("SHLVL");
	elem->val = val;
	elem->equal = 1;
	change_env_val(elem, &g_shell.env_list);
}
