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
		free(cmd);
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
// 	elem = get_env_elem("ZZZ=AAAA");
// 	lst_envadd_back(&list, elem);
// 	elem = get_env_elem("UUU=sadg");
// 	lst_envadd_back(&list, elem);
// 	elem = get_env_elem("IUHIUGUGU=sadg");
// 	lst_envadd_back(&list, elem);
// 	print_env_list(list);
// 	print_export(list);
// 	return (0);
// }
