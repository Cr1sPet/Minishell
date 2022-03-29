#include "minishell.h"

char	*get_key(char *var)
{
	int	i;

	i = 0;
	if (!ft_strchr(var, '='))
		return (ft_strdup(var));
	while (var[i] != '=')
		i++;
	return (ft_substr(var, 0, i));
}

int	ft_strcmp(char const *s1, char const *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		++i;
	return (s1[i] - s2[i]);
}

int	try_change_val(t_env_list *env_list, t_env_list *elem)
{
	while (env_list)
	{
		if (!ft_strcmp(env_list->key, elem->key))
		{
			if (!elem->equal || (env_list->val && elem->val
					&& !ft_strcmp(elem->val, env_list->val)))
				return (1);
			if (env_list->val)
				free(env_list->val);
			env_list->val = NULL;
			env_list->equal = 0;
			if (elem->val)
			{
				env_list->val = ft_strdup(elem->val);
				if (NULL == env_list->val)
					exit_with_error("Malloc error");
				env_list->equal = 1;
			}
			return (1);
		}
		env_list = env_list->next;
	}
	return (0);
}

void	change_env_val(char *input, t_env_list **env_list)
{
	t_env_list	*elem;
	char		*val;

	elem = get_env_elem(input);
	if (elem->val)
		val = ft_strdup(elem->val);
	else
		val = NULL;
	if (!try_change_val(*env_list, elem))
	{
		lst_envadd_back(env_list,
			lst_envnew(ft_strdup(elem->key), val));
	}
	else
		free (val);
	del_lst_env_elem(elem);
}


void swap(t_env_list *a, t_env_list *b)
{
    char	*temp_key;
	char	*temp_val;

	temp_key = a->key;
	temp_val = a->val;
	a->key = b->key;
	a->val = b->val;
	b->key = temp_key;
	b->val = temp_val;
}

t_env_list	*sort_list(t_env_list *start)
{
    int			swapped;
	int			i;
    t_env_list	*ptr1;
    t_env_list	*lptr;

	lptr = NULL;
    if (start == NULL)
        return NULL;
    do
    {
        swapped = 0;
        ptr1 = start;
        while (ptr1->next != lptr)
        {
            if (ft_strcmp(ptr1->key, ptr1->next->key) > 0)
            { 
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
	return (start);
}
  
/* function to swap data of two nodes a and b*/


t_env_list	*cp_env(t_env_list *env_list)
{
	t_env_list	*export;
	char		*key;
	char		*val;

	export = NULL;
	while (env_list)
	{
		key = ft_strdup(env_list->key);
		if (NULL == key)
			exit_with_error("Malloc error");
		if (env_list->val)
		{
			val = ft_strdup(env_list->val);
			if (NULL == val)
				exit_with_error("Malloc error");
		}
		lst_envadd_back(&export, lst_envnew(key, val));
		env_list = env_list->next;
	}
	return (sort_list(export));
}

void	print_export(t_env_list *env_list)
{
	t_env_list	*export;

	export = cp_env(env_list);
	print_env_list(export);
	clean_env_list(export);
}

void	export(t_env_list **env_list, char **args)
{
	int			i;
	int			len;


	i = 1;
	len = len_2d_str(args);
	if (1 == len)
	{
		print_export(*env_list);
	}
	if (len > 1)
	{
		while (args[i])
		{
			change_env_val(args[i], env_list);
			i++;
		}
	}
}
