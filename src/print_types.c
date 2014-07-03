/*
** print_types.c for strace in /home/ubuntu/rendu/AUSP_strace
**
** Made by chauvo_t
** Login   <chauvo_t@epitech.net>
**
** Started on  Thu May 15 00:55:59 2014 chauvo_t
** Last update Fri May 16 10:35:01 2014 Thomas de Beauchene
*/

#include "strace.h"

void	print_int(unsigned long long int register_value)
{
  (void)fprintf(stderr, "%d", (int)register_value);
}

void	print_long(unsigned long long int register_value)
{
  (void)fprintf(stderr, "%ld", (long)register_value);
}

void	print_uint(unsigned long long int register_value)
{
  (void)fprintf(stderr, "%u", (unsigned int)register_value);
}

void	print_ulong(unsigned long long int register_value)
{
  (void)fprintf(stderr, "%lu", (unsigned long)register_value);
}

void	print_pointer(unsigned long long int register_value)
{
  if (register_value == 0)
    fprintf(stderr, "NULL");
  else
    (void)fprintf(stderr, "%p", (void*)register_value);
}
