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

	// char **ar =  (char *[]) {"export", "ABOBA=SETTED_ABOBA", NULL};
	// char **ar2 =  (char *[]) {"export", "ABOBA2=", NULL};
	char **ar = (char **)malloc (sizeof(char *) * 3);
	ar[0] = ft_strdup("export");
	ar[1] = ft_strdup("ABOBA=HER");
	ar[2] = NULL;

	char **ar2 = (char **)malloc (sizeof(char *) * 2);
	ar2[0] = ft_strdup("export");
	ar2[1] = NULL;

	char **ar3 = (char **)malloc (sizeof(char *) * 5);
	ar3[0] = ft_strdup("unset");
	ar3[1] = ft_strdup("ABOBA=");
	ar3[2] = ft_strdup("=ABOBA");
	ar3[3] = ft_strdup("ABOBA");
	ar3[4] = NULL;
	// ft_putendl_fd(get_env("ABOBA", mshell.env), 1);
	export(ar, &mshell);
	export(ar2, &mshell);
	// env(&mshell);
	// env(&mshell);
	// ft_putendl_fd(getenv("PWD"), 1);
	// ft_putendl_fd(get_env("ABOBA2", mshell.env), 1);
	// unset(ar3, &mshell);
	// ft_putendl_fd(get_env("ABOBA", mshell.env), 1);
	// env(&mshell);
	// export(ar2, &mshell);
	// ft_putnbr_fd(find_len(ar2), 1);
	return (0);
}
