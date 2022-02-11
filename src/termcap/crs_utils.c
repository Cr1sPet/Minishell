#include "crs_termcap.h"

int         ft_putint(int c)
{
   return (write(STDOUT_FILENO, &c, 1));
}
