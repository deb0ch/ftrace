
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int	main(int ac, char **av)
{
  write(1, "Hello, World !\n", strlen("Hello, World !\n"));
  execvp("ls", av);
  return (0);
}
