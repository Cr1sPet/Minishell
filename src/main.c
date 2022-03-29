#include "minishell.h"

char	*get_cmd()
{
	char	*str;

	str = readline("🦍 minishell > ");
	if (str && *str)
		add_history (str);
	return (str);
}

int	main(int argc, char **argv, char **envp)
{
	char	*cmd;

	(void) argv;
	if (1 != argc)
		return (1);
	// signal_init();
	initialisation(envp);
	while (1)
	{
		cmd = get_cmd();
		parser(cmd, shell.env);
		exec(shell.cmd_list);
		clean_cmd_list();
		memclean(shell.env, len_2d_str(shell.env));
		shell.env = collect_env(shell.env_list);
	}
	return (0);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_env_list	*list;
// 	t_env_list	*elem;
// 	list = NULL;

// 	lst_envadd_back(&list, get_env_elem("PATH=hello"));
// 	// lst_envadd_back(&list, get_env_elem("BASH=MARK"));
// 	// lst_envadd_back(&list, get_env_elem("HIG=FIG"));
// 	shell.env_list = list;
// 	char	**args = malloc(sizeof(char *) * 5);
// 	args[0] = ft_strdup("export");
// 	args[1] = ft_strdup("AA=CAA");
// 	args[2] = ft_strdup("BB=BB");
// 	args[3] = ft_strdup("CC=CC");
// 	args[4] = NULL;
// 	export(&shell.env_list, args);
// 	print_export(shell.env_list);
// 	return (0);
// }
