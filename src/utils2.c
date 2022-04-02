#include "minishell.h"

void	clean_redir_list(t_redir *redir)
{
	t_redir	*temp_list;

	if (redir)
	{
		while (redir)
		{
			temp_list = redir->next;
			free(redir->filename);
			free(redir);
			redir = temp_list;
		}
	}
}

void	clean_cmd_list(t_cmd *cmd_list)
{
	t_cmd	*temp_list;

	if (cmd_list)
	{
		while (cmd_list)
		{
			temp_list = cmd_list->next;
			clean_redir_list(cmd_list->redir_in);
			clean_redir_list(cmd_list->redir_out);
			memclean(cmd_list->args, len_2d_str(cmd_list->args));
			free(cmd_list);
			cmd_list = temp_list;
		}
	}
	cmd_list = NULL;
}

void	clean_env_list(t_env_list *list)
{
	t_env_list	*temp_list;

	while (list)
	{
		temp_list = list->next;
		free(list->key);
		if (list->equal)
			free(list->val);
		free (list);
		list = temp_list;
	}
}

void	print_error(char *arg, char *err_name)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(err_name, STDERR_FILENO);
}
