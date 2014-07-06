/*
** trace.c for strace in /home/ubuntu/rendu/AUSP_strace
**
** Made by chauvo_t
** Login   <chauvo_t@epitech.net>
**
** Started on  Wed May 14 21:58:47 2014 chauvo_t
** Last update Sun Jul  6 17:09:05 2014 bourge_i
*/

#include "symbol_finder.h"
#include "strace.h"
#include "graph.h"

pid_t		g_tracee_pid = -1;
extern t_graph	*g_graph;

extern t_prototype	g_syscalls[];

static int	step_instruction(pid_t pid, int *status)
{
  handle_exit(status);
  if (ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL) == -1)
    {
      warn("trace PTRACE_SINGLESTEP error");
      return (FAILURE);
    }
  if (waitpid(pid, status, 0) == -1)
    {
      warn("wait error");
      return (FAILURE);
    }
  return (SUCCESS);
}

static int		analyse_syscall(struct user_regs_struct *registers,
					pid_t pid, int *status)
{
  unsigned long long	syscall_number;

  syscall_number = registers->rax;
  if (syscall_number > MAX_SYSCALL
      || print_syscall(syscall_number, registers) == FAILURE)
    return (FAILURE);
  if (syscall_number != 60 && syscall_number != 231)
    {
      if (syscall_number == 1)
	fprintf(stderr, "\033[0m\n");
      if (step_instruction(pid, status) == FAILURE
	  || ptrace(PTRACE_GETREGS, pid, NULL, registers) == -1)
	return (FAILURE);
    }
  (void)print_return_value(syscall_number,
			   g_syscalls[syscall_number].ret_type, registers);
  if (syscall_number == 60 || syscall_number == 231)
    {
      g_graph->close_graph(g_graph);
      free_graph(g_graph);
      exit(EXIT_SUCCESS);
    }
  return (SUCCESS);
}

int                     on_function_call(struct user_regs_struct *registers,
                                         t_graph *graph, int *calling)
{
  static int            count = 0;
  char                  buff[4096];

  if (*calling == 1 && ((registers->rip & 0xFF0000000000) != 0x7F0000000000)
      && ((registers->rip & 0xFF000000000000) != 0x7E000000000000))
    {
      count++;
      printf("CALL count : %d\n", count);
      printf("CALL: 0x%llx\n", registers->rip);
      sprintf(buff, "0x%llx", registers->rip);
      graph->current = graph->add_node(graph, buff, graph->current, 0);
      *calling = 2;
      return (1);
    }
  return (0);
}

int                     on_function_ret(struct user_regs_struct *registers,
                                        t_graph *graph, int *calling)
{
  static int            count = 0;

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

static int		analyse_registers(struct user_regs_struct *registers,
					  pid_t pid, int *status, t_graph *graph)
{
  long			rip_pointed_data;
  unsigned long long	syscall_number;
  static int            calling = 0;

  on_function_call(registers, graph, &calling);
  on_function_ret(registers, graph, &calling);
  syscall_number = registers->rax;
  if ((rip_pointed_data = ptrace(PTRACE_PEEKDATA, pid,
				 registers->rip, NULL)) == -1)
    return (FAILURE);
  if ((rip_pointed_data & 0xFF) == 0xE8
      && (rip_pointed_data & 0xFF00000000) == 0xFF00000000)
    calling = 1;

  rip_pointed_data &= 0xffff;
  if (rip_pointed_data == SYSCALL_OPCODE)
    {
      if (analyse_syscall(registers, pid, status) == FAILURE)
	return (FAILURE);
      printf("RAX : %llu\n", syscall_number);
      if (syscall_number < MAX_SYSCALL)
        graph->add_node(graph, g_syscalls[syscall_number].name,
                        graph->current, 1);
    }
  return (SUCCESS);
}

int				trace_process(pid_t pid, t_graph *graph)
{
  struct user_regs_struct	registers;
  int				status;

  if (waitpid(pid, &status, 0) == -1)
    {
      warn("wait error");
      return (FAILURE);
    }
  while (42)
    {
      if (ptrace(PTRACE_GETREGS, pid, NULL, &registers) == -1)
	{
	  warn("ptrace PTRACE_GETREGS error");
	  return (FAILURE);
	}
      if (analyse_registers(&registers, pid, &status, graph) == FAILURE)
	return (FAILURE);
      if (step_instruction(pid, &status) == FAILURE)
	return (FAILURE);
    }
}
