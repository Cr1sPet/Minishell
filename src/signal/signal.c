# include "minishell.h"
void	sig_INT()
{
		rl_on_new_line();
		write(2, "  \n", 3);
		rl_on_new_line();
		rl_redisplay();
}

void signal_init()
{
    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, sig_INT);
}