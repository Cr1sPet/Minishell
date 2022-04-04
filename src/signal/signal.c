# include "minishell.h"
void	sig_INT(int sig)
{
	write(2, "  \n", 3);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	shell.status = 130;
}

void signal_init()
{
    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, SIG_IGN);
}

void signal_init_main()
{
	signal(SIGTERM, SIG_IGN);
	signal(SIGINT, sig_INT);
	signal(SIGQUIT, SIG_IGN);
}

void signal_init_here()
{
	signal(SIGTERM, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}