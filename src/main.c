# include "minishell.h"

char	*get_cmd()
{
	char  *str;

	str = readline("minishell > ");
	if (str && *str)
		add_history (str);
	return (str);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	mshell;
	t_cmd		*temp_cmd;
	initialisation (&mshell, envp);
	
	mshell.cmd_list->args = (char **) malloc (sizeof(char *) * 3);
	mshell.cmd_list->args[0] = ft_strdup("cd");
	mshell.cmd_list->args[1] = ft_strdup("src");
	mshell.cmd_list->args[2] = NULL;

	// lst_cmdadd_back(mshell.cmd_list, lst_cmdnew(mshell));
	// temp_cmd = temp_cmd->next;
	// temp_cmd->args = (char **) malloc (sizeof(char *) * 3);
	// temp_cmd->args[0] = ft_strdup("cd");
	// temp_cmd->args[1] = ft_strdup("src");
	// temp_cmd->args[2] = NULL;
	// ft_putendl_fd(getenv("PWD"), 1);
	// pwd(&mshell);
	ft_putendl_fd(get_env("PWD", mshell.env), 1);
	ft_putendl_fd(get_env("OLDPWD", mshell.env), 1);
	// chdir("src");
	change_dir(&mshell);
	// pwd(&mshell);
	ft_putendl_fd(get_env("PWD", mshell.env), 1);
	ft_putendl_fd(get_env("OLDPWD", mshell.env), 1);
	// change_dir(&mshell);
	// ft_putendl_fd(getenv("PWD"), 1);
	// chdir("~");
	// pwd(&mshell);
	// ft_putendl_fd(getenv("PWD"), 1);
	// exec(&mshell);
	return (0);
}
