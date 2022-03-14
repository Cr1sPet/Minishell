# include "minishell.h"
void signal_INT()
{
    printf("CTRL + C\n");
}

void signal_QUIT()
{
    printf("CTRL + D\n");
}

void signal_init()
{
    signal(SIGINT, signal_INT);
    signal(SIGQUIT, signal_QUIT);
}