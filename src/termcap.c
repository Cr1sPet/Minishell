/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spurple <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 18:32:35 by spurple           #+#    #+#             */
/*   Updated: 2022/01/26 18:33:36 by spurple          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <curses.h>
#include <term.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int l;
char str[100];
char    room_termtype[2048];
char    *termtype;
char    buf[10];
char    *buffer;
 
//необходима для tputs
int         ft_putint(int c)
{
   return (write(STDOUT_FILENO, &c, 1));
}

void        test_tgetnum(void)
{
	int     col;
	int     li;

	col = tgetnum("co");
	li = tgetnum("li");
	printf("Columns = %d, lines = %d\n", col, li);
}

void        test_clean_screen(void)
{
   char    *clean_screen;
  
   buffer = buf;
   clean_screen = tgetstr("nd", &buffer);
  
   tputs(clean_screen, 1, ft_putint);
 
   buffer = buf;
   bzero(buffer, 100);
}


int         main(int argc, char **argv)
{
	struct termios term;

//    	//define the terminal
//    	if (!isatty(STDIN_FILENO))
//        return(1);
	tcgetattr (STDIN_FILENO, &term);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	tcsetattr (STDIN_FILENO, TCSAFLUSH, &term);
//    //чтобы было удобнее тестировать, будут использоваться аргументы
// //    if (argc < 2)
// //        return (1);
//    	termtype = getenv("TERM");
//    	if (termtype == NULL || tgetent(0, termtype) != 1) 
//        return (1);
// 	//далее будут вызываться функции
	while (1)
	{
		
		l = read(0, str, 100);
		str[l] = 0;
		if (strcmp(str, "tgetnum") == 0)
		{
			printf("HELLO\n");
       		test_tgetnum();
			continue;
		}
		else if (strcmp(str, "full_screen") == 0)
		{
       		test_clean_screen();
			continue;
		}
   		write(1, str, l);
	}
   	return (0);
}
