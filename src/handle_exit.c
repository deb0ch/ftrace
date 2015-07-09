/*
** handle_exit.c for strace in /home/ubuntu/rendu/AUSP_strace
**
** Made by chauvo_t
** Login   <chauvo_t@epitech.net>
**
** Started on  Fri May 16 19:22:06 2014 chauvo_t
** Last update Sun Jul  6 21:38:25 2014 chauvo_t
*/

#include "symbol_finder.h"
#include "strace.h"

extern t_graph		*g_graph;
extern t_signal		g_signals[];
extern t_libelf_data	g_elf_data;

void	handle_exit(int *status)
{
  if (WIFEXITED(*status) || WIFSIGNALED(*status))
    {
      g_graph->close_graph(g_graph);
      free_graph(g_graph);
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
  fprintf(stderr, "tracee was terminated by default action of signal %s\n",
	  g_signals[WSTOPSIG(*status)].name);
  g_graph->close_graph(g_graph);
  (void)elf_end(g_elf_data.elf);
  free_graph(g_graph);
  exit(EXIT_SUCCESS);
}
