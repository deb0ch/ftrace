
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(int ac, char **av)
{
  write(1, "Hello, World !\n", strlen("Hello, World !\n"));
  /* while (42) */
  /*   { */
  /*     ++ac; */
  /*   } */
  *((int*)NULL) = 0;
  /* abort(); */
  return (0);
}
