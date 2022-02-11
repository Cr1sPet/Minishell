# include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	char	*cmd;
	if (1 != argc)
		return (1);
	while (1)
	{
		cmd = get_cmd ();
	}
	return (0);
}