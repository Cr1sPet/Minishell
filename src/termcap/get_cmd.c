#include "crs_termcap.h"
#define INP_BUF_SIZE 100
#include <string.h>

// char    buf[100];
// char    *buffer;

// void        do_tgetnum(char *str)
// {
//    char    *clean_screen;
  
//    buffer = buf;
//    clean_screen = tgetstr(str, &buffer);
  
//    tputs(clean_screen, 1, ft_putint);
 
//    buffer = buf;
//    bzero(buffer, 100);
// }


void del_last(t_get_cmd *cmd)
{
	char *new_cmd;
	int	l;
	int	i;

	i = 0;
	l = strlen(cmd->cmd);
	if (l)
	{
		new_cmd = malloc(l - 1);
		while (i < l - 1)
			new_cmd[i] = cmd->cmd[i++];
		new_cmd[i] = 0;
		free(cmd->cmd);
		cmd->cmd = new_cmd;
	}
}

void	do_tgetnum(char *str)
{
	char	buf[100];
	char	*buffer;
	char    *prop;
	// char	*buffer;

	// buffer = (char *)malloc (100);
	buffer = buf;
	prop = tgetstr(str, &buffer);
	tputs(prop, 1, ft_putint);
	// free (buffer);
	buffer = buf;
   bzero(buffer, 99);
}

void set_input_mode (t_get_cmd	*get_cmd)
{
  tcgetattr (STDIN_FILENO, &get_cmd->saved_tattr);

  tcgetattr (STDIN_FILENO, &get_cmd->tattr);
  get_cmd->tattr.c_lflag &= ~(ICANON);
  get_cmd->tattr.c_lflag &= ~(ECHO);
  tcsetattr (STDIN_FILENO, TCSAFLUSH, &get_cmd->tattr);
}

int	manage_symb (char *input, t_get_cmd *get_cmd)
{
	if (!strcmp(input, "\033[A"))
	{
		do_tgetnum("rc");
		do_tgetnum("ce");
		write (1, "up", 2);
		return (1);
	}
	else if (!strcmp(input, "\033[B"))
	{
		do_tgetnum("rc");
		do_tgetnum("ce");
		write (1, "down", 4);
		return (1);
	}
	else if (!strcmp(input, "\177"))
	{
		if (get_cmd->balance > 0)
		{
			do_tgetnum("le");
			do_tgetnum("dc");
			del_last(get_cmd);
			--get_cmd->balance;
		}
		return (1);
	}
	else if (!strcmp(input, "\033[D"))
	{
		if (get_cmd->balance > 0)
		{
			do_tgetnum("le");
			--get_cmd->balance;
		}
		return (1);
	}
	else if (!strcmp(input, "\033[C"))
	{
		// if (get_cmd->balance < strlen(get_cmd->cmd))
		// {
			do_tgetnum("%i");
			++get_cmd->balance;
		// }
		return (1);
	}
	return (0);
}

char *get_cmd()
{
	int			l;
	char		input_buf[INP_BUF_SIZE];
	t_get_cmd	get_cmd;

	get_cmd.balance = 0;
	get_cmd.cmd = ft_strdup("");
	write (1, "ヽ(・∀・)ﾉ", strlen("ヽ(・∀・)ﾉ"));
	get_cmd.termtype = getenv("TERM");
	if (NULL == get_cmd.termtype || 1 != tgetent(0, get_cmd.termtype))
	{
		// puts("ERROR with termtype");
		// exit (1);
		;
	}
	// устанавливаем новые настройки терминала, сохраняем копию исходных
	set_input_mode(&get_cmd);
	do_tgetnum("sc");
	l = read(STDIN_FILENO, input_buf, INP_BUF_SIZE);
	if (-1 == l)
	{
		perror("ERROR");
		exit(EXIT_FAILURE);
	}
	input_buf[l] = '\0';
	while(strncmp(input_buf, "\n", 1) && strcmp(input_buf, "\4"))
	{
		if (!manage_symb(input_buf, &get_cmd))
		{
			write (1, input_buf, l);
			get_cmd.balance += 1;
			get_cmd.cmd = crs_strjoin(get_cmd.cmd, input_buf);
		}
		l = read(STDIN_FILENO, input_buf, INP_BUF_SIZE);
		if (-1 == l)
		{
			perror("ERROR");
			exit(EXIT_FAILURE);
		}
	}
	if (!strcmp(input_buf, "\4"))
	{
		write (1, "exit\n", 5);
		exit(EXIT_SUCCESS);
	}
	write(1, "\n", 1);
	// возвращаем исходные настройки терминала
	tcsetattr (STDIN_FILENO, TCSAFLUSH, &get_cmd.saved_tattr);
	return (get_cmd.cmd);
}