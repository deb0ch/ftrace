/*
** print_syscall.c for strace in /home/ubuntu/rendu/AUSP_strace
**
** Made by chauvo_t
** Login   <chauvo_t@epitech.net>
**
** Started on  Wed May 14 21:59:47 2014 chauvo_t
** Last update Sun May 18 02:42:55 2014 chauvo_t
*/

#include "strace.h"

extern t_prototype	g_syscalls[];
extern t_types		g_types[];

unsigned long long int	arg_nb_to_register(int arg_nb,
					   struct user_regs_struct *registers)
{
  if (arg_nb == -1)
    return (registers->rax);
  if (arg_nb == 0)
    return (registers->rdi);
  if (arg_nb == 1)
    return (registers->rsi);
  if (arg_nb == 2)
    return (registers->rdx);
  if (arg_nb == 3)
    return (registers->rcx);
  if (arg_nb == 4)
    return (registers->r8);
  if (arg_nb == 5)
    return (registers->r9);
  return (0);
}

void	print_arg(char *type, int arg_nb, struct user_regs_struct *registers)
{
  int	i;

  i = 0;
  if (type[strlen(type) - 1] == '*'
      && strcmp(type, "char *") && strcmp(type, "char **"))
    print_pointer(arg_nb_to_register(arg_nb, registers));
  else
    {
      while (g_types[i + 1].name != NULL && strcmp(g_types[i].name, type))
	++i;
      g_types[i].print_fct(arg_nb_to_register(arg_nb, registers));
    }
}

void	print_return_value(int nb_syscall,
			   char *type, struct user_regs_struct *registers)
{
  (void)fprintf(stderr, "\033[0m) = \033[31m");
  if (nb_syscall != 60 && nb_syscall != 231)
    {
      if ((long long)registers->rax < 0)
	fprintf(stderr, "-1 (%s)", strerror(-registers->rax));
      else
	print_arg(type, -1, registers);
    }
  else
    fprintf(stderr, "?");
  (void)fprintf(stderr, "\033[0m\n");
}

void	print_args(int nb_syscall, struct user_regs_struct *registers)
{
  int	i;

  i = 0;
  while (i < g_syscalls[nb_syscall].nb_params - 1)
    {
      (void)fprintf(stderr, "\033[33m");
      print_arg(g_syscalls[nb_syscall].params[i], i, registers);
      (void)fprintf(stderr, "\033[0m, ");
      ++i;
    }
  (void)fprintf(stderr, "\033[33m");
  print_arg(g_syscalls[nb_syscall].params[i], i, registers);
}

int	print_syscall(int nb_syscall, struct user_regs_struct *registers)
{
  (void)registers;
  (void)fprintf(stderr, "\033[32m");
  (void)fprintf(stderr, "%s", g_syscalls[nb_syscall].name);
  (void)fprintf(stderr, "\033[0m(");
  print_args(nb_syscall, registers);
  return (SUCCESS);
}
