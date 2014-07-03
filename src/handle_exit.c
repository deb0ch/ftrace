/*
** handle_exit.c for strace in /home/ubuntu/rendu/AUSP_strace
**
** Made by chauvo_t
** Login   <chauvo_t@epitech.net>
**
** Started on  Fri May 16 19:22:06 2014 chauvo_t
** Last update Sun May 18 20:13:27 2014 chauvo_t
*/

#include "strace.h"

static void	print_signal(int *status)
{
  if (WSTOPSIG(*status) == SIGSEGV)
    fprintf(stderr, "SIGSEGV\n");
  else if (WSTOPSIG(*status) == SIGTERM)
    fprintf(stderr, "SIGTERM\n");
  else if (WSTOPSIG(*status) == SIGINT)
    fprintf(stderr, "SIGINT\n");
  else if (WSTOPSIG(*status) == SIGKILL)
    fprintf(stderr, "SIGKILL\n");
  else if (WSTOPSIG(*status) == SIGPIPE)
    fprintf(stderr, "SIGPIPE\n");
  else if (WSTOPSIG(*status) == SIGQUIT)
    fprintf(stderr, "SIGQUIT\n");
  else if (WSTOPSIG(*status) == SIGFPE)
    fprintf(stderr, "SIGFPE\n");
  else if (WSTOPSIG(*status) == SIGBUS)
    fprintf(stderr, "SIGBUS\n");
  else if (WSTOPSIG(*status) == SIGSYS)
    fprintf(stderr, "SIGSYS\n");
  else if (WSTOPSIG(*status) == SIGSTKFLT)
    fprintf(stderr, "SIGSTKFLT\n");
  else if (WSTOPSIG(*status) == SIGABRT)
    fprintf(stderr, "SIGABRT\n");
  else if (WSTOPSIG(*status) == SIGUSR1
	   || WSTOPSIG(*status) == SIGUSR2)
    fprintf(stderr, "SIGUSR1 / SIGUSR2\n");
}

void	handle_exit(int *status)
{
  if (WIFEXITED(*status) || WIFSIGNALED(*status))
    {
      (void)printf(" was returned by tracee");
      (void)system("echo -n $?");
      (void)printf("\n");
      exit(EXIT_SUCCESS);
    }
  if (!(WIFSTOPPED(*status)
	&& (WSTOPSIG(*status) == SIGSEGV || WSTOPSIG(*status) == SIGTERM
	    || WSTOPSIG(*status) == SIGINT || WSTOPSIG(*status) == SIGKILL
	    || WSTOPSIG(*status) == SIGPIPE || WSTOPSIG(*status) == SIGQUIT
	    || WSTOPSIG(*status) == SIGFPE || WSTOPSIG(*status) == SIGBUS
	    || WSTOPSIG(*status) == SIGSYS || WSTOPSIG(*status) == SIGSTKFLT
	    || WSTOPSIG(*status) == SIGUSR1 || WSTOPSIG(*status) == SIGUSR2
	    || WSTOPSIG(*status) == SIGABRT)))
    return ;
  fprintf(stderr, "tracee was terminated by default action of signal ");
  print_signal(status);
  exit(EXIT_SUCCESS);
}
