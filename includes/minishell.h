#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
# include "../libft/libft.h"

typedef struct s_minishell
{
	char **env;
}				t_minishell;

int		exec(char *str, char **envp);
void	init_env(t_minishell *mshell, char **envp);
char	*get_env(char *point, char **envp);
void	initialisation(t_minishell *mshell, char **envp);

#endif