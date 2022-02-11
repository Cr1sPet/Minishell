#include "crs_termcap.h"
#define INP_BUF_SIZE 100
#include <string.h>

char    buf[100];
char    *buffer;

void        test_clean_screen(char *str)
{
   char    *clean_screen;
  
   buffer = buf;
   clean_screen = tgetstr(str, &buffer);
  
   tputs(clean_screen, 1, ft_putint);
 
   buffer = buf;
   bzero(buffer, 100);
}


// void	do_tgetnum(char *str)
// {
// 	char    *prop;
// 	char	*buffer;

// 	buffer = (char *)malloc (10);
// 	prop = tgetstr(str, &buffer);
// 	tputs(prop, 1, ft_putint);
// 	free (buffer);
// }

void set_input_mode (t_get_cmd	*get_cmd)
{
  tcgetattr (STDIN_FILENO, &get_cmd->saved_tattr);

  tcgetattr (STDIN_FILENO, &get_cmd->tattr);
  get_cmd->tattr.c_lflag &= ~(ICANON);
  get_cmd->tattr.c_lflag &= ~(ECHO);
  tcsetattr (STDIN_FILENO, TCSAFLUSH, &get_cmd->tattr);
}

int	manage_symb (char *input)
{
	if (!strcmp(input, "\033[A"))
	{
		test_clean_screen("rc");
		test_clean_screen("ce");
		write (1, "up", 2);
		return (1);
	}
	else if (!strcmp(input, "\033[B"))
	{
		test_clean_screen("rc");
		test_clean_screen("ce");
		write (1, "down", 4);
		return (1);
	}
	return (0);
}

char *get_cmd()
{
	int			l;
	char		input_buf[INP_BUF_SIZE];
	t_get_cmd	get_cmd;

	write (1, "ヽ(・∀・)ﾉ", strlen("ヽ(・∀・)ﾉ"));
	get_cmd.termtype = getenv("TERM");
	if (NULL == get_cmd.termtype || 1 != tgetent(0, get_cmd.termtype))
	{
		puts("ERROR with termtype");
		exit (1);
	}
	// устанавливаем новые настройки терминала, сохраняем копию исходных
	set_input_mode(&get_cmd);
	test_clean_screen("sc");
	l = read(STDIN_FILENO, input_buf, INP_BUF_SIZE);
	if (-1 == l)
	{
		perror("ERROR");
		exit(EXIT_FAILURE);
	}
	input_buf[l] = '\0';
	while(strcmp(input_buf, "\n") && strcmp(input_buf, "\4"))
	{
		if (!manage_symb(input_buf))
		{
			write (1, input_buf, l);
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