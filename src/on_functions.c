/*
** on_functions.c for ftrace in /home/ubuntu/rendu/ftrace
**
** Made by chauvo_t
** Login   <chauvo_t@epitech.net>
**
** Started on  Sun Jul  6 22:10:11 2014 chauvo_t
** Last update Sun Jul  6 22:18:19 2014 chauvo_t
*/

#include "symbol_finder.h"
#include "strace.h"
#include "graph.h"

t_mapped_file		g_exec_file;

int			on_function_call(struct user_regs_struct *registers,
					 t_graph *graph, int *calling)
{
  static int		count = 0;
  char			buff[4096];

  if (*calling == 1 && ((registers->rip & 0xFF0000000000) != 0x7F0000000000)
      && ((registers->rip & 0xFF000000000000) != 0x7E000000000000))
    {
      count++;
      printf("CALL count : %d\n", count);
      printf("CALL: 0x%llx\n", registers->rip);
      sprintf(buff, "0x%llx", registers->rip);
      printf("***%s\n", symbol_finder_ptr(g_exec_file.content,
					  g_exec_file.size, registers->rip));
      graph->current = graph->add_node(graph, buff, graph->current, 0);
      *calling = 2;
      return (1);
    }
  return (0);
}

int			on_function_ret(struct user_regs_struct *registers,
                                        t_graph *graph, int *calling)
{
  static int		count = 0;

  if (*calling == 2 && (registers->rip & 0xFF) == 0XC3)
    {
      (void)graph;
      graph->pop(graph);
      count++;
      printf("RET\n");
      printf("RET count : %d\n", count);
      *calling = 0;
      return (1);
    }
  return (0);
}
