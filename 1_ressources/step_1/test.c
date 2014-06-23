/*
** test.c for tp_ftrace in /home/ubuntu/TP/unix_avance_ftrace/step_1
**
** Made by chauvo_t
** Login   <chauvo_t@epitech.net>
**
** Started on  Thu Jun  5 14:23:17 2014 chauvo_t
** Last update Thu Jun  5 14:25:15 2014 chauvo_t
*/

#include <stdio.h>
#include <stdlib.h>

void	toto()
{
  printf("Je suis dans toto()\n");
}

void	tutu()
{
  printf("Je suis dans tutu()\n");
}

int	main()
{
  toto();
  tutu();
  exit(EXIT_SUCCESS);
  return (0);
}
