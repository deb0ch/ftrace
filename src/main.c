/*
** main.c for strace in /home/ubuntu/rendu/AUSP_strace
**
** Made by chauvo_t
** Login   <chauvo_t@epitech.net>
**
** Started on  Mon May 12 23:47:03 2014 chauvo_t
** Last update Sun Jul  6 16:58:01 2014 chauvo_t
*/

#include <stdio.h>
#include "strace.h"

extern pid_t	g_tracee_pid;
t_graph		*g_graph;

static int	trace_by_pid(pid_t pid, t_graph *g_graph)
{
  if (ptrace(PTRACE_ATTACH, pid, NULL, NULL) == -1)
    {
      warn("ptrace PTRACE_ATTACH error");
      return (FAILURE);
    }
  g_tracee_pid = pid;
  if (trace_process(pid, g_graph) == FAILURE)
    return (FAILURE);
  return (SUCCESS);
}

static int	trace_by_cmd(char **cmd, t_graph *g_graph)
{
  pid_t		child;

  if ((child = fork()) == -1)
    {
      warn("fork error");
      return (FAILURE);
    }
  if (child == 0)
    {
      if (launch_child(cmd) == FAILURE)
	exit(EXIT_FAILURE);
    }
  else
    {
      g_tracee_pid = child;
      if (trace_process(child, g_graph) == FAILURE)
      	return (FAILURE);
    }
  return (SUCCESS);
}

static void	sig_handler(int signum)
{
  (void)signum;
  if (ptrace(PTRACE_DETACH, g_tracee_pid, NULL, NULL) == -1)
    warn("ptrace PTRACE_DETACH error");
  else
    fprintf(stderr, "successfully detached from %d\n", g_tracee_pid);
  g_graph->close_graph(g_graph);
  free_graph(g_graph);
  exit(EXIT_SUCCESS);
}

static int	get_args(int ac, char **av, char ***cmd)
{
  if (ac < 2)
    return (FAILURE);
  if (!strcmp(av[1], "-p") && ac > 2)
    return (atoi(av[2]));
  *cmd = av + 1;
  return (SUCCESS);
}

int             main(int ac, char **av)
{
  char          **cmd;
  int   	ret_value;

  g_graph = graph_init();
  if ((ret_value = get_args(ac, av, &cmd)) == FAILURE)
    {
      fprintf(stderr, "USAGE:\n%s [command]\n%s [-p [pid]]\n", av[0], av[0]);
      return (EXIT_FAILURE);
    }
  if (signal(SIGINT, &sig_handler) == SIG_ERR
      || signal(SIGTERM, &sig_handler) == SIG_ERR)
    {
      warn("signal error");
      return (EXIT_FAILURE);
    }
  if (ret_value == SUCCESS)
    ret_value = trace_by_cmd(cmd, g_graph);
  else
    ret_value = trace_by_pid(ret_value, g_graph);
  g_graph->close_graph(g_graph);
  free_graph(g_graph);
  if (ret_value == FAILURE)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
