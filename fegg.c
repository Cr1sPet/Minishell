#include <unistd.h>
int main ()
{
    write(1, "world\n", 6);
    return (0);
}