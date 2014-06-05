#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int     toto()
{
  printf("toto\n");
  return (0);
}

int     tutu()
{
  printf("tutu\n");
  return (0);
}

int     main(int argc, char *argv[])
{
  toto();
  tutu();
  exit(EXIT_SUCCESS);
}
