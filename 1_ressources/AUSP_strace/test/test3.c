
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <err.h>

int	main(int ac, char **av)
{
  int	fd;

  write(1, "Hello, World !\n", strlen("Hello, World !\n"));
  fd = open("./notezfes", O_RDWR);
  warn("open error %d - ", fd);
  close(fd);
  return (EXIT_FAILURE);
}
